#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

class StocInsuficientException : public std::runtime_error {
public:
    explicit StocInsuficientException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class SoldInsuficientException : public std::runtime_error {
public:
    explicit SoldInsuficientException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class ProdusInexistentException : public std::runtime_error {
public:
    explicit ProdusInexistentException(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif