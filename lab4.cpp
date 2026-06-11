#include <iostream>
#include <string>

using namespace std;

class Osoba {
protected:
    int nr_indeksu;
    string imie;
    string nazwisko;

public:
    Osoba(int inx = 0, string im = "", string naz = "")
        : nr_indeksu(inx), imie(im), nazwisko(naz) {}

    virtual ~Osoba() {}

    void setIndeks(int nowy_indeks)        { nr_indeksu = nowy_indeks; }
    void setImie(string nowe_imie)         { imie = nowe_imie; }
    void setNazwisko(string nowe_nazwisko) { nazwisko = nowe_nazwisko; }

    int    getIndeks()   { return nr_indeksu; }
    string getImie()     { return imie; }
    string getNazwisko() { return nazwisko; }

    virtual void drukujInfo() {
        cout << "nr indeksu: " << nr_indeksu
             << "  imie: "     << imie
             << "  nazwisko: " << nazwisko;
    }

    virtual string typOsoby() {
        return "Osoba";
    }

    bool pusty() { return nazwisko.empty(); }
};

class Student : public Osoba {
protected:
    string kierunek;
    int rok_studiow;

public:
    Student(int inx = 0, string im = "", string naz = "",
            string kier = "", int rok = 0)
        : Osoba(inx, im, naz), kierunek(kier), rok_studiow(rok) {}

    void setKierunek(string k) { kierunek = k; }
    void setRok(int r)         { rok_studiow = r; }

    string getKierunek() { return kierunek; }
    int    getRok()      { return rok_studiow; }

    // nadpisujemy zeby wyswietlic tez kierunek i rok
    virtual void drukujInfo() override {
        Osoba::drukujInfo();
        cout << "  kierunek: " << kierunek
             << "  rok: "      << rok_studiow;
    }

    virtual string typOsoby() override {
        return "Student";
    }
};


class StudentZaoczny : public Student {
public:
    StudentZaoczny(int inx = 0, string im = "", string naz = "",
                   string kier = "", int rok = 0)
        : Student(inx, im, naz, kier, rok) {}

virtual void drukujInfo() override {
        Student::drukujInfo();
        cout << "  tryb: zaoczny";
    }

    virtual string typOsoby() override {
        return "StudentZaoczny";
    }
};


class ListaObecnosci {
private:
    static const int MAKS = 10;
    bool  tabObecnosc[MAKS];
    Osoba *tabOsob[MAKS];

    int znajdzPusteMiejsce() {
        for (int i = 0; i < MAKS; i++)
            if (tabOsob[i] == nullptr) return i;
        return -1;
    }

    int znajdzOsobe(string nazwisko) {
        for (int i = 0; i < MAKS; i++)
            if (tabOsob[i] && tabOsob[i]->getNazwisko() == nazwisko) return i;
        return -1;
    }

public:
    ListaObecnosci() {
        for (int i = 0; i < MAKS; i++) {
            tabOsob[i]     = nullptr;
            tabObecnosc[i] = false;
        }
    }

    void dodajOsobe(Osoba *nowa_osoba) {
        int i = znajdzPusteMiejsce();
        if (i != -1)
            tabOsob[i] = nowa_osoba;
        else
            cout << "lista jest pelna\n";
    }

    void drukujListe() {
        cout << "\nnr indeksu  typ              imie  nazwisko  obecnosc\n";
       

        for (int i = 0; i < MAKS; i++) {
            if (tabOsob[i] && !tabOsob[i]->pusty()) {
                cout << tabOsob[i]->getIndeks() << "  "
                     << "[" << tabOsob[i]->typOsoby() << "]  ";
                tabOsob[i]->drukujInfo();  // wywoluje odpowiednia wersje dzieki polimorfizmowi
                cout << "  " << (tabObecnosc[i] ? "TAK" : "NIE") << "\n";
            }
        }
    }

    void ustawObecnosc(string nazwisko, bool nowa_obecnosc) {
        int i = znajdzOsobe(nazwisko);
        if (i != -1) {
            tabObecnosc[i] = nowa_obecnosc;
            cout << "ustawiono obecnosc\n";
        } else {
            cout << "nie znaleziono osoby o podanym nazwisku\n";
        }
    }
};


class InterfejsUzytkownika {
private:
    static const int MAKS_OSOB = 20;
    static const int MAKS_LIST =  2;

    Osoba          *baza[MAKS_OSOB];
    ListaObecnosci  tablicaList[MAKS_LIST];
    int             ileOsob;

    int znajdzPuste() {
        for (int i = 0; i < MAKS_OSOB; i++)
            if (baza[i] == nullptr) return i;
        return -1;
    }

    int znajdzNazwisko(const string &nazwisko) {
        for (int i = 0; i < ileOsob; i++)
            if (baza[i] && baza[i]->getNazwisko() == nazwisko) return i;
        return -1;
    }

