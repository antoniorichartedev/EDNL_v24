/*
    Considere un árbol A, en el que puede suponer que no hay elementos repetidos. Dado un elemento x,
    devuelve el camino que existe entre la raíz y el nodo cuyo elemento es x, si existe.
*/


#include <iostream>
#include "../Binarios/P2/abin_enlazada.hpp"
#include "../Binarios/P2/abin_E-S.h"
#include <vector>

using std::cout;
using std::endl;

template <typename T>
void buscar_Rec(const Abin<T>& A, T elem, typename Abin<T>::nodo n, std::vector<T>& camino)
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
            buscar_Rec(A, elem, A.hijoIzqdo(n), camino);
            buscar_Rec(A, elem, A.hijoDrcho(n), camino);
        }
    }
}

template <typename T>
std::vector<T> buscar(const Abin<T>& A, T elem)
{
    std::vector<T> camino;
    buscar_Rec(A, elem, A.raiz(), camino);
    return camino;
}

int main()
{
    Abin<int> A;
    
    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    cout << "*** Árbol Binario A ***" << endl;
    imprimirAbin(A);
    
    std::vector<int> camino;
    camino = buscar(A, 99);

    cout << "Camino realizado -> ";
    for(auto i = camino.size() - 1; i > 0; i--)
        cout << camino[i] << " ";
    cout << endl;
}