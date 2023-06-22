/** @file Proc.hh
    @brief Especificació de la classe Proc
*/

#ifndef PROCES_CLUSTER
#define PROCES_CLUSTER

#ifndef NO_DIAGRAM
#include <iostream>
#endif


using namespace std;

/** @class Proc
    @brief Representa un proces que ocupa un numero d'espais de memoria
 */
class Proc {

private:
    /** @brief identificador del proces */
    int id;
    /** @brief Memoria que ocupa el proces */
    int memoria_ocupada;
    /** @brief El temps actual del proces */
    int temps_act;

public:

    //Constructoras

    /** @brief Creadora per defecte

        \pre <em>Cert</em>
        \post El resultat es un proces amb els seus parametres inicialitzats a 0.
    */
    Proc();

    //Consultores

    /** @brief Retorna id d'un procés

        \pre El parametre implicit te valor
        \post El resultat és el id del paràmetre implícit
    */
    int consultar_id() const;

    /** @brief Retorna el temps emprat d'un procés

        \pre El parametre implicit te valor
        \post El resultat és el temps del paràmetre implícit
    */
    int consultar_temps() const;

    /** @brief Retorna la memoria que ocupa el procés

        \pre El parametre implicit te valor
        \post El resultat és la memòria del paràmetre implícit
    */
    int consultar_memoria_ocupada() const;


    //Modificadores

    /** @brief Avança el temps
        @param temps és el temps a avançar
        \pre t ha de ser >= 0.
        \post S'avança el temps del proces
    */
    void modificar_temps(const int& temps);

    //Lectura i Escriptura

    /** @brief Llegeix un proces

        \pre En el canal de entrada estandard estan els parametres inicialitzats
        \post El contingut dels parametres es guarden al parametre implicit
    */
    void llegir();


    /** @brief Escriu les dades del proces

        \pre El proces no es buit
        \post Per el canal estandard de sortida s'escriuen les dades del proces
    */
    void escriure();

};
#endif

