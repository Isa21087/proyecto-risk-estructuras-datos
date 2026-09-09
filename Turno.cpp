#include "Turno.h"

using namespace std;

// Inicializa el turno empezando desde el primer jugador
// y en la etapa inicial de obtener unidades.
Turno::Turno()
{
    posicionJugadorActual = 0;
    etapaActual = ETAPA_OBTENER_UNIDADES;
}