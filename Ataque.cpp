#include <iostream>
#include <vector>
#include <sstream>
#include "Ataque.h"
#include "Jugador.h"
#include "Tablero.h"
#include "Territorio.h"

using namespace std;

//Crea el ataque con los dados del atacante y del defensor.
Ataque::Ataque()
{
}

//Verifica si los territorios seleccionados cumplen las condiciones para atacar.
//El & permite trabajar con el tablero original sin crear una copia.
//El const evita que esta funcion pueda modificar el tablero.
bool Ataque::configuracionValida(
    string codigoOrigen,
    string codigoDestino,
    string colorAtacante,
    const Tablero& tablero
) const {

    //buscarTerritorio retorna la direccion del territorio encontrado.
    //Por eso se usan punteros (*) y no copias del territorio.
    const Territorio* origen = tablero.buscarTerritorio(codigoOrigen);
    const Territorio* destino = tablero.buscarTerritorio(codigoDestino);

    //Se verifica que los dos territorios existan dentro del tablero.
    if(origen == NULL || destino == NULL){

        return false;

    }

    //Se verifica que el territorio origen pertenezca al jugador atacante.
    if(origen->obtenerColorPropietario() != colorAtacante){

        return false;

    }

    //Se verifica que el territorio destino sea de otro jugador.
    if(destino->obtenerColorPropietario() == colorAtacante){

        return false;

    }

    //Se verifica que los territorios sean vecinos.
    if(!tablero.sonVecinos(codigoOrigen,codigoDestino)){

        return false;

    }

    //El territorio origen debe tener mas de una unidad
    //para poder realizar o continuar un ataque.
    if(origen->obtenerUnidades() <= 1){

        return false;

    }

    return true;

}


