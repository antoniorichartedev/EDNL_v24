#include <iostream>
#include <fstream>
#include "../Binarios/P1/abin_enlazada.hpp"
#include "../Binarios/P1/abin_E-S.h"
using namespace std;


typedef int tElto;
const tElto fin = -1; // fin de lectura

int main()
{
    Abin<tElto> A, B;

    cout << "*** Lectura del árbol A ***\n";
    rellenarAbin(A, fin);     // Desde std::cin
    ofstream fs("Abin.dat");  // Abrir fichero de salida.
    imprimirAbin(fs, A, fin); // En fichero.
    fs.close();
    cout << "\n*** Árbol A guardado en fichero Abin.dat ***\n";

    cout << "\n*** Lectura de árbol B de Abin.dat ***\n";
    ifstream fe("Abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, B);     // Desde fichero.
    fe.close();

    cout << "\n*** Mostrar árbol B ***\n";
    imprimirAbin(B); // En std::cout
}