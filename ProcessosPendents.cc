/** @file ProcessosPendents.cc
    @brief Codi de la classe ProcessosPendents
*/

#include "ProcessosPendents.hh"
using namespace std;

ProcessosPendents::ProcessosPendents(){
    area=map<string, Pri>();
}

void ProcessosPendents::llegir(){
    int x;
    cin >> x;
    string Pr;

    for (int i = 0; i < x; ++i){
        cin >> Pr;
        Pri pp;
        list<Proc> ll;
        pp.l = ll;
        pp.acceptats = pp.rebutjos =0;
        area[Pr]=pp;
    }
}



bool ProcessosPendents::existeix_prioritat(const string& prioritat) const{
    map<string, Pri>::const_iterator it;
    it = area.find(prioritat);

    if (it != area.end()) return true;
    return false;
}

bool ProcessosPendents::conte_processos(const string& prioritat) const{ //ES POT FER DIRECTAMENT A LA FUNCIO QUE HO NECESSITI
     map<string, Pri>::const_iterator it;
     it = area.find(prioritat);

    if (it->second.l.empty()) return false;
    else return true;

}
//  CAL REVISAR CONST ITERATOR
bool ProcessosPendents::existeix_proces(const int& proces, const string& prioritat) const {
     map<string, Pri>::const_iterator it = area.find(prioritat);
     set<int>::const_iterator its = (it->second).processos_ordenats.find(proces);

     if (its == (it->second).processos_ordenats.end()) return false;
     return true;
}

void ProcessosPendents::afegir_proces (const Proc& p, const string& prioritat){
    map<string, Pri>::iterator it = area.find(prioritat);
    int identificador = p.consultar_id();
    if (not existeix_prioritat (prioritat)){
        cout << "error: no existe prioridad" << endl;
    }
    else {
        if(existeix_proces(identificador, prioritat)) cout << "error: ya existe proceso" << endl;
        else {
            (it->second).l.push_back(p);
            (it->second).processos_ordenats.insert(identificador);
        }
    }

}

void ProcessosPendents::afegir_prioritat(const string& prioritat){
    if (existeix_prioritat(prioritat)) cout << "error: ya existe prioridad" << endl;
    else {
        Pri pri;
        pri.acceptats = pri.rebutjos = 0;
        area[prioritat] = pri;

    }
}

void ProcessosPendents::eliminar_prioritat(const string& prioritat){
    if (not existeix_prioritat(prioritat)) cout << "error: no existe prioridad" << endl;
    else {
        if (conte_processos(prioritat)) cout << "error: prioridad con procesos" << endl;
        else {
            map<string, Pri>::iterator it = area.find(prioritat);
            area.erase(it);
        }
    }
}

void ProcessosPendents::imprimir_prioritat(const string& prioritat){
    if (not existeix_prioritat(prioritat)) cout << "error: no existe prioridad" << endl;
    else {
        map<string, Pri>::iterator it = area.find(prioritat);
        list<Proc>::iterator itl = (it->second).l.begin();
        while (itl != (it->second).l.end()){
            itl->escriure();
            ++itl;
        }
        cout << (it->second).acceptats << " " << (it->second).rebutjos<< endl;
    }
}

void ProcessosPendents::Escriure(){
    map<string, Pri>::iterator it = area.begin();
    while (it != area.end()){
        cout << it ->first << endl;
        imprimir_prioritat(it->first);
        ++it;
    }
}

void ProcessosPendents::enviar_processos_cluster(Cluster& cluster, int& n){
    map<string, Pri>::iterator it = area.begin();
    while (it != area.end() and n != 0){ // El segon iterador no es mou com a tal sino que es va desplaçant a mesura que movem els processos
        list<Proc>::iterator itl, itl2;
        itl = (it->second).l.begin();
        // El segon iterador dit anteriorment
        itl2 = (it->second).l.end();
        // Caldra comprovar si es tracta del primer rebutj perque aleshores el it no pot apuntar a end
        bool primer_rebutj = false;

        while (n != 0 and itl != itl2){
            Proc element = *itl;
            if (cluster.enviar_proc_cluster(element)){
                ++(it->second).acceptats;
                //borrem els elements enviats del set ordenat del privat
                (it->second).processos_ordenats.erase((element).consultar_id());
                --n;

            } else{
                ++(it->second).rebutjos;
                (it->second).l.push_back(element);
                if (not primer_rebutj){
                    // cal restar una posicio del iterador perque apunti al ultim element.
                    --itl2;
                    primer_rebutj = true;

                }
            }
            itl = (it->second).l.erase(itl);

        }
        ++it;
    }
}

















