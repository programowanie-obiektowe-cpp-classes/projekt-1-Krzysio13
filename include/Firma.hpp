#ifndef FIRMA_HPP
#define FIRMA_HPP

#include "Pracownik.hpp"
#include "Inz.hpp"
#include "Mag.hpp"
#include "Mkt.hpp"
#include "Rob.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include "Kredyt.hpp"

class Firma {
public:
    Firma(){
        _stan_konta = 10000.0;
        _liczba_inz = 0;
        _liczba_mkt = 0;
        _liczba_mag = 0;
        _liczba_rob = 0;
        _niesprzedane_poprzednio = 0;
    }
    void drukuj_pracownikow() const {
        for (const auto& pracownik : _prac) {
            pracownik->print();
        }
        if(_prac.size()==0){std::cout << "Brak pracownikow!\n";}
    }

    void zatrudnij(std::unique_ptr<Pracownik> pracownik) {
        _prac.push_back(std::move(pracownik));
    }

    void dodaj_pracownika(int pracownik){
        if (pracownik == 1){_liczba_inz += 1;}
        else if (pracownik == 2){_liczba_mkt += 1;}
        else if (pracownik == 3){_liczba_mag += 1;}
        else if (pracownik == 4){_liczba_rob += 1;}
    }

    void wez_kredyt(double kwota, int czas_splaty) {
        _kredyty.push_back(std::make_unique<Kredyt>(kwota, czas_splaty));
        _stan_konta = _stan_konta + kwota;
    }

    double get_popyt(){
        return _startowy_popyt + _liczba_mkt * CMkt;
    }

    double get_pojemnosc_magazynu(){
        return _startowa_pojemnosc_magazynu + _liczba_mag * CMag;
    }

    double get_mozliwosci_produkcyjne(){
        return _liczba_rob * CR;
    }

    double get_cena(){
        return _startowa_cena_produktu * (1+CI*(_liczba_inz));
    }

    double oblicz_przychod() {
        double teoretyczna_produkcja = get_mozliwosci_produkcyjne(); 
        double pojemnosc_magazynu = get_pojemnosc_magazynu();
        double rzeczywista_produkcja;
        if(teoretyczna_produkcja>=pojemnosc_magazynu){
            rzeczywista_produkcja = pojemnosc_magazynu;
        }
        else{
            rzeczywista_produkcja = teoretyczna_produkcja;
        }

        double sprzedane_produkty;
        double popyt = get_popyt();
        if(rzeczywista_produkcja>=popyt){
            sprzedane_produkty = popyt;
            _niesprzedane_poprzednio = rzeczywista_produkcja - popyt;
        }
        else{
            sprzedane_produkty = rzeczywista_produkcja;
        }

        double cena = get_cena();
        double przychod = sprzedane_produkty * cena;
        
        return przychod; 
    }

    void zaplac_wynagrodzenie() {
        double wyplata;
        for (const auto& pracownik : _prac) {
            wyplata += pracownik->get_wynagrodzenie();
        }
        _stan_konta -= wyplata;
        std::cout << "Wynagrodzenie wyplacone." << std::endl;
    }

    void otrzymaj_przychod() {
        double przychod = oblicz_przychod();
        _stan_konta = _stan_konta + przychod;
        std::cout << "Przychod firmy wynosi: " << przychod << std::endl;
    }

    void splac_raty() {
        double suma_rat = 0;
        int ilosc_kredytow = _kredyty.size();
        for (auto& kredyt : _kredyty) {
            suma_rat += kredyt->splac_rate();

            auto it = std::remove_if(_kredyty.begin(), _kredyty.end(),
                                [](std::unique_ptr<Kredyt>& kredyt){
                                    return kredyt->get_pozostale_raty() == 0;
                                });
            _kredyty.erase(it, _kredyty.end());
        }
        _stan_konta -= suma_rat;
        std::cout << "Zaplacono raty " << ilosc_kredytow << " kredytow, o lacznej wartosci: " << suma_rat << std::endl;
    }

    double get_stan_konta(){
        return _stan_konta;
    }

    double wartosc_firmy(){
        double sredni_przychod = 0.0;
        for (auto &przychod : _historia_przych) {
        sredni_przychod += *przychod;
        }
        return sredni_przychod/N - zadluzenie_firmy();
    }

    double zadluzenie_firmy(){
        double suma_zadluzenia = 0;
        for (auto& kredyt : _kredyty) {
            suma_zadluzenia += kredyt->get_zadluzenie();
        }
        return suma_zadluzenia;
    }

    void zliczaj_przychod() {
        double przychod = oblicz_przychod();

        if (_historia_przych.size() >= N) {
            _historia_przych.erase(_historia_przych.begin());
        }
        _historia_przych.push_back(std::make_unique<double>(przychod));
    }

    void od_nowa(){
        _stan_konta = 10000.0;
        _liczba_inz = 0;
        _liczba_mkt = 0;
        _liczba_mag = 0;
        _liczba_rob = 0;
        _niesprzedane_poprzednio = 0; 
        _prac.clear();
        _kredyty.clear();
        _historia_przych.clear();   
    }

    void kup_biuletyn(){
        _stan_konta = _stan_konta - 500;
    }

private:
    int _liczba_inz;
    int _liczba_mkt;
    int _liczba_mag;
    int _liczba_rob;
    double _niesprzedane_poprzednio;

    const double N = 6.0;
    const double _startowa_pojemnosc_magazynu = 70;
    const double _startowa_cena_produktu = 120;
    const double _startowy_popyt = 100;
    
    double _stan_konta;
    
    std::vector<std::unique_ptr<Pracownik>> _prac;
    std::vector<std::unique_ptr<Kredyt>> _kredyty;
    std::vector<std::unique_ptr<double>> _historia_przych;
};

#endif
