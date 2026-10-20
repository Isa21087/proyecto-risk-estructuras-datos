#include "Huffman.h"
#include "MonticuloHuffman.h"
#include <fstream>

using namespace std;


// construye el arbol de Huffman a partir de las frecuencias
// cada vez se unen los dos subarboles con menor frecuencia hasta que solo quede uno
bool construirArbolHuffman(
    const unsigned long long frecuencias[256],
    ArbolBinario<DatoHuffman>& arbol
) {

    // no podemos asignar una raiz nueva si el arbol ya tiene una
    if(!arbol.esVacio()){
        return false;
    }

    MonticuloHuffman monticulo;
    unsigned long long orden = 0;

    // recorremos los posibles caracteres en orden ascendente
    // asi las hojas siempre entran al monticulo en el mismo orden
    for(int i = 0; i < 256; i++){

        // si un caracter no aparece en el mensaje no necesita una hoja
        if(frecuencias[i] == 0){
            continue;
        }

        DatoHuffman dato;
        dato.simbolo = static_cast<unsigned char>(i);
        dato.frecuencia = frecuencias[i];

        NodoBinario<DatoHuffman>* hoja =
            new NodoBinario<DatoHuffman>(dato);

        monticulo.insertar(hoja, orden);
        orden++;
    }

    // si no habia ningun caracter no hay arbol que construir
    if(monticulo.esVacio()){
        return false;
    }

    // sacamos el primer minimo y mientras queden otros
    // lo vamos uniendo con el siguiente minimo disponible
    NodoBinario<DatoHuffman>* izquierdo =
        monticulo.extraerMinimo();

    while(!monticulo.esVacio()){

        NodoBinario<DatoHuffman>* derecho =
            monticulo.extraerMinimo();

        DatoHuffman datoPadre;

        // los nodos internos no representan un caracter
        // solamente guardan la suma de las frecuencias de sus dos hijos
        datoPadre.simbolo = 0;
        datoPadre.frecuencia =
            izquierdo->obtenerDato().frecuencia +
            derecho->obtenerDato().frecuencia;

        NodoBinario<DatoHuffman>* padre =
            new NodoBinario<DatoHuffman>(datoPadre);

        // el primer minimo va a la izquierda y el segundo a la derecha
        // esto tambien define despues los caminos de 0 y 1
        padre->fijarHijoIzq(izquierdo);
        padre->fijarHijoDer(derecho);

        // el nuevo padre representa todo el subarbol que acabamos de unir
        // por eso vuelve al monticulo y participa en las siguientes uniones
        monticulo.insertar(padre, orden);
        orden++;

        // volvemos a sacar el menor de todos los que quedan
        // puede ser el padre nuevo o cualquier otro subarbol
        izquierdo = monticulo.extraerMinimo();
    }

    // cuando no quedan mas elementos por unir esta es la raiz final
    // a partir de aqui ArbolBinario se encarga de liberar todos los nodos
    return arbol.fijarRaiz(izquierdo);
}


// esta funcion va bajando por el arbol mientras guarda el camino recorrido
// cuando encuentra una hoja ya tiene el codigo completo de ese caracter
static void recorrerCodigosHuffman(
    NodoBinario<DatoHuffman>* nodo,
    string camino,
    string codigos[256]
) {

    if(nodo == NULL){
        return;
    }

    if(nodo->esHoja()){

        DatoHuffman dato = nodo->obtenerDato();

        // si el mensaje solo tenia un caracter el arbol tiene una sola hoja
        // como no hubo recorrido le damos el codigo 0 para que no quede vacio
        if(camino.empty()){
            camino = "0";
        }

        // usamos el valor numerico del caracter como posicion del arreglo
        // asi despues podemos buscar su codigo sin recorrer otra estructura
        codigos[dato.simbolo] = camino;

        return;
    }

    // al bajar por el hijo izquierdo agregamos un 0 al camino
    recorrerCodigosHuffman(
        nodo->obtenerHijoIzq(),
        camino + "0",
        codigos
    );

    // al bajar por el hijo derecho agregamos un 1 al camino
    recorrerCodigosHuffman(
        nodo->obtenerHijoDer(),
        camino + "1",
        codigos
    );
}


// genera los codigos de todos los caracteres que aparecen en el arbol
bool generarCodigosHuffman(
    ArbolBinario<DatoHuffman>& arbol,
    string codigos[256]
) {

    // limpiamos los codigos para no conservar valores de otro mensaje
    // las posiciones de caracteres que no aparezcan quedaran vacias
    for(int i = 0; i < 256; i++){
        codigos[i] = "";
    }

    if(arbol.esVacio()){
        return false;
    }

    // empezamos desde la raiz con un camino vacio
    // la funcion recursiva ira agregando los ceros y unos
    recorrerCodigosHuffman(
        arbol.obtenerRaiz(),
        "",
        codigos
    );

    return true;
}


