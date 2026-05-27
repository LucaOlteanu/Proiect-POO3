#ifndef COMANDA_BUILDER_H
#define COMANDA_BUILDER_H

#include <vector>
#include <memory>
#include "Cos.h"
#include "Produs.h"
#include "Utilizator.h"

class ComandaBuilder {
private:
    Utilizator<int>* utilizator;
    struct Item {
        std::unique_ptr<Produs> produs;
        int cantitate;
    };
    std::vector<Item> produse;
    double discount; // 0..1

public:
    explicit ComandaBuilder(Utilizator<int>& user);

    ComandaBuilder& adaugaProdus(const Produs& produs, int cantitate);
    ComandaBuilder& setDiscount(double procent);
    Cos build();
};

#endif