/** @file processador.cc
    @brief Codi de la classe processador
*/

#include "processador.hh"
using namespace std;

Processador::Processador(){
    espai = espai_total = 0;
    memoria = map<int, Proc>();
    posicio_proces = map<int, int>();
    forat_mem = map<int,set<int>>();
}


bool Processador::existeix_proces(const int& proces) const{
    map<int, int>::const_iterator it = posicio_proces.find(proces);
    if (it != posicio_proces.end()) return true;
    else return false;
}

bool Processador::conte_procs () const{
    return (not memoria.empty());
}

bool Processador::hi_cap(int& f, const int& mida) const{
    map<int, set<int>>::const_iterator it = forat_mem.lower_bound(mida);
    if (it != forat_mem.end()){
        f = it->first;
        return true;
    }
    return false;
}

int Processador::consultar_memoria() const{
    return espai_total;
}

void Processador::afegir_proces(const Proc& p){

    if (p.consultar_memoria_ocupada() <= espai_total){
        map<int,set<int>>::iterator forat_it = forat_mem.lower_bound(p.consultar_memoria_ocupada());
        int inicial;
        if (forat_it != forat_mem.end()){
            int size = forat_it->first;
            set<int>::iterator pos_forat = forat_it->second.begin(); //(forat_it->second).begin()
            inicial = *pos_forat;
            espai_total -= p.consultar_memoria_ocupada();

            posicio_proces[p.consultar_id()] = inicial;
            memoria[inicial] = p;

            if ((forat_it->second).size() == 1) forat_mem.erase(forat_it);
            else (forat_it->second).erase(pos_forat);
//             (forat_it->second).erase(pos_forat);
//             if((forat_it->second).empty()){
//                 forat_mem.erase(forat_it);
//             }
            if (size > p.consultar_memoria_ocupada()){
                int nou = size - p.consultar_memoria_ocupada();
                forat_it = forat_mem.find(nou);
                forat_mem[nou].insert(inicial + p.consultar_memoria_ocupada());
            }
        }
        else cout << "error: no cabe proceso" << endl;
    }
    else cout << "error: no cabe proceso" << endl;
}


void Processador::elimina_proces(const int& proces){
    int posicio = posicio_proces[proces];
    int inicial = posicio;
    map<int, Proc>::iterator it = memoria.find(posicio);
    Proc pr = it->second;

    int nou_forat_size = pr.consultar_memoria_ocupada();
    int size_per_borrar;
    espai_total += pr.consultar_memoria_ocupada();


    if (memoria.size() != 1){ // Pel cas que sigui 1 per a evitar fer ++it i --it;
        // No caldra evitar fer ++it i --it
        posicio_proces.erase(proces); //Borrem el proces del mapa <int, int>

        if (it != memoria.begin()){ // En el cas que no es trobi al begin podem fer --it per a estudiar la pos anterior
            --it;
            int pos_proc = it->first;
                if (pos_proc + (it->second).consultar_memoria_ocupada() != posicio){
                    size_per_borrar = posicio - ((pos_proc) + (it->second).consultar_memoria_ocupada());
                    nou_forat_size += size_per_borrar; //el nou forat per borrar sera la suma dels tamanys

                    map<int, set<int>>::iterator ite = forat_mem.find(size_per_borrar);
                    (ite->second).erase((pos_proc) + (it->second).consultar_memoria_ocupada());

                    if ((ite->second).empty()) forat_mem.erase(ite); //comprovem si, borrant el forat, ens quedem sense forats de tamany int

                }
            posicio = pos_proc + (it->second).consultar_memoria_ocupada();
        } else if(it->first != 0){ // Else if del anterior ja que podria ser que la posicio sigui 0 tot i no ser begin.
//              ++it;
            posicio = 0;
            size_per_borrar = (it -> first) /*- pr.consultar_memoria_ocupada()*/;
            nou_forat_size += size_per_borrar /*+  pr.consultar_memoria_ocupada()*/;

            map<int, set<int>>::iterator ite = forat_mem.find(size_per_borrar);
            (ite->second).erase(posicio); // ja que la posicio del forat eliminat es 0

            if ((ite->second).empty()) forat_mem.erase(ite);//comprovem si, borrant el forat, ens quedem sense forats de tamany int
        }
        int proc_size = inicial + pr.consultar_memoria_ocupada();
        map<int, Proc>::iterator it2 = memoria.find(inicial);
        it2 = memoria.erase(it2);

        if (it2 != memoria.end()){ //Per als processos centrals
            if(it2->first != proc_size){
                size_per_borrar = it2->first - proc_size;
                nou_forat_size += size_per_borrar;

                map<int, set<int>>::iterator ite = forat_mem.find(size_per_borrar);

                (ite->second).erase(inicial + pr.consultar_memoria_ocupada());
                if ((ite->second).empty()) forat_mem.erase(ite);//comprovem si, borrant el forat, ens quedem sense forats de tamany int
            }
        }
        else if(proc_size != espai){ // En el cas que l'espai del proces sigui igual al
            size_per_borrar = espai - proc_size;
            nou_forat_size += size_per_borrar;

            map<int, set<int>>::iterator ite = forat_mem.find(size_per_borrar);

            (ite->second).erase(proc_size);
            if ((ite->second).empty()) forat_mem.erase(ite); //comprovem si, borrant el forat, ens quedem sense forats de tamany int
        }
        //Cas general per inserir
        map<int, set<int>>::iterator forat_it;
        forat_it = forat_mem.find(nou_forat_size);
        if (forat_it != forat_mem.end()) (forat_it->second).insert(posicio);
        else{
            set<int> noupos;
            noupos.insert(posicio);
            forat_mem[nou_forat_size] = noupos;
        }
    }
    else {
        memoria.erase(posicio); // en aquest cas nomes queda un aleshores podem borrarlo del mapa
        forat_mem = map<int, set<int>>();
        set<int> ids;
        //creem un nou
        ids.insert(0);
        forat_mem[espai]= ids;
        posicio_proces.erase(proces);

    }
}

