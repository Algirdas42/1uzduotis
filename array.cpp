#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAX_ND = 100;
const int MAX_STUD = 100;

struct Studentas {
    string vardas;
    string pavarde;
    int nd[MAX_ND];
    int ndKiekis;
    int egz;
};

double vidurkis(const Studentas& s) {
    if (s.ndKiekis == 0) return 0;
    double sum = 0;
    for (int i = 0; i < s.ndKiekis; i++) sum += s.nd[i];
    return 0.4 * (sum / s.ndKiekis) + 0.6 * s.egz;
}

double mediana(const Studentas& s) {
    if (s.ndKiekis == 0) return 0;
    int temp[MAX_ND];
    for (int i = 0; i < s.ndKiekis; i++) temp[i] = s.nd[i];
    sort(temp, temp + s.ndKiekis);
    double med;
    if (s.ndKiekis % 2 == 0)
        med = (temp[s.ndKiekis/2 - 1] + temp[s.ndKiekis/2]) / 2.0;
    else
        med = temp[s.ndKiekis/2];
    return 0.4 * med + 0.6 * s.egz;
}

int main() {
    Studentas studentai[MAX_STUD];
    int n = 0; // kiek studentų
    int budas;
    cout << "1 - vidurkis, 2 - mediana: "; cin >> budas;

    int pasirinkimas;
    do {
        cout << "\nMENIU:\n1 - ranka\n2 - generuoti tik pazymius\n3 - generuoti viska\n4 - baigti\n: ";
        cin >> pasirinkimas;

        if (pasirinkimas == 1 || pasirinkimas == 2 || pasirinkimas == 3) {
            if (n >= MAX_STUD) { cout << "Per daug studentu\n"; continue; }
            Studentas s;
            s.ndKiekis = 0;

            if (pasirinkimas == 1 || pasirinkimas == 2) {
                cout << "Vardas: "; cin >> s.vardas;
                cout << "Pavarde: "; cin >> s.pavarde;
            } else {
                // generuoti varda/pavarde
                string vardai[] = {"Jonas","Petras","Antanas","Marius","Tomas","Lina","Rasa"};
                string pavardes[] = {"Jonaitis","Petraitis","Antanaitis","Marius","Tomas","Linauskiene","Rasute"};
                s.vardas = vardai[rand() % 7];
                s.pavarde = pavardes[rand() % 7];
            }

            if (pasirinkimas == 2 || pasirinkimas == 3) {
                // generuoti pazymius
                int kiek;
                cout << "Kiek ND generuoti? "; cin >> kiek;
                for (int i = 0; i < kiek && i < MAX_ND; i++) {
                    s.nd[i] = rand() % 10 + 1;
                    s.ndKiekis++;
                }
                s.egz = rand() % 10 + 1;
            } else {
                // ranka
                cout << "ND pazymiai (-1 pabaiga):\n";
                int p;
                while (cin >> p && p != -1 && s.ndKiekis < MAX_ND) {
                    s.nd[s.ndKiekis++] = p;
                }
                cout << "Egzaminas: "; cin >> s.egz;
            }

            studentai[n++] = s;
        }
    } while (pasirinkimas != 4);

    // isvedimas
    cout << "\n| Pavardė        | Vardas         | Galutinis (Vid./Med.) |\n";
    cout << "|----------------|----------------|------------------------|\n";
    for (int i = 0; i < n; i++) {
        double rez = (budas == 1) ? vidurkis(studentai[i]) : mediana(studentai[i]);
        cout << "| " << left << setw(14) << studentai[i].pavarde << " | "
             << left << setw(14) << studentai[i].vardas << " | "
             << fixed << setprecision(2) << setw(22) << rez << " |\n";
    }
    return 0;
}
