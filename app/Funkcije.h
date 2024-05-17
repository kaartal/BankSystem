#ifndef FUNKCIJE_H
#define FUNCKIJE_H

#include <iostream>
#include <vector>
#include <string>


struct Kredit {
    double iznos;
    int brojMjeseci;
    double mjesecnaRata;
    const double KAMATNA_STOPA = 0.07;

    Kredit(double iznos, int brojMjeseci, double mjesecnaRata)
        : iznos(iznos), brojMjeseci(brojMjeseci), mjesecnaRata(mjesecnaRata) {}
};

struct Racun {
    int brojRacuna;
    double stanje;
    double stanje_stedni; // Dodao sam ovo pretpostavljajući stedni račun

    Racun(int brojRacuna, double pocetnoStanje, double pocetnoStanje_stedni)
        : brojRacuna(brojRacuna), stanje(pocetnoStanje), stanje_stedni(pocetnoStanje_stedni) {}
};

struct Transakcija {
    int posiljalacID;
    int primalacID;
    double iznos;

    Transakcija(int posiljalac, int primalac, double amount) : posiljalacID(posiljalac), primalacID(primalac), iznos(amount) {}
};




struct Korisnik {
    int id;
    std::string ime;
    std::string prezime;
    std::string jmbg;
    std::string sifra;
    std::string rola;
    Racun racun;
    std::vector<Kredit> krediti;
    std::vector<Transakcija> transakcije;

    Korisnik(int id, std::string ime, std::string prezime, std::string jmbg, std::string sifra, std::string rola,
             int brojRacuna, double pocetnoStanje, double pocetnoStanje_stedni)
        : id(id), ime(ime), prezime(prezime), jmbg(jmbg), sifra(sifra), rola(rola),
          racun(brojRacuna, pocetnoStanje, pocetnoStanje_stedni) {}
};



class SistemPrijave {
private:
    std::vector<Korisnik> korisnici;
    int preostali_pokusaji;

public:
    SistemPrijave();
    void dodajKlijenta();
    void obrisiKlijenta();
    void pregledInformacija(const Korisnik& korisnik);
    void pregledKredita();
    void podizanjeKredita(Korisnik& korisnik);
    void prijava();
    void admin();
    void transferNovca(Korisnik& posiljalac, Korisnik& primalac, double iznos);
    void pregledTransakcija();
    void pregledKlijenata();
    void pregledStanjaRacuna();
    void pregledRacuna();
    void korisnik_funkcija(Korisnik& korisnik);
    void provjeraStanjaRacuna(const Korisnik& korisnik);
    void renumerirajIDjeve();
    void promijeniSifru(Korisnik& korisnik);
    void izmjenaPodatakaKlijenta();
    Korisnik* pronadjiKorisnika(int korisnikId);
};

#endif
