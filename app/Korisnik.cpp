#include "Korisnik.h"

Korisnik::Korisnik(int id, const std::string& korisnickoIme, const std::string& ime, const std::string& prezime,
                   const std::string& jmbg, const std::string& sifra, const std::string& rola,
                   int brojRacuna, double pocetnoStanje, int brojStednogRacuna, double pocetnoStanjeStedni)
    : id(id), korisnickoIme(korisnickoIme), ime(ime), prezime(prezime), jmbg(jmbg),
      sifra(sifra), rola(rola), racun(brojRacuna, pocetnoStanje, brojStednogRacuna, pocetnoStanjeStedni) {
}

void Korisnik::promijeniSifru(const std::string& novaSifra) {
    sifra = novaSifra;
}

void Korisnik::izvrsiTransakciju(Korisnik& drugiKorisnik, double iznos) {
    // Implementacija funkcionalnosti za izvršavanje transakcije
    // ...
}
