//
// Created by Anton on 02/03/2024.
//
#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using namespace std;

template <typename T>
int numHijos(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if ((A.hijoIzqdo(n) != Abin<T>::NODO_NULO and A.hijoDrcho(n) != Abin<T>::NODO_NULO))
        return 2;

    else if ((A.hijoIzqdo(n) != Abin<T>::NODO_NULO or A.hijoDrcho(n) != Abin<T>::NODO_NULO))
        return 1;

    else return 0;
}

template <typename T>
bool pseudocompletoAbin(const Abin<T>& A)
{
    if(A.arbolVacio())
        return true;
    else return pseudocompletoAbin_rec(A.raiz(), A);
}

template <typename T>
bool pseudocompletoAbin_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    int alturaAbin = A.altura(A.raiz());

    if(n != Abin<T>::NODO_NULO)

    {
        if(alturaAbin - A.profundidad(n) == 1)
        {
            return (numHijos(n, A) == 0 or numHijos(n, A) == 2);
        }
        else
            return pseudocompletoAbin_rec(A.hijoIzqdo(n), A) and pseudocompletoAbin_rec(A.hijoDrcho(n), A);
    }
    else return true;
}

typedef char tElto;
const tElto fin = '#';

int main()
{
    Abin<char> abin;

    cout << "*** Mostramos el arbol binario ***"<< endl;
    rellenarAbin(abin, fin); // Desde std::cin

    cout << endl << "*** Mostramos el arbol binario ***"<< endl;
    imprimirAbin(abin);

    if(pseudocompletoAbin(abin))
        cout << "El arbol SI es pseudocompleto." << endl;
    else
        cout << "El arbol NO es pseudocompleto" << endl;
}
