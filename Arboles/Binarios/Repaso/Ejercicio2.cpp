/*
    Implemente una función que, dado un árbol, devuelva el número de nodos prósperos que existen en él. Se considera que un nodo
    es próspero si es estrictamente más rico que sus ascendientes, pero menos rico que sus descendientes.

    int prosperos(Abin<T> A)
    int prosperosRec(Abin<T>, Abin<T>::nodo nodo)
    bool esProspero(Abin<T> A, Abin<T>::nodo n)

    bool ascendientes(Abin<T> A, Abin<T>::nodo nodo)
    bool descendientes(Abin<T> A, Abin<T>::nodo nodo)

    ascendientes && descendiente
*/

#include "../Implementaciones/Abin.h"
#include "../Implementaciones/abin_E-S.h"

bool ascendientes(Abin<int>::nodo nodo, const Abin<int>& A)
{
    //Guardamos el nodo que queremos comprobar
    Abin<int>::nodo actual = nodo;

    //Repetimos el bucle hasta que lleguemos al raiz
    while(A.padre(nodo) != Abin<int>::NODO_NULO)
    {
        //Si se cumple ascendemos
        if(A.elemento(A.padre(nodo)) < A.elemento(actual))
            nodo = A.padre(nodo);
        else
            return false;
    }

    return true;
}

bool descendientesRec(typename Abin<int>::nodo nodo, const Abin<int>::nodo& actual, const Abin<int>& A) {
    if (nodo != Abin<int>::NODO_NULO) 
    {
        //Comprobamos si el nodo es menor que sus descendientes devolvemos false, sino continuamos
        if (A.elemento(nodo) < A.elemento(actual))
            return false;

        return descendientesRec(A.hijoIzqdo(nodo), actual, A) && descendientesRec(A.hijoDrcho(nodo), actual, A);
    }

    return true;
}

bool descendientes(Abin<int>::nodo nodo, const Abin<int>& A)
{
    return descendientesRec(nodo, nodo, A);
}

bool esProspero(Abin<int>::nodo nodo, const Abin<int>& A)
{
    if(nodo != Abin<int>::NODO_NULO)
    {
        //Si cumple las dos condiciones dicho nodo es prospero
        if(ascendientes(nodo, A) && descendientes(nodo, A))
            return true;
    }

    return false;
}

int prosperosRec(Abin<int>::nodo nodo, const Abin<int>& A)
{
    if(nodo != Abin<int>::NODO_NULO)
    {
        //Si el nodo es próspero lo sumamos y continuamos con su hijo izquierdo y derecho
        if(esProspero(nodo, A))
            return 1 + prosperosRec(A.hijoIzqdo(nodo), A) + prosperosRec(A.hijoDrcho(nodo), A);
        else
            return prosperosRec(A.hijoIzqdo(nodo), A) + prosperosRec(A.hijoDrcho(nodo), A);
    }

    return 0;
}

int prosperos(const Abin<int>& A)
{
    return prosperosRec(A.raiz(), A);
}

int main()
{

    typedef int tElto;
    const tElto fin = -1; // Fin de lectura.

    Abin<tElto> A;
    
    std::ifstream fe("Ej2.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    std::cout << "El numero de nodos prosperos del árbol A es: " << prosperos(A) << '\n';

    return 0;
}