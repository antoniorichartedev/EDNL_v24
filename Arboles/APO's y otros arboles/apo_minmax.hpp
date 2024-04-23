#ifndef APO_MINMAX_HPP
#define APO_MINMAX_HPP

#include <cassert>
#include <cstddef>
#include <iostream>

template <typename T>
class ApoMinMax
{
public:
    explicit ApoMinMax(size_t maxNodos); // constructor
    void insertar(const T &e);
    void suprimir();
    const T &cima() const;
    bool vacio() const;
    ApoMinMax(const ApoMinMax<T> &A);               // ctor. de copia
    ApoMinMax<T> &operator=(const ApoMinMax<T> &A); // asignación de apo
    ~ApoMinMax();                             // destructor
    void ver_apo() const;
private:
    typedef size_t nodo; // índice del vector
    // entre 0 y maxNodos-1
    T *nodos;        // vector de nodos
    size_t maxNodos; // tamaño del vector
    size_t numNodos; // último nodo del árbol
    nodo padre(nodo i) const { return (i - 1) / 2; }
    nodo hIzq(nodo i) const { return 2 * i + 1; }
    nodo hDer(nodo i) const { return 2 * i + 2; }
    void flotar(nodo i);
    void hundir(nodo i);
    void hundirMax(nodo i);
};

template <typename T>
inline ApoMinMax<T>::ApoMinMax(size_t maxNodos) : nodos(new T[maxNodos]),
                                      maxNodos(maxNodos),
                                      numNodos(0) // Apo vacío.
{
}

template <typename T>
inline const T &ApoMinMax<T>::cima() const
{
    assert(numNodos > 0); // Apo no vacío.
    return nodos[0];
}

template <typename T>
inline bool ApoMinMax<T>::vacio() const
{
    return (numNodos == 0);
}

template <typename T>
inline void ApoMinMax<T>::insertar(const T &e)
{
    assert(numNodos < maxNodos); // Apo no lleno.
    nodos[numNodos] = e;
    if (++numNodos > 1)
        flotar(numNodos - 1); // Reordenar.
}

// Ejercicio 2.
template <typename T>
void ApoMinMax<T>::flotar(nodo i)
{
    T e = nodos[i];
    if(e < nodos[padre(i)])
    {
        while (i > 0 && e < nodos[padre(padre(i))])
        {
            nodos[i] = nodos[padre(padre(i))];
            i = padre(padre(i));
        }
    }
    nodos[i] = e;
}

template <typename T>
inline void ApoMinMax<T>::suprimir()
{
    assert(numNodos > 0); // Apo no vacío.
    if (--numNodos > 0)   // Apo no queda vacío.
    {
        
        size_t maximo = 0;
        if(std::max(nodos[1], nodos[2]) == nodos[1])
            maximo = 1;
        else
            maximo = 2;

        nodos[maximo] = nodos[numNodos];
        if (numNodos > 1) // Quedan dos o más elementos.
            hundirMax(maximo);    // Reordenar.
    }
}

template <typename T>
void ApoMinMax<T>::hundir(nodo i)
{
    bool fin = false;
    T e = nodos[i];
    while (hIzq(i) < numNodos && !fin) // Hundir e.
    {
        nodo hMin; // Hijo menor del nodo i.
        if (hDer(i) < numNodos && nodos[hDer(i)] < nodos[hIzq(i)])
            hMin = hDer(i);
        else
            hMin = hIzq(i);
        if (nodos[hMin] < e)
        { // Subir el hijo menor.
            nodos[i] = nodos[hMin];
            i = hMin;
        }
        else // e <= nodos[hMin]
            fin = true;
    }
    nodos[i] = e; // Colocar e.
}

template <typename T>
void ApoMinMax<T>::hundirMax(nodo i)
{
    bool fin = false;
    T e = nodos[i];
    while (hIzq(i) < numNodos && !fin) // Hundir e.
    {
        
        nodo nietoMax = -1;

        // Miramos el máximo de mis nietos.
        T max_nietos = std::max(std::max(nodos[hIzq(hIzq(i))], nodos[hDer(hIzq(i))]), std::max(nodos[hIzq(hDer(i))], nodos[hDer(hDer(i))]));
        

        if(max_nietos == nodos[hIzq(hIzq(i))])
            nietoMax = hIzq(hIzq(i));

        if (max_nietos == nodos[hDer(hIzq(i))])
            nietoMax = hDer(hIzq(i));

        if(max_nietos == nodos[hIzq(hDer(i))])
            nietoMax = hIzq(hDer(i));

        if(max_nietos == nodos[hDer(hDer(i))])
            nietoMax = hDer(hDer(i));

        std::cout << "nieto -> " << nodos[nietoMax] << std::endl;
        if(nodos[nietoMax] > e)
        {  
            
            nodos[i] = nodos[nietoMax];
            i = nietoMax;
            if(nodos[i] < nodos[padre(i)])
            {
                nodos[padre(i)] = nodos[i];
            }
        }
        else
            fin = true;
    }
    nodos[i] = e;
}






template <typename T>
inline ApoMinMax<T>::~ApoMinMax()
{
    delete[] nodos;
}
template <typename T>
ApoMinMax<T>::ApoMinMax(const ApoMinMax<T> &A) : nodos(new T[A.maxNodos]),
                               maxNodos(A.maxNodos),
                               numNodos(A.numNodos)
{
    // Copiar el vector.
    for (nodo n = 0; n < numNodos; n++)
        nodos[n] = A.nodos[n];
}

template <typename T>
ApoMinMax<T> &ApoMinMax<T>::operator=(const ApoMinMax<T> &A)
{
    if (this != &A) // Evitar autoasignación.
    {               // Destruir el vector y crear uno nuevo si es necesario.
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        numNodos = A.numNodos;
        // Copiar el vector
        for (nodo n = 0; n < numNodos; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}

template <typename T>
void ApoMinMax<T>::ver_apo() const
{
    std::cout << "APO MIN-MAX -> ";
    for(size_t i = 0; i < maxNodos; i++)
    {
        std::cout << " " << nodos[i];
    }
    std::cout << std::endl;
}

#endif