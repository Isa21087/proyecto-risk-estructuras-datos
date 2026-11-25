
#include "Partida.h"
#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

// Inicializa la partida sin datos cargados.
Partida::Partida()
{
    inicializada = false;
    terminada = false;
    ganador = "";
}

// Inicializa la partida desde un archivo.
EstadoComando Partida::inicializar(string nombreArchivo)
{
    // No permite cargar otra partida si ya hay una inicializada.
    if (inicializada)
    {
        return JUEGO_EN_CURSO;
    }

    ifstream archivo(nombreArchivo.c_str(), ios::binary);

    if (!archivo.is_open())
    {
        return ARCHIVO_ERRONEO;
    }

    // USO DE IA - LECTURA DE PARTIDAS COMPRIMIDAS
    //
    // Se partio de la funcion inicializar de la Entrega 1,
    // que ya permitia cargar jugadores y territorios desde
    // un archivo de texto.
    //
    // Para la Entrega 2 se adapto la lectura para aceptar
    // tambien archivos comprimidos con Huffman, conservando
    // las validaciones y el procesamiento original.
    //
    // Referencia tecnica para revisar esta adaptacion:
    // https://en.cppreference.com/w/cpp/io/basic_istringstream
    //
    // Consulta descrita posteriormente (no es el prompt literal):
    //
    // "Ya tengo implementada la inicializacion de partidas
    // en texto desde la primera entrega y estoy integrando
    // el almacenamiento comprimido de Huffman.
    //
    // Estoy revisando como utilizar istringstream para
    // procesar el texto recuperado desde un archivo binario,
    // sin duplicar toda la lectura de jugadores y territorios.
    //
    // Quiero comprobar si puedo manejar ambas fuentes con
    // istream y conservar las validaciones existentes.
    // Ayudame a revisar la adaptacion, especialmente el
    // manejo de errores y el flujo de lectura."
    //
    // ChatGPT apoyo la propuesta y revision de esta
    // adaptacion. La inicializacion original y sus
    // validaciones se conservaron como base del proyecto.

    // si el archivo es comprimido, recuperamos su texto con Huffman
    string contenidoDescomprimido;
    istringstream textoDescomprimido;
    istream *fuente = &archivo;

    if (nombreArchivo.size() >= 4 &&
        nombreArchivo.substr(nombreArchivo.size() - 4) == ".bin")
    {
        if (!descomprimirHuffman(nombreArchivo, contenidoDescomprimido))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        textoDescomprimido.str(contenidoDescomprimido);
        fuente = &textoDescomprimido;
    }

    string linea;

    if (!getline(*fuente, linea))
    {
        archivo.close();
        return ARCHIVO_VACIO;
    }

    // Salta las lineas vacias al inicio.
    while (linea.empty() && getline(*fuente, linea))
    {
    }

    if (linea.empty())
    {
        archivo.close();
        return ARCHIVO_VACIO;
    }

    // Lee la cantidad de jugadores.
    istringstream lineaJugadores(linea);
    int cantidadJugadores;
    string datoExtra;

    if (!(lineaJugadores >> cantidadJugadores))
    {
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    // La linea solo debe tener la cantidad de jugadores.
    if (lineaJugadores >> datoExtra)
    {
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    if (cantidadJugadores < 3 || cantidadJugadores > 6)
    {
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    vector<Jugador> jugadoresLeidos;

    // Lee el nombre y el color de cada jugador.
    for (int i = 0; i < cantidadJugadores; i++)
    {
        if (!getline(*fuente, linea))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        while (linea.empty() && getline(*fuente, linea))
        {
        }

        if (linea.empty())
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        istringstream lineaJugador(linea);
        string nombre;
        string color;

        if (!(lineaJugador >> nombre >> color))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        if (lineaJugador >> datoExtra)
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // El nombre puede tener hasta 8 caracteres.
        if (nombre.length() > 8)
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Revisa que el color sea uno de los permitidos.
        if (color != "verde" &&
            color != "azul" &&
            color != "rojo" &&
            color != "amarillo" &&
            color != "negro" &&
            color != "gris")
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // No permite nombres ni colores repetidos.
        for (int j = 0; j < jugadoresLeidos.size(); j++)
        {
            if (jugadoresLeidos[j].obtenerNombre() == nombre ||
                jugadoresLeidos[j].obtenerColor() == color)
            {
                archivo.close();
                return ARCHIVO_SIN_FORMATO;
            }
        }

        jugadoresLeidos.push_back(Jugador(nombre, color));
    }

    // Prepara el tablero para cargar los territorios.
    Tablero tableroLeido;
    tableroLeido.inicializarEstructura();

    vector<string> territoriosLeidos;

    // Lee los 42 territorios.
    for (int i = 0; i < 42; i++)
    {
        if (!getline(*fuente, linea))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        while (linea.empty() && getline(*fuente, linea))
        {
        }

        if (linea.empty())
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        istringstream lineaTerritorio(linea);
        string codigo;
        string color;
        int unidades;

        if (!(lineaTerritorio >> codigo >> color >> unidades))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        if (lineaTerritorio >> datoExtra)
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Revisa que el territorio exista.
        if (!tableroLeido.existeTerritorio(codigo))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Revisa que el territorio no se haya leido antes.
        bool repetido = false;

        for (int j = 0; j < territoriosLeidos.size(); j++)
        {
            if (territoriosLeidos[j] == codigo)
            {
                repetido = true;
            }
        }

        if (repetido)
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        territoriosLeidos.push_back(codigo);

        // Aceptamos cero unidades porque una conquista puede dejar
        // un territorio asi y ese estado tambien debe poder recuperarse
        // desde una partida guardada
        // Las cantidades negativas siguen siendo invalidas
        if (unidades < 0)
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Busca el jugador que tiene ese color.
        int posicionJugador = -1;

        for (int j = 0; j < jugadoresLeidos.size(); j++)
        {
            if (jugadoresLeidos[j].obtenerColor() == color)
            {
                posicionJugador = j;
            }
        }

        if (posicionJugador == -1)
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }

        // Asigna el propietario y las unidades.
        if (!tableroLeido.configurarTerritorio(codigo, color, unidades))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }
    }

    // No permite mas datos despues de los 42 territorios.
    while (getline(*fuente, linea))
    {
        istringstream lineaRestante(linea);

        if (lineaRestante >> datoExtra)
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }
    }

    // revisamos que todos los territorios hayan quedado configurados
    if (!tableroLeido.todosLosTerritoriosConfigurados())
    {
        archivo.close();
        return ARCHIVO_SIN_FORMATO;
    }

    // preparamos el grafo usando los territorios que ya fueron validados
    // todavia no cambiamos la partida real por si algo falla
    Grafo grafoLeido;

    // registramos los mismos 42 codigos que se leyeron del archivo
    for (int i = 0; i < territoriosLeidos.size(); i++)
    {
        if (!grafoLeido.agregarTerritorio(territoriosLeidos[i]))
        {
            archivo.close();
            return ARCHIVO_SIN_FORMATO;
        }
    }

    // revisamos las conexiones del mapa que ya tiene Tablero
    // no necesitamos volver a escribir los vecinos de cada territorio
    for (int i = 0; i < grafoLeido.cantidadTerritorios(); i++)
    {
        string codigoOrigen = grafoLeido.obtenerTerritorio(i);

        for (int j = 0; j < grafoLeido.cantidadTerritorios(); j++)
        {
            // no registramos un territorio como vecino de si mismo
            if (i == j)
            {
                continue;
            }

            string codigoDestino = grafoLeido.obtenerTerritorio(j);

            // si Tablero dice que son vecinos, guardamos la conexion
            // por ahora usamos costo cero porque todavia no sabemos
            // para que jugador se va a calcular una estrategia
            if (tableroLeido.sonVecinos(codigoOrigen, codigoDestino))
            {
                grafoLeido.establecerCosto(i, j, 0);
            }
        }
    }

    // Guarda los datos cuando todo el archivo es valido.
    jugadores = jugadoresLeidos;
    tablero = tableroLeido;
    grafo = grafoLeido;

    // El primer jugador del archivo empieza el turno.
    turno.iniciar(0);

    // Prepara las cartas para la nueva partida.
    mazo.inicializarMazo();

    inicializada = true;
    terminada = false;
    ganador = "";

    archivo.close();

    return COMANDO_CORRECTO;
}

