#include "Racun.h"

Racun::Racun(int brojRacuna, double pocetnoStanje, int brojStednogRacuna, double pocetnoStanjeStedni)
    : brojRacuna(brojRacuna), stanje(pocetnoStanje), brojStednogRacuna(brojStednogRacuna), stanje_stedni(pocetnoStanjeStedni) {
}

void Racun::dodajTransakciju(const Transakcija& transakcija) {
    transakcije.push_back(transakcija);
}