void Processador::modificar_temps(const int& temps){
    map<int, Proc>::iterator it = memoria.begin();
    //cal crear una copia del iterador per a quan s'elimina el proces
    while(it != memoria.end()){
        (it->second).modificar_temps(temps);
        if ((it->second).consultar_temps() <=0){
            map<int, Proc>::iterator it_copia = it;
            ++it;
            elimina_proces((it_copia->second).consultar_id());
        }else {
            ++it;
        }
    }
}

void Processador::imprimir_processador_processador(){
    map<int, Proc>::iterator it = memoria.begin();
    while (it != memoria.end()){
        cout << (it->first) << " ";
        (it->second).escriure();
        ++it;
    }
}

void Processador::llegir(){
    cin >> espai;
    espai_total = espai;
    set<int> posicio;
    posicio.insert(0);
    forat_mem[espai] = posicio;
}



void Processador::compactar_memoria(){
   if (not forat_mem.empty()) { // no caldira comprovar si esta empty
        map <int, set<int>>:: iterator it = forat_mem.begin();
        int prim_forat =  *((it->second).begin());
        ++it;
        //el while serveix per trobar la posicio del primer forat
        while (it != forat_mem.end()){ // suposem que prim_forat exiteix perq hem mirat que el mapa no estigui empty
            int post_pos = *((it->second).begin());
            if (post_pos < prim_forat){ //troba el primer forat de la memoria independentment del tamany
                prim_forat = post_pos;
            }
            ++it;
        }
        int aux = prim_forat;
        // aconseguim la posicio del proces despres del forat
        map<int, Proc>::iterator it_pro = memoria.upper_bound(prim_forat);
        while (it_pro != memoria.end()){ // l'inserim a la nova posicio i cambiem la posicio del proces
            Proc pro = it_pro->second;
            memoria[aux] =  (pro);
            // ho cambiem aqui en el segon mapa
            posicio_proces[(pro).consultar_id()] = aux;
            aux += (pro).consultar_memoria_ocupada();
            it_pro = memoria.erase(it_pro);
        }
        forat_mem.clear();
        set<int> s;
        s.insert(aux);
        forat_mem[espai_total] = s;
    }
}






