//
// Created by Anton on 20/02/2024.
//
#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"
using namespace std;


int main()
{
    Abin<char> abin;

    cout << "*** Rellenamos el arbol binario ***"<< endl;
    rellenarAbin(abin, '#');

    cout << endl << "*** Mostramos el arbol binario ***"<< endl;
    imprimirAbin(abin);

    cout << "Altura del arbol -> " << abin.altura(abin.raiz()) << endl;
    cout << "Profundidad del arbol -> " << abin.profundidad(abin.hijoDrcho(abin.hijoIzqdo(abin.hijoDrcho(abin.hijoIzqdo(abin.raiz()))))) << endl;
}