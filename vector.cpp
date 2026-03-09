#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
};

double vid(const Studentas& s) {
    if (s.nd.empty()) return 0;
    double sum = 0;
    for (int x : s.nd) sum += x;
    return 0.4 * (sum / s.nd.size()) + 0.6 * s.egz;
}

double med(const Studentas& s) {
    if (s.nd.empty()) return 0;
    vector<int> temp = s.nd;
    sort(temp.begin(), temp.end());
    double m = (temp.size() % 2) ? temp[temp.size()/2] : (temp[temp.size()/2-1] + temp[temp.size()/2])/2.0;
    return 0.4 * m + 0.6 * s.egz;
}

int main() {
    srand(time(0));
    vector<Studentas> studentai;
    int budas;
    cout << "1 - vidurkis, 2 - mediana: "; cin >> budas;

    int pasirinkimas;
    do {
        cout << "\nMENIU:\n1 - ranka\n2 - generuoti tik pazymius\n3 - generuoti viska\n4 - baigti\n: ";
        cin >> pasirinkimas;

        if (pasirinkimas == 1 || pasirinkimas == 2 || pasirinkimas == 3) {
            Studentas s;

            if (pasirinkimas == 1 || pasirinkimas == 2) {
                cout << "Vardas: "; cin >> s.vardas;
                cout << "Pavarde: "; cin >> s.pavarde;
            } else {
                vector<string> vardai = {"Jonas","Petras","Antanas","Marius","Tomas","Lina","Rasa"};
                vector<string> pavardes = {"Jonaitis","Petraitis","Antanaitis","Mariunas","Tomauskas","Linauskiene","Rasute"};
                s.vardas = vardai[rand() % vardai.size()];
                s.pavarde = pavardes[rand() % pavardes.size()];
            }

            if (pasirinkimas == 2 || pasirinkimas == 3) {
                int kiek;
                cout << "Kiek ND generuoti? "; cin >> kiek;
                for (int i = 0; i < kiek; i++)
                    s.nd.push_back(rand() % 10 + 1);
                s.egz = rand() % 10 + 1;
            } else {
                cout << "ND pazymiai (-1 pabaiga):\n";
                int p;
                while (cin >> p && p != -1)
                    s.nd.push_back(p);
                cout << "Egzaminas: "; cin >> s.egz;
            }

            studentai.push_back(s);
        }
    } while (pasirinkimas != 4);

    cout << "\n| Pavardė        | Vardas         | Galutinis (Vid./Med.) |\n";
    cout << "|----------------|----------------|------------------------|\n";
    for (auto& s : studentai) {
        double rez = (budas == 1) ? vid(s) : med(s);
        cout << "| " << left << setw(14) << s.pavarde << " | "
             << left << setw(14) << s.vardas << " | "
             << fixed << setprecision(2) << setw(22) << rez << " |\n";
    }
    return 0;
}
