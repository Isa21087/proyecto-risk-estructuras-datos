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
vector <Comandos> estrategias;

vector <vector <Comandos>> categorias = {config, almacenamiento, estrategias};

int main(){


    int elegir = -1;

    do {
        cout<<"###############-COMANDOS-###############"<<endl;
        cout<<"CONFIG JUEGO"<<endl;
        cout<<"1. inicializar"<<endl;
        cout<<"2. obtener_unidades"<<endl;
        cout<<"3. atacar"<<endl;
        cout<<"4. foritficar"<<endl;
        cout<<"5. estado_juego"<<endl;
        cout<<"0. salir"<<endl;
        cout<<"ALMACENAMIENTO"<<endl;
        cout<<"6. guardar"<<endl;
        cout<<"7. guardar_comprimido"<<endl;
        cout<<"8. inicializar"<<endl;
        cout<<"ESTRATEGIAS DE JUEGO"<<endl;
        cout<<"9. costo_conquista"<<endl;
        cout<<"10. conquista_mas_barata"<<endl;


        cin>>elegir;
        switch (elegir){
            case '1':
                cout<<"===============Inicializar==============="<<endl;
                cout<<"Inicializa el juego a partir de la información contenida en el archivo .txt,"<<endl;
                cout<<"dejando la interfaz del juego lista para recibir los turnos de cada jugador"<<endl;
            break;
            case '2':
                cout<<"===============Obtener Unidades==============="<<endl;
                cout<<" *Informa cuantas unidades adicionales puede reclamar el jugador"<<endl;
                cout<<" *Donde asignar las  unidades y cuantas desea en cada territorio" <<endl;
            break;



        }

    }while(elegir!= 0);
    elegir = -1;

}