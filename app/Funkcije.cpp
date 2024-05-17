#include "Funkcije.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iomanip>

SistemPrijave::SistemPrijave() : preostali_pokusaji(3) {
    korisnici.push_back(Korisnik(0, "admin", "Admin", "1234567890123", "admin123", "admin", 0, 0.0, 0.0));
    korisnici.push_back(Korisnik(1, "Armin", "Hupic", "1345723456789", "user1", "korisnik", 1, 30000.0, 7000.0));
    korisnici.push_back(Korisnik(2, "Goran", "Lonic", "3145234567890", "user2", "korisnik", 2, 40000.0, 80000.0));
    korisnici.push_back(Korisnik(3, "Halid", "Kartal", "5714245678901", "user3", "korisnik", 3, 50000.0, 95000.0));
    korisnici.push_back(Korisnik(4, "Jusuf", "Salkanovic", "6123646789012", "user4", "korisnik", 4, 60000.0, 100000.0));
}

void loading() {
    for (int i = 0; i < 3; i++) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;
}

#include <iostream>
#include <thread>
#include <chrono>

void SistemPrijave::prijava() {
    std::string uneseno_ime, unesena_sifra;
    while (preostali_pokusaji > 0) {
        system("clear");
        std::cout << "╔════════════════════════════╗" << std::endl;
        std::cout << "║          PRIJAVA           ║" << std::endl;
        std::cout << "╚════════════════════════════╝" << std::endl;

        std::cout << "| Korisnicko ime: ";
        std::cin >> uneseno_ime;

        std::cout << "| Sifra: ";
        std::cin >> unesena_sifra;

        bool prijava_uspjesna = false;
        for (auto& korisnik : korisnici) {
            if (uneseno_ime == korisnik.ime && unesena_sifra == korisnik.sifra) {
                system("clear");
                loading();
                std::cout << "| Dobrodosli, " << korisnik.ime << "! |" << std::endl;
                if (korisnik.rola == "admin") {
                    admin();
                } else if (korisnik.rola == "korisnik") {
                    korisnik_funkcija(korisnik);
                }
                preostali_pokusaji = 3;
                prijava_uspjesna = true;
                break;
            }
        }

        if (!prijava_uspjesna) {
            std::cout << "| Pogresno korisnicko ime ili sifra. Preostali pokusaji: " << preostali_pokusaji - 1 << std::endl;
            preostali_pokusaji--;

            if (preostali_pokusaji > 0) {
                std::cout << "| Molimo, pokusajte ponovo unijeti podatke |" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3)); 
            } else {
                std::cout << "| Previse pogresnih. Odjava |" << std::endl;
                loading();
                exit(0);
            }
        } else {
            preostali_pokusaji = 3;
        }
    }
    system("clear");
}



void SistemPrijave::pregledKlijenata() { // admin
    system("clear"); 

    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                PREGLED KLIJENATA U SISTEMU                   ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;

    for (const auto& korisnik : korisnici) {
        if (korisnik.rola == "korisnik") {
            std::cout << "| Ime: " << korisnik.ime << std::endl;
            std::cout << "| Prezime: " << korisnik.prezime << std::endl;
            std::cout << "| ID: " << korisnik.id << std::endl;
            std::cout << "| JMBG: " << korisnik.jmbg << std::endl;
     std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
        }
    }
}


void SistemPrijave::dodajKlijenta() {  // admin
    system("clear");
    int noviID = korisnici.size() + 1;
    std::string novoIme, novoPrezime, novoJMBG, novaSifra;
    double pocetnoStanjeTekuci, pocetnoStanjeStedni;

    std::cout << "| Unesite ime novog klijenta: " << std::flush;
    std::cin >> novoIme;
    std::cout << "| Unesite prezime novog klijenta: " << std::flush;
    std::cin >> novoPrezime;
    do {
        std::cout << "| Unesite JMBG novog klijenta (13 cifara): " << std::flush;
        std::cin >> novoJMBG;

        if (novoJMBG.length() != 13) {
            std::cout << "| JMBG mora imati tačno 13 cifara. Molimo pokušajte ponovo.|" << std::endl;
        }
    } while (novoJMBG.length() != 13);
    
    std::cout << "| Unesite sifru novog klijenta: " << std::flush;
    std::cin >> novaSifra;
    std::cout << "| Unesite pocetno stanje na tekucem racunu novog klijenta: " << std::flush;
    std::cin >> pocetnoStanjeTekuci;
    std::cout << "| Unesite pocetno stanje na stednom racunu novog klijenta: " << std::flush;
    std::cin >> pocetnoStanjeStedni;

    korisnici.push_back(Korisnik(noviID, novoIme, novoPrezime, novoJMBG, novaSifra, "korisnik", noviID, pocetnoStanjeTekuci, pocetnoStanjeStedni));
    std::cout << "| Novi klijent je uspjesno dodan u sistem|" << std::endl;
}

