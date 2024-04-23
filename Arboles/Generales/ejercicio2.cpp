#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

using namespace std;

template <typename T>
int profundidadAgen(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidadAgen(A.padre(n), A);
    }
}


int main()
{
    Agen<int> A;
    cout << "\n*** Lectura de árbol A de agen.dat ***\n";
    ifstream fe("agen.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, A);     // Desde fichero.
    fe.close();

    cout << "\n*** Mostrar árbol A ***\n";
    imprimirAgen(A); // En std::cout

    int profundidad = profundidadAgen(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), A);

    cout << "La profundidad desde el nodo cuyo elemento es " << A.elemento(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())))) << ", es de -> " << profundidad << endl;
}