#include <iostream>
#include "Comandos.h"
// el que lea esto le deseo el mejor dia :)
using namespace std;

int main() {

    string linea; //Guarda toda la linea de texto que escribe el usuario despues del $
    vector<string> palabras; //Guarda las palabras que devuelve la funcion separarEntrada

    //Controla si el programa debe seguir funcionando
    //empieza en true para que pueda entrar al while
    bool continuar = true;

    //Mientras continuar sea true el programa sigue mostrando el y permite que el usuario escriba mas comandos
    while (continuar) {

        cout << "$ ";

        //Isa: getline lee toda la linea escrita por el usuario
        //incluyendo los espacios que haya entre las palabras
        if (!getline(cin, linea)) {

            //Si getline no puede seguir leyendo significa que la entrada fue cerrada
            cout << endl;
            cout << "La entrada fue cerrada. Finalizando el programa." << endl;

            //Cambia continuar a false para que el while termine
            continuar = false;
        }
        else {

            //envia la linea escrita a separarEntrada y guarda en palabras el vector que devuelve la funcion
            palabras = separarEntrada(linea);

            //Si el tamaño del vector es cero significa que el usuario presiono Enter sin escribir ningun comando
            if (palabras.size() == 0) {
                cout << "(Entrada vacia) Debe escribir un comando." << endl;
                cout << "Escriba 'ayuda' para ver los comandos disponibles." << endl;
            }
            else {

                //La primera palabra siempre corresponde al nombre del comando
                string comando = palabras[0];

                //La cantidad de argumentos es la cantidad total de palabras menos uno porque la primera palabra es el comando y no cuenta como argumento
                int cantidadArgumentos = palabras.size() - 1;

                //Alejo e Isa: valida que el comando exista y que
                //la cantidad de argumentos sea correcta
                if (validarComando(comando, cantidadArgumentos)) {

                    //Saul: si el comando es ayuda se debe mostrar
                    //la ayuda general o la ayuda de un comando especifico
                    if (comando == "ayuda") {

                        //Si ayuda no recibe argumentos muestra todos los comandos
                        if (cantidadArgumentos == 0) {
                            mostrarAyudaGeneral();
                        }
                        else {

                            //Si ayuda recibe un argumento busca la ayuda
                            //del comando que esta guardado en palabras[1]
                            mostrarAyudaComando(palabras[1]);
                        }
                    }

                    //Si el comando es salir se termina la ejecucion del programa
                    else if (comando == "salir") {
                        cout << "Finalizando el juego. Hasta pronto." << endl;
                        continuar = false;
                    }
                    else {
                        cout << "(Comando correcto) El comando '"
                             << comando
                             << "' y sus parametros fueron validados correctamente."
                             << endl;
                        cout << "El procesamiento de la interfaz ha terminado." << endl;
                    }
                }
            }
        }
    }
    return 0;
}