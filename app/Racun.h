#ifndef RACUN_H
#define RACUN_H

#include <vector>
#include <string>

class Transakcija {
public:
    std::string opis;
    double iznos;
};

class Racun {
public:
    int brojRacuna;
    double stanje;
    int brojStednogRacuna;
    double stanje_stedni;
    std::vector<Transakcija> transakcije;

    Racun(int brojRacuna, double pocetnoStanje, int brojStednogRacuna, double pocetnoStanjeStedni);

    void dodajTransakciju(const Transakcija& transakcija);
};

#endif // RACUN_H
