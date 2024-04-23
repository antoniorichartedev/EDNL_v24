#include <iostream>
#include "apo_minmax.hpp"

using std::cout;
using std::endl;

int main()
{
    ApoMinMax<int> A(10);

    A.insertar(21);
    A.insertar(5);
    A.insertar(6);
    A.insertar(15);
    A.insertar(9);
    A.insertar(10);
    A.insertar(16);
    A.insertar(17);
    A.insertar(19);
    A.insertar(25);

    
    A.ver_apo();
    return 0;
}