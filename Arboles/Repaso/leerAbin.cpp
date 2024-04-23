#include <iostream>
#include <fstream>
#include "../Binarios/P2/abin_enlazada.hpp"
#include "../Binarios/P2/abin_E-S.h"

using namespace std;

typedef int tElto;
const tElto fin = -1; // Fin de lectura.

int main()
{
    Abin<tElto> A, B;

    cout << "*** Lectura del árbol binario A ***\n";
    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat");  // Abrir fichero de salida.
    imprimirAbin(fs, A, fin); // En fichero.
    fs.close();
    cout << "\n*** Árbol A guardado en fichero abin.dat ***\n";

    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin.dat"); // Abrir fichero de entrada.
    rellenarAbin(fe, B);     // Desde fichero.
    fe.close();

    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(B); // En std::cout
}