/*
    Considere un árbol A, en el que puede suponer que no hay elementos repetidos. Dado un elemento x,
    devuelve el camino que existe entre la raíz y el nodo cuyo elemento es x, si existe.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using std::cout;
using std::endl;
using std::vector;

typedef char tElto;
const tElto fin = '#'; // Fin de lectura.

template <typename T>
vector<T> CaminoAbin(const Abin<T>& A, const T& elem)
{
    vector<T> camino;
    CaminoAbin_rec(A.raiz(), A, elem, camino);
    return camino;
}

template <typename T>
void CaminoAbin_rec(typename Abin<T>::nodo n, const Abin<T>& A, const T& elem, vector<T>& camino)
{
    if(n != Abin<T>::NODO_NULO)
    {
        // En el momento en el que encontremos el elemento, vamos a almacenar el camino en el vector.
        if(A.elemento(n) == elem)
        {
            typename Abin<T>::nodo aux = n;

            while(A.padre(aux) != Abin<T>::NODO_NULO)
            {
                camino.insert(camino.begin(), A.elemento(aux));
                aux = A.padre(aux);
            }

            // En el while, la raíz no se llega a introducir en el vector porque no tiene padre. Así que lo introducimos.
            camino.insert(camino.begin(), A.elemento(A.raiz()));
        }

        else
        {
            // Si no es el elemento, seguimos buscando el mismo por las ramas.
            CaminoAbin_rec(A.hijoIzqdo(n), A, elem, camino);
            CaminoAbin_rec(A.hijoDrcho(n), A, elem, camino);
        }
    }
}


int main()
{
    Abin<tElto> A;

    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A);     // Desde fichero.
    fe.close();
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); // En std::cout

    vector<char> camino = CaminoAbin(A, 'f');

    // Mostramos el vector con el camino.
    cout << "Camino hasta el elemento f -> ";
    for(const auto& i : camino)
        cout << i << " ";

    cout << endl;

    return 0;
}