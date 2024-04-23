#include <iostream> // std::cout, std::endl
#include <cstddef> // size_t
#include <istream> // ifstream.
#include "../Generales/agen.hpp" // Agen.
#include "../Generales/agen_E-S.h" // Agen E/S.
#include <vector>



// Estructura Pixel para representar un nodo del agen cuaternario.
struct Pixel
{
    int color; // 0 -> blanco, 1 -> negro, -1 -> nodo intermedio.
	int x0, x1, y0, y1; // También se puede hacer así -> int x0x1[2]; int y0y1[2];
    Pixel(int c, int uno, int dos, int tres, int cuatro): color{c}, x0{uno}, x1{dos}, y0{tres}, y1{cuatro} {}
};

// La idea está en que, si el nodo es un nodo sin color, tenemos que ver el estado de sus hijos.
// Pero si el nodo tiene color, nos tendremos que ir a la matriz para guardar la información de los nodos.


void colorearMatriz_rec(typename Agen<Pixel>::nodo n, const Agen<Pixel>& A, std::vector<std::vector<int> >& matriz)
{
    if (A.elemento(n).color == -1)      // es un nodo intermedio.
    {
        Agen<Pixel>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<Pixel>::NODO_NULO)
        {
            colorearMatriz_rec(hijo, A, matriz);
            hijo = A.hermDrcho(hijo);
        }
    }
    else    // Tiene color y es hoja.
    {
        for(auto i = A.elemento(n).x0; i <= A.elemento(n).x1; i++)
        {
            for(auto j = A.elemento(n).y0; j <= A.elemento(n).y1; j++)
            {
                matriz[i][j] = A.elemento(n).color;
            }
        }
    }
}

void colorearMatriz(const Agen<Pixel>& A, std::vector<std::vector<int> >& matriz)
{
    colorearMatriz_rec(A.raiz(), A, matriz);
}

void mostrar_matriz(std::vector<std::vector<int> > matriz)
{
    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            std::cout << elemento << ' ';
        }
        std::cout << '\n'; // Nueva línea al final de cada fila
    }
}


int main()
{
    Agen<Pixel> A;
    A.insertarRaiz(Pixel{-1, 0, 3, 0, 3});
    A.insertarHijoIzqdo(A.raiz(), Pixel{-1, 0, 1, 0, 1});

    // Cuadrantes de la raíz.
    typename Agen<Pixel>::nodo hizqRaiz = A.hijoIzqdo(A.raiz());
    A.insertarHermDrcho(hizqRaiz, Pixel{0, 0, 1, 2, 3});
    A.insertarHermDrcho(hizqRaiz, Pixel{1, 2, 3, 2, 3});
    A.insertarHermDrcho(hizqRaiz, Pixel{0, 2, 3, 0, 1});

    A.insertarHijoIzqdo(hizqRaiz, Pixel{1, 0, 0, 0, 0});
    A.insertarHermDrcho(A.hijoIzqdo(hizqRaiz), Pixel{1, 0, 0, 0, 1});
    A.insertarHermDrcho(A.hijoIzqdo(hizqRaiz), Pixel{1, 0, 1, 0, 0});
    A.insertarHermDrcho(A.hijoIzqdo(hizqRaiz), Pixel{0, 0, 1, 0, 1});
    

    std::vector<std::vector<int> > matriz{4, std::vector<int>(4, -1)};
    //mostrar_matriz(matriz);
    colorearMatriz(A, matriz);
    mostrar_matriz(matriz);
}