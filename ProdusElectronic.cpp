#include "ProdusElectronic.h"
#include <stdexcept>
#include <iomanip>

// Constructor default
ProdusElectronic::ProdusElectronic()
    : Produs(), garantieLuni(12), putereWati(0.0) {}

ProdusElectronic::ProdusElectronic(const std::string& nume, double pret, int stoc,
                                   int garLuni, double putere)
    : Produs(nume, pret, stoc), garantieLuni(garLuni), putereWati(putere) {
    if (garLuni < 0 || putere < 0)
        throw std::invalid_argument("Garantia sau puterea nu pot fi negative");
}

ProdusElectronic::~ProdusElectronic() = default;

double ProdusElectronic::calculeazaPretFinal() const {
    double pret = getPretBaza();
    if (garantieLuni > 24)
        pret *= 0.9;
    return pret;
}

ProdusElectronic* ProdusElectronic::clone() const {
    return new ProdusElectronic(*this);
}

void ProdusElectronic::afisare(std::ostream& os) const {
    os << "Produs electronic: " << getNume()
       << ", ID: " << getId()
       << ", Pret baza: " << getPretBaza()
       << ", Stoc: " << getStoc()
       << ", Garantie: " << garantieLuni << " luni"
       << ", Putere: " << putereWati << " W";
}