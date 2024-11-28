#ifndef INZ_HPP
#define INZ_HPP

#include "Pracownik.hpp"

#define CI 1.6

class Inz : public Pracownik {
public:
    Inz(const std::string& imie, const std::string& wydzial)
        : _wydzial(wydzial) {
        set_imie(imie);
    }

    void print() const override {
        std::cout << "Inzynier: " << get_imie() << ", Wydzial: " << _wydzial << std::endl;
    }

    double get_wynagrodzenie() const override {
        return 8000;
    }

private:
    std::string _wydzial;
};

#endif
