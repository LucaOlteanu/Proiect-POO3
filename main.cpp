#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <chrono>
#include <string>
#include <ctime>

#include "Produs.h"
#include "ProdusAlimentar.h"
#include "ProdusElectronic.h"
#include "ProdusMobilier.h"
#include "Utilizator.h"
#include "Cos.h"
#include "Exceptii.h"
#include "Discount.h"
#include "Catalog.h"
#include "ProdusFactory.h"
#include "ComandaBuilder.h"

// helper trim
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

// conversie data
std::chrono::system_clock::time_point stringToDate(const std::string& dataStr) {
    int an, luna, zi;
    char dash1, dash2;
    std::istringstream ss(dataStr);
    ss >> an >> dash1 >> luna >> dash2 >> zi;
    if (ss.fail() || dash1 != '-' || dash2 != '-') {
        throw std::invalid_argument("Data invalida: " + dataStr);
    }
    std::tm tm = {};
    tm.tm_year = an - 1900;
    tm.tm_mon = luna - 1;
    tm.tm_mday = zi;
    tm.tm_hour = 0; tm.tm_min = 0; tm.tm_sec = 0;
    std::time_t time = std::mktime(&tm);
    if (time == -1) {
        throw std::invalid_argument("Data invalida (mktime): " + dataStr);
    }
    return std::chrono::system_clock::from_time_t(time);
}

int main() {
    std::cout << "=== BINE ATI VENIT LA MAGAZINUL ONLINE ===\n\n";

    // 1. Singleton catalog
    auto& catalog = Catalog::getInstance();

    // 2. Citire date din fisier
    std::ifstream fin("date_intrare.txt");
    if (!fin.is_open()) {
        std::cerr << "Eroare: Nu s-a putut deschide fisierul date_intrare.txt\n";
        return 1;
    }

    Utilizator<int> user;
    bool userCitit = false;
    std::string linie;

    while (std::getline(fin, linie)) {
        linie = trim(linie);
        if (linie.empty()) continue;

        std::istringstream iss(linie);
        std::string tip;
        std::getline(iss, tip, ':');
        tip = trim(tip);
        if (tip.empty()) continue;

        std::string rest;
        std::getline(iss, rest);
        rest = trim(rest);
        if (rest.empty()) continue;

        if (tip == "USER") {
            std::string nume, adresa;
            double sold;
            size_t pos1 = rest.find(',');
            if (pos1 == std::string::npos) continue;
            nume = trim(rest.substr(0, pos1));
            size_t pos2 = rest.find(',', pos1 + 1);
            if (pos2 == std::string::npos) continue;
            adresa = trim(rest.substr(pos1 + 1, pos2 - pos1 - 1));
            sold = std::stod(trim(rest.substr(pos2 + 1)));
            user = Utilizator<int>(nume, adresa, sold, 0);
            userCitit = true;
            std::cout << "Utilizator citit: " << user << "\n";
        }
        else if (tip == "PRODUS_ALIMENTAR") {
            std::string nume, dataExp;
            double pret;
            int stoc;
            size_t pos1 = rest.find(',');
            if (pos1 == std::string::npos) continue;
            nume = trim(rest.substr(0, pos1));
            size_t pos2 = rest.find(',', pos1 + 1);
            if (pos2 == std::string::npos) continue;
            pret = std::stod(trim(rest.substr(pos1 + 1, pos2 - pos1 - 1)));
            size_t pos3 = rest.find(',', pos2 + 1);
            if (pos3 == std::string::npos) continue;
            stoc = std::stoi(trim(rest.substr(pos2 + 1, pos3 - pos2 - 1)));
            dataExp = trim(rest.substr(pos3 + 1));
            auto dataExpPoint = stringToDate(dataExp);
            if (std::chrono::system_clock::now() > dataExpPoint) {
                std::cout << "Produsul alimentar '" << nume << "' este expirat si nu va fi adaugat in catalog.\n";
                continue;
            }
            auto produs = ProdusFactory::createProdus(tip, nume, pret, stoc, dataExp);
            catalog.adaugaProdus(std::move(produs));
        }
        else if (tip == "PRODUS_ELECTRONIC") {
            std::string nume;
            double pret, putere;
            int stoc, garantie;
            size_t pos1 = rest.find(',');
            if (pos1 == std::string::npos) continue;
            nume = trim(rest.substr(0, pos1));
            size_t pos2 = rest.find(',', pos1 + 1);
            if (pos2 == std::string::npos) continue;
            pret = std::stod(trim(rest.substr(pos1 + 1, pos2 - pos1 - 1)));
            size_t pos3 = rest.find(',', pos2 + 1);
            if (pos3 == std::string::npos) continue;
            stoc = std::stoi(trim(rest.substr(pos2 + 1, pos3 - pos2 - 1)));
            size_t pos4 = rest.find(',', pos3 + 1);
            if (pos4 == std::string::npos) continue;
            garantie = std::stoi(trim(rest.substr(pos3 + 1, pos4 - pos3 - 1)));
            putere = std::stod(trim(rest.substr(pos4 + 1)));
            std::string extra = std::to_string(garantie) + "," + std::to_string(putere);
            auto produs = ProdusFactory::createProdus(tip, nume, pret, stoc, extra);
            catalog.adaugaProdus(std::move(produs));
        }
        else if (tip == "PRODUS_MOBILIER") {
            std::string nume, material;
            double pret, greutate;
            int stoc;
            size_t pos1 = rest.find(',');
            if (pos1 == std::string::npos) continue;
            nume = trim(rest.substr(0, pos1));
            size_t pos2 = rest.find(',', pos1 + 1);
            if (pos2 == std::string::npos) continue;
            pret = std::stod(trim(rest.substr(pos1 + 1, pos2 - pos1 - 1)));
            size_t pos3 = rest.find(',', pos2 + 1);
            if (pos3 == std::string::npos) continue;
            stoc = std::stoi(trim(rest.substr(pos2 + 1, pos3 - pos2 - 1)));
            size_t pos4 = rest.find(',', pos3 + 1);
            if (pos4 == std::string::npos) continue;
            material = trim(rest.substr(pos3 + 1, pos4 - pos3 - 1));
            greutate = std::stod(trim(rest.substr(pos4 + 1)));
            std::string extra = material + "," + std::to_string(greutate);
            auto produs = ProdusFactory::createProdus(tip, nume, pret, stoc, extra);
            catalog.adaugaProdus(std::move(produs));
        }
    }
    fin.close();

    if (!userCitit || catalog.size() == 0) {
        std::cerr << "Eroare: Nu s-au citit datele corect (utilizator sau catalog gol).\n";
        return 1;
    }

    // 3. Afisare catalog si preturi finale
    std::cout << "\n=== CATALOG PRODUSE ===\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        std::cout << i + 1 << ". " << *catalog.getProdus(i) << '\n';
    }
    std::cout << "=======================\n\n";

    std::cout << "\n=== PRETURI FINALE (dupa reduceri/taxe) ===\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        const auto* prod = catalog.getProdus(i);
        std::cout << prod->getNume() << " : " << prod->calculeazaPretFinal() << " lei\n";
    }
    std::cout << "=======================\n\n";

    // 4. Sesiune interactiva de cumparare
    Cos cos(user);

    std::ifstream finComenzi("comenzi.txt");
    std::istream& inputStream = finComenzi.is_open() ? static_cast<std::istream&>(finComenzi) : std::cin;

    std::cout << "=== SESIUNE DE CUMPARARE ===\n";
