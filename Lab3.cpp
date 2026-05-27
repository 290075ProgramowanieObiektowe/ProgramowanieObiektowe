#include <iostream>
#include <string>

using namespace std;



class Osoba {
private:
    int nr_indeksu;
    string imie;
    string nazwisko;

public:
    Osoba(int inx = 0, string im = "", string naz = "") 
        : nr_indeksu(inx), imie(im), nazwisko(naz) {}


    void setIndeks(int nowy_indeks) { 
        nr_indeksu = nowy_indeks; 
    }

    void setImie(string nowe_imie) { 
        imie = nowe_imie; 
    }

    void setNazwisko(string nowe_nazwisko) { 
        nazwisko = nowe_nazwisko; 
    }


    int getIndeks() { 
        return nr_indeksu; 
    }

    string getImie() { 
        return imie; 
    }

    string getNazwisko() { 
        return nazwisko; 
    }
};



class ListaObecnosci {
private:
    bool tabObecnosc[10] = {false};
    Osoba tabOsob[10];


    int znajdzPusteMiejsce() {
        for (int i = 0; i < 10; i++) {
            if (tabOsob[i].getNazwisko() == "") {
                return i;
            }
        }
        return -1;
    }


    int znajdzOsobe(string nazwisko) {
        for (int i = 0; i < 10; i++) {
            if (tabOsob[i].getNazwisko() == nazwisko) {
                return i;
            }
        }
        return -1;
    }


public:
    void dodajOsobe(Osoba nowa_osoba) {
        int i = znajdzPusteMiejsce();
        
        if (i != -1) {
            tabOsob[i] = nowa_osoba;
        }
    }


    void drukujListe() {
        cout << endl << "Nr INDEKSU    IMIE    NAZWISKO   OBECNOSC" << endl;
        cout << "-------------------------------------------------" << endl;
        
        for (int i = 0; i < 10; i++) {
            if (tabOsob[i].getNazwisko() != "") {
                cout << tabOsob[i].getIndeks() << "    " 
                     << tabOsob[i].getImie() << "    " 
                     << tabOsob[i].getNazwisko() << "    " 
                     << (tabObecnosc[i] ? "TAK" : "NIE") << endl;
            }
        }
    }


    void ustawObecnosc(string nazwisko, bool nowa_obecnosc) {
        int i = znajdzOsobe(nazwisko);
        
        if (i != -1) {
            tabObecnosc[i] = nowa_obecnosc;
            cout << "ustawiam obecnosc \n";
        } else {
            cout << "Nie znaleziono osoby o podanym nazwisku.\n";
        }
    }
};




class InterfejsUzytkownika {
private:
    Osoba *tablicaOsob;
    ListaObecnosci *tablicaList;
    int ileOsob;
    int ileList;
    int wybor;


    int znajdzPuste() {
        for (int i = 0; i < ileOsob; i++) {
            if (tablicaOsob[i].getNazwisko().empty()) {
                return i;
            }
        }
        return -1;
    }


    int znajdzNazwisko(string nazwisko) {
        for (int i = 0; i < ileOsob; i++) {
            if (tablicaOsob[i].getNazwisko() == nazwisko) {
                return i;
            }
        }
        return -1;
    }


    void utworzOsobe() {
        int indeks;
        string imie;
        string nazwisko;
        Osoba nowa_osoba;

        cout << "Podaj indeks: ";
        cin >> indeks;
        nowa_osoba.setIndeks(indeks);

        cout << "Podaj imie: ";
        cin >> imie;
        nowa_osoba.setImie(imie);

        cout << "Podaj nazwisko: ";
        cin >> nazwisko;
        nowa_osoba.setNazwisko(nazwisko);

        int i = znajdzPuste();
        if (i != -1) {
            tablicaOsob[i] = nowa_osoba;
        } else {
            cout << "Brak miejsca w bazie osób!\n";
        }
    }


    void dodajOsobe() {
        string nazwisko;
        int lista;

        cout << "Kogo chcesz dodac (podaj nazwisko): ";
        cin >> nazwisko;

        cout << "Do ktorej listy (0 lub 1): ";
        cin >> lista;

        int i = znajdzNazwisko(nazwisko);
        
        if (i != -1 && lista >= 0 && lista < ileList) {
            tablicaList[lista].dodajOsobe(tablicaOsob[i]);
        } else {
            cout << "Niepoprawne dane lub brak osoby.\n";
        }
    }


