#include "Dados.h"
// Para usar rand() se utiliza para generar números aleatorios y srand() se utiliza para inicializar el valor semilla del generador de números aleatorios. 
#include <cstdlib>
// Para usar la hora del sistema como semilla. Convierte un valor time_t en una representación local de fecha y hora
#include <ctime>
using namespace std;

// Constructor de Dados
Dados::Dados() {
    // La semilla hace que los resultados cambien en cada ejecución
    srand(time(NULL));
}

// Lanza la cantidad de dados que se recibe
void Dados::lanzar(int cantidadDados) {
    // Borra los resultados del lanzamiento anterior
    limpiar();

    // Si la cantidad no es válida, no se lanza ningún dado
    if (cantidadDados <= 0) {
        return;
    }

    // Genera un número entre 1 y 6 por cada dado
    for (int i = 0; i < cantidadDados; i++) {
        int resultadoDado = rand() % 6 + 1;
        resultados.push_back(resultadoDado);
    }

    // Ordena los resultados de mayor a menor con Bubble Sort
    // porque en el ataque se comparan primero los dados mayores
    int cantidadResultados = resultados.size();

    // El primer for controla la cantidad de pasadas
    for (int i = 0; i < cantidadResultados - 1; i++) {

        // Se resta 1 porque se compara la posición j con la posición j + 1
        // También se resta i porque al final de cada pasada queda
        // una posición ordenada y ya no es necesario volver a revisarla
        for (int j = 0; j < cantidadResultados - i - 1; j++) {

            // Si el valor de la izquierda es menor, se intercambian
            if (resultados[j] < resultados[j + 1]) {
                int auxiliar = resultados[j];
                resultados[j] = resultados[j + 1];
                resultados[j + 1] = auxiliar;
            }
        }
    }
}

// El & evita crear una copia completa del vector
// El primer const evita modificar el vector desde afuera
// El const del final indica que la función no modifica el objeto Dados
const vector<int>& Dados::obtenerResultados() const {
    return resultados;
}

// Devuelve la cantidad indicada de dados con mayor valor
// El const del final indica que la función no modifica el objeto Dados
vector<int> Dados::obtenerMayores(int cantidad) const {
    vector<int> mayores;

    // Si la cantidad no es válida, devuelve el vector vacío
    if (cantidad <= 0) {
        return mayores;
    }

    int limite = cantidad;
    int cantidadResultados = resultados.size();

    // Evita pedir más resultados de los que hay guardados
    if (limite > cantidadResultados) {
        limite = cantidadResultados;
    }

    // Los primeros valores son los mayores porque ya están ordenados
    for (int i = 0; i < limite; i++) {
        mayores.push_back(resultados[i]);
    }

    return mayores;
}

// Borra los resultados guardados
void Dados::limpiar() {
    resultados.clear();
}