void SistemPrijave::obrisiKlijenta() {
    system("clear");
    int IDbrisanje;
    std::cout << "| Unesite ID klijenta kojeg zelite izbrisati iz sistema: " << std::flush;
    std::cin >> IDbrisanje;

    auto it = std::remove_if(korisnici.begin(), korisnici.end(), [IDbrisanje](const Korisnik& k) {
        return k.id == IDbrisanje && k.rola == "korisnik";
    });

    if (it != korisnici.end()) {
        korisnici.erase(it, korisnici.end());
        std::cout << "| Klijent je uspjesno izbrisan iz sistema|" << std::endl;
        renumerirajIDjeve();
    } else {
        std::cout << "| Klijent pod ID brojem " << IDbrisanje << " nije pronadjen u sistemu|" << std::endl;
    }
}


void SistemPrijave::pregledInformacija(const Korisnik& korisnik) {
    system("clear");
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                PREGLED INFORMACIJA O KORISNIKU               ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "| ID: " << korisnik.id << std::endl;
    std::cout << "| Ime: " << korisnik.ime << std::endl;
    std::cout << "| Prezime: " << korisnik.prezime << std::endl;
    std::cout << "| JMBG: " << korisnik.jmbg << std::endl;
    std::cout << "| Broj tekuceg racuna: " << korisnik.racun.brojRacuna << std::endl;
    std::cout << "| Stanje tekuceg racuna: " << korisnik.racun.stanje << std::endl;
    std::cout << "| Stanje stednog racuna: " << korisnik.racun.stanje_stedni << std::endl;
}


void SistemPrijave::podizanjeKredita(Korisnik& korisnik) {
    system("clear");
    const double kamatnaStopa = 0.07;
    const double maksimalniIznosKredita = 20 * korisnik.racun.stanje;

    double iznosKredita;
    std::cout << "| Unesite iznos kredita: " << std::flush;
    std::cin >> iznosKredita;

    if (std::cin.fail() || iznosKredita <= 0 || iznosKredita > maksimalniIznosKredita) {
        std::cout << "| Neispravan unos iznosa kredita. Molimo unesite broj veći od 0 i manji ili jednak " << maksimalniIznosKredita << " |" << std::endl;
        std::cin.clear(); // Resetujemo stanje ulaznog bafera
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorišemo preostale znakove u baferu
        return;
    }

    int brojMeseci;
    std::cout << "| Unesite period otplate kredita u mesecima: " << std::flush;
    std::cin >> brojMeseci;

    if (std::cin.fail() || brojMeseci <= 0) {
        std::cout << "| Neispravan unos perioda otplate. Molimo unesite broj veći od 0. |" << std::endl;
        std::cin.clear(); // Resetujemo stanje ulaznog bafera
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorišemo preostale znakove u baferu
        return;
    }

    double kamata = iznosKredita * kamatnaStopa;
    double ukupanIznos = iznosKredita + kamata;

    korisnik.racun.stanje += iznosKredita;

    Kredit noviKredit{iznosKredita, brojMeseci, ukupanIznos};
    korisnik.krediti.push_back(noviKredit);

    std::cout << "| Kredit uspjesno podignut. Novo stanje na tekucem racunu: " << korisnik.racun.stanje << " KM|" << std::endl;
    std::cout << "| Mjesecna rata: " << ukupanIznos / brojMeseci << " KM|" << std::endl;

    // Ispisivanje ugovora
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                        DETALJI O KREDITU                     ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "| Korisnik: " << korisnik.ime << " " << korisnik.prezime << std::endl;
    std::cout << "| Iznos kredita: " << iznosKredita << " KM" << std::endl;
    std::cout << "| Kamatna stopa: " << kamatnaStopa * 100 << "%" << std::endl;
    std::cout << "| Period otplate: " << brojMeseci << " meseci" << std::endl;
    std::cout << "| Mjesecna rata: " << ukupanIznos / brojMeseci << " KM" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
}



