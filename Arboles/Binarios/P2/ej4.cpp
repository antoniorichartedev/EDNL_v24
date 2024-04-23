//
// Created by Anton on 05/03/2024.
//
#include <iostream>
#include <cassert>
#include <cmath>
#include "ej4.hpp"
#include "abin_E-S.h"

/* **************** Implementación del TAD de este ejercicio **************** */

/* Definición del nodo nulo */
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(SIZE_MAX);

template <typename T>
Abin<T>::Abin(size_t altmax, const T& e_nulo):
    Hmax{altmax}, N{(size_t)pow(2, Hmax + 1) - 1}, ELTO_NULO{e_nulo}, elementos{new T[N]}
    {
        // Marcamos todas las celdas libres con ELTO_NULO.
        for(nodo i = 0; i < N; i++)
            elementos[i] = ELTO_NULO;
    }


template <typename T>
Abin<T>::Abin(const Abin<T> &a): elementos{new T[a.N]}, N{a.N}, Hmax{a.Hmax}, ELTO_NULO{a.ELTO_NULO}
{
    // Copiamos el vector.
    for(size_t i = 0; i < N; i++)
        elementos[i] = a.elementos[i];
}

template <typename T>
Abin<T> &Abin<T>::operator=(const Abin<T> &A)
{
    if(this != &A)
    {
        if(N != A.N)
        {
            delete[] elementos;
            N = A.N;
            Hmax = A.Hmax;
            elementos = new T[N];
        }

        ELTO_NULO = A.ELTO_NULO;

        // Copiamos el vector.
        for(size_t i = 0; i < N; i++)
            elementos[i] = A.elementos[i];
    }

    return *this;
}

template <typename T>
void Abin<T>::insertarRaiz(const T &e)
{
    // Si la raíz es nula, podemos introducir el elemento.
    assert(elementos[N/2] == ELTO_NULO);

    elementos[N/2] = e;
}

template <typename T>
void Abin<T>::insertarHijoIzqdo(Abin::nodo n, const T &e)
{
    // Calculamos h.
    unsigned h = altura(n);

    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    // El hizq cabe en el vector.
    assert(n - pow(2, h - 1) < N);

    // La celda donde vamos a colocar ese hizq tiene que estar libre.
    assert(elementos[n - (size_t)pow(2, h - 1)] == ELTO_NULO);

    elementos[n - (size_t)pow(2, h - 1)] = e;
}

template <typename T>
void Abin<T>::insertarHijoDrcho(Abin::nodo n, const T &e)
{
    // Calculamos h.
    unsigned h = altura(n);

    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    // El hder cabe en el vector.
    assert(n + pow(2, h - 1) < N);

    // La celda donde vamos a colocar ese hder tiene que estar libre.
    assert(elementos[n + (size_t)pow(2, h - 1)] == ELTO_NULO);

    elementos[n + (size_t)pow(2, h - 1)] = e;
}

template <typename T>
T &Abin<T>::elemento(Abin::nodo n)
{
    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    return elementos[n];
}

template <typename T>
const T &Abin<T>::elemento(Abin::nodo n) const
{
    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    return elementos[n];
}

template <typename T>
Abin<T>::nodo Abin<T>::hijoIzqdo(Abin::nodo n) const
{
    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    // Calculamos h.
    unsigned h = altura(n);

    return (elementos[n - (size_t)pow(2, h - 1)] == ELTO_NULO) ? NODO_NULO : n - (size_t)pow(2, h-1);
}

template <typename T>
Abin<T>::nodo Abin<T>::hijoDrcho(Abin::nodo n) const
{
    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    // Calculamos h.
    unsigned h = altura(n);

    return (elementos[n + (size_t)pow(2, h - 1)] == ELTO_NULO) ? NODO_NULO : n + (size_t)pow(2, h-1);
}

template <typename T>
bool Abin<T>::arbolVacio() const
{
    return elementos[N/2] == ELTO_NULO;
}

template <typename T>
Abin<T>::nodo Abin<T>::padre(Abin::nodo n) const
{
    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    // Comprobamos si es hizq o hder.
    unsigned h = altura(n);

    // Si es hizq...
    if((n % (size_t)pow(2, h + 2)) == pow(2, h) - 1)
        return (elementos[n + (size_t)pow(2, h)] == ELTO_NULO) ? NODO_NULO : n + (size_t)pow(2, h);
    else
        return (elementos[n - (size_t)pow(2, h)] == ELTO_NULO) ? NODO_NULO : n - (size_t)pow(2, h);

}

template <typename T>
Abin<T>::nodo Abin<T>::raiz() const
{
    return (elementos[N/2] == ELTO_NULO) ? NODO_NULO : N/2;
}

template <typename T>
Abin<T>::~Abin()
{
    delete[] elementos;
}

template <typename T>
void Abin<T>::eliminarRaiz()
{
    // La raíz no es un ELTO_NULO.
    assert(elementos[N/2] != ELTO_NULO);

    // Hay que ver también que la raíz es hoja.
    unsigned ubiraiz = N/2;
    assert(elementos[ubiraiz - (size_t)pow(2, Hmax - 1)] == ELTO_NULO and elementos[ubiraiz + (size_t)pow(2, Hmax - 1)] == ELTO_NULO);

    // Si no es un ELTO_NULO, pero sus hijos si lo son, entonces ponemos la celda de la raíz a ELTO_NULO.
    elementos[N/2] = ELTO_NULO;
}

template <typename T>
void Abin<T>::eliminarHijoIzqdo(Abin::nodo n)
{
    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    // Aparte, tiene que ser una hoja.
    assert(elementos[n - (size_t)pow(2, Hmax - 1)] == ELTO_NULO and elementos[n + (size_t)pow(2, Hmax - 1)] == ELTO_NULO);

    // Si cumple con las precondiciones antedichas, eliminamos el hizq.
    elementos[n] == ELTO_NULO;
}

template <typename T>
void Abin<T>::eliminarHijoDrcho(Abin::nodo n)
{
    // Nodo válido.
    assert(n >= 0 and n < N);

    // El nodo no es un ELTO_NULO.
    assert(elementos[n] != ELTO_NULO);

    // Aparte, tiene que ser una hoja.
    assert(elementos[n - (size_t)pow(2, Hmax - 1)] == ELTO_NULO and elementos[n + (size_t)pow(2, Hmax - 1)] == ELTO_NULO);

    // Si cumple con las precondiciones antedichas, eliminamos el hizq.
    elementos[n] == ELTO_NULO;
}

template <typename T>
int Abin<T>::altura(Abin::nodo n) const
{
    return Hmax - profundidad(n);
}

template <typename T>
int Abin<T>::profundidad(Abin::nodo n) const
{
    if(n == Abin<T>::NODO_NULO)
        return -1;
    else
        return 1 + profundidad(padre(n));
}

typedef char tElto;
const tElto fin = '#';

int main()
{
    Abin<char> a(3, '@');

    cout << "*** Mostramos el arbol binario A ***"<< endl;
    rellenarAbin(a, fin); // Desde std::cin

    cout << endl << "*** Mostramos el arbol binario A ***"<< endl;
    imprimirAbin(a);
}