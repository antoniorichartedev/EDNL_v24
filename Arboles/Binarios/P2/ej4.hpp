//
// Created by Anton on 05/03/2024.
//

#ifndef P2_EJ4_HPP
#define P2_EJ4_HPP

#include <cstddef>

template <typename T>
class Abin{
public:
    typedef size_t nodo;    // Índice del vector que va desde 0 hasta maxNodos - 1.
    static const nodo NODO_NULO;
    Abin(size_t altmax, const T& e_nulo);
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T &elemento(nodo n) const; // Lec. en Abin const
    T &elemento(nodo n);             // Lec/Esc. en Abin no-const
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Abin(const Abin<T> &a);               // Ctor. de copia
    Abin<T> &operator=(const Abin<T> &A); // Asig. de árboles
    ~Abin();
private:
    T* elementos;   // vector de elementos del árbol.
    size_t N;       // Número máximo de nodos del árbol.
    T ELTO_NULO;    // Igual que el nodo nulo pero para esta representación.
    size_t Hmax;    // Altura máxima que puede alcanzar el árbol.

    int altura(nodo n) const;
    int profundidad(nodo n) const;
};

unsigned powi(unsigned a, unsigned b){
    unsigned res = 1;
    for(unsigned i = 0; i < b; i++)
        res *= a;

    return res;
}
#endif //P2_EJ4_HPP
