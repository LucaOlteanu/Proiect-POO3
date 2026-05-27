#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <string>
#include <iostream>
#include <stdexcept>

template<typename T>
class Utilizator {
private:
    static int nextId;
    const int id;
    std::string nume;
    std::string adresa;
    double sold;
    T extra;

public:
    Utilizator() : id(nextId++), nume("Anonim"), adresa("Necunoscuta"), sold(0.0), extra(T{}) {}

    Utilizator(const std::string& nume, const std::string& adresa, double sold, const T& extra = T{})
        : id(nextId++), nume(nume), adresa(adresa), sold(sold), extra(extra) {
        if (sold < 0)
            throw std::invalid_argument("Soldul nu poate fi negativ");
    }

    Utilizator(const Utilizator& other)
        : id(other.id), nume(other.nume), adresa(other.adresa), sold(other.sold), extra(other.extra) {}

    Utilizator(Utilizator&& other) noexcept
        : id(other.id), nume(std::move(other.nume)), adresa(std::move(other.adresa)), sold(other.sold), extra(std::move(other.extra)) {
        other.sold = 0.0;
    }

    ~Utilizator() = default;

    Utilizator& operator=(const Utilizator& other) {
        if (this != &other) {
            nume = other.nume;
            adresa = other.adresa;
            sold = other.sold;
            extra = other.extra;
        }
        return *this;
    }

    Utilizator& operator=(Utilizator&& other) noexcept {
        if (this != &other) {
            nume = std::move(other.nume);
            adresa = std::move(other.adresa);
            sold = other.sold;
            extra = std::move(other.extra);
            other.sold = 0.0;
        }
        return *this;
    }

    int getId() const { return id; }
    const std::string& getNume() const { return nume; }
    const std::string& getAdresa() const { return adresa; }
    double getSold() const { return sold; }
    const T& getExtra() const { return extra; }

    void setExtra(const T& val) { extra = val; }

    void setSold(double soldNou) {
        if (soldNou < 0) throw std::invalid_argument("Soldul nu poate fi negativ");
        sold = soldNou;
    }
    void adaugaFonduri(double suma) {
        if (suma < 0) throw std::invalid_argument("Suma adăugata nu poate fi negativa");
        sold += suma;
    }
    void extrageFonduri(double suma) {
        if (suma < 0) throw std::invalid_argument("Suma extrasa nu poate fi negativa");
        if (sold < suma) throw std::runtime_error("Fonduri insuficiente");
        sold -= suma;
    }

    static int getNextId() { return nextId; }

    friend std::ostream& operator<<(std::ostream& os, const Utilizator& u) {
        os << "Utilizator ID: " << u.getId()
           << ", Nume: " << u.getNume()
           << ", Adresa: " << u.getAdresa()
           << ", Sold: " << u.getSold() << " lei"
           << ", Puncte: " << u.getExtra();
        return os;
    }
};

template<typename T>
int Utilizator<T>::nextId = 1;

#endif