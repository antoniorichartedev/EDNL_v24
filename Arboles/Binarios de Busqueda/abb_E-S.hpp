#include <iostream>
#include "abb.hpp"

using namespace std;

template <typename T>
void leer_abb(Abb<T>& A)
{
    char fin;
    T elem;
    do
    {
        cout << "Introduce un elemento -> ";
        cin >> elem;

        A.insertar(elem);

        cout << endl << "¿Desea seguir introduciendo elementos en el ABB? (s/n) -> ";
        cin >> fin;
        cout << endl;
    }while(fin != 'n');
}

template <typename T>
void imprimir_descendientes_abb(const Abb<T>& A)
{
    if(!A.vacio())
    {
        if(!A.izqdo().vacio())
        {
            cout << "Hijo izqdo de " << A.elemento() << " -> " << A.izqdo().elemento() << endl;
            imprimir_descendientes_abb(A.izqdo());
        }

        if(!A.drcho().vacio())
        {
            cout << "Hijo drcho de " << A.elemento() << " -> " << A.drcho().elemento() << endl;
            imprimir_descendientes_abb(A.drcho());
        }
    }
}


template <typename T>
void imprimir_abb(const Abb<T>& A)
{
    if(!A.vacio())
    {
        cout << "Raíz del árbol -> " << A.elemento() << endl;

        // Imprimimos los descendientes.
        imprimir_descendientes_abb(A);
       
    }
    else
        cout << "Árbol vacío." << endl;
}