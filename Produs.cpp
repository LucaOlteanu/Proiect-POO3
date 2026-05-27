#include "Produs.h"
#include <stdexcept>

int Produs::nextId = 1;

Produs::Produs() : id(nextId++), nume("necunoscut"), pretBaza(0.0), stoc(0) {}

Produs::Produs(const std::string& nume, double pret, int stoc)
    : id(nextId++), nume(nume), pretBaza(pret), stoc(stoc) {
    if (pret < 0 || stoc < 0)
        throw std::invalid_argument("Pretul sau stocul nu poate fi negativ");
}

Produs::Produs(const Produs& other)
    : id(other.id), nume(other.nume), pretBaza(other.pretBaza), stoc(other.stoc) {}

Produs::Produs(Produs&& other) noexcept
    : id(other.id), nume(std::move(other.nume)), pretBaza(other.pretBaza), stoc(other.stoc) {
    other.pretBaza = 0;
    other.stoc = 0;
}

Produs& Produs::operator=(const Produs& other) {
    if (this != &other) {
        nume = other.nume;
        pretBaza = other.pretBaza;
        stoc = other.stoc;
    }
    return *this;
}

Produs& Produs::operator=(Produs&& other) noexcept {
    if (this != &other) {
        nume = std::move(other.nume);
        pretBaza = other.pretBaza;
        stoc = other.stoc;
        other.pretBaza = 0;
        other.stoc = 0;
    }
    return *this;
}

Produs::~Produs() {}

int Produs::getId() const { return id; }
const std::string& Produs::getNume() const { return nume; }
double Produs::getPretBaza() const { return pretBaza; }
int Produs::getStoc() const { return stoc; }

void Produs::setStoc(int stocNou) {
    if (stocNou < 0) throw std::invalid_argument("Stoc negativ");
    stoc = stocNou;
}

void Produs::actualizeazaStoc(int cantitate) { //setter pentru actualizare stoc
    if (cantitate < 0 && stoc + cantitate < 0)
        throw std::runtime_error("Stoc insuficient");
    stoc += cantitate;
}

std::ostream& operator<<(std::ostream& os, const Produs& p) {
    p.afisare(os);
    return os;
}

int Produs::getNextId() { return nextId; }