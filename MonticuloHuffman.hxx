#ifndef MONTICULOHUFFMAN_HXX
#define MONTICULOHUFFMAN_HXX

inline MonticuloHuffman::MonticuloHuffman() {
}

inline bool MonticuloHuffman::insertar(
    NodoBinario<DatoHuffman>* raiz,
    unsigned long long orden
) {

    if(raiz == NULL){
        return false;
    }

    ElementoMonticuloHuffman nuevoElemento;

    nuevoElemento.raiz = raiz;
    nuevoElemento.orden = orden;

    // primero se agrega el elemento al final del deque
    datos.push_back(nuevoElemento);

    // despues reorganizamos el monticulo usando nuestro comparador
    // asi el elemento con menor frecuencia queda con mayor prioridad
    std::push_heap(
        datos.begin(),
        datos.end(),
        ComparadorMonticuloHuffman()
    );

    return true;
}

inline NodoBinario<DatoHuffman>* MonticuloHuffman::extraerMinimo() {

    if(esVacio()){
        return NULL;
    }

    // mueve el elemento con mayor prioridad al final para poder sacarlo del deque
    std::pop_heap(
        datos.begin(),
        datos.end(),
        ComparadorMonticuloHuffman()
    );

    // guardamos su raiz antes de quitar el elemento del deque
    // porque esa raiz todavia la necesitamos para construir el arbol de Huffman
    NodoBinario<DatoHuffman>* minimo = datos.back().raiz;

    // solo quitamos el elemento del monticulo
    // no hacemos delete porque los nodos siguen formando parte de los subarboles
    datos.pop_back();

    return minimo;
}

inline bool MonticuloHuffman::esVacio() {
    return datos.empty();
}

#endif