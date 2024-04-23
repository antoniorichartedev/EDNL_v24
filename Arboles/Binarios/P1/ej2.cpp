//
// Created by Anton on 20/02/2024.
//
#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"
using namespace std;

template <typename T>
int alturaAbin(const Abin<T>& a, typename Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
        return 1 + max(alturaAbin(a, a.hijoIzqdo(n)), alturaAbin(a, a.hijoDrcho(n)));
    else
        return -1;
}

template <typename T>
int alturaAbin(const Abin<T>& a)
{
    if (a.arbolVacio())
        return 0;
    else
        return alturaAbin(a, a.raiz());
}

int main()
{
    Abin<char> abin;

    cout << "*** Rellenamos el arbol binario ***"<< endl;
    rellenarAbin(abin, '#');

    cout << endl << "*** Mostramos el arbol binario ***"<< endl;
    imprimirAbin(abin);

    cout << "*** Contamos la altura de dicho arbol binario ***" << endl;
    cout << "Altura -> " << alturaAbin(abin) << endl;
}