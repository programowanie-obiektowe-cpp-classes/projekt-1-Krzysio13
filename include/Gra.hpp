#ifndef GRA_HPP
#define GRA_HPP

#include "Firma.hpp"
#include "Inz.hpp"
#include "Mkt.hpp"
#include "Mag.hpp"
#include "Rob.hpp"
#include <iostream>

class Gra {
public:
    void akcja_gracza() {
        std::cout << "Wybierz akcje:\n";
        std::cout << "1. Zatrudnij pracownika\n";
        std::cout << "2. Wez kredyt\n";
        std::cout << "3. Kup biuletyn informacyjny\n";
        std::cout << "4. Pokaz pracownikow\n";
        std::cout << "5. Pokaz stan finansowy firmy\n";
        std::cout << "6. Przejdz do kolejnej tury\n";
        std::cout << "7. Zakonczenie gry\n";
        
        int input = 0;
        int wybor;
        std::cin >> wybor;

        switch (wybor) {
            case 1: {
                zatrudnij_pracownika();
                break;
            }
            case 2: {
                wez_kredyt();
                break;
            }
            case 3: {
                m_firma.kup_biuletyn();
                std::cout << "Biuletyn informacyjny:\n";
                std::cout << "Biuletyn informacyjny kosztuje 500.\n";
                std::cout << "Kredyt oprocentowany jest 5% w skali miesiaca.\n";
                std::cout << "Pracownicy zarabiaja:\n";
                std::cout << " - Inzynier - 8000\n";
                std::cout << " - Marketer - 4500\n";
                std::cout << " - Magazynier - 3300\n";
                std::cout << " - Robotnik - 4000\n";
                std::cout << "Aktualna cena produktu: " << m_firma.get_cena() << std::endl;
                std::cout << "Pojemnosc magazynu: " << m_firma.get_pojemnosc_magazynu() << std::endl; 
                std::cout << "Popyt: " << m_firma.get_popyt() << std::endl;
                std::cout << "Mozliwosci produkcyjne " << m_firma.get_mozliwosci_produkcyjne() << std::endl;
                std::cout << "Dziekujemy za zakup biuletynu!\n";
                std::cout << "\n";
                break;
            }
            case 4: {
                m_firma.drukuj_pracownikow();
                break;
            }
            case 5: {
                pokaz_stan_finansowy();
                break;
            }
            case 6: {
                przejdz_do_kolejnej_tury();
                break;
            }
            case 7: {
                std::cout << "Konczenie gry!" << std::endl;
                std::cout << "Twoj wynik to:" << std::endl;
                pokaz_stan_finansowy();
                
                while(input!=1){
                    std::cout << "Wybierz 1 by zagrac ponownie...";
                    std::cin >> input;
                }
                m_firma.od_nowa();
                std::cout << " " << std::endl;
                std::cout << "Rozpoczynamy nowa gre!" << std::endl;
                break;
            }
            default:{
                std::cout << "Nieznana opcja!" << std::endl;
            }
        }
    }

    int get_stan(){
        if(m_firma.wartosc_firmy() >= 1000000){return 1;}
        else if(m_firma.get_stan_konta() < 0){return -1;}
        else{return 0;}
    }
    


    void zatrudnij_pracownika() {
        std::cout << "Wybierz typ pracownika:\n";
        std::cout << "1. Inzynier\n";
        std::cout << "2. Marketer\n";
        std::cout << "3. Magazynier\n";
        std::cout << "4. Robotnik\n";
        
        int wybor;

        std::cin >> wybor;
        
        std::string imie;
        std::cout << "Podaj imie pracownika: ";
        std::cin >> imie;

        switch (wybor) {
            case 1: {
                std::string wydzial;
                std::cout << "Podaj wydzial: ";
                std::cin >> wydzial;
                m_firma.zatrudnij(std::make_unique<Inz>(imie, wydzial));
                m_firma.dodaj_pracownika(1);
                break;
            }
            case 2: {
                int follows;
                std::cout << "Podaj liczbe obserwujacych: ";
                std::cin >> follows;
                m_firma.zatrudnij(std::make_unique<Mkt>(imie, follows));
                m_firma.dodaj_pracownika(2);
                break;
            }
            case 3: {
                bool obsl_widl;
                std::cout << "Czy moze obslugiwac wozek widlowy? (1 - Tak, 0 - Nie): ";
                std::cin >> obsl_widl;
                m_firma.zatrudnij(std::make_unique<Mag>(imie, obsl_widl));
                m_firma.dodaj_pracownika(3);
                break;
            }
            case 4: {
                double but;
                std::cout << "Podaj rozmiar buta: ";
                std::cin >> but;
                m_firma.zatrudnij(std::make_unique<Rob>(imie, but));
                m_firma.dodaj_pracownika(4);
                break;
            }
            default:
                std::cout << "Nieznany typ pracownika!" << std::endl;
        }
    }

    void wez_kredyt() {
        double kwota;
        int czas_splaty;

        std::cout << "Podaj kwote kredytu: ";
        std::cin >> kwota;
        while(kwota*1.1+m_firma.zadluzenie_firmy()>M){
            std::cout << "Zbyt duze zadluzenie!" << std::endl;
            std::cout << "Podaj kwote kredytu: ";
            std::cin >> kwota;
        }
        std::cout << "Podaj okres splacenia w miesiacach: " << std::endl;
        std::cin >> czas_splaty;
        while(czas_splaty>20*12){
            std::cout << "Zbyt dlugi czas splaty! Maksymalny okres to 20lat! (240 msc)" << std::endl;
            std::cout << "Podaj okres splacenia w miesiacach: ";
            std::cin >> czas_splaty;
        }

        m_firma.wez_kredyt(kwota, czas_splaty);
    }

    void pokaz_stan_finansowy() {
        std::cout << "Stan konta: " << m_firma.get_stan_konta() << std::endl;
        std::cout << "Zadluzenie: " << m_firma.zadluzenie_firmy() << std::endl; 
        std::cout << "Wartosc firmy: " << m_firma.wartosc_firmy() << std::endl;
    }

    void przejdz_do_kolejnej_tury() {
        std::cout << "Przechodzenie do kolejnej tury..." << std::endl;
        m_firma.zaplac_wynagrodzenie();
        m_firma.otrzymaj_przychod();
        m_firma.splac_raty();
        m_firma.zliczaj_przychod();
        std::cout << "Stan konta po turze: " << m_firma.get_stan_konta() << std::endl;
        std::cout << "Wartosc firmy po rundzie: " << m_firma.wartosc_firmy() << std::endl;
    }

    void rozgrywka() {
        while (get_stan() == 0) {
            akcja_gracza();
        }
        if(get_stan()<0){
            std::cout << " " << std::endl;
            std::cout << "Koniec gry. Firma zbankrutowala!" << std::endl;
            }
        else if(get_stan()>0){
            std::cout << " " << std::endl;
            std::cout << "Wygrana! Jestes MILIONEREM!" << std::endl;
            }
        pokaz_stan_finansowy();
        int input = 0;
        while(input!=1){
            std::cout << "Wybierz 1 by zagrac ponownie...";
            std::cin >> input;
        }   
        m_firma.od_nowa();
        std::cout << " " << std::endl;
        std::cout << "Rozpoczynamy nowa gre!" << std::endl;
    }

private:
    Firma m_firma;
};

#endif
