#include <iostream>
#include "Comandos.h"
#include "Tablero.h" //
#include "Ataque.h"  //[cite: 5]
#include "Jugador.h" // Asumimos que tus compañeros ya definieron su estructura básica

using namespace std;

int main() {
    // ========================================================
    // 1. SETUP DE PRUEBAS PARA EL COMANDO ATACAR
    // ========================================================
    Tablero tablero;
    tablero.inicializarEstructura(); // Carga todos los continentes y territorios[cite: 9]
    
    // Configuramos territorios simulados usando las funciones de Tablero[cite: 9]
    // 2.2 Brasil será el origen (Rojo, 5 tropas). 2.1 Argentina será el destino (Verde, 1 tropa).
    tablero.configurarTerritorio("2.2", "Rojo", 5); 
    tablero.configurarTerritorio("2.1", "Verde", 1); 

    // Creamos el jugador de prueba y la instancia del sistema de ataque
    Jugador jugadorPrueba("Alejo", "Rojo"); 
    Ataque sistemaAtaque;
    // ========================================================


    string linea; 
    vector<string> palabras; 
    bool continuar = true;

    while (continuar) {
        cout << "$ ";

        if (!getline(cin, linea)) {
            cout << endl;
            cout << "La entrada fue cerrada. Finalizando el programa." << endl;
            continuar = false;
        }
        else {
            palabras = separarEntrada(linea);

            if (palabras.size() == 0) {
                cout << "(Entrada vacia) Debe escribir un comando." << endl;
                cout << "Escriba 'ayuda' para ver los comandos disponibles." << endl;
            }
            else {
                string comando = palabras[0];
                int cantidadArgumentos = palabras.size() - 1;

                if (validarComando(comando, cantidadArgumentos)) {

                    if (comando == "ayuda") {
                        if (cantidadArgumentos == 0) {
                            mostrarAyudaGeneral();
                        }
                        else {
                            mostrarAyudaComando(palabras[1]);
                        }
                    }
                    else if (comando == "salir") {
                        cout << "Finalizando el juego. Hasta pronto." << endl;
                        continuar = false;
                    }
                    // ========================================================
                    // 2. INTERCEPCIÓN DEL COMANDO ATACAR
                    // ========================================================
                    else if (comando == "atacar") {
                        string nombreAtacante = palabras[1];
                        
                        // Validaciones exigidas en tu responsabilidad
                        if (nombreAtacante != jugadorPrueba.obtenerNombre()) {
                             cout << "(Jugador no valido) El jugador " << nombreAtacante << " no forma parte de esta partida." << endl;
                        } 
                        else {
                             // Ejecutamos la lógica de batalla[cite: 5]
                             ResultadoAtaque res = sistemaAtaque.ejecutar(jugadorPrueba, tablero);
                             
                             // Si el ataque se realizó exitosamente (no rebotó en la validación inicial)
                             if (res.ataqueRealizado) {
                                 cout << "(Comando correcto) El jugador " << nombreAtacante << " ha terminado de atacar." << endl;
                             }
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