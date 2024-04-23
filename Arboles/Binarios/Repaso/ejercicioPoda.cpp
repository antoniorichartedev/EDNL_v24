/*
    Implemente una función que, dado un árbol A y un elemento T, realice la poda del subárbol cuya raíz
    tiene por elemento T. Puede suponer que no hay elementos repetidos en el árbol.
*/



#include <iostream>
#include <fstream>
#include <vector>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using std::cout;
using std::endl;

typedef char tElto;
const tElto fin = '#'; // Fin de lectura.

template <typename T>
bool esHoja(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO and A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        return true;
    else 
        return false;
}

template <typename T>
void destruir_nodos(typename Abin<T>::nodo n, Abin<T>& A, const T& elem)
{
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
    {
        if (!esHoja(A.hijoIzqdo(n), A))
            destruir_nodos(A.hijoIzqdo(n), A, elem);
        else
            A.eliminarHijoIzqdo(n);
    }

    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    {
        if (!esHoja(A.hijoDrcho(n), A))
            destruir_nodos(A.hijoDrcho(n), A, elem);
        else
            A.eliminarHijoDrcho(n);
    }

    if (A.raiz() != Abin<T>::NODO_NULO and esHoja(A.raiz(), A))
        A.eliminarRaiz();

    if (esHoja(n, A) and A.elemento(A.hijoIzqdo(A.padre(n))) == A.elemento(n))
        A.eliminarHijoIzqdo(A.padre(n));
    else
        A.eliminarHijoDrcho(A.padre(n));
}

template <typename T>
void poda(Abin<T>& A, const T& elem)
{
    if(A.elemento(A.raiz()) == elem)
        poda_rec(A.raiz(), A, elem);
    else
    {
        poda_rec(A.hijoIzqdo(A.raiz()), A, elem); 
        poda_rec(A.hijoDrcho(A.raiz()), A, elem);
    }
        
}


template <typename T>
void poda_rec(typename Abin<T>::nodo n, Abin<T>& A, const T& elem)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(A.elemento(n) == elem)
        {
            destruir_nodos(n, A, elem);
        }
        else
        {
            poda_rec(A.hijoIzqdo(n), A, elem);
            poda_rec(A.hijoDrcho(n), A, elem);
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

    // Podamos árbol.
    poda(A, 'b');

    // Imprimimos el resultado.
    cout << endl << "*** Árbol después de podar. ***" << endl;
    imprimirAbin(A);

    return 0;
}