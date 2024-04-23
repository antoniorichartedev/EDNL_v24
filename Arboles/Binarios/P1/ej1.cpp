#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;
const tElto fin = '#'; // Fin de lectura. 

template <typename T>
int contarNodos(const Abin<T>& abin, typename Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
        return 1 + contarNodos(abin, abin.hijoIzqdo(n)) + contarNodos(abin, abin.hijoDrcho(n));
    else return 0;
}

template <typename T>
int contarNodos(const Abin<T>& abin)
{
    if(abin.arbolVacio())
        return 0;
    else
        return contarNodos(abin, abin.raiz());
}


int main()
{
    Abin<int> abin;

    cout << "*** Rellenamos el arbol binario ***"<< endl;
    rellenarAbin(abin, -1);

    cout << endl << "*** Mostramos el arbol binario ***"<< endl;
    imprimirAbin(abin);

    cout << "*** Contamos el nº de nodos de dicho arbol binario ***" << endl;
    cout << "Nodos -> " << contarNodos(abin) << endl;
}

