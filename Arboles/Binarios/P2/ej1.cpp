#include <iostream>
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;
const tElto fin = '#';

template <typename T>
bool SimilarAbin_rec(const Abin<T>& A, const Abin<T>& B, typename Abin<T>::nodo nA, typename Abin<T>::nodo nB);

template <typename T>
bool SimilarAbin(const Abin<T>& A, const Abin<T>& B)
{
    if(A.arbolVacio() and B.arbolVacio())
        return true;
    else return SimilarAbin_rec(A, B, A.raiz(), B.raiz());
}

template <typename T>
bool SimilarAbin_rec(const Abin<T>& A, const Abin<T>& B, typename Abin<T>::nodo nA, typename Abin<T>::nodo nB)
{
    if(nA == Abin<T>::NODO_NULO and nB == Abin<T>::NODO_NULO)
        return true;
    else
    {
        if(nA != Abin<T>::NODO_NULO)

            if(nB != Abin<T>::NODO_NULO)

                if((A.hijoIzqdo(nA) != Abin<T>::NODO_NULO and B.hijoIzqdo(nB) != Abin<T>::NODO_NULO) or
                        (A.hijoDrcho(nA) != Abin<T>::NODO_NULO and B.hijoDrcho(nB) != Abin<T>::NODO_NULO))
                    return SimilarAbin_rec(A, B, A.hijoIzqdo(nA), B.hijoIzqdo(nB)) and SimilarAbin_rec(A, B, A.hijoDrcho(nA), B.hijoDrcho(nB));

                else return true;

            else return false;

        else return false;
    }
}

int main()
{
    Abin<char> a, b;

    cout << "*** Mostramos el arbol binario A ***"<< endl;
    rellenarAbin(a, fin); // Desde std::cin

    cout << endl << "*** Mostramos el arbol binario A ***"<< endl;
    imprimirAbin(a);

    cout << endl << "*** Mostramos el arbol binario B ***"<< endl;
    rellenarAbin(b, fin); // Desde std::cin

    cout << endl << "*** Mostramos el arbol binario B ***"<< endl;
    imprimirAbin(b);

    if(SimilarAbin(a, b))
        cout << "Los arboles SI son similares." << endl;
    else
        cout << "Los arboles NO son similares." << endl;
}
