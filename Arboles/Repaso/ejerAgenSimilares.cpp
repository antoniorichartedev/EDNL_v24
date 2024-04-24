/*

    Dos Agen son similares si tienen la misma ramificación y sus hojas son similares tanto en contenido
    como en posición. Implementar una función que me diga si dos Agen son similares o no.
    Nota: ten en cuenta que, si en una hoja, los contenidos son distintos, aunque la ramificación es correcta,
    NO son similares. Si resulta que un nodo que tiene hijos, tiene la misma ramificación que el otro,
    pero tiene distinto contenido, de momento son similares. Entonces, en las hojas tienen que tener
    el mismo contenido y posición mientras que, en los que no son hojas, no tiene por qué tener el mismo
    contenido, pero sí la misma ramificación.

    Para resolverlo, tenemos que tener en cuenta 4 casos:
        - Ambos agen son vacíos.
        - Uno es nulo y el otro no.
        - Ambos son hojas.
        - Si el nodo por el que estamos tiene hijos, exploramos. El núm. de hijos lo comprobamos
        con una función externa.

*/

#include <iostream>
#include "../Generales/agen.hpp"
#include "../Generales/agen_E-S.h"
#include <fstream>

using std::cout;
using std::endl;

template <typename T>
bool esHoja(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (A.hijoIzqdo(n) != Agen<T>::NODO_NULO)
        return false;
    else
        return true;
}

template <typename T>
int NumHijosAgen(typename Agen<T>::nodo n, const Agen<T> &A)
{
    int hijos = 0;

    if (!esHoja(n, A))
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            hijos++;
            hijo = A.hermDrcho(hijo);
        }
    }

    return hijos;
}

template <typename T>
bool esSimetrico_rec(const Agen<T> &A, const Agen<T> &B, typename Agen<T>::nodo nA, typename Agen<T>::nodo nB)
{
    // Caso 1: Ambos árboles son vacíos.
    if (A.arbolVacio() and B.arbolVacio())
        return true;

    // Caso 2: Un nodo es nulo y el otro no.
    else if ((nA != Agen<T>::NODO_NULO and nB == Agen<T>::NODO_NULO) or (nA == Agen<T>::NODO_NULO and nB != Agen<T>::NODO_NULO))
        return false;

    // Caso 3: Ambos nodos son hojas.
    else if (esHoja(nA, A) and esHoja(nB, B))
    {
        if (A.elemento(nA) == B.elemento(nB))
            return true;
        else
            return false;
    }

    // Caso 4: ambos nodos son nodos intermedios.
    else
    {
        if (NumHijosAgen(nA, A) == NumHijosAgen(nB, B))
        {
            typename Agen<T>::nodo hijo_de_nA = A.hijoIzqdo(nA);
            typename Agen<T>::nodo hijo_de_nB = B.hijoIzqdo(nB);
            bool fin = true;

            while (hijo_de_nA != Agen<T>::NODO_NULO and hijo_de_nB != Agen<T>::NODO_NULO and fin)
            {
                fin = fin and esSimetrico_rec(A, B, hijo_de_nA, hijo_de_nB);

                hijo_de_nA = A.hermDrcho(hijo_de_nA);
                hijo_de_nB = A.hermDrcho(hijo_de_nB);
            }

            return fin;
        }
        else
            return false;
    }
}

// agen.dat -> 1 2 -1 3 4 -1 -1 6 -1 -1
// agen2.dat -> 99 2 -1 7 4 -1 -1 6 -1 -1

template <typename T>
bool esSimetrico(const Agen<T> &A, const Agen<T> &B)
{
    return esSimetrico_rec(A, B, A.raiz(), B.raiz());
}

int main()
{
    Agen<int> A, B;

    std::ifstream fe("agen.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, A);          // Desde fichero.
    fe.close();

    cout << "*** Árbol General A ***" << endl;
    imprimirAgen(A);

    std::ifstream fe2("agen2.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe2, B);           // Desde fichero.
    fe2.close();

    cout << endl
         << endl
         << "*** Árbol General B ***" << endl;
    imprimirAgen(B);

    if (esSimetrico(A, B))
        cout << endl
             << "Ambos árboles generales SON SIMÉTRICOS." << endl;
    else
        cout << endl
             << "Ambos árboles generales NO SON simétricos." << endl;
}