#include "red.h"

Red::Red()
{

}



void Red::guardarRuta()
{
    string data;
    
    // Iteramos sobre cada nodo de la topología
    for(int i=0; i < len(); ++i){
        data += topologia[i].getNodo() + ":{";
        
        // Iteramos sobre cada conexión de cada nodo
        for(int j=0; j < len(); ++j){
            data += topologia[j].getNodo() + ":";
            // Si el costo es infinito, lo representamos con "-"
            if(topologia[i].getCosto(topologia[j].getNodo()) == INF){ 
                data += "- "; 
                
            }
            // Si no, agregamos el costo
            else{
                data += to_string(topologia[i].getCosto(topologia[j].getNodo())) + " ";
            }
        }
        // Eliminamos el último espacio en blanco y agregamos un salto de línea
        
        
        data.pop_back();
        data += "}\n";
    }
     // Eliminamos el último salto de línea
    data.pop_back();
    // Escribimos el resultado en el archivo correspondiente
    write(data);
    
}

void Red::random(const int &numNodos)
{
    nombre = "Red_aleatoria";

    // Configuramos la semilla para generar números aleatorios
    srand(time(NULL));
    
    // Creamos un vector con todas las letras mayúsculas del alfabeto
    vector<char> caracteres;
    
    for(int i=65; i<=90; ++i){
        caracteres.push_back(i);
    }
    
    // Creamos un nodo para cada letra elegida aleatoriamente del vector de caracteres
    for(int i=0; i < numNodos; ++i){

        int random = rand()%caracteres.size();
        topologia.push_back(Nodo(string(1, caracteres[random])));
        caracteres.erase(caracteres.begin()+random);
    }
    
    // Agregamos conexiones aleatorias entre los nodos
    for(int i=0; i < topologia.size(); ++i){

        for(int j=0; j<topologia.size(); ++j){

            if(j != i){
                 // En un tercio de las veces, agregamos una conexión con un costo aleatorio entre 1 y 15
                if(rand()%3){
                    topologia[i].addConexion(topologia[j].getNodo(), 1+rand()%15);
                }
                // En los otros casos, agregamos una conexión con costo infinito
                else{
                   topologia[i].addConexion(topologia[j].getNodo(), INF);
                }
                // Aseguramos que la conexión sea bidireccional
                topologia[j].addConexion(topologia[i].getNodo(), topologia[i].getCosto(topologia[j].getNodo()));
            }
        }
    }
}
// Esta función encuentra el mejor camino entre dos nodos de una red

int Red::mejorCamino(const string &rutaInicio, const string &rutaDestino)
{
    char l[10];
    // Copiar la topología de la red para no modificar la original
    vector<Nodo> opT = topologia;
    
    // Iterar sobre todos los caminos posibles
    for(int k=0; k < opT.size(); ++k){

        for(int i=0; i < opT.size(); ++i){

            for(int j=0; j < opT.size(); ++j){
                
                // Verificar que el costo de la conexión entre i y k y entre k y j sean mayores que cero
                int costik = opT[i].getCosto(opT[k].getNodo());
                int costkj = opT[k].getCosto(opT[j].getNodo());
                if(costik > 0 && costkj > 0 && costik + costkj < opT[i].getCosto(opT[j].getNodo())){
                    // actualizar la conexión entre los nodos i y j
                    opT[i].addConexion(opT[j].getNodo(), costik + costkj); 
                    
                }
            }
        }
    }

    return opT[buscarRuta(rutaInicio)].getCosto(rutaDestino);
}

/*int Red::mejorCamino(const string &rutaInicio, const string &rutaDestino)
{
    // Copiar la topología de la red para no modificar la original
    vector<Nodo> optimizedTopologia = topologia;

    // Iterar sobre todos los caminos posibles
    for(int k=0; k < optimizedTopologia.size(); ++k){
        for(int i=0; i < optimizedTopologia.size(); ++i){
            for(int j=0; j < optimizedTopologia.size(); ++j){

                // Comprueba si hay un camino mejor a través del nodo actual
                if(optimizedTopologia[i].getCosto(optimizedTopologia[k].getNodo()) + optimizedTopologia[k].getCosto(optimizedTopologia[j].getNodo()) < optimizedTopologia[i].getCosto(optimizedTopologia[j].getNodo())){

                    // actualizar la conexión entre los nodos i y j
                    optimizedTopologia[i].addConexion(optimizedTopologia[j].getNodo(), optimizedTopologia[i].getCosto(optimizedTopologia[k].getNodo()) + optimizedTopologia[k].getCosto(optimizedTopologia[j].getNodo()));
                }
                // No sé para qué sirve esta línea, pero parece innecesaria.
                optimizedTopologia;
            }
        }
    }

    // Devuelve el coste de la mejor ruta
    return optimizedTopologia[buscarRuta(rutaInicio)].getCosto(rutaDestino);
}
*/

// Esta función añade un nuevo nodo a la red
void Red::addRuta(const Nodo &nuevoNodo)
{
    // Añade el nuevo nodo a todos los nodos existentes y añádelo a la red
    for(int i=0; i < topologia.size(); ++i){
        topologia[i].addConexion(nuevoNodo.getNodo(), nuevoNodo.getCosto(topologia[i].getNodo()));
    }
    topologia.push_back(nuevoNodo);
}

// Esta función elimina un nodo de la red
void Red::deleteRuta(const string &elimNodo)
{
    // Eliminar el nodo de todos los nodos existentes y eliminarlo de la red
    for(int i=0; i < topologia.size(); ++i){
        topologia[i].deleteConexion(elimNodo);
    }
    topologia.erase(topologia.begin() + buscarRuta(elimNodo));
}

// Esta función comprueba si un nodo está en la red
bool Red::salir(const string &nombre)
{
     // Iterar sobre todos los nodos y comprobar si el nombre coincide
    for(int i=0; i < topologia.size(); ++i){
        if(topologia[i].getNodo() == nombre){
            return true;
        }
    }
    return false;
}

// Esta función devuelve los nombres de todos los nodos de la red
const vector<string> Red::nombres() const
{
    vector<string> nombres;
    for(int i=0; i < topologia.size(); ++i){
        nombres.push_back(topologia[i].getNodo());
    }
    return nombres;
}
string Red::toString() const {
    string result;
    // Construir la tabla como una cadena y agregarla a 'result'
    //...
    return result;
}
int Red::len() const
{
    return topologia.size();
}

/***/
void Red::write(const string &data)
{


    ofstream file;

    file.open("../networks/" + nombre);
    if (file.is_open()){

        file << data;

        file.close();
    }
    else{
        cout << "Error al crear " << nombre << endl;
        exit(1);
    }
}

int Red::buscarRuta(const string &nombreRuta)
{
    for(int i=0; i < topologia.size(); ++i){
        if(topologia[i].getNodo() == nombreRuta){
            return i;
        }
    }

    return 0;
}


