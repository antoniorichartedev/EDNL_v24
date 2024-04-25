/*

    Teniendo una familia representada con un árbol general, un nodo padre tiene que repartir su 
    patrimonio y sus propiedades entre sus descendientes. Haz ese reparto de forma equitativa. 
    Cuando se haya repartido el patrimonio y sus propiedades con los hijos, esos hijos tienen que,
    de manera recursiva, repartir ese patrimonio y las propiedades de la misma forma.
    Nota: si estamos repartiendo el patrimonio y las propiedades entre los hijos, si un hijo tiene
    más hijos, ese es el que más se lleva por ejemplo.

    Padre tiene -> 40k€, un Aston Martin y una casa en la playa.
    Ese padre tiene 4 hijos, de forma que:
        - Hijo 1: no tiene hijos, entonces se lleva 10k€
        - Hijo 2: tiene 3 hijos, se lleva 10k€ y el Aston Martin.
        - Hijo 3: no tiene hijos, se lleva 10k€
        - Hijo 4: tiene 2 hijos, se lleva 10k€ y la casa en la playa.

    Luego, el hijo 2 y 4 tienen que repartir lo que han recibido con sus hijos y así sucesivamente.

    Para hacer esto:
        - Contar el nHijos del nodo por el que estamos iterando y encontrar el nodo que más hijos tenga.
        - Actualizamos el nodo por el que estamos iterando.
        - Hacemos la llamada recursiva con el hizq del nodo y luego pasamos al hermano derecho del hizq.

*/

#include <iostream>
#include "../Generales/agen.hpp"
#include "../Generales/agen_E-S.h"
#include <fstream>
#include <vector>
#include <cmath> // ceil.

using std::cout;
using std::endl;

// Tipo necesario para este ejercicio.
struct herencia
{
    int id;
    unsigned int dinero;
    std::vector<std::string> propiedades;
    herencia(int i = 0, unsigned int d = 0, std::vector<std::string> p = {}): id{i}, dinero{d}, propiedades{p} {}
};

void mostrar_arbol_herencia_rec(const Agen<herencia> &A, typename Agen<herencia>::nodo n)
{
    if (n != Agen<herencia>::NODO_NULO)
    {
        typename Agen<herencia>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<herencia>::NODO_NULO)
        {
            cout << "Hijo llamado " << A.elemento(hijo).id << " cuyo padre es " << A.elemento(A.padre(hijo)).id << ", dinero: " << A.elemento(hijo).dinero << ", propiedades: ";
            for (const auto &p : A.elemento(hijo).propiedades)
            {
                cout << p << " - ";
            }
            cout << endl;

            mostrar_arbol_herencia_rec(A, hijo);
            hijo = A.hermDrcho(hijo);
        }
    }
    else 
        cout << "Árbol vacío." << endl;
}

void mostrar_arbol_herencia(const Agen<herencia> &A)
{
    if(!A.arbolVacio())
    {
        cout << "Raíz del árbol -> " << "dinero: " << A.elemento(A.raiz()).dinero << ", propiedades: ";
        for (const auto &p : A.elemento(A.raiz()).propiedades)
        {
            cout << p << " - ";
        }
        cout << endl;

        mostrar_arbol_herencia_rec(A, A.raiz());
    }
    else
        cout << "Árbol vacío." << endl;
}

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

void repartir_herencia_Rec(Agen<herencia>& A, typename Agen<herencia>::nodo n)
{
    if(n != Agen<herencia>::NODO_NULO)
    {
        int nHijos = NumHijosAgen(n, A);

        // Hay hijos para repartir la herencia.
        if(nHijos > 0)
        {
            // Obtenemos la cantidad de dinero que hay que darle a cada hijo.
            int dinero_cada_hijo = A.elemento(n).dinero / nHijos;

            // Obtenemos la cantidad de propiedades que hay que darle a cada hijo.
            int npropiedades_cada_hijo = static_cast<int>(ceil(A.elemento(n).propiedades.size()));

            // Repartimos dinero.
            if(dinero_cada_hijo > 0)
            {
                typename Agen<herencia>::nodo hijo = A.hijoIzqdo(n);
                while(hijo != Agen<herencia>::NODO_NULO)
                {
                    A.elemento(hijo).dinero = dinero_cada_hijo;
                    hijo = A.hermDrcho(hijo);
                }
            }
            
            // Una vez repartido el dinero, se lo quitamos al padre.
            A.elemento(n).dinero = 0;
            
            // Repartirmos propiedades.
            if(npropiedades_cada_hijo > 0)
            {
                typename Agen<herencia>::nodo hijo = A.hijoIzqdo(n);
                while(hijo != Agen<herencia>::NODO_NULO)
                {
                    if(NumHijosAgen(hijo, A) > 0)
                    {
                        A.elemento(hijo).propiedades.push_back(A.elemento(n).propiedades[A.elemento(n).propiedades.size() - 1]);
                        A.elemento(n).propiedades.pop_back();
                    }
                    hijo = A.hermDrcho(hijo);
                }

                if(!A.elemento(n).propiedades.empty())
                {
                    typename Agen<herencia>::nodo hijo = A.hijoIzqdo(n);
                    while(hijo != Agen<herencia>::NODO_NULO && A.elemento(n).propiedades.size() > 0)
                    {
                        if(NumHijosAgen(hijo, A) == 0)
                        {
                            A.elemento(hijo).propiedades.push_back(A.elemento(n).propiedades[A.elemento(n).propiedades.size() - 1]);
                            A.elemento(n).propiedades.pop_back();
                        }
                        hijo = A.hermDrcho(hijo);
                    }
                }
            }

            repartir_herencia_Rec(A, A.hijoIzqdo(n));
        }
    }
}

void repartir_herencia(Agen<herencia>& A)
{
    repartir_herencia_Rec(A, A.raiz());
}


int main()
{
    Agen<herencia> A;

    std::vector<std::string> prop;
    prop.push_back("Aston Martin");
    prop.push_back("Casa playa");

    A.insertarRaiz(herencia{1, 30000, prop});
    A.insertarHijoIzqdo(A.raiz(), herencia{2, 0, std::vector<std::string>{}});
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), herencia{3, 0, std::vector<std::string>{}});
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())), herencia{4, 0, std::vector<std::string>{}});
    
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), herencia{5, 0, std::vector<std::string>{}});
    A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), herencia{6, 0, std::vector<std::string>{}});

    cout << "*** Árbol General de herencia A ***" << endl << endl;
    mostrar_arbol_herencia(A);

    cout << endl;

    cout << "*** Repartimos las herencias ***" << endl;
    repartir_herencia(A);

    cout << "*** Ahora, mostramos el Árbol general de herencias A tras el reparto ***" << endl;
    mostrar_arbol_herencia(A);
}
