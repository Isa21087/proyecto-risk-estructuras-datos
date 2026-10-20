#ifndef MONTICULOHUFFMAN_H
#define MONTICULOHUFFMAN_H

#include <deque>
#include <algorithm>
#include "NodoBinario.h"
#include "Tipos.h"

// cada elemento guarda la raiz de un subarbol y el orden en que entro al monticulo
// el orden nos sirve para decidir cual sale primero cuando dos subarboles tienen la misma frecuencia
struct ElementoMonticuloHuffman {
    NodoBinario<DatoHuffman>* raiz;
    unsigned long long orden;
};

struct ComparadorMonticuloHuffman {

    bool operator()(
        const ElementoMonticuloHuffman& primero,
        const ElementoMonticuloHuffman& segundo
    ) const {

        DatoHuffman datoPrimero = primero.raiz->obtenerDato();
        DatoHuffman datoSegundo = segundo.raiz->obtenerDato();

        // queremos sacar primero la frecuencia menor
        // usamos > porque los algoritmos de monticulo normalmente dejan el mayor arriba
        if(datoPrimero.frecuencia != datoSegundo.frecuencia){
            return datoPrimero.frecuencia > datoSegundo.frecuencia;
        }

        // si empatan sale primero el que entro antes
        // asi podemos construir el mismo arbol al comprimir y al descomprimir
        return primero.orden > segundo.orden;
    }
};

class MonticuloHuffman {

protected:
    // aqui se guardan las raices de los subarboles que todavia faltan por unir
    std::deque<ElementoMonticuloHuffman> datos;

public:
    MonticuloHuffman();

    bool insertar(
        NodoBinario<DatoHuffman>* raiz,
        unsigned long long orden
    );

    NodoBinario<DatoHuffman>* extraerMinimo();

    bool esVacio();
};

#include "MonticuloHuffman.hxx"

#endif