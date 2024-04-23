#include "conjunto.hpp"
#include <iostream>

int main()
{
    std::vector<int> elementosc1 = {1, 2, 3, 4};
    std::vector<int> elementosc2 = {5, 2, 3, 6};
    Conjunto<int> c1{elementosc1}, c2{elementosc2};
    
    cout << "Elementos del Conjunto 1 -> ";
    for(const auto& i : c1.elementos())
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "Elementos del Conjunto 2 -> ";
    for(const auto& i : c2.elementos())
    {
        cout << i << " ";
    }
    cout << endl;


    // Unión.
    Conjunto<int> uni{c1 & c2};
    cout << "Unión de c1 & c2 -> ";
    for(const auto& i : uni.elementos())
    {
        cout << i << " ";
    }
    cout << endl;

    // Intersección.
/*    Abb<int> A;
    A.insertar(1);
    A.insertar(5);
    A.insertar(77);
    A.insertar(14);
*/
    Conjunto<int> inter{c1 | c2};
    cout << "Intersección de c1 | c2 -> ";
    for(const auto& i : inter.elementos())
    {
        cout << i << " ";
    }
    cout << endl;

    // Diferencia simétrica.
    Conjunto dif{uni - inter};
    cout << "Diferencia simétrica de Unión(c1, c2) - Intersección(c1, c2) -> ";
    for(const auto& i : dif.elementos())
    {
        cout << i << " ";
    }
    cout << endl;


    return 0;
}