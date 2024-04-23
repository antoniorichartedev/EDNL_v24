#include "abb.hpp"
#include <algorithm> // std::set_union
#include <vector>
#include <iostream>
using namespace std;

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

template <typename T>
class Conjunto{
	public:
		Conjunto(){};
        Conjunto(const Conjunto& B);
		Conjunto(const Abb<T>& A);
        Conjunto(const std::vector<T>& elementos);
		void anadir(const T& elto);
		inline bool pertenece(const T& elto) const; // Función necesaria para la intersección y la diferencia simétrica.
		Conjunto operator &(const Conjunto& B); // unión de conjuntos.
		Conjunto operator |(const Conjunto& B); // Intersección de conjuntos.
		Conjunto operator -(const Conjunto& B); // Diferencia de conjuntos.
		Conjunto& operator =(const Conjunto& B); // Operador de asignación por copia de Conjuntos.
		const std::vector<T>& elementos() const { return eltos_; };

	
	private:
		std::vector<T> eltos_;
		Abb<T> arbol_;

};

template <typename T>
Conjunto<T>::Conjunto(const Abb<T>& A): arbol_{A}
{
    std::vector<T> elementos;
    obtener_elementos(A, elementos);
    eltos_ = elementos;
}

template <typename T>
Conjunto<T>::Conjunto(const std::vector<T>& elementos): eltos_{elementos}
{
    Abb<T> aux;
    equilibrarAbb_rec(aux, eltos_, 0, eltos_.size() - 1);
    arbol_ = aux;
}

template <typename T>
Conjunto<T>::Conjunto(const Conjunto& B): eltos_{B.eltos_}, arbol_{B.arbol_} 
{
    equilibrarAbb(arbol_);
}

template <typename T>
Conjunto<T>& Conjunto<T>::operator=(const Conjunto& B)
{
    if (*this != &B)
    {
        eltos_ = B.eltos_;
        arbol_ = B.arbol_;
    }
    
    return *this;
}

template <typename T>
void Conjunto<T>::anadir(const T& elto)
{
    arbol_.insertar(elto);
    eltos_.push_back(elto);
    std::sort(eltos_.begin(), eltos_.end());
}

template <typename T>
inline bool Conjunto<T>::pertenece(const T& elto) const
{
    
    Abb<T> aux = arbol_.buscar(elto);
    if(!aux.vacio())
        return true;
    else
        return false;
    //return std::find(eltos_.begin(), eltos_.end(), elto) != eltos_.end();
}

// ejercicio 3
template <typename T>
Conjunto<T> Conjunto<T>::operator &(const Conjunto<T>& B)
{
    Conjunto<T> mio{*this};

    for(const auto& e : B.elementos())
    {
        if(!pertenece(e))
            mio.anadir(e);
    }

    return mio;
}

// ejercicio 4
template <typename T>
Conjunto<T> Conjunto<T>::operator|(const Conjunto<T>& B)
{
    // Conjunto donde almacenaremos la intersección.
    Conjunto<T> interseccion;

    for(const auto& e : B.elementos())
    {
        if(this->pertenece(e))
            interseccion.anadir(e);
    }

    // Devolvemos el conjunto.
    return interseccion;
    
}

// ejercicio 5
template <typename T>
Conjunto<T> Conjunto<T>::operator-(const Conjunto<T>& B)
{
    // Primero, obtenemos la intersección y la unión de ambos conjuntos.
    Conjunto<T> mio(*this);
    Conjunto<T> u(mio & B), inter(mio | B), diferencia_simetrica;

    // Ahora, hagamos la diferencia simétrica de conjuntos.
    for(const auto& elem : u.elementos())
    {
        if(!inter.pertenece(elem))
            diferencia_simetrica.anadir(elem);
    }

    return diferencia_simetrica;
}