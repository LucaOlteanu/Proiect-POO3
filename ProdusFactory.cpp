#include "ProdusFactory.h"
#include "ProdusAlimentar.h"
#include "ProdusElectronic.h"
#include "ProdusMobilier.h"
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>

static std::chrono::system_clock::time_point stringToDate(const std::string& dataStr) {
    int an, luna, zi;
    char dash1, dash2;
    std::istringstream ss(dataStr);
    ss >> an >> dash1 >> luna >> dash2 >> zi;
    if (ss.fail() || dash1 != '-' || dash2 != '-')
        throw std::invalid_argument("Data invalida: " + dataStr);
    std::tm tm = {};
    tm.tm_year = an - 1900;
    tm.tm_mon = luna - 1;
    tm.tm_mday = zi;
    tm.tm_hour = 0; tm.tm_min = 0; tm.tm_sec = 0;
    std::time_t time = std::mktime(&tm);
    if (time == -1)
        throw std::invalid_argument("Data invalida (mktime): " + dataStr);
    return std::chrono::system_clock::from_time_t(time);
}

std::unique_ptr<Produs> ProdusFactory::createProdus(
    const std::string& tip,
    const std::string& nume,
    double pret,
    int stoc,
    const std::string& extra) {

    if (tip == "PRODUS_ALIMENTAR") {
        auto dataExp = stringToDate(extra);
        return std::make_unique<ProdusAlimentar>(nume, pret, stoc, dataExp);
    }
    else if (tip == "PRODUS_ELECTRONIC") {
        int garantie = 12;
        double putere = 0.0;
        std::istringstream ss(extra);
        ss >> garantie;
        if (ss.peek() == ',') ss.ignore();
        ss >> putere;
        return std::make_unique<ProdusElectronic>(nume, pret, stoc, garantie, putere);
    }
    else if (tip == "PRODUS_MOBILIER") {
        std::string material;
        double greutate = 0.0;
        std::istringstream ss(extra);
        std::getline(ss, material, ',');
        ss >> greutate;
        return std::make_unique<ProdusMobilier>(nume, pret, stoc, material, greutate);
    }
    else {
        throw std::invalid_argument("Tip produs necunoscut: " + tip);
    }
}