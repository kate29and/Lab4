#include "nodo.h"

Nodo::Nodo()
{

}

Nodo::Nodo(const string &nodo)
{
    this->nodo = nodo;
    conexiones[nodo] = 0;
}
// devuelve el nombre del Nodo.
const string &Nodo::getNodo() const
{
    return nodo;
}

//permite cambiar el nombre del Nodo y establecer una conexión a sí mismo con costo cero.
void Nodo::setNombre(const string &nodo) 
{
    this->nodo = nodo;
    conexiones[nodo] = 0;
}
//devuelve el costo de la conexión entre este Nodo y otro Nodo.
const int &Nodo::getCosto(const string &nodo) const
{
    return conexiones.find(nodo)->second;
}

//permite agregar una conexión a otro Nodo con un costo dado.
void Nodo::addConexion(const string &nodo, const int &costo)
{
    conexiones[nodo] = costo;
}
//permite eliminar una conexión existente con otro Nodo.
void Nodo::deleteConexion(const string &nodo)
{
    conexiones.erase(nodo);
}