//Ejecuta el ataque entre dos territorios.
ResultadoAtaque Ataque::ejecutar(
    Jugador& jugadorAtacante,
    Tablero& tablero
){

    //Se inicializa el resultado indicando que todavia no ocurre nada.
    ResultadoAtaque resultado;

    resultado.ataqueRealizado = false;
    resultado.conquistoTerritorio = false;

    string codigoOrigen;
    string codigoDestino;

    //Se muestra el tablero para que el jugador pueda escoger
    //desde donde atacar y a que territorio atacar.
    tablero.mostrarTablero();

    cout << "Ingrese el codigo del territorio desde el que desea atacar: ";
    if(!getline(cin, codigoOrigen)){
        return resultado;
    }

    cout << "Ingrese el codigo del territorio que desea atacar: ";

    if(!getline(cin, codigoDestino)){
        return resultado;
    }


    //Se verifica que la configuracion del ataque sea valida.
    if(!configuracionValida(
        codigoOrigen,
        codigoDestino,
        jugadorAtacante.obtenerColor(),
        tablero
    )){

        cout << "La configuracion del ataque no es valida." << endl;

        return resultado;

    }


    //Se buscan nuevamente los territorios pero sin const,
    //porque durante el ataque las unidades pueden cambiar.
    Territorio* origen = tablero.buscarTerritorio(codigoOrigen);
    Territorio* destino = tablero.buscarTerritorio(codigoDestino);

    bool continuar = true;


    //El ataque continua mientras:
    //- El jugador quiera continuar.
    //- El origen tenga mas de una unidad.
    //- El destino tenga unidades.
    while(
        continuar &&
        origen->obtenerUnidades() > 1 &&
        destino->obtenerUnidades() > 0
    ){

        //Se determina la cantidad de dados que puede lanzar el atacante.
        int cantidadDadosAtacante;

        if(origen->obtenerUnidades() >= 4){

            cantidadDadosAtacante = 3;

        }
        else if(origen->obtenerUnidades() == 3){

            cantidadDadosAtacante = 2;

        }
        else{

            cantidadDadosAtacante = 1;

        }


        //Se determina la cantidad de dados que puede lanzar el defensor.
        int cantidadDadosDefensor;

        if(destino->obtenerUnidades() >= 2){

            cantidadDadosDefensor = 2;

        }
        else{

            cantidadDadosDefensor = 1;

        }


        //Se lanzan los dados de ambos jugadores.
        dadosAtacante.lanzar(cantidadDadosAtacante);
        dadosDefensor.lanzar(cantidadDadosDefensor);

        resultado.ataqueRealizado = true;


        //Se guardan los dados organizados de mayor a menor
        //para realizar las comparaciones.
        vector<int> mayoresAtacante =
            dadosAtacante.obtenerMayores(cantidadDadosAtacante);

        vector<int> mayoresDefensor =
            dadosDefensor.obtenerMayores(cantidadDadosDefensor);


        cout << "Dados del atacante: ";

        for(int i = 0; i < cantidadDadosAtacante; i++){

            cout << mayoresAtacante[i] << " ";

        }

        cout << endl;


        cout << "Dados del defensor: ";

        for(int i = 0; i < cantidadDadosDefensor; i++){

            cout << mayoresDefensor[i] << " ";

        }

        cout << endl;
        //Se realizan las comparaciones entre los dados de atacante y defensor.
//Solo se comparan los dados que ambos jugadores tengan disponibles.
        int cantidadComparaciones = cantidadDadosAtacante;

        if(cantidadDadosDefensor < cantidadComparaciones){

            cantidadComparaciones = cantidadDadosDefensor;

        }


        //Se comparan los dados empezando por los valores mas altos.
        for(int i = 0; i < cantidadComparaciones; i++){

            cout << "Comparacion " << i + 1 << ": "
                 << mayoresAtacante[i] << " contra "
                 << mayoresDefensor[i] << endl;


            //Si el dado del atacante es mayor,
            //el defensor pierde una unidad.
            if(mayoresAtacante[i] > mayoresDefensor[i]){

                destino->retirarUnidades(1,0);

                cout << "El defensor pierde una unidad." << endl;

            }
            else{

                //Si el defensor gana o hay empate,
                //el atacante pierde una unidad.
                //Se deja minimo una unidad en el territorio origen.
                origen->retirarUnidades(1,1);

                cout << "El atacante pierde una unidad." << endl;

            }

        }


        cout << "Unidades del atacante: "
             << origen->obtenerUnidades() << endl;

        cout << "Unidades del defensor: "
             << destino->obtenerUnidades() << endl;



        //Se verifica si el territorio defensor quedo sin unidades.
        //En este caso el jugador atacante conquista el territorio.
        if(destino->obtenerUnidades() == 0){

            cout << "El territorio fue conquistado." << endl;


            int cantidadTraslado = 0;

            // Debe quedar al menos una unidad en el origen.
            int maximoTraslado = origen->obtenerUnidades() - 1;

            cout << "Puede trasladar entre 1 y "
                 << maximoTraslado
                 << " unidades al territorio conquistado." << endl;

            bool cantidadValida = false;

            while(!cantidadValida){

                cout << "Cantidad de unidades que desea trasladar: ";

                string linea;

                // Si se cierra la entrada, completa la conquista con el minimo.
                if(!getline(cin, linea)){

                    cantidadTraslado = 1;
                    cantidadValida = true;

                    cout << "La entrada fue cerrada. Se trasladara una unidad para completar la conquista." << endl;

                }
                else{

                    istringstream entrada(linea);
                    string datoExtra;

                    if(!(entrada >> cantidadTraslado)){
                        cout << "Debe escribir una cantidad entera." << endl;
                    }
                    else if(entrada >> datoExtra){
                        cout << "Debe escribir solo una cantidad entera." << endl;
                    }
                    else if(cantidadTraslado < 1 ||
                            cantidadTraslado > maximoTraslado){

                        cout << "Ingrese una cantidad entre 1 y "
                             << maximoTraslado << "." << endl;

                    }
                    else{
                        cantidadValida = true;
                    }

                }

            }

            //Se retiran primero las unidades del territorio origen.
            origen->retirarUnidades(cantidadTraslado,1);


            //Se cambia el propietario del territorio conquistado
            //y se agregan las unidades trasladadas.
            if(tablero.cambiarPropietario(
                codigoDestino,
                jugadorAtacante.obtenerColor(),
                cantidadTraslado
            )){

                resultado.conquistoTerritorio = true;

                cout << "Nuevo propietario del territorio: "
                     << jugadorAtacante.obtenerColor() << endl;

            }


            //Cuando se conquista termina este ataque.
            continuar = false;

        }


        //Si no se ha conquistado el territorio,
        //el jugador puede decidir si continua atacando.
        else if(origen->obtenerUnidades() > 1){

            string respuesta;

            cout << "Desea continuar atacando este territorio? (s/n): ";

            if(!getline(cin, respuesta)){
                return resultado;
            }

            while(respuesta != "s" && respuesta != "S" && respuesta != "n" && respuesta != "N"){

                cout << "Escriba s para continuar o n para terminar: ";

                if(!getline(cin, respuesta)){
                    return resultado;
                }

            }

            continuar = (respuesta == "s" || respuesta == "S");

        }


        //Si el territorio origen queda con una sola unidad,
        //el jugador ya no puede continuar atacando.
        else{

            cout << "No hay suficientes unidades para continuar el ataque." << endl;

            continuar = false;

        }


    }


    //Se retorna el resultado final del ataque.
    return resultado;

}