#include "ComandaBuilder.h"
#include "Discount.h"
#include <stdexcept>

ComandaBuilder::ComandaBuilder(Utilizator<int>& user)
    : utilizator(&user), discount(0.0) {}

ComandaBuilder& ComandaBuilder::adaugaProdus(const Produs& produs, int cantitate) {
    if (cantitate <= 0)
        throw std::invalid_argument("Cantitate invalida");
    produse.push_back({std::unique_ptr<Produs>(produs.clone()), cantitate});
    return *this;
}

ComandaBuilder& ComandaBuilder::setDiscount(double procent) {
    if (procent < 0.0 || procent > 1.0)
        throw std::invalid_argument("Discount invalid");
    discount = procent;
    return *this;
}

Cos ComandaBuilder::build() {
    Cos cos(*utilizator);
    for (auto& item : produse) {
        cos.adaugaProdus(std::move(item.produs), item.cantitate);
    }
    return cos;
}