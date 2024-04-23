#include "abb_E-S.hpp" // se incluye también el abb.hpp

int main()
{
    // Podar implementado en abb.hpp
    Abb<int> A;
    leer_abb(A);
    imprimir_abb(A);
    A.podar(18);

    cout << "*** Podamos desde el elemento 18 ***" << endl;
    imprimir_abb(A);

    return 0;
}

