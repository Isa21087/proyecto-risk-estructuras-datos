#include <iostream>
#include "Tablero.h"

Tablero::Tablero()
{
}

void Tablero::inicializarEstructura() { //crea el tablero de juego
    continentes.clear();//inicializa todo slos continentes vacios
    // ===== Continentes =====
    Continente americaDelNorte("1", "America del Norte", 5);
    Continente americaDelSur("2", "America del Sur", 2);
    Continente europa("3", "Europa", 5);
    Continente africa("4", "Africa", 3);
    Continente asia("5", "Asia", 7);
    Continente oceania("6", "Oceania", 2);

    // ===== 1. America del Norte =====
    Territorio t1_1("1.1", "Alaska", "1");
    Territorio t1_2("1.2", "Alberta", "1");
    Territorio t1_3("1.3", "America Central", "1");
    Territorio t1_4("1.4", "Estados Unidos Orientales", "1");
    Territorio t1_5("1.5", "Groenlandia", "1");
    Territorio t1_6("1.6", "Territorio Noroccidental", "1");
    Territorio t1_7("1.7", "Ontario", "1");
    Territorio t1_8("1.8", "Quebec", "1");
    Territorio t1_9("1.9", "Estados Unidos Occidentales", "1");

    t1_1.agregarVecino("1.6"); t1_1.agregarVecino("1.2"); t1_1.agregarVecino("5.6");
    t1_2.agregarVecino("1.1"); t1_2.agregarVecino("1.6"); t1_2.agregarVecino("1.7"); t1_2.agregarVecino("1.9");
    t1_3.agregarVecino("1.9"); t1_3.agregarVecino("2.4");
    t1_4.agregarVecino("1.7"); t1_4.agregarVecino("1.8"); t1_4.agregarVecino("1.9"); t1_4.agregarVecino("1.3");
    t1_5.agregarVecino("1.6"); t1_5.agregarVecino("1.7"); t1_5.agregarVecino("1.8"); t1_5.agregarVecino("3.2");
    t1_6.agregarVecino("1.1"); t1_6.agregarVecino("1.2"); t1_6.agregarVecino("1.5"); t1_6.agregarVecino("1.7");
    t1_7.agregarVecino("1.2"); t1_7.agregarVecino("1.6"); t1_7.agregarVecino("1.5"); t1_7.agregarVecino("1.8"); t1_7.agregarVecino("1.4"); t1_7.agregarVecino("1.9");
    t1_8.agregarVecino("1.5"); t1_8.agregarVecino("1.7"); t1_8.agregarVecino("1.4");
    t1_9.agregarVecino("1.2"); t1_9.agregarVecino("1.6"); t1_9.agregarVecino("1.7"); t1_9.agregarVecino("1.4"); t1_9.agregarVecino("1.3");

    americaDelNorte.agregarTerritorio(t1_1);
    americaDelNorte.agregarTerritorio(t1_2);
    americaDelNorte.agregarTerritorio(t1_3);
    americaDelNorte.agregarTerritorio(t1_4);
    americaDelNorte.agregarTerritorio(t1_5);
    americaDelNorte.agregarTerritorio(t1_6);
    americaDelNorte.agregarTerritorio(t1_7);
    americaDelNorte.agregarTerritorio(t1_8);
    americaDelNorte.agregarTerritorio(t1_9);

    // ===== 2. America del Sur =====
    Territorio t2_1("2.1", "Argentina", "2");
    Territorio t2_2("2.2", "Brasil", "2");
    Territorio t2_3("2.3", "Peru", "2");
    Territorio t2_4("2.4", "Venezuela", "2");

    t2_1.agregarVecino("2.3"); t2_1.agregarVecino("2.2");
    t2_2.agregarVecino("2.1"); t2_2.agregarVecino("2.3"); t2_2.agregarVecino("2.4"); t2_2.agregarVecino("4.5");
    t2_3.agregarVecino("2.1"); t2_3.agregarVecino("2.2"); t2_3.agregarVecino("2.4");
    t2_4.agregarVecino("2.2"); t2_4.agregarVecino("2.3"); t2_4.agregarVecino("1.3");

    americaDelSur.agregarTerritorio(t2_1);
    americaDelSur.agregarTerritorio(t2_2);
    americaDelSur.agregarTerritorio(t2_3);
    americaDelSur.agregarTerritorio(t2_4);

    // ===== 3. Europa =====
    Territorio t3_1("3.1", "Gran Bretana", "3");
    Territorio t3_2("3.2", "Islandia", "3");
    Territorio t3_3("3.3", "Europa del Norte", "3");
    Territorio t3_4("3.4", "Escandinavia", "3");
    Territorio t3_5("3.5", "Europa del Sur", "3");
    Territorio t3_6("3.6", "Ucrania", "3");
    Territorio t3_7("3.7", "Europa Occidental", "3");

    t3_1.agregarVecino("3.2"); t3_1.agregarVecino("3.4"); t3_1.agregarVecino("3.3"); t3_1.agregarVecino("3.7");
    t3_2.agregarVecino("1.5"); t3_2.agregarVecino("3.1"); t3_2.agregarVecino("3.4");
    t3_3.agregarVecino("3.1"); t3_3.agregarVecino("3.4"); t3_3.agregarVecino("3.6"); t3_3.agregarVecino("3.5"); t3_3.agregarVecino("3.7");
    t3_4.agregarVecino("3.2"); t3_4.agregarVecino("3.1"); t3_4.agregarVecino("3.3"); t3_4.agregarVecino("3.6");
    t3_5.agregarVecino("3.7"); t3_5.agregarVecino("3.3"); t3_5.agregarVecino("3.6"); t3_5.agregarVecino("4.3"); t3_5.agregarVecino("4.2"); t3_5.agregarVecino("5.7");
    t3_6.agregarVecino("3.4"); t3_6.agregarVecino("3.3"); t3_6.agregarVecino("3.5"); t3_6.agregarVecino("5.7"); t3_6.agregarVecino("5.11"); t3_6.agregarVecino("5.1");
    t3_7.agregarVecino("3.1"); t3_7.agregarVecino("3.3"); t3_7.agregarVecino("3.5"); t3_7.agregarVecino("4.5");

    europa.agregarTerritorio(t3_1);
    europa.agregarTerritorio(t3_2);
    europa.agregarTerritorio(t3_3);
    europa.agregarTerritorio(t3_4);
    europa.agregarTerritorio(t3_5);
    europa.agregarTerritorio(t3_6);
    europa.agregarTerritorio(t3_7);

    // ===== 4. Africa =====
    Territorio t4_1("4.1", "Congo", "4");
    Territorio t4_2("4.2", "Africa Oriental", "4");
    Territorio t4_3("4.3", "Egipto", "4");
    Territorio t4_4("4.4", "Madagascar", "4");
    Territorio t4_5("4.5", "Africa del Norte", "4");
    Territorio t4_6("4.6", "Africa del Sur", "4");

    t4_1.agregarVecino("4.2"); t4_1.agregarVecino("4.5"); t4_1.agregarVecino("4.6");
    t4_2.agregarVecino("4.3"); t4_2.agregarVecino("4.1"); t4_2.agregarVecino("4.5"); t4_2.agregarVecino("4.6"); t4_2.agregarVecino("4.4"); t4_2.agregarVecino("5.7");
    t4_3.agregarVecino("3.5"); t4_3.agregarVecino("3.7"); t4_3.agregarVecino("4.5"); t4_3.agregarVecino("4.2"); t4_3.agregarVecino("5.7");
    t4_4.agregarVecino("4.2"); t4_4.agregarVecino("4.6");
    t4_5.agregarVecino("2.2"); t4_5.agregarVecino("3.7"); t4_5.agregarVecino("4.3"); t4_5.agregarVecino("4.1"); t4_5.agregarVecino("4.2");
    t4_6.agregarVecino("4.1"); t4_6.agregarVecino("4.2"); t4_6.agregarVecino("4.4");

    africa.agregarTerritorio(t4_1);
    africa.agregarTerritorio(t4_2);
    africa.agregarTerritorio(t4_3);
    africa.agregarTerritorio(t4_4);
    africa.agregarTerritorio(t4_5);
    africa.agregarTerritorio(t4_6);

    // ===== 5. Asia =====
    Territorio t5_1("5.1", "Afghanistan", "5");
    Territorio t5_2("5.2", "China", "5");
    Territorio t5_3("5.3", "India", "5");
    Territorio t5_4("5.4", "Irkutsk", "5");
    Territorio t5_5("5.5", "Japon", "5");
    Territorio t5_6("5.6", "Kamchatka", "5");
    Territorio t5_7("5.7", "Medio Oriente", "5");
    Territorio t5_8("5.8", "Mongolia", "5");
    Territorio t5_9("5.9", "Siam", "5");
    Territorio t5_10("5.10", "Siberia", "5");
    Territorio t5_11("5.11", "Ural", "5");
    Territorio t5_12("5.12", "Yakutsk", "5");

    t5_1.agregarVecino("3.6"); t5_1.agregarVecino("5.11"); t5_1.agregarVecino("5.2"); t5_1.agregarVecino("5.3"); t5_1.agregarVecino("5.7");
    t5_2.agregarVecino("5.1"); t5_2.agregarVecino("5.11"); t5_2.agregarVecino("5.10"); t5_2.agregarVecino("5.8"); t5_2.agregarVecino("5.9"); t5_2.agregarVecino("5.3");
    t5_3.agregarVecino("5.1"); t5_3.agregarVecino("5.7"); t5_3.agregarVecino("5.9"); t5_3.agregarVecino("5.2");
    t5_4.agregarVecino("5.10"); t5_4.agregarVecino("5.8"); t5_4.agregarVecino("5.6");
    t5_5.agregarVecino("5.6"); t5_5.agregarVecino("5.8");
    t5_6.agregarVecino("5.4"); t5_6.agregarVecino("5.8"); t5_6.agregarVecino("5.5"); t5_6.agregarVecino("1.1"); t5_6.agregarVecino("5.12");
    t5_7.agregarVecino("3.5"); t5_7.agregarVecino("3.6"); t5_7.agregarVecino("4.3"); t5_7.agregarVecino("4.2"); t5_7.agregarVecino("5.1"); t5_7.agregarVecino("5.3");
    t5_8.agregarVecino("5.10"); t5_8.agregarVecino("5.4"); t5_8.agregarVecino("5.6"); t5_8.agregarVecino("5.5"); t5_8.agregarVecino("5.2");
    t5_9.agregarVecino("5.3"); t5_9.agregarVecino("5.2"); t5_9.agregarVecino("6.2");
    t5_10.agregarVecino("5.11"); t5_10.agregarVecino("5.4"); t5_10.agregarVecino("5.8"); t5_10.agregarVecino("5.2");
    t5_11.agregarVecino("3.6"); t5_11.agregarVecino("5.1"); t5_11.agregarVecino("5.2"); t5_11.agregarVecino("5.10");
    t5_12.agregarVecino("5.4"); t5_12.agregarVecino("5.6");

    asia.agregarTerritorio(t5_1);
    asia.agregarTerritorio(t5_2);
    asia.agregarTerritorio(t5_3);
    asia.agregarTerritorio(t5_4);
    asia.agregarTerritorio(t5_5);
    asia.agregarTerritorio(t5_6);
    asia.agregarTerritorio(t5_7);
    asia.agregarTerritorio(t5_8);
    asia.agregarTerritorio(t5_9);
    asia.agregarTerritorio(t5_10);
    asia.agregarTerritorio(t5_11);
    asia.agregarTerritorio(t5_12);

    // ===== 6. Oceania =====
    Territorio t6_1("6.1", "Australia Oriental", "6");
    Territorio t6_2("6.2", "Indonesia", "6");
    Territorio t6_3("6.3", "Nueva Guinea", "6");
    Territorio t6_4("6.4", "Australia Occidental", "6");

    t6_1.agregarVecino("6.4"); t6_1.agregarVecino("6.3");
    t6_2.agregarVecino("5.9"); t6_2.agregarVecino("6.3"); t6_2.agregarVecino("6.4");
    t6_3.agregarVecino("6.1"); t6_3.agregarVecino("6.4"); t6_3.agregarVecino("6.2");
    t6_4.agregarVecino("6.1"); t6_4.agregarVecino("6.2"); t6_4.agregarVecino("6.3");

    oceania.agregarTerritorio(t6_1);
    oceania.agregarTerritorio(t6_2);
    oceania.agregarTerritorio(t6_3);
    oceania.agregarTerritorio(t6_4);

    // ===== Ensamblado final =====
    continentes.push_back(americaDelNorte);
    continentes.push_back(americaDelSur);
    continentes.push_back(europa);
    continentes.push_back(africa);
    continentes.push_back(asia);
    continentes.push_back(oceania);
}