    void utworzOsobe() {
        cout << "typ osoby:\n"
             << "  1.osoba\n"
             << "  2.student\n"
             << "  3.student zaoczny\n"
             << "wybor: ";
        int typ; cin >> typ;

        int indeks;
        string imie, nazwisko;

        cout << "podaj indeks: ";   cin >> indeks;
        cout << "podaj imie: ";     cin >> imie;
        cout << "podaj nazwisko: "; cin >> nazwisko;

        Osoba *nowa = nullptr;

        if (typ == 1) {
            nowa = new Osoba(indeks, imie, nazwisko);
        } else if (typ == 2 || typ == 3) {
            string kierunek; int rok;
            cout << "podaj kierunek: ";    cin >> kierunek;
            cout << "podaj rok studiow: "; cin >> rok;

            if (typ == 2)
                nowa = new Student(indeks, imie, nazwisko, kierunek, rok);
            else
                nowa = new StudentZaoczny(indeks, imie, nazwisko, kierunek, rok);
        } else {
            cout << "nieznany typ\n";
            return;
        }

        int miejsce = znajdzPuste();
        if (miejsce != -1) {
            baza[miejsce] = nowa;
            ileOsob++;
            cout << "dodano\n";
        } else {
            cout << "brak miejsca w bazie\n";
            delete nowa;
        }
    }

    void dodajOsobe() {
        string nazwisko; int lista;
        cout << "kogo dodac (nazwisko): ";       cin >> nazwisko;
        cout << "do ktorej listy (0 lub 1): ";   cin >> lista;

        int i = znajdzNazwisko(nazwisko);
        if (i != -1 && lista >= 0 && lista < MAKS_LIST)
            tablicaList[lista].dodajOsobe(baza[i]);
        else
            cout << "niepoprawne dane lub brak osoby\n";
    }

    void ustawObecnosc() {
        string nazwisko; int lista; bool obecnosc;
        cout << "komu ustawic obecnosc (nazwisko): "; cin >> nazwisko;
        cout << "w ktorej liscie (0 lub 1): ";         cin >> lista;
        cout << "obecny? (1=tak / 0=nie): ";           cin >> obecnosc;

        if (lista >= 0 && lista < MAKS_LIST)
            tablicaList[lista].ustawObecnosc(nazwisko, obecnosc);
    }

    void usunOsobe() {
        string nazwisko;
        cout << "kogo usunac (nazwisko): "; cin >> nazwisko;
        int i = znajdzNazwisko(nazwisko);
        if (i != -1) {
            delete baza[i];
            baza[i] = nullptr;
            for (int j = i; j < ileOsob - 1; j++)
                baza[j] = baza[j + 1];
            baza[--ileOsob] = nullptr;
            cout << "usunieto\n";
        } else {
            cout << "nie znaleziono osoby\n";
        }
    }

    void edytujOsobe() {
        string nazwisko;
        cout << "kogo edytowac (nazwisko): "; cin >> nazwisko;
        int i = znajdzNazwisko(nazwisko);
        if (i == -1) { cout << "nie znaleziono\n"; return; }

        int nowy_indeks;
        string nowe_imie, nowe_nazwisko;
        cout << "nowy indeks: ";   cin >> nowy_indeks;
        cout << "nowe imie: ";     cin >> nowe_imie;
        cout << "nowe nazwisko: "; cin >> nowe_nazwisko;
        baza[i]->setIndeks(nowy_indeks);
        baza[i]->setImie(nowe_imie);
        baza[i]->setNazwisko(nowe_nazwisko);

        // jesli to student to pozwalamy tez zmienic kierunek i rok
        Student *s = dynamic_cast<Student*>(baza[i]);
        if (s) {
            string kier; int rok;
            cout << "nowy kierunek: "; cin >> kier;
            cout << "nowy rok: ";      cin >> rok;
            s->setKierunek(kier);
            s->setRok(rok);
        }

        cout << "git\n";
    }

    void wyswietlListe() {
        int lista;
        cout << "ktora liste wyswietlic (0 lub 1): "; cin >> lista;
        system("clear");
        if (lista >= 0 && lista < MAKS_LIST)
            tablicaList[lista].drukujListe();
        else
            cout << "niepoprawny numer listy\n";
    }

    void wyswietlBaze() {
        cout << "\nbaza\n";
        for (int i = 0; i < ileOsob; i++) {
            if (baza[i]) {
                cout << "[" << baza[i]->typOsoby() << "]  ";
                baza[i]->drukujInfo();
                cout << "\n";
            }
        }
    }

public:
    InterfejsUzytkownika() : ileOsob(0) {
        for (int i = 0; i < MAKS_OSOB; i++) baza[i] = nullptr;
    }

    ~InterfejsUzytkownika() {
        for (int i = 0; i < MAKS_OSOB; i++) delete baza[i];
    }

    void petla() {
        int wybor;
        while (true) {
            
            cout << "menu\n\n";
            cout << "1.utworz osobe / studenta\n";
            cout << "2.dodaj osobe do listy obecnosci\n";
            cout << "3.ustaw obecnosc osoby na liscie\n";
            cout << "4.usun osobe z bazy\n";
            cout << "5.edytuj dane osoby\n";
            cout << "6.wyswietl liste obecnosci\n";
            cout << "7.wyswietl baze osob\n\n";
            cout << "wybierz: ";
            cin >> wybor;
            system("clear");

            switch (wybor) {
                case 1: utworzOsobe();   break;
                case 2: dodajOsobe();    break;
                case 3: ustawObecnosc(); break;
                case 4: usunOsobe();     break;
                case 5: edytujOsobe();   break;
                case 6: wyswietlListe(); break;
                case 7: wyswietlBaze();  break;
                default: cout << "braktakiej opcji\n"; break;
            }
        }
    }
};


int main() {
    InterfejsUzytkownika ui;
    ui.petla();
    return 0;
}
