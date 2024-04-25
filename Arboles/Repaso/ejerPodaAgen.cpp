/*

    Dado un árbol general de enteros A y un elemento x, haz la poda del subárbol cuya raíz tiene como elemento x.

*/
#include <iostream>
#include "../Generales/agen.hpp"
#include "../Generales/agen_E-S.h"
#include <fstream>

using std::cout;
using std::endl;

template <typename T>
bool esHoja(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (A.hijoIzqdo(n) != Agen<T>::NODO_NULO)
        return false;
    else
        return true;
}

template <typename T>
void buscar(const Agen<int>& A, T elem, typename Agen<T>::nodo n, typename Agen<T>::nodo& nodo_a_buscar)
{
    if(n != Agen<T>::NODO_NULO)
    {
        if(A.elemento(n) == elem)
            nodo_a_buscar = n;
        else
        {
            typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
            while(hijo != Agen<T>::NODO_NULO)
            {
                buscar(A, elem, hijo, nodo_a_buscar);
                hijo = A.hermDrcho(hijo);
            }
        }
    }
}

void destruir_nodos(typename Agen<int>::nodo n, Agen<int>& A)
{
    if(n != Agen<int>::NODO_NULO)
    {
        typename Agen<int>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<int>::NODO_NULO)
        {
            destruir_nodos(hijo, A);
            hijo = A.hijoIzqdo(n);
        }

        if(esHoja(n, A) && A.hijoIzqdo(A.padre(n)) != Agen<int>::NODO_NULO && A.elemento(n) == A.elemento(A.hijoIzqdo(A.padre(n))))
            A.eliminarHijoIzqdo(A.padre(n));
        else if(esHoja(n, A) && n == A.raiz())
            A.eliminarRaiz(); 
    }
}


void podaAgen(Agen<int>& A, int elem)
{
    if(!A.arbolVacio())
    {
        typename Agen<int>::nodo n = Agen<int>::NODO_NULO;
        buscar(A, elem, A.raiz(), n);

        if(n != Agen<int>::NODO_NULO)
        {
            destruir_nodos(n, A);
        

            if(esHoja(n,A) && A.elemento(n) == A.elemento(A.hijoIzqdo(A.padre(n))))
                A.eliminarHijoIzqdo(A.padre(n));
            else if (esHoja(n, A) && n == A.raiz())
                A.eliminarRaiz();
            else
            {
                typename Agen<int>::nodo hijo = A.hijoIzqdo(A.padre(n));
                while (A.elemento(A.hermDrcho(hijo)) != elem)
                    hijo = A.hermDrcho(hijo);

                A.eliminarHermDrcho(hijo);
            }

        }
    }
}

int main()
{
    Agen<int> A;

    std::ifstream fe("agen.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, A);          // Desde fichero.
    fe.close();

    cout << "*** Árbol General A antes de la poda ***" << endl;
    imprimirAgen(A);

    typename Agen<int>::nodo bus = Agen<int>::NODO_NULO;
    buscar(A, 9, A.raiz(), bus);

    if(bus != Agen<int>::NODO_NULO)
        cout << "El elemento se encuentra en el árbol general -> " << A.elemento(bus) << endl << endl;

    
    cout << "--- Podamos el subárbol que tiene como raíz el elemento x = 9 ---" << endl;
    podaAgen(A, 9);

    cout << "*** Árbol General A después de la poda ***" << endl;
    imprimirAgen(A);

}