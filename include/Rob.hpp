#ifndef ROB_HPP
#define ROB_HPP

#include "Pracownik.hpp"

#define CR 30.0

class Rob : public Pracownik {
public:
    Rob(const std::string& imie, double but)
        : _but(but) {
        set_imie(imie);
    }

    void print() const override {
        std::cout << "Robotnik: " << get_imie() << ", Rozmiar buta: " << _but << std::endl;
    }

    double get_wynagrodzenie() const override {
        return 4000;
    }

private:
    double _but;
};

#endif
