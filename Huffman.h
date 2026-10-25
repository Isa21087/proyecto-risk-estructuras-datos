#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include "ArbolBinario.h"
#include "Tipos.h"

// recibe las frecuencias de los posibles 256 caracteres y construye el arbol
// el arbol recibido debe estar vacio porque aqui vamos a asignarle la raiz final
bool construirArbolHuffman(
    const unsigned long long frecuencias[256],
    ArbolBinario<DatoHuffman>& arbol
);

// recorre el arbol y guarda en cada posicion del arreglo
// el codigo de ceros y unos que corresponde a ese caracter
bool generarCodigosHuffman(
    ArbolBinario<DatoHuffman>& arbol,
    std::string codigos[256]
);

// comprime el mensaje usando Huffman y guarda el resultado como bytes reales
// tambien guarda las frecuencias para reconstruir el arbol al leer el archivo
bool comprimirHuffman(
    const std::string& mensaje,
    const std::string& nombreArchivo
);

// lee el archivo binario y recupera el mensaje original
bool descomprimirHuffman(
    const std::string& nombreArchivo,
    std::string& mensaje
);

#endif