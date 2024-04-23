/*
    Implemente una función que, dado un árbol A y un elemento T, realice la poda del subárbol cuya raíz
    tiene por elemento T. Puede suponer que no hay elementos repetidos en el árbol.
*/

#include <iostream>
#include "../Binarios/P2/abin_enlazada.hpp"
#include "../Binarios/P2/abin_E-S.h"


using std::cout;
using std::endl;

template <typename T>
void buscar_Rec(const Abin<T>& A, T elem, typename Abin<T>::nodo n, typename Abin<T>::nodo& buscado)
{
    if(n != Abin<T>::NODO_NULO)
    {     
        if(A.elemento(n) == elem)
            buscado = n;
        else
        {
            buscar_Rec(A, elem, A.hijoIzqdo(n), buscado);
            buscar_Rec(A, elem, A.hijoDrcho(n), buscado);
        }
    }
}

template <typename T>
typename Abin<T>::nodo buscar(const Abin<T>& A, T elem)
{
    typename Abin<T>::nodo buscado = Abin<T>::NODO_NULO;
    buscar_Rec(A, elem, A.raiz(), buscado);
    return buscado;
}

template <typename T>
bool esHoja(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        return true;
    else return false;
}


template <typename T>
void destruir_nodos(Abin<T>& A, typename Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
        {
            if(esHoja(A.hijoIzqdo(n), A))
                A.eliminarHijoIzqdo(n);
            else
                destruir_nodos(A, A.hijoIzqdo(n));
        }

        if(A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        {
            if(esHoja(A.hijoDrcho(n), A))
                A.eliminarHijoDrcho(n);
            else
                destruir_nodos(A, A.hijoDrcho(n));
        }

        if(esHoja(n, A))
            if(A.hijoIzqdo(A.padre(n)) != Abin<T>::NODO_NULO and A.elemento(n) == A.elemento(A.hijoIzqdo(A.padre(n))))
                A.eliminarHijoIzqdo(A.padre(n));
            else
                A.eliminarHijoDrcho(A.padre(n));
    }
} 

template <typename T>
void podarAbin(Abin<T>& A, typename Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
    {
        typename Abin<T>::nodo raiz_subarbol_a_eliminar = Abin<T>::NODO_NULO;
        raiz_subarbol_a_eliminar = buscar(A, A.elemento(n));

        if(raiz_subarbol_a_eliminar != Abin<T>::NODO_NULO)
        {
            destruir_nodos(A, raiz_subarbol_a_eliminar);
        }
    }
}


int main()
{
    Abin<int> A;
    
    std::ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    cout << "*** Árbol Binario A ***" << endl;
    imprimirAbin(A);

    cout << endl << endl;

    typename Abin<int>::nodo nodo;
    nodo = buscar(A, 21);
    if(nodo != Abin<int>::NODO_NULO)
        cout << "El elemento a buscar es -> " << A.elemento(nodo) << endl;
        if(esHoja(nodo, A))
            cout << "Encima, el nodo es hoja." << endl;

    podarAbin(A, nodo);

    cout << endl << endl << "*** Árbol Binario A después de podar desde el elemento 21 ***" << endl;
    imprimirAbin(A);
}