#include <iostream>
#include "Comandos.h"
#include "Partida.h"
#include <cstdlib>
#include <ctime>
// *el que lea esto le deseo el mejor dia :)*
using namespace std;



int main() {

    // Inicializa una sola vez la aleatoriedad de dados y cartas.
    srand(time(NULL));

    // *Guarda la partida durante la ejecucion del programa.*
    Partida partida;

    string linea; //*Guarda toda la linea de texto que escribe el usuario despues del $*

    vector<string> palabras; //*Guarda las palabras que devuelve la funcion separarEntrada*

    //*Controla si el programa debe seguir funcionando*
    //*empieza en true para que pueda entrar al while*
    bool continuar = true;

    //*Mientras continuar sea true el programa sigue mostrando el y permite que el usuario escriba mas comandos*
    while (continuar) {
        cout << "$ ";

        //*Isa: getline lee toda la linea escrita por el usuario*
        //*incluyendo los espacios que haya entre las palabras*
        if (!getline(cin, linea)) {

            //*Si getline no puede seguir leyendo significa que la entrada fue cerrada*
            cout << endl;
            cout << "La entrada fue cerrada. Finalizando el programa." << endl;

            //*Cambia continuar a false para que el while termine*
            continuar = false;

        }

        else {

            //*envia la linea escrita a separarEntrada y guarda en palabras el vector que devuelve la funcion*
            palabras = separarEntrada(linea);

            //*Si el tamaño del vector es cero significa que el usuario presiono Enter sin escribir ningun comando*
            if (palabras.size() == 0) {

                cout << "(Entrada vacia) Debe escribir un comando." << endl;
                cout << "Escriba 'ayuda' para ver los comandos disponibles." << endl;

            }

            else {

                //*La primera palabra siempre corresponde al nombre del comando*
                string comando = palabras[0];

                //*La cantidad de argumentos es la cantidad total de palabras menos uno porque la primera palabra es el comando y no cuenta como argumento*
                int cantidadArgumentos = palabras.size() - 1;

                //*Alejo e Isa: valida que el comando exista y que*
                //*la cantidad de argumentos sea correcta*
                if (validarComando(comando, cantidadArgumentos)) {

                    //*Saul: si el comando es ayuda se debe mostrar*
                    //*la ayuda general o la ayuda de un comando especifico*
                    if (comando == "ayuda") {

                        //*Si ayuda no recibe argumentos muestra todos los comandos*
                        if (cantidadArgumentos == 0) {

                            mostrarAyudaGeneral();

                        }

                        else {

                            //*Si ayuda recibe un argumento busca la ayuda*
                            //*del comando que esta guardado en palabras[1]*
                            mostrarAyudaComando(palabras[1]);

                        }

                    }

                    //*Si el comando es salir se termina la ejecucion del programa*
                    else if (comando == "salir") {

                        cout << "Finalizando el juego. Hasta pronto." << endl;

                        continuar = false;

                    }

                    else if (comando == "inicializar") {

                        // *Carga la partida desde el archivo indicado.*
                        EstadoComando resultado = partida.inicializar(palabras[1]);

                        if (resultado == COMANDO_CORRECTO) {

                            cout << "(Comando correcto) El juego se ha inicializado correctamente." << endl;

                        }

                        else if (resultado == ARCHIVO_VACIO) {

                            cout << "(Archivo vacío) " << palabras[1] << " no contiene información." << endl;

                        }

                        else if (resultado == ARCHIVO_ERRONEO) {

                            cout << "(Archivo erróneo) " << palabras[1] << " no se encuentra o no puede leerse." << endl;

                        }

                        else if (resultado == ARCHIVO_SIN_FORMATO) {

                            cout << "(Archivo sin formato) " << palabras[1] << " no contiene información en el formato esperado." << endl;

                        }

                        else if (resultado == JUEGO_EN_CURSO) {

                            cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;

                        }

                    }
                    else if(comando == "estado_juego"){

                        EstadoComando resultado = partida.validarEstadoJuego();

                        if(resultado == JUEGO_NO_INICIALIZADO){
                            cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
                        }
                        else if(resultado == JUEGO_TERMINADO){
                            cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
                        }
                        else{
                            partida.mostrarEstadoJuego();
                        }

                    }
                                        else if(comando == "obtener_unidades"){

                        EstadoComando resultado = partida.obtenerUnidades(palabras[1]);

                        if(resultado == JUEGO_NO_INICIALIZADO){
                            cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
                        }
                        else if(resultado == JUEGO_TERMINADO){
                            cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
                        }
                        else if(resultado == JUGADOR_NO_VALIDO){
                            cout << "(Jugador no válido) El jugador " << palabras[1]
                                 << " no forma parte de esta partida." << endl;
                        }
                        else if(resultado == JUGADOR_FUERA_DE_TURNO){
                            cout << "(Jugador fuera de turno) No es el turno del jugador "
                                 << palabras[1] << "." << endl;
                        }
                        else if(resultado == JUGADOR_YA_OBTUVO_UNIDADES){
                            cout << "El jugador ya obtuvo y ubico las unidades de este turno." << endl;
                        }
                        else if(resultado == ENTRADA_CERRADA){
                            cout << "La entrada fue cerrada. No se guardo el reparto de unidades." << endl;
                            continuar = false;
                        }
                        else if(resultado == COMANDO_CORRECTO){
                            cout << "(Comando correcto) El jugador " << palabras[1]
                                 << " ha terminado de reclamar y ubicar sus unidades." << endl;
                        }

                    }
                    else if(comando == "atacar"){

                        EstadoComando resultado = partida.atacar(palabras[1]);

                        if(resultado == JUEGO_NO_INICIALIZADO){
                            cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
                        }
                        else if(resultado == JUEGO_TERMINADO){
                            cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
                        }
                        else if(resultado == JUGADOR_NO_VALIDO){
                            cout << "(Jugador no válido) El jugador " << palabras[1]
                                 << " no forma parte de esta partida." << endl;
                        }
                        else if(resultado == JUGADOR_FUERA_DE_TURNO){
                            cout << "(Jugador fuera de turno) No es el turno del jugador "
                                 << palabras[1] << "." << endl;
                        }
                        else if(resultado == JUGADOR_NO_HA_UBICADO_UNIDADES){
                            cout << "(Jugador no ha ubicado unidades) El jugador "
                                 << palabras[1]
                                 << " no ha ejecutado el comando obtener_unidades." << endl;
                        }
                        else if(resultado == JUGADOR_YA_TERMINO_ATAQUE){
                            cout << "El jugador ya termino de atacar. Ahora debe fortificar." << endl;
                        }
                        else if(resultado == ENTRADA_CERRADA){
                            cout << "La entrada fue cerrada. Finalizando el programa." << endl;
                            continuar = false;
                        }
                        else if(resultado == COMANDO_CORRECTO){
                            cout << "(Comando correcto) El jugador " << palabras[1]
                                 << " ha terminado de atacar." << endl;
                        }

                    }
                                        else if(comando == "fortificar"){

                        EstadoComando resultado = partida.fortificar(palabras[1]);

                        if(resultado == JUEGO_NO_INICIALIZADO){
                            cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
                        }
                        else if(resultado == JUEGO_TERMINADO){
                            cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
                        }
                        else if(resultado == JUGADOR_NO_VALIDO){
                            cout << "(Jugador no válido) El jugador " << palabras[1]
                                 << " no forma parte de esta partida." << endl;
                        }
                        else if(resultado == JUGADOR_FUERA_DE_TURNO){
                            cout << "(Jugador fuera de turno) No es el turno del jugador "
                                 << palabras[1] << "." << endl;
                        }
                        else if(resultado == JUGADOR_NO_HA_ATACADO){
                            cout << "(Jugador no ha atacado) El jugador " << palabras[1]
                                 << " no ha ejecutado el comando atacar." << endl;
                        }
                        else if(resultado == ENTRADA_CERRADA){
                            cout << "La entrada fue cerrada. Finalizando el programa." << endl;
                            continuar = false;
                        }
                        else if(resultado == COMANDO_CORRECTO){
                            cout << "(Comando correcto) El jugador " << palabras[1]
                                 << " ha terminado de fortificar su posición." << endl;
                        }

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