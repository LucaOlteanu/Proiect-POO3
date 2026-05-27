#ifndef CATALOG_H
#define CATALOG_H

#include <vector>
#include <memory>
#include "Produs.h"

class Catalog {
private:
    Catalog() = default;
    std::vector<std::unique_ptr<Produs>> produse;

public:
    Catalog(const Catalog&) = delete;
    Catalog& operator=(const Catalog&) = delete;

    static Catalog& getInstance() {
        static Catalog instance;
        return instance;
    }

    void adaugaProdus(std::unique_ptr<Produs> produs) {
        produse.push_back(std::move(produs));
    }

    Produs* getProdus(int index) {
        if (index < 0 || index >= static_cast<int>(produse.size()))
            throw std::out_of_range("Index invalid");
        return produse[index].get();
    }

    const Produs* getProdus(int index) const {
        if (index < 0 || index >= static_cast<int>(produse.size()))
            throw std::out_of_range("Index invalid");
        return produse[index].get();
    }

    size_t size() const { return produse.size(); }

    auto begin() const { return produse.begin(); }
    auto end() const { return produse.end(); }

    void clear() { produse.clear(); }

    std::vector<std::unique_ptr<Produs>>& getProduse() { return produse; }
    const std::vector<std::unique_ptr<Produs>>& getProduse() const { return produse; }
};

#endif