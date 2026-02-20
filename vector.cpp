#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd_rezultatai;
    int egzaminas;
};

double skaiciuotiVidurki(const vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0;
    double suma = 0;
    for (int paz : pazymiai) {
        suma += paz;
    }
    return suma / pazymiai.size();
}

double skaiciuotiMediana(vector<int> pazymiai) {
    if (pazymiai.empty()) return 0;

    sort(pazymiai.begin(), pazymiai.end());
    int kiekis = pazymiai.size();

    if (kiekis % 2 == 0) {
        return (pazymiai[kiekis/2 - 1] + pazymiai[kiekis/2]) / 2.0;
    } else {
        return pazymiai[kiekis/2];
    }
}

double skaiciuotiGalutini(double ndVid, int egzaminas) {
    return 0.4 * ndVid + 0.6 * egzaminas;
}

void generuotiAtsitiktinius(vector<int>& pazymiai, int& egzaminas) {
    int kiekis = rand() % 10 + 5;  // 5-15 namų darbų
    pazymiai.clear();
    for (int i = 0; i < kiekis; i++) {
        pazymiai.push_back(rand() % 10 + 1);  // 1-10
    }
    egzaminas = rand() % 10 + 1;
}

int main() {
    srand(time(0));

    vector<Studentas> studentai;
    int pasirinkimas;

    do {
        cout << "\n=== MENIU ===\n";
        cout << "1 - Įvesti ranka\n";
        cout << "2 - Generuoti tik pažymius\n";
        cout << "3 - Generuoti viską (vardus, pavardes, pažymius)\n";
        cout << "4 - Baigti darbą\n";
        cout << "Pasirinkite: ";
        cin >> pasirinkimas;

        if (pasirinkimas == 4) break;

        if (pasirinkimas >= 1 && pasirinkimas <= 3) {
            Studentas s;

            if (pasirinkimas == 3) {
                // Generuoti vardus ir pavardes
                string vardai[] = {"Jonas", "Petras", "Antanas", "Marius", "Tomas"};
                string pavardes[] = {"Jonaitis", "Petraitis", "Antanaitis", "Mariūnas", "Tomaitis"};
                s.vardas = vardai[rand() % 5];
                s.pavarde = pavardes[rand() % 5];
            } else {
                cout << "Įveskite vardą: ";
                cin >> s.vardas;
                cout << "Įveskite pavardę: ";
                cin >> s.pavarde;
            }

            if (pasirinkimas == 2 || pasirinkimas == 3) {
                generuotiAtsitiktinius(s.nd_rezultatai, s.egzaminas);
                cout << "Sugeneruoti " << s.nd_rezultatai.size() << " namų darbų pažymiai.\n";
            } else {
                s.nd_rezultatai.clear();
                char atsakymas;

                do {
                    cout << "Įveskite namų darbų pažymį (arba -1 jei baigėte): ";
                    int paz;
                    cin >> paz;

                    if (paz == -1) break;

                    if (paz >= 1 && paz <= 10) {
                        s.nd_rezultatai.push_back(paz);
                    } else {
                        cout << "Pažymys turi būti nuo 1 iki 10!\n";
                        continue;
                    }

                    cout << "Ar norite įvesti dar vieną pažymį? (t/n): ";
                    cin >> atsakymas;
                } while (atsakymas == 't' || atsakymas == 'T');

                cout << "Įveskite egzamino pažymį: ";
                cin >> s.egzaminas;
            }

            studentai.push_back(s);
            cout << "Studentas pridėtas!\n";
        }
    } while (pasirinkimas != 4);

    if (!studentai.empty()) {
        int skaiciavimoBudas;
        cout << "\nPasirinkite galutinio balo skaičiavimo būdą:\n";
        cout << "1 - Vidurkis\n";
        cout << "2 - Mediana\n";
        cout << "Pasirinkimas: ";
        cin >> skaiciavimoBudas;

        cout << "\n" << setw(15) << left << "Pavardė"
             << setw(15) << "Vardas"
             << setw(20) << (skaiciavimoBudas == 1 ? "Galutinis (Vid.)" : "Galutinis (Med.)") << "\n";
        cout << string(50, '-') << "\n";

        for (const auto& s : studentai) {
            double ndRezultatas;
            if (skaiciavimoBudas == 1) {
                ndRezultatas = skaiciuotiVidurki(s.nd_rezultatai);
            } else {
                ndRezultatas = skaiciuotiMediana(s.nd_rezultatai);
            }

            double galutinis = skaiciuotiGalutini(ndRezultatas, s.egzaminas);

            cout << setw(15) << left << s.pavarde
                 << setw(15) << s.vardas
                 << setw(20) << fixed << setprecision(2) << galutinis << "\n";
        }
    }

    return 0;
}
