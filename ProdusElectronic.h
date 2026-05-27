#ifndef PRODUS_ELECTRONIC_H
#define PRODUS_ELECTRONIC_H

#include "Produs.h"

class ProdusElectronic : public Produs {
private:
    int garantieLuni;
    double putereWati;
public:
    ProdusElectronic();
    ProdusElectronic(const std::string& nume, double pret, int stoc, int gar, double w);
    ProdusElectronic(const ProdusElectronic&) = default;
    ProdusElectronic(ProdusElectronic&&) = default;
    ~ProdusElectronic() override;
    ProdusElectronic& operator=(const ProdusElectronic&) = default;
    ProdusElectronic& operator=(ProdusElectronic&&) = default;

    double calculeazaPretFinal() const override;
    ProdusElectronic* clone() const override;

protected:
    void afisare(std::ostream& os) const override;
};

#endif