#include "Cos.h"
#include "ProdusAlimentar.h"
#include "Exceptii.h"
#include <utility>
#include <algorithm>

Cos::Cos() : proprietar(nullptr), total(0.0) {}

Cos::Cos(Utilizator<int>& prop) : proprietar(&prop), total(0.0) {}

Cos::Cos(const Cos& other)
    : proprietar(other.proprietar), total(other.total) {
    for (const auto& item : other.produse) {
        produse.push_back(ItemComanda{
            std::unique_ptr<Produs>(item.produs->clone()),
            item.cantitate
        });
    }
}

Cos::Cos(Cos&& other) noexcept
    : proprietar(other.proprietar),
      produse(std::move(other.produse)),
      total(other.total) {
    other.total = 0.0;
}

Cos& Cos::operator=(const Cos& other) {
    if (this != &other) {
        Cos temp(other);
        swap(*this, temp);
    }
    return *this;
}

Cos& Cos::operator=(Cos&& other) noexcept {
    if (this != &other) {
        proprietar = other.proprietar;
        produse = std::move(other.produse);
        total = other.total;
        other.total = 0.0;
    }
    return *this;
}

Cos::~Cos() = default;

void swap(Cos& first, Cos& second) noexcept {
    using std::swap;
    swap(first.proprietar, second.proprietar);
    swap(first.produse, second.produse);
    swap(first.total, second.total);
}

void Cos::adaugaProdus(const Produs& produs, int cantitate) {
    if (cantitate <= 0) {
        throw std::invalid_argument("Cantitatea trebuie sa fie pozitiva");
    }
    for (auto& item : produse) {
        if (item.produs->getId() == produs.getId()) {
            item.cantitate += cantitate;
            total += produs.calculeazaPretFinal() * cantitate;
            return;
        }
    }
    produse.push_back(ItemComanda{
        std::unique_ptr<Produs>(produs.clone()),
        cantitate
    });
    total += produs.calculeazaPretFinal() * cantitate;
}

void Cos::adaugaProdus(std::unique_ptr<Produs> produs, int cantitate) {
    if (cantitate <= 0) {
        throw std::invalid_argument("Cantitatea trebuie sa fie pozitiva");
    }
    for (auto& item : produse) {
        if (item.produs->getId() == produs->getId()) {
            item.cantitate += cantitate;
            total += produs->calculeazaPretFinal() * cantitate;
            return;
        }
    }
    produse.push_back(ItemComanda{std::move(produs), cantitate});
    total += produse.back().produs->calculeazaPretFinal() * cantitate;
}

void Cos::eliminaProdus(int index) {
    if (index < 0 || index >= static_cast<int>(produse.size())) {
        throw std::out_of_range("Index invalid");
    }
    total -= produse[index].produs->calculeazaPretFinal() * produse[index].cantitate;
    produse.erase(produse.begin() + index);
}

double Cos::getTotal() const {
    return total;
}

void Cos::afisareCos(std::ostream& os) const {
    os << "=== COS DE CUMPARATURI ===\n";
    os << *proprietar << "\n";
    if (produse.empty()) {
        os << "Cosul este gol.\n";
    } else {
        os << "Produse in cos:\n";
        for (size_t i = 0; i < produse.size(); ++i) {
            const auto& item = produse[i];
            os << i + 1 << ". " << *item.produs;
            os << ", Cantitate: " << item.cantitate
               << ", Subtotal: " << item.produs->calculeazaPretFinal() * item.cantitate << " lei\n";
        }
        os << "Total: " << total << " lei\n";
    }
    os << "========================\n";
}

void Cos::finalizeazaComanda(std::vector<std::unique_ptr<Produs>>& catalog, bool folosestePuncte) {
    if (produse.empty()) {
        throw std::runtime_error("Cosul este gol");
    }

    // 1. Verificare stocuri
    for (const auto& item : produse) {
        bool gasit = false;
        for (const auto& prodCat : catalog) {
            if (prodCat->getId() == item.produs->getId()) {
                if (prodCat->getStoc() < item.cantitate) {
                    throw StocInsuficientException("Stoc insuficient pentru produsul " +
                                                    std::string(prodCat->getNume()));
                }
                gasit = true;
                break;
            }
        }
        if (!gasit) {
            throw ProdusInexistentException("Produsul cu ID " +
                                             std::to_string(item.produs->getId()) +
                                             " nu mai exista in catalog");
        }
    }

    // 2. Calcul suma de plata si puncte de loialitate
    double totalPlata = total;
    int puncteVeche = proprietar->getExtra();
    int puncteFolosite = 0;

    if (folosestePuncte && puncteVeche > 0) {
        puncteFolosite = std::min(puncteVeche, static_cast<int>(totalPlata));
        totalPlata -= puncteFolosite;
        std::cout << "Ati folosit " << puncteFolosite << " puncte (valoare " << puncteFolosite << " lei).\n";
    }

    // 3. Verificare sold
    if (proprietar->getSold() < totalPlata) {
        throw SoldInsuficientException("Sold insuficient pentru a finaliza comanda");
    }

    // 4. Actualizare stocuri
    for (const auto& item : produse) {
        for (auto& prodCat : catalog) {
            if (prodCat->getId() == item.produs->getId()) {
                prodCat->actualizeazaStoc(-item.cantitate);
                break;
            }
        }
    }

    // 5. Scadere bani din cont
    proprietar->extrageFonduri(totalPlata);

    // 6. Calcul si adaugare puncte noi (1 punct la 10 lei platiti efectiv)
    int puncteNoi = static_cast<int>(totalPlata / 10.0);
    int puncteRamase = puncteVeche - puncteFolosite + puncteNoi;
    proprietar->setExtra(puncteRamase);

    std::cout << "Ati cheltuit " << totalPlata << " lei, primiti " << puncteNoi << " puncte noi.\n";
    std::cout << "Puncte ramase: " << puncteRamase << "\n";

    // 7. Golim cosul
    produse.clear();
    total = 0.0;
}

std::ostream& operator<<(std::ostream& os, const Cos& cos) {
    cos.afisareCos(os);
    return os;
}