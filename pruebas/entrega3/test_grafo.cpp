
#include <iostream>
#include <cassert>
#include "Grafo.h"

using namespace std;

int main() {
    Grafo grafo;

    // al crear el grafo todavia no debe tener territorios
    assert(grafo.cantidadTerritorios() == 0);

    // registramos tres territorios para comprobar que se guarden en orden
    assert(grafo.agregarTerritorio("1.1"));
    assert(grafo.agregarTerritorio("1.2"));
    assert(grafo.agregarTerritorio("1.3"));

    assert(grafo.cantidadTerritorios() == 3);

    // no se debe permitir un codigo repetido ni uno vacio
    assert(!grafo.agregarTerritorio("1.1"));
    assert(!grafo.agregarTerritorio(""));

    assert(grafo.cantidadTerritorios() == 3);

    // comprobamos que cada codigo tenga la posicion esperada
    assert(grafo.buscarTerritorio("1.1") == 0);
    assert(grafo.buscarTerritorio("1.2") == 1);
    assert(grafo.buscarTerritorio("1.3") == 2);
    assert(grafo.buscarTerritorio("9.9") == -1);

    // buscamos los codigos usando sus posiciones
    assert(grafo.obtenerTerritorio(0) == "1.1");
    assert(grafo.obtenerTerritorio(1) == "1.2");
    assert(grafo.obtenerTerritorio(2) == "1.3");

    // las posiciones inexistentes no deben producir accesos invalidos
    assert(grafo.obtenerTerritorio(-1) == "");
    assert(grafo.obtenerTerritorio(3) == "");

    // inicialmente no hay conexiones entre territorios diferentes
    assert(grafo.obtenerCosto(0, 1) == -1);
    assert(!grafo.sonAdyacentes(0, 1));

    // registramos la conexion de 1.1 hacia 1.2 con costo 4
    grafo.establecerCosto(0, 1, 4);

    assert(grafo.obtenerCosto(0, 1) == 4);
    assert(grafo.sonAdyacentes(0, 1));

    // el otro sentido todavia no debe estar conectado
    assert(grafo.obtenerCosto(1, 0) == -1);
    assert(!grafo.sonAdyacentes(1, 0));

    // registramos el otro sentido con un costo diferente
    grafo.establecerCosto(1, 0, 2);

    assert(grafo.obtenerCosto(1, 0) == 2);
    assert(grafo.obtenerCosto(0, 1) == 4);

    // una conexion de costo cero sigue siendo una conexion valida
    grafo.establecerCosto(1, 2, 0);

    assert(grafo.obtenerCosto(1, 2) == 0);
    assert(grafo.sonAdyacentes(1, 2));

    // un territorio no se considera vecino de si mismo
    assert(!grafo.sonAdyacentes(0, 0));
    assert(grafo.obtenerCosto(0, 0) == 0);

    // no se deben aceptar costos negativos ni posiciones invalidas
    grafo.establecerCosto(0, 1, -5);
    grafo.establecerCosto(-1, 1, 8);
    grafo.establecerCosto(0, 10, 8);
    grafo.establecerCosto(0, 0, 8);

    // las operaciones anteriores no deben cambiar la matriz
    assert(grafo.obtenerCosto(0, 1) == 4);
    assert(grafo.obtenerCosto(0, 0) == 0);
    assert(grafo.obtenerCosto(-1, 1) == -1);
    assert(grafo.obtenerCosto(0, 10) == -1);

    // probamos tambien que la matriz pueda crecer hasta 42 territorios
    Grafo grafoCompleto;

    for (int i = 0; i < 42; i++) {
        string codigo = "T" + to_string(i);
        assert(grafoCompleto.agregarTerritorio(codigo));
    }

    assert(grafoCompleto.cantidadTerritorios() == 42);

    // comprobamos una conexion entre el primero y el ultimo
    grafoCompleto.establecerCosto(0, 41, 7);

    assert(grafoCompleto.obtenerCosto(0, 41) == 7);
    assert(grafoCompleto.sonAdyacentes(0, 41));

    cout << "Todas las pruebas del TAD Grafo pasaron correctamente" << endl;

    return 0;
}
