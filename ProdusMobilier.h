#ifndef PRODUS_MOBILIER_H
#define PRODUS_MOBILIER_H

#include "Produs.h"
#include <string>

class ProdusMobilier : public Produs {
private:
    std::string material;
    double greutateKg;
public:
    ProdusMobilier();
    ProdusMobilier(const std::string& nume, double pret, int stoc, const std::string& material, double greutate);
    ProdusMobilier(const ProdusMobilier&) = default;
    ProdusMobilier(ProdusMobilier&&) = default;
    ~ProdusMobilier() override;
    ProdusMobilier& operator=(const ProdusMobilier&) = default;
    ProdusMobilier& operator=(ProdusMobilier&&) = default;

    double calculeazaPretFinal() const override;
    ProdusMobilier* clone() const override;

protected:
    void afisare(std::ostream& os) const override;
};

#endif