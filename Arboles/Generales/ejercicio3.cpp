#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

using namespace std;

template <typename T>
int alturaAgen(const Agen<T>& A)
{
    return alturaAgen_rec(A.raiz(), A);
}

template <typename T>
int alturaAgen_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int altura = 0;
    if(n == Agen<T>::NODO_NULO)
    {
        return altura;
    }
    else{
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            altura = max(1 + alturaAgen_rec(hijo, A), altura);
            hijo = A.hermDrcho(hijo);
        }
        
        return altura;
    }
}

template <typename T>
int desequilibrioAgen(const Agen<T>& A)
{
    return desequilibrioAgen_rec(A.raiz(), A);
}

template <typename T>
int desequilibrioAgen_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int desequilibrio = 0; int max = 0, min = 0;
    if(n == Agen<T>::NODO_NULO)
    {
        return desequilibrio;
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            max = std::max(std::max(alturaAgen_rec(hijo, A), alturaAgen_rec(A.hermDrcho(hijo), A)), max);
            min = std::min(std::min(alturaAgen_rec(hijo, A), alturaAgen_rec(A.hermDrcho(hijo), A)), min);
            desequilibrio = std::max(desequilibrioAgen_rec(hijo, A), max - min);
            hijo = A.hermDrcho(hijo);
        }
    }
    return desequilibrio;
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

    int altura = alturaAgen(A);
    int desequilibrio = desequilibrioAgen(A);

    cout << "Altura -> " << altura << endl;
    cout << endl << "Desequilibrio de este Agen -> " << desequilibrio << endl;

    return 0;
}