#include "abb_E-S.hpp"

int main()
{
    // Podemos cambiar el tipo de dato a nuestro antojo.
    typedef int tElto;
    Abb<tElto> A;
    leer_abb(A);
    imprimir_abb(A);

    return 0;
}