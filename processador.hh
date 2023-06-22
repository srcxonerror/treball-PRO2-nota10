/** @file processador.hh
    @brief Especificació de la classe processador
*/

#ifndef PROCESSADOR_HH
#define PROCESSADOR_HH

#include "Proc.hh"
#ifndef NO_DIAGRAM
#include <vector>
#include <set>
#include <map>
#endif


/** @class Processador
    @brief Representa un processador on hi hauran processos
 */

class Processador {

private:
    /** @brief Espai fixe de un processador */
    int espai;
    /** @brief Espai variable d'un processador */
    int espai_total;
    /** @brief Mapa on es guarden les poicions inicials i els processos de la memoria */
    map<int, Proc> memoria; //<Pos inicial, proces>
    /** @brief Mapa on es guarda cada identificador de un processador amb la seva posicio */
    map<int, int> posicio_proces; //<id proces, posicio proces>
    /** @brief Mapa on es guarden els tamanys dels forats i les posicions de on es troben els forats de tal mida */
    map<int,set<int>> forat_mem; //<tamany forat i posicions dels forats inicals>


public:

    //Constructores

    /** @brief Creadora per defecte

        S'executa automaticament quan es declara un processador
        \pre <em>cert</em>
        \post El resultat es un processador
    */
    Processador();

    //Consultores

    /** @brief Comprova si existeix el proces amb identificador id en el processador
        @param proces és el identificador d'un proces
        \pre Cert
        \post Retorna si el proces existeix
    */
    bool existeix_proces(const int& proces) const;

    /** @brief Consulta si el processador te processos

        \pre Cert
        \post Retorna cert si el processador conte processos, sino retorna false
    */
    bool conte_procs () const;

    /** @brief Consulta si el proces hi cap (en general) a qualsevol forat
        @param f és la posicio del forat
        @param mida és el tamany del forat
        \pre Cert
        \post Retorna cert si el processador hi cap al processador i f passa a valer la posicio d'aquest forat
    */
    bool hi_cap(int& f, const int& mida) const;

    /** @brief Consulta la memoria disponible (memoria_total) del processador

        \pre Cert
        \post Retorna la memoria disponible del processador
    */
    int consultar_memoria() const;

    //Modificadores

    /** @brief Avança el temps
        @param temps és el temps que han d'avançar tots els processadors del cluster
        \pre t ha de ser >= 0. El parametre implicit esta inicialitzat
        \post S'avança el temps de tots els processos i aquells que han acabat s'eliminen
    */
    void modificar_temps(const int& temps);

    /** @brief Afegeix un procés al processador
        @param p és un procés que es vol afegir al processador
        \pre Comprova que el processador existeixi i que no tingui un procés amb el mateix id
        \post S'ha afegit el proces al processador
    */
    void afegir_proces(const Proc& p);

    /** @brief Elimina un procés del processador
        @param proces és l'identificador d'un procés a eliminar
        \pre Comprova que el processador existeixi i té un procés amb el mateix id
        \post S'elimina un procés del processador
    */
    void elimina_proces(const int& proces);

     /** @brief Compacta la memoria de un procesador

        \pre El parametre implicit esta inicialitzat
        \post Es compacta tota la memoria del processador
    */
    void compactar_memoria();




    //Lectura i Escriptura
    /** @brief Llegeix un cluster

        \pre En el canal de entrada estandard estan els parametres preparats
        \post El contingut dels parametres es guarden al parametre implicit
    */
    void llegir();

    /** @brief S'escriuen les dades d'un proces

        S'escriuen les dades del processador en orden creixent juntament amb les seves dades
        \pre El processador no esta buit
        \post Per el canal estandard de sortida s'escriuen les dades
    */
    void imprimir_processador_processador();
};
#endif

