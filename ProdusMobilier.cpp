#include "ProdusMobilier.h"
#include <stdexcept>
#include <iomanip>

ProdusMobilier::ProdusMobilier()
    : Produs(), material("lemn"), greutateKg(0.0) {}

ProdusMobilier::ProdusMobilier(const std::string& nume, double pret, int stoc,
                               const std::string& material, double greutate)
    : Produs(nume, pret, stoc), material(material), greutateKg(greutate) {
    if (greutate < 0)
        throw std::invalid_argument("Greutatea nu poate fi negativa");
}


ProdusMobilier::~ProdusMobilier() = default;

double ProdusMobilier::calculeazaPretFinal() const {
    double pret = getPretBaza();
    if (greutateKg > 30)
        pret *= 1.15;
    return pret;
}


ProdusMobilier* ProdusMobilier::clone() const {
    return new ProdusMobilier(*this);
}

void ProdusMobilier::afisare(std::ostream& os) const {
    os << "Produs mobilier: " << getNume()
       << ", ID: " << getId()
       << ", Pret baza: " << getPretBaza()
       << ", Stoc: " << getStoc()
       << ", Material: " << material
       << ", Greutate: " << greutateKg << " kg";
}