    void ustawObecnosc() {
        string nazwisko;
        int lista;
        bool obecnosc;

        cout << "Komu chcesz ustawic obecnosc (podaj nazwisko): ";
        cin >> nazwisko;

        cout << "W ktorej liscie: ";
        cin >> lista;

        cout << "Ustaw obecnosc (1 - obecny, 0 - nieobecny): ";
        cin >> obecnosc;

        if (lista >= 0 && lista < ileList) {
            tablicaList[lista].ustawObecnosc(nazwisko, obecnosc);
        }
    }


    void przesun(int index) {
        for (int i = index; i < ileOsob - 1; i++) {
            tablicaOsob[i].setIndeks(tablicaOsob[i + 1].getIndeks());
            tablicaOsob[i].setNazwisko(tablicaOsob[i + 1].getNazwisko());
            tablicaOsob[i].setImie(tablicaOsob[i + 1].getImie());
        }
        
        tablicaOsob[ileOsob - 1].setIndeks(0);
        tablicaOsob[ileOsob - 1].setNazwisko("");
        tablicaOsob[ileOsob - 1].setImie("");
    }


    void usunOsobe() {
        string nazwisko;

        cout << "Kogo chcesz usunac (podaj nazwisko): ";
        cin >> nazwisko;

        int i = znajdzNazwisko(nazwisko);
        if (i != -1) {
            przesun(i);
        } else {
            cout << "Nie znaleziono osoby.\n";
        }
    }


    void edytujOsobe() {
        string nazwisko;
        int nowy_indeks;
        string nowe_nazwisko;
        string nowe_imie;

        cout << "Kogo chcesz edytowac (podaj nazwisko): ";
        cin >> nazwisko;
        
        int i = znajdzNazwisko(nazwisko);

        if (i != -1) {
            cout << "Podaj nowy indeks: ";
            cin >> nowy_indeks;
            tablicaOsob[i].setIndeks(nowy_indeks);

            cout << "Podaj nowe imie: ";
            cin >> nowe_imie;
            tablicaOsob[i].setImie(nowe_imie);

            cout << "Podaj nowe nazwisko: ";
            cin >> nowe_nazwisko;
            tablicaOsob[i].setNazwisko(nowe_nazwisko);
        } else {
            cout << "Nie znaleziono osoby.\n";
        }
    }


    void wyswietlListe() {
        int lista;
        cout << "Ktora liste chcesz wyswietlic: ";
        cin >> lista;

        system("clear");

        if (lista >= 0 && lista < ileList) {
            tablicaList[lista].drukujListe();
        } else {
            cout << "Niepoprawny numer listy.\n";
        }
    }


public:
    InterfejsUzytkownika(Osoba *tbos, int os, ListaObecnosci *tbls, int ls) 
        : tablicaOsob(tbos), ileOsob(os), tablicaList(tbls), ileList(ls) {}


    void petla() {
        while (true) {
            cout << "\n=============================\n";
            cout << "========== M E N U ==========\n\n";

            cout << "1. Utworz osobe\n";
            cout << "2. Dodaj osobe do listy\n";
            cout << "3. Ustaw obecnosc osoby na liscie\n";
            cout << "4. Usun osobe z bazy\n";
            cout << "5. Zmien dane osoby\n";
            cout << "6. Wyswietl liste\n\n";

            cout << "Wybierz: ";
            cin >> wybor;

            system("clear");

            switch (wybor) {
                case 1:
                    utworzOsobe();
                    break;
                case 2:
                    dodajOsobe();
                    break;
                case 3:
                    ustawObecnosc();
                    break;
                case 4:
                    usunOsobe();
                    break;
                case 5:
                    edytujOsobe();
                    break;
                case 6:
                    wyswietlListe();
                    break;
                default:
                    cout << endl << "Brak takiej opcji." << endl;
                    break;
            }
        }
    }
};



int main() {
    Osoba tablicaOsob[10];
    ListaObecnosci tablicaList[2];
    
    InterfejsUzytkownika ui(tablicaOsob, 10, tablicaList, 2);
    ui.petla();

    return 0;
}
