#ifndef RED_H
#define RED_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include "nodo.h"

using namespace std;

class Red
{

private:

    string nombre;
    vector<Nodo> topologia;//almacena los nodos de la red

    string read(); //lee un archivo y retorna su contenido
    void write(const string &data); //escribe el contenido de una cadena en un archivo
    int buscarRuta(const string &nombreRuta); //busca un nodo en la red

public:
    Red();


    //métodos para cargar y guardar la red en archivos
    void cargarRed(const string &nombre);
    void guardarRuta();

    void random(const int &numRutas); //genera rutas aleatorias
    int mejorCamino(const string &rutaInicio, const string &rutaDestino); //busca el mejor camino entre dos nodos

    void addRuta(const Nodo &nuevoNodo); //agrega un nodo a la red
    void deleteRuta(const string &elimNodo); //elimina un nodo de la red

    bool salir(const string &nombre); //verifica si un nodo está en la red
    const vector<string> nombres() const; //retorna los nombres de todos los nodos en la red
    int len() const; //retorna la cantidad de nodos en la red
    string toString() const;
    //sobrecarga del operador << para imprimir la red en la consola

    friend ostream& operator<<(ostream &out, const Red &Red){

        if(!Red.topologia.size()){
            out << "La red esta vacia." << endl;
            return out;
        }

       

        int ancho = 7; //ancho de cada celda en la tabla
        string line(1, char(196)); //cadena que se usa para dibujar las líneas horizontales

        out << left;
        for(int i=0; i < (Red.len()+1)*ancho; ++i){ line += char(196); } //se construye la línea superior
        out << line << endl;

        out << setw(ancho) << "*******"; //se dibuja la primera celda
        for(int i=0; i < Red.topologia.size(); ++i){
            out << setw(ancho) << "| " +  Red.topologia[i].getNodo(); //se dibujan las celdas de la primera fila
        }out << "|" << endl << line << endl;

        for(int i=0; i < Red.topologia.size(); ++i){
            out << setw(ancho) << "| " + Red.topologia[i].getNodo(); //se dibuja la celda de la primera columna
            for(int j=0; j < Red.topologia.size(); ++j){
                if(!(Red.topologia[i].getCosto(Red.topologia[j].getNodo()) == INF)){
                    out << setw(ancho) << "| " + to_string(Red.topologia[i].getCosto(Red.topologia[j].getNodo())); //se dibujan las celdas de la tabla
                }else{ out << setw(ancho) << "| ~"; }
            }out << "|" << endl << line << endl;
        }
        return out;
    }
};




#endif // RED_H
