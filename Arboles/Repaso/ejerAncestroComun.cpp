/*

    Dado dos elementos de un árbol, devuelve el ancestro común de los dos elementos. 
    Nota: el árbol no tiene elementos repetidos.

*/

#include <iostream>
#include "../Binarios/P2/abin_enlazada.hpp"
#include "../Binarios/P2/abin_E-S.h"
#include <vector>

using std::cout;
using std::endl;


template <typename T>
void hacerCamino_rec(const Abin<T>& A, T elem, typename Abin<T>::nodo n, std::vector<T>& camino)
{
    if(n != Abin<T>::NODO_NULO)
    {     
        if(A.elemento(n) == elem)
        {
            typename Abin<int>::nodo hijo = n;
            camino.push_back(A.elemento(n));
            while(A.padre(hijo) != Abin<int>::NODO_NULO)
            {
                camino.push_back(A.elemento(hijo));
                hijo = A.padre(hijo);
            }

            if(hijo == A.raiz())
                camino.push_back(A.elemento(hijo));
        }
        else
        {
            hacerCamino_rec(A, elem, A.hijoIzqdo(n), camino);
            hacerCamino_rec(A, elem, A.hijoDrcho(n), camino);
        }
    }
}

template <typename T>
std::vector<T> hacerCamino(const Abin<T>& A, T elem)
{
    std::vector<T> camino;
    hacerCamino_rec(A, elem, A.raiz(), camino);
    return camino;
}

template <typename T>
void buscar_Rec(const Abin<T>& A, T elem, typename Abin<T>::nodo n, typename Abin<T>::nodo& buscado)
{
    if(n != Abin<T>::NODO_NULO)
    {     
        if(A.elemento(n) == elem)
            buscado = n;
        else
        {
            buscar_Rec(A, elem, A.hijoIzqdo(n), buscado);
            buscar_Rec(A, elem, A.hijoDrcho(n), buscado);
        }
    }
}

template <typename T>
typename Abin<T>::nodo buscar(const Abin<T>& A, T elem)
{
    typename Abin<T>::nodo buscado = Abin<T>::NODO_NULO;
    buscar_Rec(A, elem, A.raiz(), buscado);
    return buscado;
}

template <typename T>
T AncestroComun(const Abin<T>& A, const T& elem1, const T& elem2)
{
    std::vector<T> camino1, camino2, ancestros;
    
    // Comprobamos que los dos elementos están en el árbol.
    typename Abin<T>::nodo n1 = buscar(A, elem1);
    typename Abin<T>::nodo n2 = buscar(A, elem2);

    T ancestro_comun;

    if(A.elemento(n1) == elem1 and A.elemento(n2) == elem2)
    {
        // Obtenemos los caminos desde la raíz hasta los nodos donde se encuentran los elementos.
        camino1 = hacerCamino(A, elem1);
        camino2 = hacerCamino(A, elem2);

        // Vamos recorriendo los vectores hasta encontrar el primer ancestro común, en el caso de que solo tengan uno
        // o el último ancestro común, en el caso de que tengan más ancestros (que serían sus abuelos, bisabuelos, etc).
        for(auto i = 0; i < camino1.size(); i++)
        {
            for(auto j = 0; j < camino2.size(); j++)
            {
                if(camino1[i] == camino2[j])
                    ancestros.push_back(camino1[i]);
            }
        }

        // Nos quedamos con el último ancestro, siendo el ancestro más cercano a los dos elementos.
        ancestro_comun = ancestros[0];
    }

    

    return ancestro_comun;
}

int main()
{
    Abin<int> A;
    
    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    cout << "*** Árbol Binario A ***" << endl;
    imprimirAbin(A);

    cout << endl << endl;

    typename Abin<int>::nodo nodo, nodo2;
    nodo = buscar(A, 8);
    nodo2 = buscar(A, 7);
    if(nodo != Abin<int>::NODO_NULO && nodo2 != Abin<int>::NODO_NULO)
        cout << "El primer elemento a buscar es -> " << A.elemento(nodo) << endl << "Y el segundo es -> " << A.elemento(nodo2) << endl;

    int ancestro = AncestroComun(A, 8, 7);
    cout << "El ancestro común entre " << A.elemento(nodo) << " y " << A.elemento(nodo2) << " es -> " << ancestro << endl;
}