// convierte un mensaje en un archivo binario usando los codigos de Huffman
bool comprimirHuffman(
    const string& mensaje,
    const string& nombreArchivo
) {

    // no construimos un arbol si el mensaje no tiene caracteres
    if(mensaje.empty()){
        return false;
    }

    // comprobamos los tamaños antes de escribir el encabezado
    // estos tipos los escogimos nosotros para cumplir los bytes del enunciado
    if(sizeof(unsigned short) != 2 ||
       sizeof(unsigned char) != 1 ||
       sizeof(unsigned long long) != 8){
        return false;
    }

    unsigned long long frecuencias[256] = {};

    // contamos cada byte del mensaje incluyendo espacios y saltos de linea
    // unsigned char permite usar su valor como posicion entre 0 y 255
    for(unsigned long long i = 0; i < mensaje.size(); i++){

        unsigned char simbolo =
            static_cast<unsigned char>(mensaje[i]);

        frecuencias[simbolo]++;
    }

    ArbolBinario<DatoHuffman> arbol;

    if(!construirArbolHuffman(frecuencias, arbol)){
        return false;
    }

    string codigos[256];

    if(!generarCodigosHuffman(arbol, codigos)){
        return false;
    }

    unsigned short cantidadSimbolos = 0;

    // contamos cuantos caracteres distintos aparecieron
    // solo ellos tendran una pareja de simbolo y frecuencia en el archivo
    for(int i = 0; i < 256; i++){
        if(frecuencias[i] > 0){
            cantidadSimbolos++;
        }
    }

    unsigned long long totalCaracteres =
        static_cast<unsigned long long>(mensaje.size());

    ofstream archivo(
        nombreArchivo.c_str(),
        ios::binary
    );

    if(!archivo.is_open()){
        return false;
    }

    // escribimos n ocupando exactamente dos bytes
    // los enteros se guardan en representacion nativa de esta maquina
    // el enunciado exige los tamaños pero no especifica el orden de sus bytes
    archivo.write(
        (const char*)&cantidadSimbolos,
        sizeof(cantidadSimbolos)
    );

    // guardamos las parejas ci y fi en orden ascendente del valor del caracter
    // ci ocupa un byte y fi ocupa ocho bytes
    for(int i = 0; i < 256; i++){

        if(frecuencias[i] == 0){
            continue;
        }

        unsigned char simbolo = static_cast<unsigned char>(i);

        archivo.write(
            (const char*)&simbolo,
            sizeof(simbolo)
        );

        archivo.write(
            (const char*)&frecuencias[i],
            sizeof(frecuencias[i])
        );
    }

    // w es la cantidad de caracteres que tenia el mensaje original
    // despues nos servira para saber cuando detener la descompresion
    archivo.write(
        (const char*)&totalCaracteres,
        sizeof(totalCaracteres)
    );

    unsigned char byteActual = 0;
    int bitsGuardados = 0;

    // recorremos el mensaje y buscamos el codigo de cada caracter
    // en vez de escribir el texto "0" y "1" vamos formando bytes de ocho bits
    for(unsigned long long i = 0; i < mensaje.size(); i++){

        unsigned char simbolo =
            static_cast<unsigned char>(mensaje[i]);

        string codigo = codigos[simbolo];

        for(unsigned long long j = 0; j < codigo.size(); j++){

            // multiplicar por dos desplaza los bits hacia la izquierda
            // asi el primer bit del codigo queda hacia el lado mas significativo
            byteActual = static_cast<unsigned char>(byteActual * 2);

            if(codigo[j] == '1'){
                byteActual = static_cast<unsigned char>(byteActual + 1);
            }

            bitsGuardados++;

            // cuando juntamos ocho bits ya tenemos un byte completo
            // lo escribimos y empezamos a formar el siguiente
            if(bitsGuardados == 8){

                archivo.put(static_cast<char>(byteActual));

                byteActual = 0;
                bitsGuardados = 0;
            }
        }
    }

    // si el ultimo byte no alcanzo los ocho bits
    // agregamos ceros a la derecha hasta completarlo
    if(bitsGuardados > 0){

        while(bitsGuardados < 8){
            byteActual = static_cast<unsigned char>(byteActual * 2);
            bitsGuardados++;
        }

        archivo.put(static_cast<char>(byteActual));
    }

    // close tambien permite detectar si hubo un problema al terminar de escribir
    archivo.close();

    return archivo.good();
}


