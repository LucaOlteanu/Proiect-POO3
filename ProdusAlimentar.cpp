#include "ProdusAlimentar.h"
#include <chrono>
#include <iomanip>
#include <ctime>

ProdusAlimentar::ProdusAlimentar()
    : Produs(), dataExpirare(std::chrono::system_clock::now() + std::chrono::hours(24 * 30)) {}

ProdusAlimentar::ProdusAlimentar(const std::string& nume, double pret, int stoc,
                                 const std::chrono::system_clock::time_point& dataExp)
    : Produs(nume, pret, stoc), dataExpirare(dataExp) {}

ProdusAlimentar::ProdusAlimentar(const ProdusAlimentar& other) = default;
ProdusAlimentar::ProdusAlimentar(ProdusAlimentar&& other) noexcept = default;
ProdusAlimentar& ProdusAlimentar::operator=(const ProdusAlimentar& other) = default;
ProdusAlimentar& ProdusAlimentar::operator=(ProdusAlimentar&& other) noexcept = default;
ProdusAlimentar::~ProdusAlimentar() = default;

double ProdusAlimentar::calculeazaPretFinal() const {
    double pret = getPretBaza();
    auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::hours>(dataExpirare - now).count();
    if (diff < 24)
        pret *= 0.5;
    return pret;
}

ProdusAlimentar* ProdusAlimentar::clone() const {
    return new ProdusAlimentar(*this);
}

bool ProdusAlimentar::esteExpirat() const {
    return std::chrono::system_clock::now() > dataExpirare;
}

void ProdusAlimentar::afisare(std::ostream& os) const {
    os << "Produs alimentar: " << getNume()
       << ", ID: " << getId()
       << ", Pret baza: " << getPretBaza()
       << ", Stoc: " << getStoc()
       << ", Expira la: ";
    std::time_t t = std::chrono::system_clock::to_time_t(dataExpirare);
    os << std::put_time(std::localtime(&t), "%Y-%m-%d");
}