/** @file  Proc.cc
    @brief Codi de la classe Proc
*/

#include "Proc.hh"
using namespace std;


void Proc::llegir(){
    cin>> id >>memoria_ocupada >>temps_act;
}


Proc::Proc(){
    id=memoria_ocupada=temps_act= 0;
}

int Proc::consultar_id() const{
    return id;
}

int Proc::consultar_temps() const{
    return temps_act;
}

int Proc::consultar_memoria_ocupada() const{
    return memoria_ocupada;
}

void Proc::modificar_temps(const int& temps){
    temps_act -= temps;
}


void Proc::escriure(){
    cout << id << " " << memoria_ocupada <<  " " << temps_act << endl;
}
