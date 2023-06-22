/** @file Cluster.cc
    @brief Codi de la classe Cluster
*/

#include "Cluster.hh"
using namespace std;

Cluster::Cluster(){
    arbre=BinTree<string>();
    procs=map<string, Processador>();
}
 //static
void Cluster::llegir_im(BinTree<string>& t, map<string,Processador>& p){ //inmersio
    string ident;
    cin >> ident;
    if (ident != "*") {
        Processador procdr;
        procdr.llegir();

        p[ident]=procdr;
        BinTree<string> esquerra;
        BinTree<string> dreta;

        llegir_im(esquerra, p);
        llegir_im(dreta, p);

        t=BinTree<string>(ident, esquerra, dreta);
    }
}

void Cluster::configurar_cluster(){
    procs.clear();
    llegir_im(arbre, procs); //arbre i mapa de privat

}

void Cluster::alta_proces_processador(const Proc& p, const string& processador){
    map<string, Processador>::iterator it = procs.find(processador);
    if (it != procs.end()){
        if ((it->second).existeix_proces(p.consultar_id())) cout << "error: ya existe proceso"<< endl;
        else (it->second).afegir_proces(p);
    }
    else cout << "error: no existe procesador" << endl;

}

void Cluster::baixa_proces_processador(const int& proces, const string& processador){
    map<string, Processador>::iterator it = procs.find(processador);
    if (it != procs.end()){
        if (not (it->second).existeix_proces(proces)) cout << "error: no existe proceso"<< endl;
        else (it->second).elimina_proces(proces);
    }
    else cout << "error: no existe procesador" << endl;

}

void Cluster::modificar_temps(const int& temps){
    for(map<string, Processador>::iterator it=procs.begin(); it!=procs.end(); ++it){
        (it->second).modificar_temps(temps);
    }
}

void Cluster::imprimir_processador(const string& processador){
    map<string, Processador>::iterator it = procs.find(processador);
    if(it != procs.end()){
        (it->second).imprimir_processador_processador();
    }
    else cout <<"error: no existe procesador" << endl;
}

void Cluster::imprimir_processador_cluster(){
    for(map<string, Processador>::iterator it=procs.begin(); it!=procs.end(); ++it){
        (it->second).imprimir_processador_processador();
    }
}

void Cluster::imprimir_processadors_cluster() {
    for(map<string, Processador>::iterator it = procs.begin(); it != procs.end(); ++it){
        cout << (it-> first) << endl;
        (it->second).imprimir_processador_processador();
    }
}

//static
void Cluster::imprimir_i(const BinTree<string>& t){
    if (not t.empty()){
        cout <<"("<<t.value();
        imprimir_i(t.left());
        imprimir_i(t.right());
        cout << ")";
    }
    else cout << " ";
}

void Cluster::imprimir_cluster(){
    imprimir_i(arbre);
    cout << endl;
}

void Cluster::compactar_memoria_processador(const string& processador){
     map<string, Processador>::iterator it = procs.find(processador);
     if (it != procs.end()){
         (it->second).compactar_memoria();
    } else cout << "error: no existe procesador" << endl;
}



void Cluster::compactar_memoria_cluster(){
    map<string, Processador>::iterator it = procs.begin();
    while (it != procs.end()){
        (it->second).compactar_memoria();
        ++it;
    }
}

//static
bool Cluster::encaixa(const string& id_processador, BinTree<string>& t, BinTree<string>& aux){
    if (not t.empty()){
        BinTree<string> l = t.left();
        BinTree<string> r = t.right();
        string id = t.value();
        //Comprovem els dos casos base que retornen true o false
        if (t.value() == id_processador){
            if (l.empty() and r.empty()){
                t = aux;

                return true;
            } else {

                cout << "error: procesador con auxiliares" << endl;
                return false;
            }
        }
        //Declarem una variable booleana per veure si "encaixa" per la esquerra
        bool encaixa_per_esq;
        encaixa_per_esq = encaixa(id_processador, l, aux);
        //Declarem una variable booleana per veure si "encaixa" per la dreta
        bool encaixa_per_dre;
        encaixa_per_dre = encaixa(id_processador, r, aux);
        t = BinTree<string>(id, l, r);
        return encaixa_per_dre and encaixa_per_esq;
    }
    return true;
}


void Cluster::modificar(const string& processador){
    map<string, Processador> m;
    BinTree<string> a;
    // cridem la funcio recursiva per a llegir el cluster nou
    llegir_im(a, m);
    map<string, Processador>::iterator it = procs.find(processador);
    if (it == procs.end()) cout << "error: no existe procesador" << endl;
    else{
        if ((it->second).conte_procs()) cout << "error: procesador con procesos" << endl;
        else{
            if (encaixa(processador, arbre, a)){
                procs.erase(it);
                procs.insert(m.begin(), m.end());
            }
        }
    }
}


bool Cluster::enviar_proc_cluster(const Proc& p){

    map<string, Processador>::iterator it = procs.end();
    queue<BinTree<string>> que; //podria ferse amb una llista i comparar posteriorment
    que.push(arbre);

    int max = 0; // Es guarda el forat mes gran trobat
    while (not que.empty()){
        //Iniciem un recorregut en amplitud
        BinTree<string> arbre_aux(que.front());
        map<string, Processador>::iterator itf = procs.find(arbre_aux.value());
        int nou;

        if (not arbre_aux.left().empty()) que.push(arbre_aux.left());
        if (not arbre_aux.right().empty()) que.push(arbre_aux.right());

        if ((itf->second).hi_cap(nou, p.consultar_memoria_ocupada()) and not (itf->second).existeix_proces(p.consultar_id())){
            if (it == procs.end() or nou < max){
                it = itf;
                max = nou;
            }
            //cas d'empat
            else if(nou == max and (itf->second).consultar_memoria() > (it->second).consultar_memoria()) it = itf;
        }
        que.pop();
    }
    if (it != procs.end()){
        (it->second).afegir_proces(p);
        return true;
    }
    return false;
}













