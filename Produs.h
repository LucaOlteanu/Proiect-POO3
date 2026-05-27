#ifndef PRODUS_H
#define PRODUS_H

#include <iostream>
#include <string>

class Produs {
private:
    static int nextId;
    const int id;
    std::string nume;
    double pretBaza;
    int stoc;

public:
    Produs();
    Produs(const std::string& nume, double pret, int stoc);
    Produs(const Produs& other);
    Produs(Produs&& other) noexcept;
    virtual ~Produs();

    Produs& operator=(const Produs& other);
    Produs& operator=(Produs&& other) noexcept;

    int getId() const;
    const std::string& getNume() const;
    double getPretBaza() const;
    int getStoc() const;

    void setStoc(int stocNou);
    void actualizeazaStoc(int cantitate);

    virtual double calculeazaPretFinal() const = 0;
    virtual Produs* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Produs& p);

    static int getNextId();

protected:
    virtual void afisare(std::ostream& os) const = 0;
};

#endif