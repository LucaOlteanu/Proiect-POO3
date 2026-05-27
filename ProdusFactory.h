#ifndef PRODUS_FACTORY_H
#define PRODUS_FACTORY_H

#include <memory>
#include <string>
#include "Produs.h"

class ProdusFactory {
public:
    static std::unique_ptr<Produs> createProdus(
        const std::string& tip,
        const std::string& nume,
        double pret,
        int stoc,
        const std::string& extra = ""
    );
};

#endif