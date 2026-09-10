#include "Mazo.h"
#include "Jugador.h"
#include "Tablero.h"
#include "Territorio.h"
#include <sstream>
#include <cstdlib>

using namespace std;

// Inicializa el mazo sin intercambios realizados.
Mazo::Mazo()
{
    cantidadIntercambios = 0;
}

// Revisa si quedan cartas para entregar.
// El const indica que no modifica el mazo.
bool Mazo::tieneCartasDisponibles() const
{
    return !cartasDisponibles.empty();
}

// Revisa si las tres cartas forman una combinacion permitida.
//
// El vector se recibe por referencia para no crear otra copia.
// El const evita modificar las cartas recibidas.
bool Mazo::combinacionValida(
    const vector<Carta>& cartas
) const {

    if(cartas.size() != 3){
        return false;
    }

    int infanterias = 0;
    int caballerias = 0;
    int artillerias = 0;
    int comodines = 0;

    for(int i = 0; i < cartas.size(); i++){

        if(cartas[i].obtenerTipo() == CARTA_INFANTERIA){

            infanterias++;

        }
        else if(cartas[i].obtenerTipo() == CARTA_CABALLERIA){

            caballerias++;

        }
        else if(cartas[i].obtenerTipo() == CARTA_ARTILLERIA){

            artillerias++;

        }
        else if(cartas[i].esComodin()){

            comodines++;

        }
        else{

            return false;

        }

    }

    // Tres cartas con el mismo dibujo.
    if(infanterias == 3 ||
       caballerias == 3 ||
       artillerias == 3){

        return true;

    }

    // Una carta de cada dibujo.
    if(infanterias == 1 && caballerias == 1 && artillerias == 1){

        return true;

    }

    // Dos cartas de ejercito y un comodin.
    if(comodines == 1 && infanterias + caballerias + artillerias == 2){

        return true;

    }

    return false;
}

// Crea las 42 cartas de territorios y los dos comodines.
void Mazo::inicializarMazo()
{
    cartasDisponibles.clear();
    cantidadIntercambios = 0;

    int numeroCarta = 0;

    for(int continente = 1; continente <= 6; continente++){

        int cantidadTerritorios = 0;

        if(continente == 1){

            cantidadTerritorios = 9;

        }
        else if(continente == 2){

            cantidadTerritorios = 4;

        }
        else if(continente == 3){

            cantidadTerritorios = 7;

        }
        else if(continente == 4){

            cantidadTerritorios = 6;

        }
        else if(continente == 5){

            cantidadTerritorios = 12;

        }
        else{

            cantidadTerritorios = 4;

        }

        for(
            int territorio = 1;
            territorio <= cantidadTerritorios;
            territorio++
        ){

            // Forma el codigo con el numero del continente
            // y el numero del territorio.
            stringstream codigo;

            codigo << continente
                   << "."
                   << territorio;

            TipoCarta tipo;

            // Alterna los tres dibujos de las cartas.
            if(numeroCarta % 3 == 0){

                tipo = CARTA_INFANTERIA;

            }
            else if(numeroCarta % 3 == 1){

                tipo = CARTA_CABALLERIA;

            }
            else{

                tipo = CARTA_ARTILLERIA;

            }

            cartasDisponibles.push_back(
                Carta(tipo, codigo.str())
            );

            numeroCarta++;

        }

    }

    // Los comodines no tienen territorio asociado.
    cartasDisponibles.push_back(
        Carta(CARTA_COMODIN, "")
    );

    cartasDisponibles.push_back(
        Carta(CARTA_COMODIN, "")
    );
}

// Entrega una carta al jugador y la retira del mazo.
// El & permite modificar el jugador recibido
// sin crear una copia de el.
bool Mazo::entregarCarta(Jugador& jugador)
{
    if(!tieneCartasDisponibles()){
        return false;
    }

    int posicion =
        rand() % cartasDisponibles.size();

    jugador.agregarCarta(
        cartasDisponibles[posicion]
    );

    // Lleva la ultima carta a la posicion
    // que quedara disponible.
    cartasDisponibles[posicion] =
        cartasDisponibles.back();

    // Elimina la ultima posicion del vector.
    cartasDisponibles.pop_back();

    return true;
}