void SistemPrijave::pregledTransakcija() {
    std::cout << "| Pregled svih transakcija u sistemu:|" << std::endl;
    std::cout << "══════════════════════════════════════════════════════" << std::endl;

    for (const auto& korisnik : korisnici) {
        if (!korisnik.transakcije.empty()) {
            for (const auto& transakcija : korisnik.transakcije) {
                Korisnik* posiljalac = pronadjiKorisnika(transakcija.posiljalacID);
                Korisnik* primalac = pronadjiKorisnika(transakcija.primalacID);
                if (posiljalac && primalac) {
                    std::cout << "| Posiljalac: " << posiljalac->ime + " " + posiljalac->prezime << std::endl;
                    std::cout << "| Primalac:   " << primalac->ime + " " + primalac->prezime << std::endl;
                    std::cout << "| Iznos:      " << transakcija.iznos << std::endl;
     std::cout << "══════════════════════════════════════════════════════" << std::endl;
                } else {
                    std::cout << "| Neki od korisnika u transakciji nije pronadjen |" << std::endl;
                }
            }
        }
    }
}

void SistemPrijave::pregledRacuna() {
    system("clear");
    std::cout << "| Pregled racuna u sistemu:|" << std::endl;
    std::cout << "══════════════════════════════════════════════════════" << std::endl;

    for (const auto& korisnik : korisnici) {
        if (korisnik.rola == "korisnik") {
            std::cout << "| ID:                 " << korisnik.id << std::endl;
            std::cout << "| Ime i prezime:      " << korisnik.ime + " " + korisnik.prezime << std::endl;
            std::cout << "| JMBG:               " << korisnik.jmbg << std::endl;
            std::cout << "| Stanje tekuceg:     " << korisnik.racun.stanje << std::endl;
            std::cout << "| Stanje stednog:     " << korisnik.racun.stanje_stedni << std::endl;
            std::cout << "| Sifra:              " << korisnik.sifra << std::endl;
     std::cout << "══════════════════════════════════════════════════════" << std::endl;
        }
    }
}

void SistemPrijave::admin() {
    int izbor;
    char odgovor;
    do {
             system("clear");
    
        std::cout << "╔════════════════════════════════════╗" << std::endl;
        std::cout << "║              ADMIN                 ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "║ 1. Pregled klijenata               ║" << std::endl;
        std::cout << "║ 2. Dodaj novog klijenta            ║" << std::endl;
        std::cout << "║ 3. Izmjena podataka klijenta       ║" << std::endl;
        std::cout << "║ 4. Obrisi klijenta                 ║" << std::endl;
        std::cout << "║ 5. Pregled racuna                  ║" << std::endl;
        std::cout << "║ 6. Pregled transakcija             ║" << std::endl;
        std::cout << "║ 7. Pregled kredita                 ║" << std::endl;
        std::cout << "║ 8. Odjava                          ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;

        std::cout << "Unesite opciju: ";
        std::cin >> izbor;

        switch (izbor) {
            case 1:
                pregledKlijenata();
                break;
            case 2:
                dodajKlijenta();
                break;
            case 3:
		izmjenaPodatakaKlijenta();
                break;
            case 4:
                obrisiKlijenta();
                break;
            case 5:
                pregledRacuna();
                break;
            case 6:
                pregledTransakcija();
                break;
            case 7:
                pregledKredita();
                break;
            case 8:
                std::cout << "Odjava..." << std::endl;
                loading();
                prijava();
                break;
            default:
                std::cout << "| Nepostojeca opcija. Molimo pokusajte ponovo." << std::endl;
                break;
        }
    std::cout << "Zelite li izaci iz programa? (D/N): ";
            std::cin >> odgovor;

        } while (odgovor != 'D' && odgovor != 'd');
	loading();
	std::cout<<"Odjava"<<std::flush;
	prijava();
    }



