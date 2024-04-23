//
// Created by Anton on 05/03/2024.
//
#include <iostream>
#include <cctype> // Para la función isdigit
#include "abin_enlazada.hpp"
#include "abin_E-S.h"

using namespace std;

struct expresion
{
    char operador;
    double operando;

};



istream& operator >>(istream& is, expresion& exp)
{
    std::cout << "Introduce el operador -> ";
    is >> exp.operador;

    std::cout << "Introduce el operando -> ";
    is >> exp.operando;

    return is;
}

ostream& operator <<(ostream& os, const expresion& exp)
{
    os << exp.operador << ", " << exp.operando << endl;

    return os;
}

bool operator != (const expresion& e1, const expresion& e2)
{
    return (e1.operador != e2.operador);
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

double OperacionAbin_rec(const Abin<expresion>& A, typename Abin<expresion>::nodo n)
{
    if(A.hijoIzqdo(n) == Abin<expresion>::NODO_NULO)
        return A.elemento(n).operando;

    switch (A.elemento(n).operador)
    {
        case '+':
            return OperacionAbin_rec(A, A.hijoIzqdo(n)) + OperacionAbin_rec(A, A.hijoDrcho(n));

        case '-':
            return OperacionAbin_rec(A, A.hijoIzqdo(n)) - OperacionAbin_rec(A, A.hijoDrcho(n));

        case '*':
            return OperacionAbin_rec(A, A.hijoIzqdo(n)) * OperacionAbin_rec(A, A.hijoDrcho(n));

        case '/':
            return OperacionAbin_rec(A, A.hijoIzqdo(n)) / OperacionAbin_rec(A, A.hijoDrcho(n));

    }
}

double OperacionAbin(const Abin<expresion>& exp)
{
    return OperacionAbin_rec(exp, exp.raiz());
}


int main()
{
    Abin<expresion> a;

    cout << "*** Mostramos el arbol binario A ***"<< endl;
    rellenarAbin(a, expresion{'#', 0.0}); // Desde std::cin

    cout << endl << "*** Mostramos el arbol binario A ***"<< endl;
    imprimirAbin(a);
}

/*
    Abin<expresion> A;
    A.insertarRaiz('*');
    
    if(A.elemento(n).isOper == false)
      return A.elemento(n).operando
    else 
      switch (A.elemento(n).operador):
        case '+'
          return operacionAbin(A, A.hijoIzqdo(n)) + operacionAbin(A, A.hijoDrcho(n));
          // así con los demás casos.

*/
