#include <iostream> // std::cout, std::endl;
#include <fstream> // Para meter los elementos del árbol en abin.dat
#include "../Binarios/P1/abin_enlazada.hpp"
#include "../Binarios/P1/abin_E-S.h"

// Espacios de nombres.
using std::cout;
using std::endl;
using std::ifstream;

void hundir(typename Abin<int>::nodo n, Abin<int>& A)
{
    if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
    {
        if(A.elemento(A.hijoIzqdo(n)) < A.elemento(A.hijoDrcho(n)))
        {
            int elem = A.elemento(A.hijoIzqdo(n));
            A.elemento(A.hijoIzqdo(n)) = A.elemento(n);
            A.elemento(n) = elem;
            hundir(A.hijoIzqdo(n), A);
        }
        else
        {
            int elem = A.elemento(A.hijoDrcho(n));
            A.elemento(A.hijoDrcho(n)) = A.elemento(n);
            A.elemento(n) = elem;
            hundir(A.hijoDrcho(n), A);
        }
    }

    else if (A.hijoIzqdo(n) != Abin<int>::NODO_NULO)
    {
        int elem = A.elemento(A.hijoIzqdo(n));
        A.elemento(A.hijoIzqdo(n)) = A.elemento(n);
        A.elemento(n) = elem;
        hundir(A.hijoIzqdo(n), A);
    }
    
    else if (A.hijoDrcho(n) != Abin<int>::NODO_NULO)
    {
        int elem = A.elemento(A.hijoDrcho(n));
        A.elemento(A.hijoDrcho(n)) = A.elemento(n);
        A.elemento(n) = elem;
        hundir(A.hijoDrcho(n), A);
    }
}

template <typename T>
void buscar(const T& elem, typename Abin<T>::nodo n, typename Abin<T>::nodo& nodobuscado, const Abin<T>& A)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(A.elemento(n) != elem)
        {
            buscar(elem, A.hijoIzqdo(n), nodobuscado, A);
            buscar(elem, A.hijoDrcho(n), nodobuscado, A);
        }
        else
            nodobuscado = n;
    }
}

void suprimir(const int& elem, Abin<int>& A)
{
    typename Abin<int>::nodo nodo_a_eliminar = Abin<int>::NODO_NULO;

    // Buscamos el nodo a eliminar.
    buscar(elem, A.raiz(), nodo_a_eliminar, A);

    // Lo hundimos.
    hundir(nodo_a_eliminar, A);

    // Una vez hundido, perderemos su referencia, así que lo volvemos a buscar.
    buscar(elem, A.raiz(), nodo_a_eliminar, A);
    
    // Ahora, si es hizq de su padre, lo eliminamos como hizq que es. Sino, lo contrario.
    if(A.elemento(A.hijoIzqdo(A.padre(nodo_a_eliminar))) == elem)
        A.eliminarHijoIzqdo(A.padre(nodo_a_eliminar));
    else
        A.eliminarHijoDrcho(A.padre(nodo_a_eliminar));
}




int main()
{
    Abin<int> A;
    cout << "\n*** Lectura de árbol A de abin.dat ***\n";
    ifstream fe("Abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, A);     // Desde fichero.
    fe.close();
    
    cout << "*** Mostramos el Abin ***" << endl;
    imprimirAbin(A);

    typename Abin<int>::nodo sol = Abin<int>::NODO_NULO;

    cout << "*** Árbol después de hundir el nodo anterior ***" << endl;
    suprimir(14, A);
    imprimirAbin(A);
}