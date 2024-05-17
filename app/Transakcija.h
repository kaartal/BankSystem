#ifndef TRANSAKCIJA_H
#define TRANSAKCIJA_H

struct Transakcija {
    int posiljateljID;
    int primateljID;
    double iznos;

    Transakcija(int posiljateljID, int primateljID, double iznos);
};

#endif
