/* 
    Comprueba que un Abin es un AVL (ABB equilibrado) 
*/

#include <iostream>
#include "../Binarios/P2/abin_enlazada.hpp"
#include "../Binarios/P2/abin_E-S.h"
#include <cmath>

using std::max;
using std::cout;
using std::endl;

template <typename T>
int DesequilibrioAbin(const Abin<T>& a)
{
    return DesequilibrioAbin_rec(a.raiz(), a);
}

template <typename T>
int DesequilibrioAbin_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return max(max(DesequilibrioAbin_rec(A.hijoIzqdo(n), A), DesequilibrioAbin_rec(A.hijoDrcho(n), A)), abs(A.altura(A.hijoIzqdo(n)) - A.altura(A.hijoDrcho(n))));
}

template <typename T>
bool esHoja(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        return true;
    else
        return false;
}

template <typename T>
void Abin_es_Abb_rec(const Abin<T>& A, typename Abin<T>::nodo n, bool& esAbb)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(!esHoja(n, A))
        {
            if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
            {
                if(A.elemento(A.hijoIzqdo(n)) < A.elemento(n) && A.elemento(A.hijoDrcho(n)) > A.elemento(n))
                {
                    Abin_es_Abb_rec(A, A.hijoIzqdo(n), esAbb);
                    Abin_es_Abb_rec(A, A.hijoDrcho(n), esAbb);
                }
            }
            else if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
            {
                if(A.elemento(A.hijoIzqdo(n)) < A.elemento(n))
                {
                    Abin_es_Abb_rec(A, A.hijoIzqdo(n), esAbb);
                }
            }
            else
            {
                if(A.elemento(A.hijoDrcho(n)) > A.elemento(n))
                {
                    Abin_es_Abb_rec(A, A.hijoDrcho(n), esAbb);
                }
            }
            
        }
        else
            esAbb = true;
    }
}

template <typename T>
bool Abin_es_Abb(const Abin<T>& A)
{
    bool esAbb = false;
    Abin_es_Abb_rec(A, A.raiz(), esAbb);
    return esAbb;
}

template <typename T>
bool Abin_es_AVL(const Abin<T>& A)
{
    bool esAVL = false;

    if(Abin_es_Abb(A))
    {
        int factorEq = DesequilibrioAbin(A);

        if(factorEq == 1 || factorEq == 0 || factorEq == -1)
            esAVL = true;
    }
 
    return esAVL;
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

    if(Abin_es_Abb(A))
        cout << "Este Abin es un Abb." << endl;
    else
        cout << "Este Abin no es un Abb." << endl;

    if(Abin_es_AVL(A))
        cout << "Además, es un AVL." << endl;
    else
        cout << "Pero no es un AVL." << endl;
}