// lee el archivo comprimido y recupera el mensaje original
bool descomprimirHuffman(
    const string& nombreArchivo,
    string& mensaje
) {

    // usamos los mismos tamaños con los que escribimos el encabezado
    if(sizeof(unsigned short) != 2 ||
       sizeof(unsigned char) != 1 ||
       sizeof(unsigned long long) != 8){
        return false;
    }

    ifstream archivo(
        nombreArchivo.c_str(),
        ios::binary
    );

    if(!archivo.is_open()){
        return false;
    }

    unsigned short cantidadSimbolos = 0;

    // primero leemos n que ocupa dos bytes
    archivo.read(
        (char*)&cantidadSimbolos,
        sizeof(cantidadSimbolos)
    );

    // no puede haber mas de 256 simbolos distintos
    // tampoco aceptamos un encabezado incompleto o sin simbolos
    if(!archivo || cantidadSimbolos == 0 || cantidadSimbolos > 256){
        return false;
    }

    unsigned long long frecuencias[256] = {};
    int simboloAnterior = -1;

    // leemos las parejas de simbolo y frecuencia que siguen despues de n
    // deben estar ordenadas igual que cuando comprimimos el mensaje
    for(int i = 0; i < cantidadSimbolos; i++){

        unsigned char simbolo = 0;
        unsigned long long frecuencia = 0;

        archivo.read(
            (char*)&simbolo,
            sizeof(simbolo)
        );

        archivo.read(
            (char*)&frecuencia,
            sizeof(frecuencia)
        );

        // cada frecuencia debe ser positiva
        // tambien evitamos simbolos repetidos o fuera de orden
        if(!archivo ||
           frecuencia == 0 ||
           static_cast<int>(simbolo) <= simboloAnterior){
            return false;
        }

        frecuencias[simbolo] = frecuencia;
        simboloAnterior = simbolo;
    }

    unsigned long long totalCaracteres = 0;

    // despues de las frecuencias viene w
    // este valor indica cuantos caracteres debemos recuperar
    archivo.read(
        (char*)&totalCaracteres,
        sizeof(totalCaracteres)
    );

    if(!archivo || totalCaracteres == 0){
        return false;
    }

    unsigned long long sumaFrecuencias = 0;

    // la suma de las frecuencias debe coincidir con el tamaño original
    // tambien comprobamos que ninguna suma sobrepase ese tamaño
    for(int i = 0; i < 256; i++){

        if(frecuencias[i] > totalCaracteres - sumaFrecuencias){
            return false;
        }

        sumaFrecuencias += frecuencias[i];
    }

    if(sumaFrecuencias != totalCaracteres){
        return false;
    }

    ArbolBinario<DatoHuffman> arbol;

    // reconstruimos el mismo arbol a partir de las frecuencias guardadas
    // usamos el mismo desempate que en la compresion
    if(!construirArbolHuffman(frecuencias, arbol)){
        return false;
    }

    NodoBinario<DatoHuffman>* raiz = arbol.obtenerRaiz();
    NodoBinario<DatoHuffman>* actual = raiz;

    string recuperado;

    // guardamos cuantas veces falta recuperar cada simbolo
    // esto ayuda a detectar archivos con datos incorrectos
    unsigned long long restantes[256];

    for(int i = 0; i < 256; i++){
        restantes[i] = frecuencias[i];
    }

    unsigned char byteActual = 0;
    int bitsPendientes = 0;
    unsigned long long recuperados = 0;

    // leemos los bits hasta recuperar exactamente w caracteres
    while(recuperados < totalCaracteres){

        // cuando consumimos ocho bits necesitamos leer otro byte
        if(bitsPendientes == 0){

            char byteLeido = 0;

            // si el archivo termina antes de recuperar el mensaje esta incompleto
            if(!archivo.get(byteLeido)){
                return false;
            }

            byteActual = static_cast<unsigned char>(byteLeido);
            bitsPendientes = 8;
        }

        // el bit mas significativo es el primero que escribimos
        // si vale 1 avanzamos a la derecha y si vale 0 a la izquierda
        bool bitUno = byteActual >= 128;

        // movemos los bits para consultar el siguiente
        byteActual = static_cast<unsigned char>(byteActual * 2);
        bitsPendientes--;

        unsigned char simbolo = 0;

        if(raiz->esHoja()){

            // cuando solo habia un simbolo le asignamos el codigo 0
            if(bitUno){
                return false;
            }

            simbolo = raiz->obtenerDato().simbolo;
        }
        else{

            if(bitUno){
                actual = actual->obtenerHijoDer();
            }
            else{
                actual = actual->obtenerHijoIzq();
            }

            // si el camino no existe el archivo no corresponde al arbol
            if(actual == NULL){
                return false;
            }

            // mientras no lleguemos a una hoja seguimos leyendo bits
            if(!actual->esHoja()){
                continue;
            }

            // llegar a una hoja significa que recuperamos un caracter
            simbolo = actual->obtenerDato().simbolo;

            // volvemos a la raiz para recuperar el siguiente caracter
            actual = raiz;
        }

        // no podemos recuperar un simbolo mas veces de las que dice el encabezado
        if(restantes[simbolo] == 0){
            return false;
        }

        restantes[simbolo]--;

        recuperado.push_back(static_cast<char>(simbolo));
        recuperados++;
    }

    // los bits que sobran en el ultimo byte deben ser ceros de relleno
    if(bitsPendientes > 0 && byteActual != 0){
        return false;
    }

    // despues de recuperar el mensaje no deben quedar bytes adicionales
    char sobrante = 0;

    if(archivo.get(sobrante)){
        return false;
    }

    if(!archivo.eof()){
        return false;
    }

    // solo cambiamos el mensaje recibido cuando toda la lectura fue correcta
    // asi no dejamos un mensaje recuperado a medias si hubo un error
    mensaje = recuperado;

    return true;
}