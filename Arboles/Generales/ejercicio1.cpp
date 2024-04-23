#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

using namespace std;

template <typename T>
int NumHijos(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int hijos = 0;

    if(n != Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);

        while(hijo != Agen<T>::NODO_NULO)
        {
            hijos++;
            hijo = A.hermDrcho(hijo);
        }
    }

    return hijos;
}

template <typename T>
void gradoAgen_rec(typename Agen<T>::nodo n, const Agen<T>& A, int& grado)
{
    grado = std::max(grado, NumHijos(n, A));

    typename Agen<int>::nodo hijo = A.hijoIzqdo(n);

    while(hijo != Agen<int>::NODO_NULO)
    {
        gradoAgen_rec(hijo, A, grado);
        hijo = A.hermDrcho(hijo);
    }
}

template <typename T>
int gradoAgen(const Agen<T>& A)
{
    int gradoMax = 0;
    gradoAgen_rec(A.raiz(), A, gradoMax);
    return gradoMax;
}

/*
  Corregido por Juanfran.
  void gradoAgen_rec(nodo n, Agen A, int& gradoMax)
  {
    int grado = max(gradomax, Numhijos(n, A));
    nodo nodoaux = A.hijoIzqdo(n);
    
    while(nodoaux != NODO_NULO)
    {
      gradoAgen_rec(nodoaux, A, grado);
      nodoaux = A.hermDrcho(nodoaux);
    }
  }

*/
int main()
{
    Agen<int> A;
    cout << "\n*** Lectura de árbol A de agen.dat ***\n";
    ifstream fe("agen.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, A);     // Desde fichero.
    fe.close();

    cout << "\n*** Mostrar árbol A ***\n";
    imprimirAgen(A); // En std::cout

    int grado = gradoAgen(A);

    cout << "El grado del Agen es -> " << grado << endl;
}
