#include <ctime>
#include "nodo.h"
#include "red.h"
#include <iostream>

using namespace std;

int menu(const int &opc);


int main()
{
    Red rednodos;
    int opcion = menu(0);
    string aux[2];

    if(opcion == 1){
        cout << "Ingrese la cantidad de routers que desea: \n";
        getline(cin, aux[0]);

        rednodos.random(stoi(aux[0]));
        cout << "Red generada con exito.\n" << endl;

    }
    cout << rednodos << endl;

    while(true){
        system("pause");
        opcion = menu(1);

        if(opcion == 1){
            Nodo nuevoNodo;

            cout << "Ingrese el nombre del nuevo enrutador: \n";
            getline(cin, aux[0]);

            if(!rednodos.salir(aux[0])){
                nuevoNodo.setNombre(aux[0]);

                for(int i=0; i < rednodos.len(); ++i){
                    cout << "Ingrese el valor de la conexion con: " << rednodos.nombres()[i] << "\n -> ";
                    getline(cin, aux[0]); system("cls");

                    if(aux[0] == "~"){ nuevoNodo.addConexion(rednodos.nombres()[i], INF); }
                    else{
                     nuevoNodo.addConexion(rednodos.nombres()[i], stoi(aux[0])); }
                }
                rednodos.addRuta(nuevoNodo);

                cout << "Enrutador agregado con exito.\n" << endl;
                cout << rednodos << endl;

            }
            else{ cout << "El enrutador ya esta en la red.\n" << endl; }

        }
        else if(opcion == 2){
            cout << "Ingrese el nombre del enrutador a eliminar: \n";
            getline(cin, aux[0]);

            if(rednodos.salir(aux[0])){
                rednodos.deleteRuta(aux[0]);

                cout << "Enrutador eliminado con exito.\n" << endl;
                cout << rednodos << endl;

            }
            else{cout << "El enrutador: " << aux[0] << " no existe.\n" << endl; }

        }
        else if(opcion == 3){
            cout << "Ingrese el enrutador de partida: \n ";
            getline(cin, aux[0]);

            if(rednodos.salir(aux[0])){
                cout << "Ingrese el enrutador destino: \n ";
                getline(cin, aux[1]);

                if(rednodos.salir(aux[1])){
                    cout << "El menor costo mas bajo de: " << aux[0] << " hasta: " << aux[1]
                         << " es de: " << rednodos.mejorCamino(aux[0], aux[1]) << ".\n" << endl;
                    continue;
                }
            }
            cout << "El enrutador ingresado no existe.\n" << endl;

        }
        else if(opcion == 4){
            rednodos.guardarRuta();
            break;

        }

    }

    return 0;





}



int menu(const int &opc){

    string opcion;

    while(true){
        if(opc == 0){
            cout << "Menu:\n"
                    "  1. Generar red aleatoria.\n"
                    "  2. Generar red vacia.\n"
                    " Opcion: ";

            cin >> opcion; cin.ignore();

            system("cls");
            break;



        }
        else{ // Se imprime el menu principal
            cout << "\nQue desea hacer?\n"
                    "  1. Agregar enrrutador.\n"
                    "  2. Eliminar enrrutador.\n"
                    "  3. Consultar costo mas bajo.\n"
                    "  4. Salir.\n "
                    " Opcion: ";
            cin >> opcion; cin.ignore();

            system("cls");


            break;
        }
    }

    return stoi(opcion); // Se retorna la opcion tomada por el usuario
}
