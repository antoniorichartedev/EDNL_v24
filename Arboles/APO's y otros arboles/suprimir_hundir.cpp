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