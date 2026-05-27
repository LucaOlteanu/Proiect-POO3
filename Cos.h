#ifndef COS_H
#define COS_H

#include <iostream>
#include <vector>
#include <memory>
#include "Utilizator.h"
#include "Produs.h"

class Cos {
private:
    struct ItemComanda {
        std::unique_ptr<Produs> produs;
        int cantitate;
    };

    Utilizator<int>* proprietar;
    std::vector<ItemComanda> produse;
    double total;

    friend void swap(Cos& first, Cos& second) noexcept;

public:
    explicit Cos(Utilizator<int>& prop);
    Cos();
    Cos(const Cos& other);
    Cos(Cos&& other) noexcept;
    ~Cos();

    Cos& operator=(const Cos& other);
    Cos& operator=(Cos&& other) noexcept;

    void adaugaProdus(const Produs& produs, int cantitate);
    void adaugaProdus(std::unique_ptr<Produs> produs, int cantitate);
    void eliminaProdus(int index);
    double getTotal() const;
    void afisareCos(std::ostream& os) const;
    void finalizeazaComanda(std::vector<std::unique_ptr<Produs>>& catalog, bool folosestePuncte = false);

    friend std::ostream& operator<<(std::ostream& os, const Cos& cos);
};

#endif