//
// Created by Anton on 20/02/2024.
//
#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"
using namespace std;

template <typename T>
int ProfundidadAbin(const Abin<T>& a, typename Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
        return 1 + ProfundidadAbin(a, a.padre(n));
    else
        return -1;
}

int main()
{
    Abin<char> abin;

    cout << "*** Rellenamos el arbol binario ***"<< endl;
    rellenarAbin(abin, '#');

    cout << endl << "*** Mostramos el arbol binario ***"<< endl;
    imprimirAbin(abin);

    cout << "*** Contamos la profundidad de dicho arbol binario ***" << endl;
    cout << "Profundidad -> " << ProfundidadAbin(abin, abin.hijoDrcho(abin.hijoIzqdo(abin.hijoDrcho(abin.hijoIzqdo(abin.raiz()))))) << endl;
}