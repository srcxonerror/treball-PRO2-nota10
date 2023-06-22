/** @mainpage Aquest treball tracta la gestió i configuració d'un clúster composat per processadors amb processos. En aquest clúster li entren comandes que modifiquen aquest clúster de processadors.
*/

/** @file program.cc

    @brief Programa principal
*/

#include "Cluster.hh"
#include "ProcessosPendents.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <iostream>
#endif

using namespace std;


int main(){
    Cluster cluster;
    cluster.configurar_cluster();

    ProcessosPendents area;
    area.llegir();

    string comanda;
    cin >> comanda;


    string id;
    string id_processador;
    string id_prioritat;
    int id_proces;

    int n;
    Proc p;


    while (comanda != "fin") {
        if (comanda == "cc" or comanda == "configurar_cluster") {
            cout << '#' << comanda << endl;
            cluster.configurar_cluster();
        }

        else if (comanda == "mc" or comanda == "modificar_cluster") {
            cin >> id_processador;
            cout << '#' << comanda << " " << id_processador << endl;
            cluster.modificar(id_processador);

        }

        else if (comanda == "ap" or comanda == "alta_prioridad") {
            cin >> id_prioritat;
            cout << '#' << comanda <<" " << id_prioritat << endl;
            area.afegir_prioritat(id_prioritat);

        }

        else if (comanda == "bp" or comanda == "baja_prioridad") {
            cin >> id_prioritat;
            cout << '#' << comanda <<" " << id_prioritat << endl;
            area.eliminar_prioritat(id_prioritat);
        }

        else if (comanda == "ape" or comanda == "alta_proceso_espera") {
            cin >> id_prioritat;
            p.llegir();
            cout << '#' << comanda <<" " << id_prioritat << " " << p.consultar_id() << endl;
            area.afegir_proces(p, id_prioritat);
        }

        else if (comanda == "app" or comanda == "alta_proceso_procesador") {
            cin >> id_processador;
            p.llegir();
            cout << '#' << comanda <<" " << id_processador << " " << p.consultar_id() << endl;

            cluster.alta_proces_processador(p, id_processador);
        }

        else if (comanda == "bpp" or comanda == "baja_proceso_procesador") {
            cin >> id_processador >> id_proces;
            cout << '#' << comanda <<" " << id_processador << " " << id_proces << endl;

            cluster.baixa_proces_processador(id_proces, id_processador);

        }

        else if (comanda == "epc" or comanda == "enviar_procesos_cluster") {
            cin >> n;
            cout << '#' << comanda <<" " << n << endl;
            area.enviar_processos_cluster(cluster, n);


        }

        else if (comanda == "at" or comanda == "avanzar_tiempo") {
            cin >> n;
            cout << '#' << comanda <<" " << n << endl;
            cluster.modificar_temps(n);
        }

        else if (comanda == "ipri" or comanda == "imprimir_prioridad") {
            cin >> id_prioritat;
            cout << '#' << comanda <<" " << id_prioritat << endl;

            area.imprimir_prioritat(id_prioritat);
        }

        else if (comanda == "iae" or comanda == "imprimir_area_espera") {
            cout << '#' << comanda << endl;
            area.Escriure();
        }

        else if (comanda == "ipro" or comanda == "imprimir_procesador") {
            cin >> id_processador;
            cout << '#' << comanda <<" " << id_processador << endl;
            cluster.imprimir_processador(id_processador);
        }

        else if (comanda == "ipc" or comanda == "imprimir_procesadores_cluster") {
            cout << '#' << comanda << endl;
            cluster.imprimir_processadors_cluster();
        }

        else if (comanda == "iec" or comanda == "imprimir_estructura_cluster") {
            cout << '#' << comanda << endl;
            cluster.imprimir_cluster();
        }

        else if (comanda == "cmp" or comanda == "compactar_memoria_procesador") {
            cin >> id_processador;
            cout << '#' << comanda <<" " << id_processador << endl;
            cluster.compactar_memoria_processador(id_processador);

        }

        else if (comanda == "cmc" or comanda == "compactar_memoria_cluster") {
            cluster.compactar_memoria_cluster();
            cout << '#' << comanda << endl;
        }

        cin >> comanda;
    }
}
