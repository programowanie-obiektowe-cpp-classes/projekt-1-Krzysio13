#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP

#include <string>
#include <iostream>

class Pracownik {
public:
    virtual void print() const = 0;
    virtual double get_wynagrodzenie() const = 0;

    std::string get_imie() const { return _imie; }
    void set_imie(const std::string& imie) { _imie = imie; }

protected:
    std::string _imie;
};

#endif
