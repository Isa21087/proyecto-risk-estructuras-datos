#ifndef DADOS_H
#define DADOS_H
#include <vector>
using namespace std;

// Representa los dados utilizados durante un ataque.
class Dados {
private:
    // Guarda los resultados del ultimo lanzamiento.
    vector<int> resultados;

public:
    // Construye los dados y prepara la generacion de numeros aleatorios.
    Dados();

    // Lanza la cantidad de dados recibida y ordena sus resultados de mayor a menor.
    void lanzar(int cantidadDados);

    // Devuelve todos los resultados del ultimo lanzamiento.
    const vector<int>& obtenerResultados() const;

    // Devuelve la cantidad solicitada de resultados con mayor valor.
    vector<int> obtenerMayores(int cantidad) const;

    // Elimina los resultados del lanzamiento anterior.
    void limpiar();
};

#endif