
#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <string>
#include <map>

#define INF 999999

using namespace std;

class Nodo
{

private:
    string nodo;    // El nombre del nodo.
    map<string, int> conexiones; // Un mapa que almacena las conexiones del nodo y sus costos.
public:
    Nodo(); // Constructor por defecto.
    Nodo(const string &nodo); // Constructor que recibe el nombre del nodo.


    const string &getNodo() const; // Método para obtener el nombre del nodo.
    void  setNombre(const string &nodo); // Método para cambiar el nombre del nodo.

    const  int &getCosto(const string &nodo) const; // Método para obtener el costo de una conexión.

    void addConexion(const string &nodo, const int &costo); // Método para agregar una conexión al nodo.
    void deleteConexion(const string &nodo); // Método para eliminar una conexión del nodo.
};

#endif // NODO_H
