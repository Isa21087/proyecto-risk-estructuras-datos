#ifndef DADOS_H
#define DADOS_H
#include <vector>
using namespace std;
class Dados {
private:
    vector<int> resultados;
public:
    Dados();
    void lanzar(int cantidadDados);
    const vector<int>& obtenerResultados() const;
    vector<int> obtenerMayores(int cantidad) const;
    void limpiar();
};
#endif