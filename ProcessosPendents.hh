/** @file ProcessosPendents.hh
    @brief Especificació de la classe ProcessosPendents
*/

#ifndef PROCESSOS_PENDENTS
#define PROCESSOS_PENDENTS

#ifndef NO_DIAGRAM
#include <map>
#include <list>
#include <iostream>
#endif
#include "Proc.hh"
#include "Cluster.hh"


using namespace std;

/** @class ProcessosPendents
    @brief Representa l'area de processos pendents
 */
class ProcessosPendents {
private:
    /**  @struct Pri
        @brief Un struct on es guarden els processos acceptats i rebutjats, un set on ordenem els processos i una llista on es guarden els processos en ordre de antiguitat
    */
    struct Pri {
        int acceptats;
        int rebutjos;
        set<int> processos_ordenats;
        list<Proc> l;
    };
    /** @brief Mapa on es guarden les prioritats en ordre */
    map<string, Pri> area;

public:
    //Constructores
    /** @brief Creadora per defecte

        \pre <em>Cert</em>
        \post Es retorna l'area de processos pendents amb els parametres inicialitzats a 0
    */
    ProcessosPendents();

    //Consultores

    /** @brief Comprova si existeix un proces
        @param proces és l'identificador del procés
        @param prioritat és l'identificador de la prioritat
        \pre Cert
        \post Retorna true si exiteix el proces, sino retorna false
    */
    bool existeix_proces(const int& proces, const string& prioritat) const;

     /** @brief Comprova si existeix una prioritat
        @param prioritat és l'identificador de la prioritat
        \pre Cert
        \post Retorna true si exiteix la prioritat, sino retorna false
    */
    bool existeix_prioritat(const string& prioritat) const;

     /** @brief Comprova una prioritat conte processos
        @param prioritat és l'identificador de la prioritat
        \pre Cert
        \post Retorna true si conte processos, sino retorna false
    */
    bool conte_processos(const string& prioritat) const;



    // Modificadores

       /** @brief Envia els processos al cluster

        Els processos entrants s'intenten colocar en ordre de prioritat al cluster i, quan aquesta prioritat es la mateixa, s'ordenen de mes antics a mes nous.
        Es seguirà intentant fins que s'haguin col·locat n processos en el cluster o bé, fins que no quedin processos pendents o bé, fins que tots els pendents s'hagin intetat colocar sense èxit.
        @param cluster és el cluster al que volem enviar els processos
        @param n és el numero de processos a enviar
        \pre El parametre implicit esta inicialitzat i n >= 0
        \post S'envien com a molt n processos al cluster i es col·loquen tants processos com n'hi hagin d'acceptats.
    */
    void enviar_processos_cluster(Cluster& cluster, int& n);


    /** @brief Afegeix una prioritat

        Comprova si ja existeix la prioritat. En aquest afirmatiu, salta un error
        @param prioritat és l'identificador de la prioritat a afegir
        \pre L'area de processos pendents esta inicialitzada
        \post S'afegeix la prioritat amb els parametres inicialitzats a 0 a l'area de processos pendents en cas que no existeixi
    */
    void afegir_prioritat(const string& prioritat);

     /** @brief Elimina una prioritat

        Comprova abans si existeix en l'area de processos i si te processos pendents
        Si existeix i no te processos pendents l'elimina, si no es cumpleix alguna de les dues condicions salta un error
        @param prioritat és l'identificador de la prioritat
        \pre L'area de processos pendents esta inicialitzada
        \post S'elimina la prioritat a l'area de processos pendents en cas que no existeixi i que no tingui prioritats pendents
    */
    void eliminar_prioritat(const string& prioritat);

    /** @brief Afegeix un proces

        Comprova abans si existeix en l'area de processos
        Si existeix salta un error
        @param p és el procés a afegir
        @param prioritat és l'identificador de la prioritat
        \pre L'area de processos pendents esta inicialitzada
        \post S'afegeix el proces a l'area de processos pendents en cas que no existeixi
    */
    void afegir_proces (const Proc& p, const string& prioritat);

    // Lectura i Escriptura

     /** @brief Imprimeix una prioritat

        Comprova abans si existeix en la prioritat
        Si existeix, imprimeix els processos pendents d'aquesta prioritat, el numero de processos i el numero de rebutjos
        @param prioritat és l'identificador d'una prioritat
        \pre El parametre implicit esta inicialitzat
        \post S'han escrit tots els processos de la prioritat, el numero de rebutjos i el numero de colocats
    */
    void imprimir_prioritat(const string& prioritat);


     /** @brief Escriu una area de processos

        \pre En el canal de entrada estandard estan els parametres preparats
        \post El contingut dels parametres es guarden al parametre implicit
    */

    void llegir();

    /** @brief Llegeix una area de processos

        \pre En el canal de entrada estandard estan els parametres preparats
        \post S'imprimeix per el canal standard de sortida l'area d'espera per ordre creixent de prioritat
    */
    void Escriure();
};
#endif
