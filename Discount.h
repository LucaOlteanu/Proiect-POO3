#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <stdexcept>

// Functie sablon pentru aplicarea de discount procentual
template<typename T>
double aplicaDiscount(T pret, double procent) {
    if (procent < 0.0 || procent > 1.0)
        throw std::invalid_argument("Procent discount invalid (0..1)");
    return static_cast<double>(pret) * (1.0 - procent);
}

#endif