#include <iostream>
#include <string>
#include <vector>
#include <cctype>

struct DatosComando {
    std::string nombre;
    int minArgs;
    int maxArgs;
    std::string ayuda;
};

const std::vector<DatosComando> TABLA_COMANDOS = {

    {"inicializar", 1, 1,
     "Inicializa el juego desde un archivo. "
     "Uso: inicializar [archivo_inicio]"},

    {"obtener_unidades", 1, 1,
     "Realiza la obtencion y ubicacion de nuevas unidades para un jugador. "
     "Uso: obtener_unidades [nombre_jugador]"},

    {"atacar", 1, 1,
     "Realiza la fase de ataque del jugador. "
     "Uso: atacar [nombre_jugador]"},

    {"fortificar", 1, 1,
     "Realiza la fase de fortificacion del jugador. "
     "Uso: fortificar [nombre_jugador]"},

    {"estado_juego", 0, 0,
     "Muestra un resumen del estado actual del juego. "
     "Uso: estado_juego"},

    {"salir", 0, 0,
     "Termina la ejecucion de la aplicacion. "
     "Uso: salir"},

    {"guardar", 1, 1,
     "Guarda el estado actual del juego en un archivo de texto. "
     "Uso: guardar [nombre_archivo]"},

    {"guardar_comprimido", 1, 1,
     "Guarda el estado actual del juego en un archivo binario comprimido. "
     "Uso: guardar_comprimido [nombre_archivo]"},

    {"costo_conquista", 2, 2,
     "Calcula el costo y la secuencia de territorios para conquistar un territorio. "
     "Uso: costo_conquista [nombre_jugador] [territorio]"},

    {"conquista_mas_barata", 1, 1,
     "Calcula la conquista que implica el menor numero de unidades perdidas. "
     "Uso: conquista_mas_barata [nombre_jugador]"},

    {"ayuda", 0, 1,
     "Muestra la lista de comandos disponibles o la ayuda de un comando. "
     "Uso: ayuda o ayuda [comando]"}
};

bool buscarComando(const std::string& nombre, DatosComando& resultado) {

    for (const DatosComando& comando : TABLA_COMANDOS) {

        if (comando.nombre == nombre) {
            resultado = comando;
            return true;
        }
    }

    return false;
}

bool esEnteroPositivo(const std::string& texto) {

    if (texto.empty()) {
        return false;
    }

    for (char caracter : texto) {

        if (!std::isdigit(static_cast<unsigned char>(caracter))) {
            return false;
        }
    }

    return true;
}

bool esTerritorioValido(const std::string& territorio) {

    if (territorio.size() < 3) {
        return false;
    }

      std::size_t punto = territorio.find('.');

    if (punto == std::string::npos ||
        punto == 0 ||
        punto == territorio.size() - 1 ||
        territorio.find('.', punto + 1) != std::string::npos) {
        return false;
    }

    std::string continente = territorio.substr(0, punto);
    std::string numero = territorio.substr(punto + 1);

    if (!esEnteroPositivo(continente) || !esEnteroPositivo(numero)) {
        return false;
    }

    int c = std::stoi(continente);
    int t = std::stoi(numero);

      const int territoriosPorContinente[] = {
        0,  
        9,  
        4,  
        7,  
        6,  
        12, 
        4   
    };

    if (c < 1 || c > 6) {
        return false;
    }

    return t >= 1 && t <= territoriosPorContinente[c];
}

bool esNombreJugadorValido(const std::string& nombre) {

    if (nombre.empty() || nombre.size() > 8) {
        return false;
    }

    for (char caracter : nombre) {

        if (std::isspace(static_cast<unsigned char>(caracter))) {
            return false;
        }
    }

    return true;
}

bool esNombreArchivoValido(const std::string& nombre) {

    if (nombre.empty()) {
        return false;
    }

    for (char caracter : nombre) {

        if (std::isspace(static_cast<unsigned char>(caracter))) {
            return false;
        }
    }

    return true;
}

bool manejarEntrada(const std::string& linea,
                    std::vector<std::string>& tokens) {

    tokens.clear();

    std::string token;
    char comillaAbierta = '\0';

    for (std::size_t i = 0; i < linea.size(); ++i) {

        char c = linea[i];

          if (c == '\'' || c == '"') {

            if (comillaAbierta == '\0') {
                comillaAbierta = c;
            }
            else if (comillaAbierta == c) {
                comillaAbierta = '\0';
            }
            else {
                 token += c;
            }

            continue;
        }

        if (std::isspace(static_cast<unsigned char>(c)) &&
            comillaAbierta == '\0') {

            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }

            continue;
        }

        token += c;
    }

    if (comillaAbierta != '\0') {
        std::cout << "(Error de sintaxis) Se detecto una comilla abierta sin cerrar."
                  << std::endl;
        tokens.clear();
        return false;
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return true;
}

void mostrarAyudaGeneral() {

    std::cout << "Comandos disponibles:" << std::endl;

    for (const DatosComando& comando : TABLA_COMANDOS) {
        std::cout << " - " << comando.nombre << std::endl;
    }
}

void mostrarAyudaComando(const std::string& nombre) {

    DatosComando comando;

    if (!buscarComando(nombre, comando)) {
        std::cout << "(Comando invalido) El comando '" << nombre
                  << "' no existe." << std::endl;
        return;
    }

    std::cout << comando.ayuda << std::endl;
}

bool validarFormatoParametros(const std::string& comando,
                              const std::vector<std::string>& argumentos) {

    if (comando == "inicializar") {

        if (!esNombreArchivoValido(argumentos[0])) {
            std::cout << "(Formato erroneo) El nombre del archivo no es valido."
                      << std::endl;
            return false;
        }
    }

    else if (comando == "obtener_unidades" ||
             comando == "atacar" ||
             comando == "fortificar" ||
             comando == "conquista_mas_barata") {

        if (!esNombreJugadorValido(argumentos[0])) {
            std::cout << "(Formato erroneo) El nombre del jugador debe ser "
                         "una palabra de maximo 8 caracteres y sin espacios."
                      << std::endl;
            return false;
        }
    }

    else if (comando == "guardar" ||
             comando == "guardar_comprimido") {

        if (!esNombreArchivoValido(argumentos[0])) {
            std::cout << "(Formato erroneo) El nombre del archivo no es valido."
                      << std::endl;
            return false;
        }
    }

    else if (comando == "costo_conquista") {

        if (!esNombreJugadorValido(argumentos[0])) {
            std::cout << "(Formato erroneo) El nombre del jugador debe ser "
                         "una palabra de maximo 8 caracteres y sin espacios."
                      << std::endl;
            return false;
        }

        if (!esTerritorioValido(argumentos[1])) {
            std::cout << "(Formato erroneo) El codigo del territorio '"
                      << argumentos[1]
                      << "' no corresponde a un territorio valido."
                      << std::endl;
            return false;
        }
    }

    return true;
}

void procesarAyuda(const std::vector<std::string>& argumentos) {

    if (argumentos.empty()) {
        mostrarAyudaGeneral();
    }
    else {
        mostrarAyudaComando(argumentos[0]);
    }
}