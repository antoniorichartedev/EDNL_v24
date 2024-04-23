#include "abb_E-S.hpp"
#include <vector>


template <typename T>
void obtener_elementos(const Abb<T>& A, vector<T>& elementos);

template <typename T>
void equilibrarAbb_rec(Abb<T>& A, vector<T>& elementos, int ini, int fin);

template <typename T>
void equilibrarAbb(Abb<T>& A);