// Procesa el intercambio de tres cartas.
//
// Retorna la cantidad de unidades generales obtenidas.
// Si las posiciones o la combinacion no son validas,
// retorna cero y no modifica el jugador ni el tablero.
int Mazo::procesarIntercambio(
    Jugador& jugador,
    Tablero& tablero,
    int posicionUno,
    int posicionDos,
    int posicionTres
) {

    // Se obtiene una referencia al vector original
    // porque las cartas canjeadas deben eliminarse.
    vector<Carta>& cartasJugador =
        jugador.obtenerCartas();

    // Las posiciones mostradas al jugador comienzan en uno.
    if(posicionUno <= 0 ||
       posicionDos <= 0 ||
       posicionTres <= 0){

        return 0;

    }

    if(posicionUno > cartasJugador.size() ||
       posicionDos > cartasJugador.size() ||
       posicionTres > cartasJugador.size()){

        return 0;

    }

    // Las tres posiciones deben ser diferentes.
    if(posicionUno == posicionDos ||
       posicionUno == posicionTres ||
       posicionDos == posicionTres){

        return 0;

    }

    // Se resta uno porque las posiciones del vector
    // comienzan en cero.
    posicionUno--;
    posicionDos--;
    posicionTres--;

    // Se copian solamente las tres cartas seleccionadas
    // para revisar su combinacion.
    vector<Carta> cartasSeleccionadas;

    cartasSeleccionadas.push_back(
        cartasJugador[posicionUno]
    );

    cartasSeleccionadas.push_back(
        cartasJugador[posicionDos]
    );

    cartasSeleccionadas.push_back(
        cartasJugador[posicionTres]
    );

    if(!combinacionValida(cartasSeleccionadas)){
        return 0;
    }

    // El contador pertenece al mazo y es compartido
    // por los intercambios de todos los jugadores.
    cantidadIntercambios++;

    int bonificacion = 0;

    if(cantidadIntercambios == 1){

        bonificacion = 4;

    }
    else if(cantidadIntercambios == 2){

        bonificacion = 6;

    }
    else if(cantidadIntercambios == 3){

        bonificacion = 8;

    }
    else if(cantidadIntercambios == 4){

        bonificacion = 10;

    }
    else if(cantidadIntercambios == 5){

        bonificacion = 12;

    }
    else if(cantidadIntercambios == 6){

        bonificacion = 15;

    }
    else{

        bonificacion =
            15 + (cantidadIntercambios - 6) * 5;

    }

    // Revisa si alguna carta contiene un territorio
    // que pertenece al jugador.
    for(int i = 0; i < cartasSeleccionadas.size(); i++){

        string codigoTerritorio =
            cartasSeleccionadas[i].obtenerCodigoTerritorio();

        // Los comodines tienen el codigo vacio.
        if(codigoTerritorio != ""){

            // El puntero tiene const porque solamente
            // se consulta el propietario del territorio.
            const Territorio* territorio =
                tablero.buscarTerritorio(codigoTerritorio);

            if(territorio != NULL &&
               territorio->obtenerColorPropietario()
                   == jugador.obtenerColor()){

                // Estas dos unidades deben colocarse
                // obligatoriamente en el territorio de la carta.
                tablero.agregarUnidades(
                    codigoTerritorio,
                    jugador.obtenerColor(),
                    2
                );

            }

        }

    }

    // Guarda las posiciones para organizarlas
    // de mayor a menor antes de eliminarlas.
    vector<int> posiciones;

    posiciones.push_back(posicionUno);
    posiciones.push_back(posicionDos);
    posiciones.push_back(posicionTres);

    // Se usa el mismo recorrido sencillo de vectores.
    // Se organizan de mayor a menor para que erase()
    // no cambie las posiciones que faltan por eliminar.
    for(int i = 0; i < posiciones.size() - 1; i++){

        for(
            int j = 0;
            j < posiciones.size() - i - 1;
            j++
        ){

            if(posiciones[j] < posiciones[j + 1]){

                int temporal = posiciones[j];

                posiciones[j] = posiciones[j + 1];

                posiciones[j + 1] = temporal;

            }

        }

    }

    // Elimina las tres cartas del jugador.
    for(int i = 0; i < posiciones.size(); i++){

        cartasJugador.erase(
            cartasJugador.begin() + posiciones[i]
        );

    }

    return bonificacion;
}