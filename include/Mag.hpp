#ifndef MAG_HPP
#define MAG_HPP

#include "Pracownik.hpp"

#define CMag 100.0

class Mag : public Pracownik {
public:
    Mag(const std::string& imie, bool obsl_widl)
        : _obsl_widl(obsl_widl) {
        set_imie(imie);
    }

    void print() const override {
        std::cout << "Magazynier: " << get_imie() << ", Obsluguje wozek: " << (_obsl_widl ? "Tak" : "Nie") << std::endl;
    }

    double get_wynagrodzenie() const override {
        return 3300;
    }


private:
    bool _obsl_widl;
};

#endif
