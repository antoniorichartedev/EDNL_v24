#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

using namespace std;

template <typename T>
void buscarRec(typename Agen<T>::nodo n, Agen<T> &A, T elto, typename Agen<T>::nodo &nodoBuscado)
{
	if (n != Agen<T>::NODO_NULO)
	{
		if (A.elemento(n) == elto)
		{
			nodoBuscado = n;
		}

		else
		{
			typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
			while (hijo != Agen<T>::NODO_NULO)
			{
				buscarRec(hijo, A, elto, nodoBuscado);
				hijo = A.hermDrcho(hijo);
			}
		}
	}
}

void poda_rec(typename Agen<int>::nodo n, Agen<int> &A)
{
	// Vemos si tiene hijo izquierdo.
	// Si no es nulo y es hoja, eliminamos. Si no es hoja, hacemos una llamada recursiva con ese hijo izquierdo. (Aunque la llamada recursiva la hará si
	// es hoja o no).
	while(A.hijoIzqdo(n) != Agen<int>::NODO_NULO)
	{
		poda_rec(A.hijoIzqdo(n), A);
		A.eliminarHijoIzqdo(n);
	}
}

void poda(Agen<int> &A, int x)
{
	typename Agen<int>::nodo nodo_a_eliminar = Agen<int>::NODO_NULO;

	// Buscamos el nodo por el que empezaremos a podar.
	buscarRec(A.raiz(), A, x, nodo_a_eliminar);

	// Si es distinto de NODO_NULO, quiere decir que hemos encontrado el nodo.
	if(nodo_a_eliminar != Agen<int>::NODO_NULO)
	{
		// Podamos los hijos de ese nodo.
		poda_rec(nodo_a_eliminar, A);

		// Una vez eliminados los hijos de el nodo a eliminar, eliminamos dicho nodo.
		typename Agen<int>::nodo aux = A.hijoIzqdo(A.padre(nodo_a_eliminar));

		// Si el elemento del nodo por el que estamos iterando es igual al elemento x, entonces hemos encontrado el nodo a eliminar.
		// En caso contrario, seguimos buscando por los hermanos derechos hasta encontrar el nodo.
		if(A.elemento(aux) == x)
			A.eliminarHijoIzqdo(A.padre(aux));
		else
		{
			// Nos colocamos en el nodo anterior al hermano derecho que tiene el elemento igual a x.
			while(A.elemento(A.hermDrcho(aux)) != x)
				aux = A.hermDrcho(aux);
			
			A.eliminarHermDrcho(aux);
		}
	}
	else
	{
		std::cout << "El nodo a eliminar no se encuentra en el árbol." << std::endl;
	}
}

  
/*
  Corregido de Juanfran

  template <typename T>
  void buscarRec(typename Agen<T>::nodo n, Agen<T>& A, T elto, typename Agen<T>::nodo& nodoBuscado)
  {
	if(n != Agen<T>::NODO_NULO)
	{
	  if(A.elemento(n) == elto)
	  {
		nodoBuscado = n;
	  }

	  else
	  {
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		while(hijo != Agen<T>::NODO_NULO)
		{
		  buscarRec(hijo, A, elto, nodoBuscado);
		  hijo = A.hermDrcho(hijo);
		}
	  }
	}
  }

  template <typename T>
  void podaAgen_rec(typename Agen<T>::nodo n, Agen<T>& A)
  {
	typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
	while(hijo != Agen<T>::NODO_NULO)
	{
	  podaAgen_rec(hijo, A);
	  A.eliminarHijoIzqdo(n);
	}
  }


  template <typename T>
  void podaAgen(Agen<T>& A, T elto)
  {
	typename Agen<T>::nodo nodo_a_eliminar = buscarRec(A.raiz(), A, elto);

	if(nodo_a_eliminar != Agen<T>::NODO_NULO)
	{
	  podaAgen_rec(eliminar, A);

	  aux = A.hijoIzqdo(A.padre(eliminar));
	  if(A.elemento(aux) == elto)
	  {
		A.eliminarHijoIzqdo(A.padre(aux));
	  }

	  else
	  {
		while(A.elemento(A.hermDrcho(aux)) != elto)
		  aux = A.hermDrcho(aux);

		A.eliminarHermDrcho(aux);
	  }
	}
	else
	  cout << "El nodo no está en el árbol." << endl;


  }

*/
int main()
{
	Agen<int> A;
	cout << "\n*** Lectura de árbol A de agen.dat ***\n";
	ifstream fe("agen.dat"); // Abrir fichero de entrada.
	rellenarAgen(fe, A);	 // Desde fichero.
	fe.close();

	cout << "\n*** Mostrar árbol A ***\n";
	imprimirAgen(A); // En std::cout

	cout << "\nPodamos el árbol." << endl;
	poda(A, 2);
	imprimirAgen(A);
	return 0;
}
