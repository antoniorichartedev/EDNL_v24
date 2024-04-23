//
// Created by Anton on 05/03/2024.
//

#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;
const tElto fin = '#';

template <typename T>
void ReflejadoAbin_rec(const Abin<T>& B, Abin<T>& BR, typename Abin<T>::nodo nB, typename Abin<T>::nodo nBR)
{
    // La razón por la que no comprobamos si el nodo que recibo de B es nodo nulo
    // es porque no hace falta, ya que si es nodo nulo, como la función esta es void
    // no ocurrirá nada en caso de que ese caso ocurra.
        if (B.hijoIzqdo(nB) != Abin<T>::NODO_NULO) {
            BR.insertarHijoDrcho(nBR, B.elemento(B.hijoIzqdo(nB)));
            ReflejadoAbin_rec(B, BR, B.hijoIzqdo(nB), BR.hijoDrcho(nBR));
        }

        if (B.hijoDrcho(nB) != Abin<T>::NODO_NULO) {
            BR.insertarHijoIzqdo(nBR, B.elemento(B.hijoDrcho(nB)));
            ReflejadoAbin_rec(B, BR, B.hijoDrcho(nB), BR.hijoIzqdo(nBR));
        }
}

template <typename T>
Abin<T> ReflejadoAbin(const Abin<T>& B)
{
    Abin<T> BR{};

    if(B.arbolVacio())
        return BR;
    else
    {
        BR.insertarRaiz(B.elemento(B.raiz()));
        ReflejadoAbin_rec(B, BR, B.raiz(), BR.raiz());
        return BR;
    }
}



int main()
{
    Abin<char> a, b;

    cout << "*** Mostramos el arbol binario A ***"<< endl;
    rellenarAbin(a, fin); // Desde std::cin

    cout << endl << "*** Mostramos el arbol binario A ***"<< endl;
    imprimirAbin(a);

    b = ReflejadoAbin(a);

    cout << endl << "*** Mostramos el arbol binario A, pero reflejado ***"<< endl;
    imprimirAbin(b);
}
