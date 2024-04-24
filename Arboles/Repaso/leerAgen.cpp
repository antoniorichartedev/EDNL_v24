#include <iostream>
#include <fstream>
#include "../Generales/agen.hpp" // Agen.
#include "../Generales/agen_E-S.h" // Agen E/S.
using namespace std;


typedef int tElto;
const tElto fin = -1; // fin de lectura

int main()
{
    Agen<tElto> A, B;

    cout << "*** Lectura del árbol A ***\n";
    rellenarAgen(A, fin);     // Desde std::cin
    ofstream fs("agen2.dat");  // Abrir fichero de salida.
    imprimirAgen(fs, A, fin); // En fichero.
    fs.close();
    cout << "\n*** Árbol A guardado en fichero agen.dat ***\n";

    cout << "\n*** Lectura de árbol B de agen.dat ***\n";
    ifstream fe("agen2.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, B);     // Desde fichero.
    fe.close();

    cout << "\n*** Mostrar árbol B ***\n";
    imprimirAgen(B); // En std::cout
}