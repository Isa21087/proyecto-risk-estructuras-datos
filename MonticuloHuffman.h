#ifndef MONTICULOHUFFMAN_H
#define MONTICULOHUFFMAN_H

#include <deque>
#include <algorithm>
#include "NodoBinario.h"
#include "Tipos.h"


// USO DE IA - ADAPTACION DEL MONTICULO PARA HUFFMAN
//
// Para esta implementacion se tomo como base el monticulo
// desarrollado en el Taller 3 y las diapositivas de
// Monticulos y Arboles de Codificacion del segundo corte.
//
// Tambien se reviso la documentacion de las operaciones
// push_heap y pop_heap de C++:
// https://en.cppreference.com/w/cpp/algorithm/push_heap.html
// https://en.cppreference.com/w/cpp/algorithm/pop_heap.html
//
// Objetivo de la consulta realizada a ChatGPT
// (redactado posteriormente, no es una cita literal):
//
// "Estoy adaptando el monticulo que implementamos en el
// Taller 3 para utilizarlo en la construccion de un arbol
// de Huffman. He estado revisando mi implementacion y
// comparandola con las diapositivas y las operaciones
// push_heap y pop_heap de la STL.
//
// En el taller trabajamos con un monticulo maximo, pero
// para Huffman necesito que tenga prioridad el nodo
// con menor frecuencia.
//
// Quiero revisar si el comparador que estoy utilizando
// establece correctamente esa prioridad y como manejar
// los empates entre frecuencias. Tambien quiero comprobar
// que las operaciones de insercion y extraccion mantengan
// la propiedad del monticulo.
//
// Ayudame a identificar posibles errores, explicarme
// las correcciones necesarias y conservar como base
// la estructura que trabajamos en clase."
//
// ChatGPT se utilizo para revisar el diseño, explicar
// el comparador y proponer ajustes durante la adaptacion.
// Las propuestas incorporadas se integraron y probaron
// dentro del proyecto RISK.


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