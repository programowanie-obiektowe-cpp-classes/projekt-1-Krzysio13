#ifndef MKT_HPP
#define MKT_HPP

#include "Pracownik.hpp"

#define CMkt 100.0

class Mkt : public Pracownik {
public:
    Mkt(const std::string& imie, int follows)
        : _follows(follows) {
        set_imie(imie);
    }

    void print() const override {
        std::cout << "Marketer: " << get_imie() << ", Follows: " << _follows << std::endl;
    }

    double get_wynagrodzenie() const override {
        return 4500;
    }

private:
    int _follows;
};

#endif