// Revisa si se puede consultar la partida.
EstadoComando Partida::validarEstadoJuego() const
{
    if (!inicializada)
    {
        return JUEGO_NO_INICIALIZADO;
    }

    if (terminada)
    {
        return JUEGO_TERMINADO;
    }

    return COMANDO_CORRECTO;
}

// Muestra los jugadores, el turno actual y el tablero.
void Partida::mostrarEstadoJuego() const
{
    if (validarEstadoJuego() != COMANDO_CORRECTO)
    {
        return;
    }

    cout << "========== ESTADO DEL JUEGO ==========" << endl;
    cout << "Cantidad de jugadores: " << jugadores.size() << endl;

    for (int i = 0; i < jugadores.size(); i++)
    {
        cout << "Jugador: " << jugadores[i].obtenerNombre()
             << " | Color: " << jugadores[i].obtenerColor() << endl;
    }

    int posicionActual = turno.obtenerPosicionJugadorActual();

    cout << "Turno actual: "
         << jugadores[posicionActual].obtenerNombre() << endl;

    tablero.mostrarTablero();
}

// Busca al jugador por su nombre.
int Partida::buscarPosicionJugador(string nombreJugador) const
{
    for (int i = 0; i < jugadores.size(); i++)
    {
        if (jugadores[i].obtenerNombre() == nombreJugador)
        {
            return i;
        }
    }

    return -1;
}

