#include <iostream>
#include "apo_minmax.hpp"

using std::cout;
using std::endl;

// Duda -> ¿Qué criterio tengo que seguir para poder hundir correctamente?
int main()
{
    ApoMinMax<int> A(15);

    
    for(int i = 10; i > 1; i--)
        A.insertar(i);
    
    A.suprimir();
    
    A.ver_apo();
    return 0;
}