#include <iostream> // std::cout, std::endl
#include <cstddef> // size_t
#include <istream> // ifstream.
#include "../Generales/agen.hpp" // Agen.
#include "../Generales/agen_E-S.h" // Agen E/S.

// Espacios de nombre.
using std::cout;
using std::endl;
using std::ifstream;

// Función Numhijos -> Cuenta los hijos que tiene un nodo de un agen.
template <typename T>
size_t NumHijos(typename Agen<T>::nodo n, const Agen<T>& A)
{
    size_t hijos = 0;
    if(n != Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<T>::NODO_NULO)
        {
            hijos++;
            aux = A.hermDrcho(aux);
        }
    }
    
    return hijos;
}

// Función esTernario -> Función llamadora que llama a su función recursiva, que es con la que
// vamos a recorrer el árbol general.
template <typename T>
bool esTernario_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    size_t nHijos = NumHijos(n, A);
    bool flag = (nHijos == 0) or (nHijos == 3);
    if(n != Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);

        while(aux != Agen<T>::NODO_NULO and flag)
        {
            flag = flag and esTernario_rec(aux, A);
            aux = A.hermDrcho(aux);
        }
    }

    return flag;
}

template <typename T>
bool esTernario(const Agen<T>& A)
{
    return esTernario_rec(A.raiz(), A);
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

    if(esTernario(A))
        cout << "Este agen ES ternario." << endl;
    else
        cout << "Este agen NO es ternario." << endl;

}