void SistemPrijave::korisnik_funkcija(Korisnik& korisnik) {
        int izbor;
        char odgovor;

        do {
             system("clear"); 

            std::cout << "╔════════════════════════════════════╗" << std::endl;
            std::cout << "║              KORISNIK              ║" << std::endl;
            std::cout << "╚════════════════════════════════════╝" << std::endl;
            std::cout << "║  1. Pregled stanja racuna          ║" << std::endl;
            std::cout << "║  2. Podizanje kredita              ║" << std::endl;
            std::cout << "║  3. Transakcije                    ║" << std::endl;
            std::cout << "║  4. Pregled informacija            ║" << std::endl;
            std::cout << "║  5. Promjena sifre                 ║" << std::endl;
            std::cout << "║  6. Odjava                         ║" << std::endl;
            std::cout << "╚════════════════════════════════════╝" << std::endl;

            std::cout << "Unesite opciju: ";
            std::cin >> izbor;

            switch (izbor) {
                case 1:
                    provjeraStanjaRacuna(korisnik);
                    break;
                case 2:
                    podizanjeKredita(korisnik);
                    break;
                case 3:
                    {
                        int primalacId;
                        double iznosZaTransfer;
                        std::cout << "| Unesite ID korisnika kojem zelite poslati novac: " << std::flush;
                        std::cin >> primalacId;
                        std::cout << "| Unesite iznos koji zelite poslati: " << std::flush;
                        std::cin >> iznosZaTransfer;
                        Korisnik* primalac = pronadjiKorisnika(primalacId);
                        if (primalac) {
                            transferNovca(korisnik, *primalac, iznosZaTransfer);
                        } else {
                            std::cout << "| Korisnik sa unesenim ID-om ne postoji." << std::endl;
                        }
                    }
                    break;
                case 4:
                    pregledInformacija(korisnik);
                    break;
                case 5:
                    promijeniSifru(korisnik);
                    break;
                case 6:
                    std::cout << "| Odjava..." << std::endl;
                    loading();
                    prijava();
                    break;
                default:
                    std::cout << "| Nepostojeca opcija. Molimo pokusajte ponovo." << std::endl;
                    break;
            }

            std::cout << "Zelite li izaci iz programa? (D/N): ";
            std::cin >> odgovor;

        } while (odgovor != 'D' && odgovor != 'd');
	loading();
	std::cout<<"Odjava"<<std::flush;
	prijava();
    }


void SistemPrijave::provjeraStanjaRacuna(const Korisnik& korisnik) {
    system("clear");
    std::cout << "| Stanje tekuceg racuna: " << korisnik.racun.stanje <<" KM"<<std::endl;
    std::cout << "| Stanje stednog racuna: " << korisnik.racun.stanje_stedni <<" KM"<<std::endl;
}

#include <iomanip>  

void SistemPrijave::pregledKredita() {
    std::cout << "| Pregled kredita u sistemu:|" << std::endl;
    std::cout << "══════════════════════════════════════════════════════" << std::endl;

    for (const auto& korisnik : korisnici) {
        if (!korisnik.krediti.empty()) {
            for (const auto& kredit : korisnik.krediti) {
                std::cout << "| Ime i prezime:      " << korisnik.ime + " " + korisnik.prezime << std::endl;
                std::cout << "| JMBG:               " << korisnik.jmbg << std::endl;
                std::cout << "| ID:                 " << korisnik.id << std::endl;
                std::cout << "| Kolicina kredita:   " << kredit.iznos << std::endl;
                std::cout << "| Broj rata:          " << kredit.brojMjeseci << std::endl;
                std::cout << "| Mjesecna rata:      " << kredit.iznos / kredit.brojMjeseci << std::endl;
    std::cout << "══════════════════════════════════════════════════════" << std::endl;
            }
        }
    }
}

void SistemPrijave::transferNovca(Korisnik& posiljalac, Korisnik& primalac, double iznos) {
    system("clear");
    if (std::cin.fail() || iznos <= 0) {
        std::cout << "| Neispravan unos. Molimo unesite validan iznos. |" << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        return;
    }

    if (!pronadjiKorisnika(posiljalac.id) || !pronadjiKorisnika(primalac.id)) {
        std::cout << "| Korisnik nije pronadjen. Proverite unesene ID-jeve. |" << std::endl;
        return;
    }

    if (iznos <= posiljalac.racun.stanje) {
        posiljalac.racun.stanje -= iznos;
        primalac.racun.stanje += iznos;
        Transakcija transakcija{posiljalac.id, primalac.id, iznos};
        posiljalac.transakcije.push_back(transakcija);

        std::cout << "| Uspjesno ste poslali " << iznos << " KM korisniku " << primalac.ime << " |" << std::endl;
        std::cout << "| Detalji transakcije: " << std::endl;
        std::cout << "|   Posiljalac: " << posiljalac.ime << " " << posiljalac.prezime << " (" << posiljalac.jmbg << ")" << std::endl;
        std::cout << "|   Primalac: " << primalac.ime << " " << primalac.prezime << " (" << primalac.jmbg << ")" << std::endl;
        std::cout << "|   Iznos: " << iznos << " KM" << std::endl;
        std::cout << "|   Stanje tekuceg racuna posiljaoca: " << posiljalac.racun.stanje << " KM" << std::endl;
    } else {
        std::cout << "| Neuspjesan transfer. Provjexiterite iznos ili dostupno stanje na tekucem racunu. |" << std::endl;
    }
}