// Revisa el turno y permite canjear cartas
// y repartir las unidades nuevas.
EstadoComando Partida::obtenerUnidades(string nombreJugador)
{
    EstadoComando estado = validarEstadoJuego();

    if (estado != COMANDO_CORRECTO)
    {
        return estado;
    }

    int posicion = buscarPosicionJugador(nombreJugador);

    if (posicion == -1)
    {
        return JUGADOR_NO_VALIDO;
    }

    if (!turno.esTurnoDe(posicion))
    {
        return JUGADOR_FUERA_DE_TURNO;
    }

    if (!turno.puedeObtenerUnidades())
    {
        return JUGADOR_YA_OBTUVO_UNIDADES;
    }

    // Se crean copias temporales para que el jugador,
    // el tablero y el mazo solamente cambien cuando
    // se termine correctamente el comando.
    Jugador jugadorTemporal =
        jugadores[posicion];

    Tablero tableroTemporal =
        tablero;

    Mazo mazoTemporal =
        mazo;

    int bonificacionCartas = 0;

    bool terminarCanjes = false;

    // El jugador solamente puede intentar un canje
    // cuando tiene por lo menos tres cartas.
    while (!terminarCanjes &&
           jugadorTemporal.obtenerCartas().size() >= 3)
    {
        // La referencia permite consultar el vector
        // sin crear una copia de todas las cartas.
        const vector<Carta> &cartasJugador =
            jugadorTemporal.obtenerCartas();

        cout << "Cartas del jugador:" << endl;

        for (int i = 0; i < cartasJugador.size(); i++)
        {
            cout << i + 1 << ". ";

            if (cartasJugador[i].obtenerTipo() == CARTA_INFANTERIA)
            {
                cout << "Infanteria";
            }
            else if (cartasJugador[i].obtenerTipo() == CARTA_CABALLERIA)
            {
                cout << "Caballeria";
            }
            else if (cartasJugador[i].obtenerTipo() == CARTA_ARTILLERIA)
            {
                cout << "Artilleria";
            }
            else
            {
                cout << "Comodin";
            }

            string codigoTerritorio =
                cartasJugador[i].obtenerCodigoTerritorio();

            if (codigoTerritorio != "")
            {
                cout << " - Territorio "
                     << codigoTerritorio;
            }

            cout << endl;
        }

        cout << "Desea intercambiar tres cartas? (s/n): ";

        string linea;

        if (!getline(cin, linea))
        {
            return ENTRADA_CERRADA;
        }

        istringstream entrada(linea);

        string respuesta;
        string datoExtra;

        if (!(entrada >> respuesta))
        {
            cout << "Debe escribir s o n." << endl;
        }
        else if (entrada >> datoExtra)
        {
            cout << "Escriba solamente s o n." << endl;
        }
        else if (respuesta == "n" ||
                 respuesta == "N")
        {
            terminarCanjes = true;
        }
        else if (respuesta == "s" ||
                 respuesta == "S")
        {
            bool seleccionTerminada = false;

            while (!seleccionTerminada)
            {
                cout << "Escriba las posiciones de las tres cartas "
                     << "o n para cancelar: ";

                string seleccion;

                if (!getline(cin, seleccion))
                {
                    return ENTRADA_CERRADA;
                }

                if (seleccion == "n" ||
                    seleccion == "N")
                {
                    seleccionTerminada = true;
                }
                else
                {
                    istringstream entradaSeleccion(
                        seleccion);

                    int posicionUno;
                    int posicionDos;
                    int posicionTres;
                    string datoSobrante;

                    if (!(entradaSeleccion >> posicionUno >> posicionDos >> posicionTres))
                    {
                        cout << "Debe escribir tres posiciones enteras."
                             << endl;
                    }
                    else if (entradaSeleccion >> datoSobrante)
                    {
                        cout << "Escriba solamente las tres posiciones."
                             << endl;
                    }
                    else
                    {
                        int bonificacionCanje =
                            mazoTemporal.procesarIntercambio(
                                jugadorTemporal,
                                tableroTemporal,
                                posicionUno,
                                posicionDos,
                                posicionTres);

                        if (bonificacionCanje == 0)
                        {
                            cout << "Las cartas seleccionadas no forman "
                                 << "una combinacion valida."
                                 << endl;
                        }
                        else
                        {
                            bonificacionCartas +=
                                bonificacionCanje;

                            cout << "Canje realizado. "
                                 << "Unidades obtenidas: "
                                 << bonificacionCanje
                                 << endl;

                            // Solo se agregan las dos unidades cuando el territorio
                            // de la carta pertenece al jugador.
                            cout << "Si alguna carta corresponde a un territorio propio, "
                                 << "se agregaron 2 unidades en ese territorio."
                                 << endl;

                            seleccionTerminada = true;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "Debe escribir s o n." << endl;
        }
    }

    int unidadesPendientes =
        turno.calcularNuevasUnidades(
            jugadorTemporal,
            tableroTemporal,
            bonificacionCartas);

    cout << "Unidades disponibles: "
         << unidadesPendientes << endl;

    while (unidadesPendientes > 0)
    {
        cout << "Escriba el codigo del territorio "
             << "y la cantidad de unidades: ";

        string linea;

        if (!getline(cin, linea))
        {
            return ENTRADA_CERRADA;
        }

        istringstream entrada(linea);

        string codigoTerritorio;
        int cantidad;
        string datoExtra;

        if (!(entrada >> codigoTerritorio >> cantidad))
        {
            cout << "Debe escribir un codigo y una cantidad entera."
                 << endl;
        }
        else if (entrada >> datoExtra)
        {
            cout << "Solo debe escribir el codigo y la cantidad."
                 << endl;
        }
        else if (cantidad <= 0)
        {
            cout << "La cantidad debe ser mayor que cero."
                 << endl;
        }
        else if (cantidad > unidadesPendientes)
        {
            cout << "No tiene suficientes unidades disponibles."
                 << endl;
        }
        else if (!tableroTemporal.existeTerritorio(
                     codigoTerritorio))
        {
            cout << "El territorio no existe." << endl;
        }
        else if (!turno.ejecutarObtencionUnidades(
                     jugadorTemporal,
                     tableroTemporal,
                     codigoTerritorio,
                     cantidad))
        {
            cout << "Elija un territorio que pertenezca al jugador."
                 << endl;
        }
        else
        {
            unidadesPendientes -= cantidad;

            cout << "Unidades restantes: "
                 << unidadesPendientes << endl;
        }
    }

    // Los cambios se guardan cuando el jugador termina
    // de repartir todas las unidades.
    jugadores[posicion] =
        jugadorTemporal;

    tablero =
        tableroTemporal;

    mazo =
        mazoTemporal;

    turno.registrarUnidadesObtenidas();

    return COMANDO_CORRECTO;
}

// Revisa si un jugador conquisto todo el tablero.
bool Partida::comprobarGanador()
{
    if (!inicializada)
    {
        return false;
    }

    for (int i = 0; i < jugadores.size(); i++)
    {
        if (tablero.contarTerritorios(jugadores[i].obtenerColor()) == 42)
        {
            terminada = true;
            ganador = jugadores[i].obtenerNombre();

            return true;
        }
    }

    return false;
}

// Controla la etapa de ataque del jugador.
EstadoComando Partida::atacar(string nombreJugador)
{
    EstadoComando estado = validarEstadoJuego();

    if (estado != COMANDO_CORRECTO)
    {
        return estado;
    }

    int posicion = buscarPosicionJugador(nombreJugador);

    if (posicion == -1)
    {
        return JUGADOR_NO_VALIDO;
    }

    if (posicion != turno.obtenerPosicionJugadorActual())
    {
        return JUGADOR_FUERA_DE_TURNO;
    }

    if (turno.obtenerEtapaActual() == ETAPA_OBTENER_UNIDADES)
    {
        return JUGADOR_NO_HA_UBICADO_UNIDADES;
    }

    if (turno.obtenerEtapaActual() == ETAPA_FORTIFICAR)
    {
        return JUGADOR_YA_TERMINO_ATAQUE;
    }

    bool continuar = true;
    bool cartaEntregada = false;

    while (continuar)
    {
        cout << "Desea realizar un ataque? (s/n): ";

        string respuesta;

        if (!getline(cin, respuesta))
        {
            return ENTRADA_CERRADA;
        }

        if (respuesta == "n" || respuesta == "N")
        {
            continuar = false;
        }
        else if (respuesta == "s" || respuesta == "S")
        {
            ResultadoAtaque resultado = ataque.ejecutar(jugadores[posicion], tablero);

            // Comprueba la victoria despues de una conquista.
            if (resultado.conquistoTerritorio)
            {
                // Entrega una sola carta aunque conquiste varios territorios.
                if (!cartaEntregada)
                {
                    if (mazo.entregarCarta(jugadores[posicion]))
                    {
                        cartaEntregada = true;

                        cout << "Recibio una carta por conquistar un territorio." << endl;
                        cout << "Cartas del jugador: "
                             << jugadores[posicion].obtenerCartas().size() << endl;
                    }
                    else
                    {
                        cout << "No quedan cartas disponibles en el mazo." << endl;
                    }
                }

                if (comprobarGanador())
                {
                    cout << "El ganador es " << ganador << "." << endl;
                    return COMANDO_CORRECTO;
                }
            }

            if (!cin)
            {
                return ENTRADA_CERRADA;
            }
        }
        else
        {
            cout << "Escriba s para atacar o n para terminar la etapa." << endl;
        }
    }

    turno.registrarAtaqueTerminado();

    return COMANDO_CORRECTO;
}

// Permite fortificar y termina el turno del jugador.
EstadoComando Partida::fortificar(string nombreJugador)
{
    EstadoComando estado = validarEstadoJuego();

    if (estado != COMANDO_CORRECTO)
    {
        return estado;
    }

    int posicion = buscarPosicionJugador(nombreJugador);

    if (posicion == -1)
    {
        return JUGADOR_NO_VALIDO;
    }

    if (!turno.esTurnoDe(posicion))
    {
        return JUGADOR_FUERA_DE_TURNO;
    }

    if (!turno.puedeFortificar())
    {
        return JUGADOR_NO_HA_ATACADO;
    }

    bool fortificacionTerminada = false;

    // Se usa una copia para conservar el tablero original
    // si la entrada se cierra antes de terminar.
    Tablero tableroTemporal = tablero;

    while (!fortificacionTerminada)
    {
        cout << "Escriba origen, destino y cantidad, o n para no trasladar: ";

        string linea;

        if (!getline(cin, linea))
        {
            return ENTRADA_CERRADA;
        }

        istringstream entrada(linea);

        string codigoOrigen;
        string codigoDestino;
        string datoExtra;
        int cantidad;

        if (!(entrada >> codigoOrigen))
        {
            cout << "Debe escribir los datos o n para terminar."
                 << endl;
        }
        else if (codigoOrigen == "n" || codigoOrigen == "N")
        {
            if (entrada >> datoExtra)
            {
                cout << "Escriba solamente n para terminar."
                     << endl;
            }
            else
            {
                fortificacionTerminada = true;
            }
        }
        else if (!(entrada >> codigoDestino >> cantidad))
        {
            cout << "Debe escribir origen, destino y una cantidad entera."
                 << endl;
        }
        else if (entrada >> datoExtra)
        {
            cout << "Solo debe escribir origen, destino y cantidad."
                 << endl;
        }
        else if (codigoOrigen == codigoDestino)
        {
            cout << "Debe escoger dos territorios diferentes."
                 << endl;
        }
        else if (cantidad <= 0)
        {
            cout << "La cantidad debe ser mayor que cero."
                 << endl;
        }
        else if (!tableroTemporal.existeTerritorio(codigoOrigen) ||
                 !tableroTemporal.existeTerritorio(codigoDestino))
        {
            cout << "Uno de los territorios no existe."
                 << endl;
        }
        else if (!tableroTemporal.sonVecinos(
                     codigoOrigen,
                     codigoDestino))
        {
            cout << "Los territorios deben ser vecinos."
                 << endl;
        }
        else if (!turno.ejecutarFortificacion(
                     jugadores[posicion],
                     tableroTemporal,
                     codigoOrigen,
                     codigoDestino,
                     cantidad))
        {
            cout << "No se pudo realizar la fortificacion. "
                 << "Verifique que ambos territorios sean propios "
                 << "y que haya suficientes unidades."
                 << endl;
        }
        else
        {
            tablero = tableroTemporal;
            fortificacionTerminada = true;
        }
    }

    // Avanza hasta encontrar un jugador que conserve territorios.
    do
    {
        turno.finalizarTurno(jugadores.size());

    } while (tablero.contarTerritorios(
                 jugadores[turno.obtenerPosicionJugadorActual()].obtenerColor()) == 0);

    return COMANDO_CORRECTO;
}

// USO DE IA - ALMACENAMIENTO DE PARTIDAS
//
// Base del trabajo:
// Se conservo la clase Partida de la Entrega 1 y se
// utilizaron las operaciones existentes de Tablero.
// El formato de almacenamiento corresponde al componente
// 2 del enunciado oficial de RISK.
//
// Referencias tecnicas para revisar la implementacion:
// https://en.cppreference.com/w/cpp/io/basic_ostringstream
// https://en.cppreference.com/w/cpp/io/basic_ostream/write
//
// Consulta redactada posteriormente (no es el prompt literal):
//
// "Estoy trabajando sobre la clase Partida que ya tenemos
// implementada desde la primera entrega. Para el segundo
// componente estoy integrando el guardado de partidas
// en texto y en un archivo comprimido con Huffman.
//
// Quiero revisar como organizar los datos de jugadores
// y territorios en una sola representacion de texto,
// siguiendo el formato que indica el profesor.
//
// Tambien quiero comprobar como reutilizar ese contenido
// en guardar y guardarComprimido, para evitar repetir
// codigo o modificar las funciones originales del juego.
//
// Ayudame a revisar la integracion, el manejo de archivos
// y las validaciones de error, manteniendo las estructuras
// y el estilo del proyecto."
//
// ChatGPT apoyo la organizacion y propuso codigo para las
// operaciones nuevas de almacenamiento. Las propuestas
// incorporadas fueron revisadas, integradas y probadas.

// construye el contenido que vamos a escribir en el archivo
// primero van los jugadores y despues los 42 territorios del tablero
string Partida::obtenerTextoPartida() const
{
    ostringstream contenido;

    // la primera linea indica cuantos jugadores hay en la partida
    contenido << jugadores.size();

    // conservamos el orden de los jugadores que se uso al inicializar
    for (size_t i = 0; i < jugadores.size(); i++)
    {
        contenido << '\n'
                  << jugadores[i].obtenerNombre() << " "
                  << jugadores[i].obtenerColor();
    }

    // Tablero ya sabe generar las lineas de sus territorios
    // asi evitamos repetir aqui la estructura de los continentes
    contenido << '\n'
              << tablero.obtenerTextoTerritorios();

    // devolvemos todo junto para reutilizarlo al comprimir
    return contenido.str();
}

// guarda el estado de jugadores y territorios en un archivo de texto
EstadoComando Partida::guardar(string nombreArchivo) const
{
    // no podemos guardar una partida que todavia no existe
    if (!inicializada)
    {
        return JUEGO_NO_INICIALIZADO;
    }

    string contenido = obtenerTextoPartida();

    // si no se pudo formar el contenido no creamos un archivo vacio
    if (contenido.empty())
    {
        return ARCHIVO_ERRONEO;
    }

    ofstream archivo(nombreArchivo.c_str(), ios::binary);

    if (!archivo.is_open())
    {
        return ARCHIVO_ERRONEO;
    }

    // escribimos todo el contenido tal como se genero
    // no agregamos otro salto de linea para conservar el formato original
    archivo.write(contenido.c_str(), contenido.size());

    archivo.close();

    // revisamos tambien si ocurrio un error durante la escritura
    if (!archivo.good())
    {
        return ARCHIVO_ERRONEO;
    }

    return COMANDO_CORRECTO;
}

// guarda el estado de la partida en un archivo comprimido con Huffman
EstadoComando Partida::guardarComprimido(string nombreArchivo) const
{
    // no se puede guardar una partida que todavia no fue inicializada
    if (!inicializada)
    {
        return JUEGO_NO_INICIALIZADO;
    }

    // usamos el mismo contenido que utiliza el guardado normal
    // asi ambos archivos representan exactamente el mismo estado del tablero
    string contenido = obtenerTextoPartida();

    if (contenido.empty())
    {
        return ARCHIVO_ERRONEO;
    }

    // Huffman se encarga de contar frecuencias, construir el arbol
    // generar codigos y escribir el encabezado y los bytes comprimidos
    if (!comprimirHuffman(contenido, nombreArchivo))
    {
        return ARCHIVO_ERRONEO;
    }

    return COMANDO_CORRECTO;
}

// Este procedimiento se desarrollo con apoyo de ChatGPT para la Entrega 3
// La solicitud fue integrar BFS con los TAD Grafo y Tablero que ya tiene RISK
// buscando el territorio propio mas cercano y sumando las unidades enemigas
EstadoComando Partida::costoConquista(string nombreJugador, string codigoTerritorio)
{
    // primero revisamos que la partida permita hacer una consulta
    EstadoComando estado = validarEstadoJuego();

    if (estado != COMANDO_CORRECTO)
    {
        return estado;
    }

    int posicionJugador = buscarPosicionJugador(nombreJugador);

    if (posicionJugador == -1)
    {
        return JUGADOR_NO_VALIDO;
    }

    int destino = grafo.buscarTerritorio(codigoTerritorio);

    if (destino == -1)
    {
        return TERRITORIO_NO_VALIDO;
    }

    string colorJugador = jugadores[posicionJugador].obtenerColor();
    int cantidad = grafo.cantidadTerritorios();

    // usamos los territorios del tablero porque ahi estan
    // los propietarios y las unidades actuales de cada uno
    vector<const Territorio *> datos(cantidad, nullptr);

    for (int i = 0; i < cantidad; i++)
    {
        datos[i] = tablero.buscarTerritorio(grafo.obtenerTerritorio(i));

        if (datos[i] == nullptr)
        {
            return SIN_RECORRIDO;
        }
    }

    // por ahora un territorio propio no se considera una conquista
    // esta decision se debe validar con el profesor
    if (datos[destino]->obtenerColorPropietario() == colorJugador)
    {
        return DESTINO_YA_CONTROLADO;
    }

    // actualizamos el costo de cada conexion segun el jugador
    // entrar a un territorio propio cuesta cero
    // entrar a uno enemigo cuesta las unidades que tiene
    for (int i = 0; i < cantidad; i++)
    {
        for (int j = 0; j < cantidad; j++)
        {
            if (!grafo.sonAdyacentes(i, j))
            {
                continue;
            }

            int costo = 0;

            if (datos[j]->obtenerColorPropietario() != colorJugador)
            {
                costo = datos[j]->obtenerUnidades();
            }

            grafo.establecerCosto(i, j, costo);
        }
    }

    // visitado evita recorrer varias veces el mismo territorio
    // siguiente recuerda por donde debemos avanzar hacia el destino
    vector<bool> visitado(cantidad, false);
    vector<int> siguiente(cantidad, -1);
    queue<int> pendientes;

    pendientes.push(destino);
    visitado[destino] = true;

    int origen = -1;

    // BFS empieza en el destino y revisa primero los vecinos cercanos
    while (!pendientes.empty() && origen == -1)
    {
        int actual = pendientes.front();
        pendientes.pop();

        // si encontramos un territorio propio ya tenemos un origen
        // BFS garantiza que no hay otro mas cercano en cantidad de conexiones
        if (datos[actual]->obtenerColorPropietario() == colorJugador)
        {
            origen = actual;
            break;
        }

        for (int vecino = 0; vecino < cantidad; vecino++)
        {
            // buscamos territorios que tengan conexion hacia el actual
            // asi podremos reconstruir el recorrido desde origen a destino
            if (!visitado[vecino] &&
                grafo.sonAdyacentes(vecino, actual))
            {
                visitado[vecino] = true;
                siguiente[vecino] = actual;
                pendientes.push(vecino);
            }
        }
    }

    // si no encontramos territorio propio no existe un origen valido
    if (origen == -1)
    {
        return SIN_RECORRIDO;
    }

    // reconstruimos el recorrido comenzando en el territorio propio
    vector<int> camino;
    int actual = origen;

    while (actual != -1)
    {
        camino.push_back(actual);

        if (actual == destino)
        {
            break;
        }

        actual = siguiente[actual];
    }

    if (camino.back() != destino)
    {
        return SIN_RECORRIDO;
    }

    // sumamos los costos de las conexiones que forman el recorrido
    // cada costo corresponde a las unidades enemigas del destino del tramo
    int costoTotal = 0;

    for (int i = 1; i < (int)camino.size(); i++)
    {
        int costo = grafo.obtenerCosto(camino[i - 1], camino[i]);

        if (costo < 0)
        {
            return SIN_RECORRIDO;
        }

        costoTotal += costo;
    }

    // presentamos el resultado con la estructura pedida en el enunciado
    cout << "(Comando correcto) Para conquistar el territorio "
         << codigoTerritorio << ", " << nombreJugador
         << " debe atacar desde "
         << grafo.obtenerTerritorio(origen)
         << ", pasando por los territorios ";

    for (int i = 1; i < (int)camino.size(); i++)
    {
        if (i > 1)
        {
            cout << ", ";
        }

        cout << grafo.obtenerTerritorio(camino[i]);
    }

    cout << ". Debe conquistar " << costoTotal;

    // usamos singular cuando solo hay una unidad enemiga
    if (costoTotal == 1)
    {
        cout << " unidad de ejercito." << endl;
    }
    else
    {
        cout << " unidades de ejercito." << endl;
    }

    return COMANDO_CORRECTO;
}

EstadoComando Partida::conquistaMasBarata(string nombreJugador)
{
    // comprobamos que la partida este lista y que el jugador exista
    EstadoComando estado = validarEstadoJuego();

    if (estado != COMANDO_CORRECTO)
    {
        return estado;
    }

    int posicionJugador = buscarPosicionJugador(nombreJugador);

    if (posicionJugador == -1)
    {
        return JUGADOR_NO_VALIDO;
    }

    string colorJugador = jugadores[posicionJugador].obtenerColor();
    int cantidad = grafo.cantidadTerritorios();
    vector<const Territorio *> datos(cantidad, nullptr);

    // el grafo tiene los codigos, pero Tablero tiene los propietarios y unidades
    for (int i = 0; i < cantidad; i++)
    {
        datos[i] = tablero.buscarTerritorio(grafo.obtenerTerritorio(i));

        if (datos[i] == nullptr)
        {
            return SIN_RECORRIDO;
        }
    }

    // los costos se actualizan porque las unidades pueden cambiar durante el juego
    for (int i = 0; i < cantidad; i++)
    {
        for (int j = 0; j < cantidad; j++)
        {
            if (!grafo.sonAdyacentes(i, j))
            {
                continue;
            }

            int costo = 0;

            // entrar a un territorio propio cuesta cero
            // entrar a uno enemigo cuesta las unidades que tiene
            if (datos[j]->obtenerColorPropietario() != colorJugador)
            {
                costo = datos[j]->obtenerUnidades();
            }

            grafo.establecerCosto(i, j, costo);
        }
    }

    // estructuras auxiliares para Dijkstra
    const long long INFINITO = LLONG_MAX / 4;

    vector<long long> distancia(cantidad, INFINITO);
    vector<bool> procesado(cantidad, false);
    vector<int> anterior(cantidad, -1);

    bool tieneTerritorio = false;

    // todos los territorios propios pueden servir como origen
    for (int i = 0; i < cantidad; i++)
    {
        if (datos[i]->obtenerColorPropietario() == colorJugador)
        {
            distancia[i] = 0;
            tieneTerritorio = true;
        }
    }

    if (!tieneTerritorio)
    {
        return SIN_RECORRIDO;
    }

    // recorremos los territorios para encontrar las distancias minimas
    for (int paso = 0; paso < cantidad; paso++)
    {
        int actual = -1;

        // buscamos el territorio pendiente que tenga la menor distancia
        for (int i = 0; i < cantidad; i++)
        {
            if (!procesado[i] && distancia[i] < INFINITO &&
                (actual == -1 || distancia[i] < distancia[actual]))
            {
                actual = i;
            }
        }

        // si no encontramos otro territorio alcanzable terminamos
        if (actual == -1)
        {
            break;
        }

        procesado[actual] = true;

        // intentamos mejorar las distancias de sus vecinos
        for (int vecino = 0; vecino < cantidad; vecino++)
        {
            if (procesado[vecino] ||
                !grafo.sonAdyacentes(actual, vecino))
            {
                continue;
            }

            int costo = grafo.obtenerCosto(actual, vecino);
            long long nuevaDistancia = distancia[actual] + costo;

            // si encontramos un camino mas barato lo guardamos
            if (nuevaDistancia < distancia[vecino])
            {
                distancia[vecino] = nuevaDistancia;
                anterior[vecino] = actual;
            }
        }
    }

    // buscamos el territorio enemigo con el menor costo acumulado
    int destino = -1;

    for (int i = 0; i < cantidad; i++)
    {
        if (datos[i]->obtenerColorPropietario() == colorJugador ||
            distancia[i] == INFINITO)
        {
            continue;
        }

        if (destino == -1 || distancia[i] < distancia[destino])
        {
            destino = i;
        }
    }

    if (destino == -1)
    {
        return SIN_RECORRIDO;
    }

    // seguimos los anteriores para reconstruir el camino desde el destino
    vector<int> caminoInverso;
    int actual = destino;

    while (actual != -1 && (int)caminoInverso.size() < cantidad)
    {
        caminoInverso.push_back(actual);

        if (datos[actual]->obtenerColorPropietario() == colorJugador)
        {
            break;
        }

        actual = anterior[actual];
    }

    // el recorrido debe terminar en un territorio del jugador
    if (caminoInverso.empty() ||
        datos[caminoInverso.back()]->obtenerColorPropietario() != colorJugador)
    {
        return SIN_RECORRIDO;
    }

    // invertimos el recorrido para mostrarlo desde el origen
    vector<int> camino;

    for (int i = (int)caminoInverso.size() - 1; i >= 0; i--)
    {
        camino.push_back(caminoInverso[i]);
    }

    string codigoOrigen = grafo.obtenerTerritorio(camino[0]);
    string codigoDestino = grafo.obtenerTerritorio(destino);

    cout << "(Comando correcto) La conquista mas barata es avanzar sobre el territorio "
         << codigoDestino << " desde el territorio " << codigoOrigen
         << ". Para conquistar el territorio " << codigoDestino
         << ", debe atacar desde " << codigoOrigen
         << ", pasando por los territorios ";

    for (int i = 1; i < (int)camino.size(); i++)
    {
        if (i > 1)
        {
            cout << ", ";
        }

        cout << grafo.obtenerTerritorio(camino[i]);
    }

    cout << ". Debe conquistar " << distancia[destino];

    // usamos singular cuando solo hay una unidad enemiga
    if (distancia[destino] == 1)
    {
        cout << " unidad de ejercito." << endl;
    }
    else
    {
        cout << " unidades de ejercito." << endl;
    }

    return COMANDO_CORRECTO;
}
