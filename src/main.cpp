#include <iostream>
#include "Gra.hpp"
#include "Inz.hpp"
#include "Mkt.hpp"
#include "Mag.hpp"
#include "Rob.hpp"
#include "Firma.hpp"
#include "Kredyt.hpp"

int main() {
    Gra gra;
    
    std::cout << "Witaj w grze! Zaczynamy!" << std::endl;
    gra.rozgrywka();

    return 0;
}
