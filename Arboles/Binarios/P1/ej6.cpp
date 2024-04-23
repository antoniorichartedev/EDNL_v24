//
// Created by Anton on 02/03/2024.
//
#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"
#include <fstream>
#include <cmath>

using namespace std;

template <typename T>
int DesequilibrioAbin(const Abin<T>& a)
{
    return DesequilibrioAbin_rec(a.raiz(), a);
}

template <typename T>
int DesequilibrioAbin_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return max(max(DesequilibrioAbin_rec(A.hijoIzqdo(n), A), DesequilibrioAbin_rec(A.hijoDrcho(n), A)), abs(A.altura(A.hijoIzqdo(n)) - A.altura(A.hijoDrcho(n))));
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

    cout << "Desequilibrio del arbol -> " << DesequilibrioAbin(abin) << endl;
}
