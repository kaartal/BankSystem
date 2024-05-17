#ifndef KORISNIK_H
#define KORISNIK_H

#include <string>
#include <vector>
#include "Racun.h"

class Kredit {
public:
    double iznos;
    int brojMjeseci;
    double mjesecnaRata;
};

class Korisnik {
public:
    int id;
    std::string korisnickoIme;
    std::string ime;
    std::string prezime;
    std::string jmbg;
    std::string sifra;
    std::string rola;
    Racun racun;
    std::vector<Kredit> krediti;

    Korisnik(int id, const std::string& korisnickoIme, const std::string& ime, const std::string& prezime,
             const std::string& jmbg, const std::string& sifra, const std::string& rola,
             int brojRacuna, double pocetnoStanje, int brojStednogRacuna, double pocetnoStanjeStedni);
    void promijeniSifru(const std::string& novaSifra);
    void izvrsiTransakciju(Korisnik& drugiKorisnik, double iznos);
};

#endif // KORISNIK_H