Territorio* Tablero::buscarTerritorio(string codigo){
     vector<Continente>::iterator buscar = continentes.begin();
     for(; buscar != continentes.end();++buscar){ //Se busca dentro del vector de continentes
        Territorio* territorio = buscar->buscarTerritorio(codigo);
        if(territorio != NULL){ // como el iterador es de tipo continente puede buscar un territorio
            return territorio; //retorna el territrio buscado
        }
     }
     return NULL;
}

const Territorio* Tablero::buscarTerritorio(string codigo) const{
     vector<Continente>::const_iterator buscar = continentes.begin();
     for(; buscar != continentes.end();++buscar){ //Se busca dentro del vector de continentes
        const Territorio* territorio = buscar->buscarTerritorio(codigo);
        if(territorio != NULL){ // como el iterador es de tipo continente puede buscar un territorio
            return territorio; //retorna el territrio buscado
        }
     }
     return NULL;
}

    bool Tablero::existeTerritorio(string codigo) const{

        if(buscarTerritorio(codigo) == NULL){
            return false;
        }

        return true;
    }

    //inicializa los territorios al inicio del juego / da los territorios iniciales para cada jugador
    bool Tablero::configurarTerritorio(string codigo, string colorPropietario, int unidades){
        
        if(!buscarTerritorio(codigo)){//valida que exista el territorio
            return false;
        }
        Territorio* territorio = buscarTerritorio(codigo);//crea un territorio

        territorio->asignarPropietario(colorPropietario);//le asigna un propietario al territorio
        territorio->asignarUnidades(unidades);//le asigna unidades al territorio
        return true;
    }

    bool Tablero::sonVecinos(string codigoOrigen, string codigoDestino) const{
        if(!existeTerritorio(codigoOrigen)){//verifica si existe el territorio del que se va a comparar
            return false;
        }

        if(!existeTerritorio(codigoDestino)){//verifica si existe el territorio comparado
            return false;
        }

        //en caso que exista el territorio
    const Territorio* territorio = buscarTerritorio(codigoOrigen);  
    //se usa la funcion de esVecino para verificar si el segundo codigo hace parte de los vecinos del territorio     
    return territorio->esVecino(codigoDestino);                        
    }
    //Saver cuantos territorios tiene el jugador
    int Tablero::contarTerritorios(string colorJugador) const{
        int cont=0;
        //Entra en cada territorio que hay dentro del mapa
        vector<Continente>::const_iterator buscar = continentes.begin();
        for(; buscar != continentes.end() ; ++buscar){
            //Crea un alias del vector territorio de continente para que no se duplique de manera local haciendolo mas eficiente
            const vector<Territorio>& territorios = buscar->obtenerTerritorios();
            vector<Territorio>::const_iterator buscarPropietario = territorios.begin();
            //Busca todos los territorios que tiene el jugador entre nada uno de los continentes
            for(; buscarPropietario != territorios.end(); ++buscarPropietario){
                if(buscarPropietario->obtenerColorPropietario() == colorJugador){
                    ++cont;
                }
            }
        }
        //devuelve la cantidad total de territorios que tiene el jugador en todo el tablero
        return cont;
    }
    //Saber cuantas unidades totales tiene el juador
    int Tablero::sumarUnidades(string colorJugador) const{
        int unds=0;
        //Entra en cada territorio que hay dentro del mapa
        vector<Continente>::const_iterator buscar = continentes.begin();
        for(; buscar != continentes.end() ; ++buscar){
            //Crea un alias del vector territorio de continente para que no se duplique de manera local haciendolo mas eficiente
            const vector<Territorio>& territorios = buscar->obtenerTerritorios();
            vector<Territorio>::const_iterator buscarPropietario = territorios.begin();
            //busca todos los territorios que tiene el jugador y va sacando la cantidad de unidades que hay en cada uno de ellos
            for(; buscarPropietario != territorios.end(); ++buscarPropietario){
                if(buscarPropietario->obtenerColorPropietario() == colorJugador){
                    unds += buscarPropietario->obtenerUnidades();
                }
            }
        }
        //devuelve la cantidad total de unidades que tiene el jugador en todo el tablero
        return unds;    
    }

    int Tablero::calcularBonificacionContinentes(string colorJugador) const{
        //Entra dentro de cada uno de los continentes
        int bonificacion=0;
        vector<Continente>::const_iterator buscar = continentes.begin();
        for(; buscar != continentes.end() ; ++buscar){
            if(buscar->estaControladoPor(colorJugador)){
                bonificacion += buscar->obtenerBonificacion();
            }

        }
        if(bonificacion==0){
            return 0;
        }
        return bonificacion;

    }
        
    bool Tablero::agregarUnidades(string codigoTerritorio, string colorJugador, int cantidad){
        if(!existeTerritorio(codigoTerritorio)){
            return false;
        }

        Territorio* territorio = buscarTerritorio(codigoTerritorio);
        if(territorio->obtenerColorPropietario()!=colorJugador){
            return false;
        }

        return territorio->agregarUnidades(cantidad);
    }

    bool Tablero::trasladarUnidades(string codigoOrigen, string codigoDestino, string colorJugador, int cantidad, int minimoRestante){
        if(!existeTerritorio(codigoOrigen)){
            return false;
        }
        
        if(!existeTerritorio(codigoDestino)){
            return false;
        }

        Territorio* terr1 = buscarTerritorio(codigoOrigen);

        Territorio* terr2 = buscarTerritorio(codigoDestino);

        if(terr1->obtenerColorPropietario()!=colorJugador || terr2->obtenerColorPropietario() != colorJugador){
            return false;
        }

        if(!terr1->esVecino(codigoDestino)){
            return false;
        }
        if(!terr1->retirarUnidades(cantidad,minimoRestante)){
            return false;
        }

        return terr2->agregarUnidades(cantidad);

    }

    bool Tablero::cambiarPropietario(string codigoTerritorio, string nuevoColor, int cantidad){
        if(!existeTerritorio(codigoTerritorio)){
            return false;
        }

        Territorio* territorio = buscarTerritorio(codigoTerritorio);
        if(territorio->obtenerColorPropietario() == nuevoColor){
            return false;
        }
        
        return territorio->cambiarPropietario(nuevoColor, cantidad);
        
        
    }
    //Verifica que todos los continentes al inicir el juego tengan su correspondiente color en caso contrario devuelve false
    bool Tablero::todosLosTerritoriosConfigurados() const{
        vector<Continente>::const_iterator buscar = continentes.begin();
        for(; buscar != continentes.end(); ++buscar){//Busca entre todos los continentes que hay
            //Crea un alias del vector territorio de continente para que no se duplique de manera local haciendolo mas eficiente
            const vector<Territorio>& territorios = buscar->obtenerTerritorios();
            vector<Territorio>::const_iterator buscarTerr = territorios.begin();
            //Busca que todos los territorios del continente tengan un color propietario, en caso contrario que devuelva un false
            for(; buscarTerr != territorios.end(); ++buscarTerr){
                if(buscarTerr->obtenerColorPropietario() == ""){
                    return false;
                }
            }
        }
        return true;
    }
    
    void Tablero::mostrarTablero() const {
        vector<Continente>::const_iterator buscar = continentes.begin();
        cout << "========== TABLERO =========="<<endl;
        while (buscar != continentes.end()) {

            cout << "Continente: "<< buscar->obtenerNombre() << endl;

            const vector<Territorio>& territorios = buscar->obtenerTerritorios();

            vector<Territorio>::const_iterator buscarTerritorio = territorios.begin();

            while (buscarTerritorio != territorios.end()) {

                cout << "  Territorio: "<< buscarTerritorio->obtenerNombre()<< endl;

                cout << "    Codigo: "<< buscarTerritorio->obtenerCodigo() << endl;

                cout << "    Propietario: " << buscarTerritorio->obtenerColorPropietario() << endl;

                cout << "    Unidades: "<< buscarTerritorio->obtenerUnidades() << endl;

                ++buscarTerritorio;
            }
            ++buscar;
        }
    }