#include "Tablero.h"

Tablero::Tablero()
{
}

void Tablero::inicializarEstructura() { //crea el tablero de juego
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
/* 
const Territorio* Tablero::buscarTerritorio(string codigo) const{
     vector<string>::iterator
}
    bool existeTerritorio(string codigo) const;
    bool configurarTerritorio(
        string codigo,
        string colorPropietario,
        int unidades
    );
    bool sonVecinos(
        string codigoOrigen,
        string codigoDestino
    ) const;
    int contarTerritorios(string colorJugador) const;
    int sumarUnidades(string colorJugador) const;
    int calcularBonificacionContinentes(
        string colorJugador
    ) const;
    bool agregarUnidades(
        string codigoTerritorio,
        string colorJugador,
        int cantidad
    );
    bool trasladarUnidades(
        string codigoOrigen,
        string codigoDestino,
        string colorJugador,
        int cantidad,
        int minimoRestante
    );
    bool cambiarPropietario(
        string codigoTerritorio,
        string nuevoColor
    );
    bool todosLosTerritoriosConfigurados() const;
    void mostrarTablero() const;
    */