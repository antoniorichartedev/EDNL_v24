/*
    Dado un árbol A, calcula el número de nodos prósperos. Se dice que un nodo es próspero si tiene más
    dinero que sus ascendientes y menos dinero que sus descendientes.


    1. Main
    2. Ascendientes ->> bool
    3. Descendientes ->> bool
    4. Recorridos ->> int
    5. es_prospero ->> bool

    para el recorrido
    {
        si es_prospero(n, A)
            return 1 + hijoizq(n) + hijoder(n)
        si_no
            return hijoizq(n) + hijoder(n)
    }

    para los descendientes (hay que pasarle el nodo, el árbol y el elemento)
    {
        si n == NODO_NULO
            return true;
        si_no
            if((A.hijoizq(n) and A.hijoder(n)) and (A.elemento(A.hijoIzq(n)) > elem))
            {
                return descendientes(A.hijoizq(n), A) and descendientes(A.hijoder(n), A)
            }
            else return false;

    }
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using std::cout;
using std::endl;

typedef int tElto;
const tElto fin = -1; // Fin de lectura.

template <typename T>
bool ascendientes(typename Abin<T>::nodo n, const Abin<T>& A)
{
    return ascendientes_rec(n, A, A.elemento(n));
}

template <typename T>
bool ascendientes_rec(typename Abin<T>::nodo n, const Abin<T> &A, const T &elemActual)
{

    typename Abin<T>::nodo aux = n;
    while (A.padre(aux) != Abin<T>::NODO_NULO)
    {
        if (elemActual < A.elemento(A.padre(aux)))
            return false;

        aux = A.padre(aux);
    }

    return true;
}

template <typename T>
bool descendientes(typename Abin<T>::nodo n, const Abin<T>& A)
{
    return descendientes_rec(n, A, n);
}


// Nota: actual es el nodo al que le vamos a mirar sus descendientes, mientras que n será alguno de sus descendientes.
template <typename T>
bool descendientes_rec(typename Abin<T>::nodo n, const Abin<T> &A, typename Abin<T>::nodo actual)
{
    if (n == Abin<T>::NODO_NULO)
        return true;
    else
    {
        if (A.elemento(actual) > A.elemento(n))
        {
            return false;
        }
        else
            return descendientes_rec(A.hijoIzqdo(n), A, actual) and descendientes_rec(A.hijoDrcho(n), A, actual);;
    }
}

template <typename T>
bool es_prospero(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n != Abin<T>::NODO_NULO)
    {
        if(ascendientes(n, A) and descendientes(n, A))
            return true;
    }

    return false;
}

template <typename T>
int nodosProsperos(const Abin<T> &A)
{
    return nodosProsperos_rec(A.raiz(), A);
}

template <typename T>
int nodosProsperos_rec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
    {
        if (es_prospero(n, A))
            return 1 + nodosProsperos_rec(A.hijoIzqdo(n), A) + nodosProsperos_rec(A.hijoDrcho(n), A);
        else
            return nodosProsperos_rec(A.hijoIzqdo(n), A) + nodosProsperos_rec(A.hijoDrcho(n), A);
    }
}

int main()
{
    Abin<tElto> A;

    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A);          // Desde fichero.
    fe.close();
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); // En std::cout

    int nodos = nodosProsperos(A);

    cout << "Número de nodos prósperos -> " << nodos << endl;
}