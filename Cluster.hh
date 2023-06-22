/** @file Cluster.hh
    @brief Especificació de la classe Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <map>
#include <iostream>
#include <queue>
#include "Proc.hh"
#endif
#include "processador.hh"

/** @class Cluster
    @brief Representa un arbre binari de procesadors
 */

class Cluster{
private:
  /** @brief Arbre composat per els identificadors dels processadors */
    BinTree<string> arbre;
  /** @brief Mapa que relaciona els identificadors amb els processadors */
    map<string, Processador> procs; //id, Processador

public:
    //Constructores

     /** @brief Creadora per defecte

        S'executa automaticament al declarar un clúster
        \pre <em>cert</em>
        \post El resultat es un clúster
    */
    Cluster();

    //Consultores

    //Modificadores

    /** @brief Modifica el clúster

        Comprova que el processador existeixi, que no tingui processos actius i que no tingui processadors auxiliars. En el cas que cumpleixi tots els prequisits, afegeix el nou clúster al processador. En el cas que no cumpleixi una condició, salta un error
        @param processador és l'identificador del processador
        \pre El clúster esta inicialitzat
        \post Retorna, en el cas possible, el clúster modificat. Si no ha sigut possible, retorna un error
    */
    void modificar(const string& processador);

    /** @brief Dona d'alta el procés en un processador del clúster

        Comprova que el processador existeixi en el clúster. Que no tingui processos amb el mateix identificador i que el procés pugui entrar en la memòria del processador. En el cas que es cumpleixi, s'afegeix el procés al processador, sino, salta un error.
        @param p és un procés a afegir
        @param processador és el processador on s'afegeix el procés
        \pre El clúster esta inicialitzt
        \post S'ha donat d'alta el procés en el processador si es possible, sino, salta un error.
    */
    void alta_proces_processador(const Proc& p, const string& processador);


    /** @brief Dona de baixa al procés en un processador del clúster

        Comprova que el processador existeixi en el clúster. Que no tingui processos amb el mateix identificador i que el procés pugui entrar en la memòria del processador. En el cas que es cumpleixi, s'elimina el proces del processador, sino, salta un error.
        @param proces és l'identificador del procés a eliminar
        @param processador és l'identificador del processador d'on s'elimina el procés
        \pre El clúster esta inicialitzt
        \post S'ha donat de baixa el procés en el processador si és possible, sino, salta un error.
    */
    void baixa_proces_processador(const int& proces, const string& processador);

    /** @brief Avança el temps
        @param temps és el temps que s'avança el processador (tots els seus processos)
        \pre t ha de ser >= 0. El paràmetre implícit esta inicialitzat
        \post S'avança el temps de tots els processos de tots els processadors  i aquells que han acabat s'eliminen
    */
    void modificar_temps(const int& temps);

     /** @brief Compactar la memòria del clúster

        \pre El paràmetre implícit esta inicialitzat
        \post S'ha compactat la memòria de tots els processadors del clúster
    */
    void compactar_memoria_cluster();

    /** @brief Compacta la memòria d'un processador

        Comprova que el processador existeixi. En cas cert, compacta la seva memòria, sino ho fa, salta un error
        @param processador és l'identificador del processador a compactar la seva memòria
        \pre El paràmetre implícit esta inicialitzt
        \post S'ha compactat la memòria del procesador
    */
    void compactar_memoria_processador(const string& processador);

    /** @brief Busca el processador adequat i afegeix el procés
        @param p és el procés candidat a afegir
        \pre Cert
        \post Retorna true en cas que es pugui afegir el procés al clúster, sino retorna false
    */

    bool enviar_proc_cluster(const Proc& p);


    //Lectura i Escritura


    /** @brief Llegeix i configura el clúster

        Llegeix els processos del clúster, les seves connexions i la memòria de ells
        \pre Hi ha preparats en el canal standard de entrada les dades del clúster
        \post El resultat es un clúster format per els n processadors i les seves connexions
    */
    void configurar_cluster();

    /** @brief Imprimeix un processador del clúster

        Comprova que el processador existeixi en el clúster i imprieix les seves dades, sino salta un error
        @param processador és l'identificador a imprimir les seves dades
        \pre El clúster esta inicialitzat
        \post S'ha escrit pel canal estàndard de sortida del processador si existeix, si no salta un error
    */
    void imprimir_processador(const string& processador);

    /** @brief Imprimeix un processador del clúster

        \pre El clúster esta inicialitzat
        \post S'ha escrit el processador, juntament amb els seus processos i les seves dades
    */
    void imprimir_processador_cluster();

    /** @brief Imprimeix tots els processadors del clúster

        \pre El clúster esta inicialitzat
        \post S'ha escrit tots els processadors i els seus processos amb les seves dades
    */
    void imprimir_processadors_cluster();

    /** @brief Imprimeix un clúster

        \pre El clúster està inicialitzat
        \post S'ha escrit per el canal stàndard de sortida la estructura del clúster
    */
    void imprimir_cluster();

private:

    /** @brief Operació de lectura d'un arbre de processadors
        @param t és l'arbre a llegir
        @param p és l'estructura del arbre a llegir
        \pre tant el clúster com el mapa és buit
        \post T conte el abrbre i p conte el mapa
    */
    static void llegir_im(BinTree<string>& t, map<string,Processador>& p);

    /** @brief Operació de escriptura de l'estructura d'un arbre de processadors
        @param t és l'arbre a imprimir
        \pre Cert
        \post S'ha escrit t per el canal estàndard de sortida8
    */
    static void imprimir_i(const BinTree<string>& t);


    /** @brief Funció recursiva que comprova si pot colocar un arbre auxiliar a un node en concret
        @param id_processador és l'identificador del arbre
        @param t és l'arbre del privat
        @param aux és l'arbre auxiliar a afegir
        \pre Cert
        \post Retorna true si "encaixa" i en cas contrari, false. Si encaixa, genera el nou arbre amb el node substituit per l'arbre
    */
    static bool encaixa(const string& id_processador, BinTree<string>& t, BinTree<string>& aux);
};
#endif
