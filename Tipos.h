
#ifndef TIPOS_H
#define TIPOS_H
using namespace std;
enum EtapaTurno {
    ETAPA_OBTENER_UNIDADES,
    ETAPA_ATACAR,
    ETAPA_FORTIFICAR
};
enum EstadoComando {
    COMANDO_CORRECTO,
    ARCHIVO_VACIO,
    ARCHIVO_ERRONEO,
    ARCHIVO_SIN_FORMATO,
    JUEGO_EN_CURSO,
    JUEGO_NO_INICIALIZADO,
    JUEGO_TERMINADO,
    JUGADOR_NO_VALIDO,
    JUGADOR_FUERA_DE_TURNO,
    JUGADOR_NO_HA_UBICADO_UNIDADES,
    JUGADOR_NO_HA_ATACADO
};
enum TipoCarta {
    CARTA_INFANTERIA,
    CARTA_CABALLERIA,
    CARTA_ARTILLERIA,
    CARTA_COMODIN
};
struct ResultadoAtaque {
    bool ataqueRealizado;
    bool conquistoTerritorio;
};
#endif
