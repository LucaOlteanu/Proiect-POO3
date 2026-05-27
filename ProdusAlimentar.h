#ifndef PRODUS_ALIMENTAR_H
#define PRODUS_ALIMENTAR_H

#include "Produs.h"
#include <chrono>

class ProdusAlimentar : public Produs {
private:
    std::chrono::system_clock::time_point dataExpirare;

public:
    ProdusAlimentar();
    ProdusAlimentar(const std::string& nume, double pret, int stoc,
                    const std::chrono::system_clock::time_point& dataExp);
    ProdusAlimentar(const ProdusAlimentar& other);
    ProdusAlimentar(ProdusAlimentar&& other) noexcept;

    ProdusAlimentar& operator=(const ProdusAlimentar& other);
    ProdusAlimentar& operator=(ProdusAlimentar&& other) noexcept;

    ~ProdusAlimentar() override;

    double calculeazaPretFinal() const override;
    ProdusAlimentar* clone() const override;

    bool esteExpirat() const;

protected:
    void afisare(std::ostream& os) const override;
};

#endif // PRODUS_ALIMENTAR_H