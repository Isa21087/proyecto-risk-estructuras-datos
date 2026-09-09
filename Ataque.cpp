#include "Ataque.h"
#include "Jugador.h" // Asumiendo que definirán métodos públicos
#include "Tablero.h"
#include "Territorio.h"
#include <iostream>
#include <algorithm>

using namespace std;

Ataque::Ataque() {
    // Los dados se inicializan automáticamente por su constructor por defecto
}

bool Ataque::configuracionValida(string codigoOrigen, string codigoDestino, string colorAtacante, const Tablero& tablero) const {
    // Obtenemos los territorios (asumiendo que Tablero tiene un método para esto)
    const Territorio* origen = tablero.buscarTerritorio(codigoOrigen);
    const Territorio* destino = tablero.buscarTerritorio(codigoDestino);

    if (origen == nullptr || destino == nullptr) return false;

    // Verificar que el origen pertenezca al atacante
    if (origen->obtenerColorPropietario() != colorAtacante) return false;

    // Verificar que el destino sea enemigo
    if (destino->obtenerColorPropietario() == colorAtacante) return false;

    // Verificar que sean vecinos utilizando la función pública de Tablero[4]
    if (!tablero.sonVecinos(codigoOrigen, codigoDestino)) return false;

    // El origen debe tener más de 1 unidad para poder atacar
    if (origen->obtenerUnidades() <= 1) return false;

    return true;
}

ResultadoAtaque Ataque::ejecutar(Jugador& jugadorAtacante, Tablero& tablero) {
    ResultadoAtaque resultado = {false, false};
    string codigoOrigen, codigoDestino;

    // 1. Solicitar territorio de origen y destino[4]
    cout << "Ingrese el codigo del territorio desde el cual desea atacar: ";
    cin >> codigoOrigen;
    cout << "Ingrese el codigo del territorio que desea atacar: ";
    cin >> codigoDestino;

    // 2. Validaciones delegadas[4]
    if (!configuracionValida(codigoOrigen, codigoDestino, jugadorAtacante.getColor(), tablero)) {
        cout << "Configuracion de ataque invalida. Verifique propietarios, vecindad y cantidad de tropas.\n";
        return resultado; 
    }

    resultado.ataqueRealizado = true;
    Territorio* origen = tablero.buscarTerritorio(codigoOrigen);
    Territorio* destino = tablero.buscarTerritorio(codigoDestino);
    bool continuar = true;

    // 3. Ciclo de ataque, repetir mientras corresponda[4]
    while (continuar && origen->obtenerUnidades() > 1 && destino->obtenerUnidades() > 0) {
        
        // Ejecutar lanzamientos[4]
        // Se determina cantidad de dados (Atacante máximo 3, Defensor máximo 2)
        int cantDadosAtacante = min(3, origen->obtenerUnidades() - 1);
        int cantDadosDefensor = min(2, destino->obtenerUnidades());

        dadosAtacante.lanzar(cantDadosAtacante);
        dadosDefensor.lanzar(cantDadosDefensor);

        // Seleccionar los dos valores mayores del atacante[4]
        vector<int> resAtacante = dadosAtacante.obtenerMayores(2);
        vector<int> resDefensor = dadosDefensor.obtenerMayores(2);

        // Mostrar sus resultados[4]
        cout << "\n--- Resultados de los dados ---" << endl;
        cout << "Atacante: ";
        for (int val : resAtacante) cout << val << " ";
        cout << "\nDefensor: ";
        for (int val : resDefensor) cout << val << " ";
        cout << "\n";

        // Comparar los dados emparejados y aplicar pérdidas[1, 4]
        int perdidasAtacante = 0;
        int perdidasDefensor = 0;
        int paresAComparar = min(resAtacante.size(), resDefensor.size());

        for (int i = 0; i < paresAComparar; ++i) {
            // Si hay empate, el defensor es quien gana
            if (resAtacante[i] > resDefensor[i]) {
                perdidasDefensor++;
            } else {
                perdidasAtacante++;
            }
        }

        cout << "Perdidas -> Atacante: " << perdidasAtacante << " | Defensor: " << perdidasDefensor << "\n";
        
        origen->retirarUnidades(perdidasAtacante, 1);
        destino->retirarUnidades(perdidasDefensor, 0);

// Detectar la conquista
        if (destino->obtenerUnidades() == 0) {
            cout << "\n¡Has conquistado el territorio " << codigoDestino << "!\n";
            resultado.conquistoTerritorio = true;
            
            // 1. Preguntar por las tropas a trasladar ANTES de usarlas
            int tropasAMover = -1;
            int maxMover = origen->obtenerUnidades() - 1;
            
            while (tropasAMover < 0 || tropasAMover > maxMover) {
                cout << "Cuantas tropas deseas trasladar? (0 a " << maxMover << "): ";
                cin >> tropasAMover;
                
                if(tropasAMover < 0 || tropasAMover > maxMover){
                     cout << "Cantidad invalida. Intente de nuevo.\n";
                }
            }
            
            // 2. Retirar las unidades del origen
            origen->retirarUnidades(tropasAMover, 1);
            
            // 3. Cambiar propietario y asignar las tropas trasladadas usando el método del Tablero
            tablero.cambiarPropietario(codigoDestino, jugadorAtacante.getColor(), tropasAMover);

            // 4. Comprobar si el jugador llegó a controlar los 42 territorios
            if (tablero.contarTerritorios(jugadorAtacante.getColor()) == 42) {
                cout << "\n¡" << jugadorAtacante.getNombre() << " ha conquistado los 42 territorios y gana el juego!\n";
            }
            break; // El ataque a este territorio termina porque ya se conquistó
        }

        // Preguntar si el atacante desea continuar
        if (origen->obtenerUnidades() > 1) {
            char respuesta;
            cout << "Deseas continuar atacando este territorio? (s/n): ";
            cin >> respuesta;
            continuar = (respuesta == 's' || respuesta == 'S');
        } else {
            cout << "Ya no tienes tropas suficientes para continuar el ataque desde este territorio.\n";
            continuar = false;
        }
    }

    // Comentado temporalmente para pruebas hasta que tus compañeros creen el método en Jugador.h
    // jugadorAtacante.setHaAtacado(true);

    return resultado;
}