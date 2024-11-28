#ifndef KREDYT_HPP
#define KREDYT_HPP

#include <iostream>
#define M 1000000

class Kredyt {
public:
    Kredyt(double dlug, int pozostale_raty) : _dlug(dlug), _pozostale_raty(pozostale_raty) {
        _dlug = _dlug*(1+(0.05*pozostale_raty));
        _rata = _dlug/_pozostale_raty;
        std::cout << "Rata kredytu: " << _rata << std::endl;
    }

    double splac_rate() {
        _dlug -= _rata;
        _pozostale_raty--;
        
        return _rata;
    }

    int get_pozostale_raty(){
        return _pozostale_raty;
    }

    double get_zadluzenie(){
        return _dlug;
    }

private:
    double _rata;
    double _dlug;
    int _pozostale_raty;
};

#endif
