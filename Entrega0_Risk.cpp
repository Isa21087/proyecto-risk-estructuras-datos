#include <iostream>
#include <vector>
// el que lea esto le deseo el mejor dia :)
using namespace std;


struct Comandos{
    string nombre;
    string ayuda;
    int minArgs;
    int maxArgs;
};

vector <Comandos> config={
    {"Inicializar", "Inicializa el juego apartir del archivo .txt elegido, "
                    "en caso de no existir el archivo se crea", 1, 1},
    {"Obtener unidades", "Informa cuantas unidades adicionales puede reclamar el jugador"
                         "Y pregunta donde asignar estas tropa", 1, 1},
    {"Atacar [Nombre Jugador]",  "Se pregunta desde que territorio (que actualmente tiene unidades del jugador actual)"
                "se quiere atacar y hacia que territorio se desea atacar."
                "Luego se informa los valores obtenidos con los dados y la cantidad de unidades "
                "que se ganan o pierden."
                "Este proceso se puede repetir hasta que alguno de los dos territorios se quede sin unidades, "
                "o que el atacante desee detenerse.", 1, 1},
    {"Fortificar [Nombre Jugador]", "Pregunta al jugador los territorios vecinos que desea seleccionar para la fortificación, "
                                    "así como la cantidad de unidades que se trasladarán de uno al otro",1,1},
    {"Estado de juego", "Presenta en pantalla un resumen de la situación actual del juego: "
                        "número de jugadores, nombres y colores de cada uno, jugador con el turno actual, "
                        "y lista de los territorios con el color del jugador que lo controla y la cantidad "
                        "de unidades que hay ubicadas en cada uno.",1,1},
    {"Salir", "Termina la ejecucion de la aplicacion",1,1}};

vector <Comandos> almacenamiento= {
    {"Guardar", "El estado actual del juego es guardado en un archivo de texto, con el mismo formato del"
                "archivo usado para la inicialización del juego. Note que este comando guarda un archivo "
                "de texto plano, sin codificación.",1,1},
    {"Guardar coprimido", "El estado actual del juego es guardado en un archivo binario con la información, " 
                          "con el mismo formato del archivo usado para la inicialización del juego, comprimida.",1,1},
    {"Inicializar [Nombre archivo]", "Inicializa el juego con los datos contenidos en el archivo identificado por [Nombre Archivo]. "
                                     "El archivo debería contener la información descrita en el comando guardar. "
                                     "El comando debe poder inicializar el juego desde un archivo de juego normal o un archivo binario con los "
                                     "datos comprimidos.", 1,1}};
vector <Comandos> estrategias = {
    {"Costo conquista [Nombre jugador] [Territorio]", "Se calcula el costo y la secuencia de territorios a ser conquistados" 
                                                      "para lograr controlar el territorio dado por el jugador acutal. El territorio desde donde" 
                                                      "debe atacar debe ser aquel que el jugador tenga controlado más cerca al dado por el jugador. ",1,1},
    {"Conquista mas barata [Nombre jugador]", "De todos los territorios posibles, el programa calcula aquel que pueda implicar un menor número de unidades"
                                              "de ejército perdidas. Esta información se analiza desde el punto de vista del jugador [Nombre jugador actual].", 1,1}};

vector <vector <Comandos>> categorias = {config, almacenamiento, estrategias};

int main(){



}