void SistemPrijave::renumerirajIDjeve() {
    int noviID = 1;
    for (auto& korisnik : korisnici) {
        if (korisnik.rola == "korisnik") {
            korisnik.id = noviID++;
        }
    }
}

void SistemPrijave::izmjenaPodatakaKlijenta() {
    system("clear");
    int idKlijenta;
    std::cout << "| Unesite ID klijenta kojeg zelite izmijeniti: " << std::flush;
    std::cin >> idKlijenta;

    Korisnik* klijent = pronadjiKorisnika(idKlijenta);
    if (klijent != nullptr) {
        int izbor;
        do {
            system("clear");
            std::cout << "╔════════════════════════════════════════╗" << std::endl;
            std::cout << "║        IZMJENA PODATAKA KLIJENTA       ║" << std::endl;
            std::cout << "╚════════════════════════════════════════╝" << std::endl;
            std::cout << "| 1. Ime                                |" << std::endl;
            std::cout << "| 2. Prezime                            |" << std::endl;
            std::cout << "| 3. JMBG                               |" << std::endl;
            std::cout << "| 4. Sifra                              |" << std::endl;
            std::cout << "| 5. Pocetno stanje tekuceg racuna      |" << std::endl;
            std::cout << "| 6. Pocetno stanje stednog racuna      |" << std::endl;
            std::cout << "| 7. Zavrsi izmjenu                     |" << std::endl;
            std::cout << "╚══════════════════════════════════════╝" << std::endl;

            std::cout << "Unesite opciju: ";
            std::cin >> izbor;

            switch (izbor) {
                case 1:
                    std::cout << "| Trenutno ime: " << klijent->ime << std::endl;
                    std::cout << "| Unesite novo ime: " << std::flush;
                    std::cin >> klijent->ime;
                    break;
                case 2:
                    std::cout << "| Trenutno prezime: " << klijent->prezime << std::endl;
                    std::cout << "| Unesite novo prezime: " << std::flush;
                    std::cin >> klijent->prezime;
                    break;
                case 3:
                    std::cout << "| Trenutni JMBG: " << klijent->jmbg << std::endl;
                    std::cout << "| Unesite novi JMBG: " << std::flush;
                    std::cin >> klijent->jmbg;
                    break;
                case 4:
                    std::cout << "| Trenutna sifra: " << klijent->sifra << std::endl;
                    std::cout << "| Unesite novu sifru: " << std::flush;
                    std::cin >> klijent->sifra;
                    break;
                case 5:
                    std::cout << "| Stanje tekuceg racuna: " << klijent->racun.stanje << std::endl;
                    std::cout << "| Unesite novo stanje tekuceg racuna: " << std::flush;
                    std::cin >> klijent->racun.stanje;
                    break;
                case 6:
                    std::cout << "| Stanje stednog racuna: " << klijent->racun.stanje_stedni << std::endl;
                    std::cout << "| Unesite novo stanje stednog racuna: " << std::flush;
                    std::cin >> klijent->racun.stanje_stedni;
                    break;
                case 7:
                    std::cout << "| Zavrsena izmjena podataka za klijenta " << klijent->ime << std::endl;
                    break;
                default:
                    std::cout << "| Nepostojeca opcija. Molimo pokusajte ponovo." << std::endl;
                    break;
            }
            std::cout << "| Pritisnite enter taster za nastavak..." << std::endl;
            std::cin.ignore(); 
            std::cin.get(); 
        } while (izbor != 7);
    } else {
        std::cout << "| Klijent sa unesenim ID-om ne postoji." << std::endl;
    }
}


void SistemPrijave::promijeniSifru(Korisnik& korisnik) {
    system("clear");
    std::string staraSifra;
    std::cout << "| Unesite staru sifru: ";
    std::cin >> staraSifra;

    if (staraSifra == korisnik.sifra) {
        std::string novaSifra;
        std::cout << "| Unesite novu sifru: ";
        std::cin >> novaSifra;
        korisnik.sifra = novaSifra;

        std::cout << "| Sifra uspjesno promijenjena!" << std::endl;
    } else {
        std::cout << "| Pogresna stara sifra. Promjena sifre nije uspjela." << std::endl;
    }
}

Korisnik* SistemPrijave::pronadjiKorisnika(int korisnikId) {
    for (auto& korisnik : korisnici) {
        if (korisnik.id == korisnikId) {
            return &korisnik;
        }
    }
    return nullptr; 
}