if (finComenzi.is_open())
    std::cout << "Se executa comenzile din fisierul 'comenzi.txt'...\n";
else
    std::cout << "Mod interactiv. Introduceti comenzile:\n";

std::cout << "Optiuni:\n";
std::cout << "  add <index> <cantitate>  - adauga produsul cu indexul dat\n";
std::cout << "  remove <index>           - sterge produsul din cos (indexul din cos)\n";
std::cout << "  show                     - afiseaza cosul curent\n";
std::cout << "  catalog                  - afiseaza catalogul din nou\n";
std::cout << "  checkout                 - finalizeaza comanda\n";
std::cout << "  quit                     - iesire fara comanda\n\n";

std::string comanda;
while (true) {
    std::cout << "> ";
    if (!std::getline(inputStream, comanda)) break;
    if (comanda.empty()) continue;

    std::istringstream iss(comanda);
    std::string actiune;
    iss >> actiune;

    if (actiune == "add") {
        int index, cantitate;
        if (!(iss >> index >> cantitate)) {
            std::cout << "Format: add <index> <cantitate>\n";
            continue;
        }
        if (index < 1 || index > static_cast<int>(catalog.size())) {
            std::cout << "Index invalid (1-" << catalog.size() << ")\n";
            continue;
        }
        try {
            cos.adaugaProdus(*catalog.getProdus(index - 1), cantitate);
            std::cout << "Produs adaugat.\n";
        } catch (const std::exception& e) {
            std::cout << "Eroare: " << e.what() << '\n';
        }
    }
    else if (actiune == "remove") {
        int index;
        if (!(iss >> index)) {
            std::cout << "Format: remove <index>\n";
            continue;
        }
        try {
            cos.eliminaProdus(index - 1);
            std::cout << "Produs eliminat.\n";
        } catch (const std::out_of_range& e) {
            std::cout << "Index invalid in cos.\n";
        }
    }
    else if (actiune == "show") {
        std::cout << cos;
    }
    else if (actiune == "catalog") {
        std::cout << "\n=== CATALOG PRODUSE ===\n";
        for (size_t i = 0; i < catalog.size(); ++i) {
            std::cout << i + 1 << ". " << *catalog.getProdus(i) << '\n';
        }
        std::cout << "=======================\n\n";
    }
    else if (actiune == "checkout") {
        break;
    }
    else if (actiune == "quit") {
        std::cout << "Ati renuntat la comanda. La revedere!\n";
        return 0;
    }
    else {
        std::cout << "Comanda necunoscuta. Optiuni: add, remove, show, catalog, checkout, quit\n";
    }
}

    // 5. Finalizare comanda
    std::cout << "\n=== COS FINAL ===\n";
    std::cout << cos;

    if (cos.getTotal() == 0) {
        std::cout << "Cosul este gol. Comanda nu poate fi finalizata.\n";
        return 0;
    }

    std::cout << "\nDoriti sa folositi punctele de loialitate? (1=da / 0=nu): ";
    int opt;
    std::cin >> opt;
    bool folosestePuncte = (opt == 1);

    std::cout << "=== FINALIZARE COMADA ===\n";
    try {
        cos.finalizeazaComanda(catalog.getProduse(), folosestePuncte);
        std::cout << "Comanda finalizata cu succes!\n";
        std::cout << "Sold ramas: " << user.getSold() << '\n';
        std::cout << "Puncte loialitate ramase: " << user.getExtra() << '\n';
    } catch (const SoldInsuficientException& e) {
        std::cerr << "Eroare sold: " << e.what() << '\n';
    } catch (const StocInsuficientException& e) {
        std::cerr << "Eroare stoc: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << '\n';
    }

    // 6. Afisare catalog final
    std::cout << "\n=== CATALOG FINAL ===\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        std::cout << *catalog.getProdus(i) << '\n';
    }

    std::cout << "\n=== PROGRAM TERMINAT ===\n";
    return 0;
}