#include "Turno.h"
#include "Jugador.h"
#include "Tablero.h"

using namespace std;

// Inicializa el turno en el primer jugador
// y en la etapa de obtener unidades.
Turno::Turno()
    : posicionJugadorActual(0),
      etapaActual(ETAPA_OBTENER_UNIDADES)
{
}

// Inicia el turno desde la posicion indicada.
void Turno::iniciar(int primeraPosicion)
{
    posicionJugadorActual = primeraPosicion;
    etapaActual = ETAPA_OBTENER_UNIDADES;
}

// Retorna la posicion del jugador actual.
// El const indica que no modifica el turno.
int Turno::obtenerPosicionJugadorActual() const
{
    return posicionJugadorActual;
}

// Retorna la etapa actual sin modificarla.
EtapaTurno Turno::obtenerEtapaActual() const
{
    return etapaActual;
}

// Verifica si la posicion corresponde al jugador actual.
bool Turno::esTurnoDe(int posicionJugador) const
{
    if(posicionJugadorActual != posicionJugador){
        return false;
    }

    return true;
}

// Verifica si se encuentra en la etapa de obtener unidades.
bool Turno::puedeObtenerUnidades() const
{
    if(etapaActual != ETAPA_OBTENER_UNIDADES){
        return false;
    }

    return true;
}

// Verifica si se encuentra en la etapa de ataque.
bool Turno::puedeAtacar() const
{
    if(etapaActual != ETAPA_ATACAR){
        return false;
    }

    return true;
}

// Verifica si se encuentra en la etapa de fortificacion.
bool Turno::puedeFortificar() const
{
    if(etapaActual != ETAPA_FORTIFICAR){
        return false;
    }

    return true;
}

// Calcula las unidades nuevas obtenidas por territorios,
// continentes y cartas.
//
// El jugador y el tablero se reciben por referencia para no copiarlos.
// Tambien tienen const porque esta funcion solamente los consulta.
int Turno::calcularNuevasUnidades(
    const Jugador& jugador,
    const Tablero& tablero,
    int bonificacionCartas
) const {

    string color = jugador.obtenerColor();

    // El enunciado indica contar los territorios ocupados.
    int cantidadTerritorios =
        tablero.contarTerritorios(color);

    // La division entera toma solamente las unidades completas.
    int unidadesTerritorios =
        cantidadTerritorios / 3;

    int unidadesContinentes =
        tablero.calcularBonificacionContinentes(color);

    return unidadesTerritorios
        + unidadesContinentes
        + bonificacionCartas;
}

// Agrega una parte de las unidades obtenidas en un territorio.
//
// El jugador tiene const porque solo se consulta su color.
// El tablero no tiene const porque se agregan unidades.
// El & permite modificar el tablero recibido y evita crear una copia.
bool Turno::ejecutarObtencionUnidades(
    const Jugador& jugador,
    Tablero& tablero,
    string codigoTerritorio,
    int cantidad
) {

    if(!puedeObtenerUnidades()){
        return false;
    }

    if(cantidad <= 0){
        return false;
    }

    if(!tablero.agregarUnidades(
        codigoTerritorio,
        jugador.obtenerColor(),
        cantidad
    )){
        return false;
    }

    return true;
}

// Cambia a la etapa de ataque cuando se terminan
// de repartir todas las unidades.
void Turno::registrarUnidadesObtenidas()
{
    if(etapaActual == ETAPA_OBTENER_UNIDADES){
        etapaActual = ETAPA_ATACAR;
    }
}

// Cambia a la etapa de fortificacion
// cuando el jugador termina de atacar.
void Turno::registrarAtaqueTerminado()
{
    if(etapaActual == ETAPA_ATACAR){
        etapaActual = ETAPA_FORTIFICAR;
    }
}

// Traslada unidades entre dos territorios del jugador.
//
// El jugador solamente se consulta.
// El tablero se modifica directamente por medio de la referencia.
bool Turno::ejecutarFortificacion(
    const Jugador& jugador,
    Tablero& tablero,
    string codigoOrigen,
    string codigoDestino,
    int cantidad
) {

    if(!puedeFortificar()){
        return false;
    }

    if(cantidad <= 0){
        return false;
    }

    if(!tablero.trasladarUnidades(
        codigoOrigen,
        codigoDestino,
        jugador.obtenerColor(),
        cantidad,
        1
    )){
        return false;
    }

    return true;
}

// Pasa al siguiente jugador.
// Si era el ultimo, vuelve al primero.
void Turno::finalizarTurno(int cantidadJugadores)
{
    posicionJugadorActual++;

    if(posicionJugadorActual >= cantidadJugadores){
        posicionJugadorActual = 0;
    }

    etapaActual = ETAPA_OBTENER_UNIDADES;
}