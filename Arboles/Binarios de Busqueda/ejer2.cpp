#include "ejer2.hpp"

template <typename T>
void obtener_elementos(const Abb<T>& A, vector<T>& elementos)
{
    // Obtenemos los elementos en inorden.
    if(!A.izqdo().vacio())
        obtener_elementos(A.izqdo(), elementos);

    elementos.push_back(A.elemento());
    
    if(!A.drcho().vacio())
        obtener_elementos(A.drcho(), elementos);
}

template <typename T>
void equilibrarAbb_rec(Abb<T>& A, vector<T>& elementos, int ini, int fin)
{
    // Obtenemos la mediana.
    size_t med = (fin + ini) / 2;

    // Insertamos el elemento en la mediana.
    A.insertar(elementos[med]);
    
    // Equilibramos por el subárbol izquierdo y derecho.
    if(fin >= ini)
    {
        equilibrarAbb_rec(A, elementos, 0, med - 1);
        equilibrarAbb_rec(A, elementos, med + 1, fin);
    }
}

template <typename T>
void equilibrarAbb(Abb<T>& A)
{
    vector<T> elementos;

    // Primero, obtenemos los elementos ordenados del abb.
    obtener_elementos(A, elementos);
    
    Abb<T> res;
    equilibrarAbb_rec(res, elementos, 0, elementos.size() - 1);
    A = res;
}

int main()
{
    Abb<int> A;
    leer_abb(A);
    imprimir_abb(A);
    equilibrarAbb(A);

    cout << "*** Árbol después del equilibrado ***" << endl;
    imprimir_abb(A);
}