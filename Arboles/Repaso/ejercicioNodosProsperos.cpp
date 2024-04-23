/*

Dado un árbol A, calcula el número de nodos prósperos. Se dice que un nodo es próspero si tiene más
    dinero que sus ascendientes y menos dinero que sus descendientes.


    1. Main
    2. Ascendientes ->> bool
    3. Descendientes ->> bool
    4. Recorridos ->> int
    5. es_prospero ->> bool


*/
#include <iostream>
#include "../Binarios/P2/abin_enlazada.hpp"
#include "../Binarios/P2/abin_E-S.h"

using std::cout;
using std::endl;

bool ascendientes(const Abin<int> &A, typename Abin<int>::nodo n)
{
    if (n != Abin<int>::NODO_NULO)
        if (A.elemento(n) > A.elemento(A.padre(n)))
            return true;
        else
            return false;
    else
        return true;
}

bool descendientes(const Abin<int> &A, typename Abin<int>::nodo n)
{
    bool bandera = false;

    if (n != Abin<int>::NODO_NULO)
    {
        if (A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
        {
            if (A.elemento(n) < A.elemento(A.hijoIzqdo(n)) && A.elemento(n) < A.elemento(A.hijoDrcho(n)))
                bandera = true;
        }

        else if (A.hijoIzqdo(n) != Abin<int>::NODO_NULO)
        {
            if (A.elemento(n) < A.elemento(A.hijoIzqdo(n)))
                bandera = true;
        }

        else if (A.hijoDrcho(n) != Abin<int>::NODO_NULO)
        {
            if (A.elemento(n) < A.elemento(A.hijoDrcho(n)))
                bandera = true;
        }

        else bandera = true;
    }

    return bandera;
}

bool esProspero(const Abin<int> &A, typename Abin<int>::nodo n)
{
    if (n == A.raiz())
        if (descendientes(A, n))
            return true;
        else
            return false;
    else
    {
        if (ascendientes(A, n) && descendientes(A, n))
            return true;
        else
            return false;
    }
}

int nodosProsperos_rec(const Abin<int> &A, typename Abin<int>::nodo n)
{
    if(n != Abin<int>::NODO_NULO)
    {   
        if (esProspero(A, n))
            return 1 + nodosProsperos_rec(A, A.hijoIzqdo(n)) + nodosProsperos_rec(A, A.hijoDrcho(n));
        else
            return 0 + nodosProsperos_rec(A, A.hijoIzqdo(n)) + nodosProsperos_rec(A, A.hijoDrcho(n));
    }
    else return 0;
}

int nodosProsperos(const Abin<int> &A)
{
    return nodosProsperos_rec(A, A.raiz());
}

int main()
{
    Abin<int> A;

    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A);          // Desde fichero.
    fe.close();

    cout << "*** Árbol Binario A ***" << endl;
    imprimirAbin(A);

    cout << endl
         << endl;

    int nodosPros = nodosProsperos(A);
    cout << "Este árbol binario tiene " << nodosPros << " nodos prósperos." << endl;
}