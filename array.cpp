#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    int nd_rezultatai[100];  // Maksimalus namų darbų skaičius
    int nd_kiekis;
    int egzaminas;
};

double skaiciuotiVidurki(int pazymiai[], int kiekis) {
    if (kiekis == 0) return 0;
    double suma = 0;
    for (int i = 0; i < kiekis; i++) {
        suma += pazymiai[i];
    }
    return suma / kiekis;
}

double skaiciuotiMediana(int pazymiai[], int kiekis) {
    if (kiekis == 0) return 0;
    
    // Surušiuoti pažymius (burbuliuko metodas)
    for (int i = 0; i < kiekis - 1; i++) {
        for (int j = 0; j < kiekis - i - 1; j++) {
            if (pazymiai[j] > pazymiai[j + 1]) {
                int temp = pazymiai[j];
                pazymiai[j] = pazymiai[j + 1];
                pazymiai[j + 1] = temp;
            }
        }
    }
    
    if (kiekis % 2 == 0) {
        return (pazymiai[kiekis/2 - 1] + pazymiai[kiekis/2]) / 2.0;
    } else {
        return pazymiai[kiekis/2];
    }
}

double skaiciuotiGalutini(double ndVid, int egzaminas) {
    return 0.4 * ndVid + 0.6 * egzaminas;
}

void generuotiAtsitiktinius(int pazymiai[], int& kiekis, int& egzaminas) {
    kiekis = rand() % 10 + 5;  // 5-15 namų darbų
    for (int i = 0; i < kiekis; i++) {
        pazymiai[i] = rand() % 10 + 1;  // 1-10
    }
    egzaminas = rand() % 10 + 1;
}

int main() {
    srand(time(0));
    
    Studentas studentai[100];  // Maksimalus studentų skaičius
    int studentuKiekis = 0;
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
                generuotiAtsitiktinius(s.nd_rezultatai, s.nd_kiekis, s.egzaminas);
                cout << "Sugeneruoti " << s.nd_kiekis << " namų darbų pažymiai.\n";
            } else {
                s.nd_kiekis = 0;
                char atsakymas;
                
                do {
                    cout << "Įveskite namų darbų pažymį (arba -1 jei baigėte): ";
                    int paz;
                    cin >> paz;
                    
                    if (paz == -1) break;
                    
                    if (paz >= 1 && paz <= 10) {
                        s.nd_rezultatai[s.nd_kiekis] = paz;
                        s.nd_kiekis++;
                    } else {
                        cout << "Pažymys turi būti nuo 1 iki 10!\n";
                    }
                    
                    cout << "Ar norite įvesti dar vieną pažymį? (t/n): ";
                    cin >> atsakymas;
                } while (atsakymas == 't' || atsakymas == 'T');
                
                cout << "Įveskite egzamino pažymį: ";
                cin >> s.egzaminas;
            }
            
            studentai[studentuKiekis] = s;
            studentuKiekis++;
            
            cout << "Studentas pridėtas!\n";
        }
    } while (pasirinkimas != 4);
    
    if (studentuKiekis > 0) {
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
        
        for (int i = 0; i < studentuKiekis; i++) {
            double ndRezultatas;
            if (skaiciavimoBudas == 1) {
                ndRezultatas = skaiciuotiVidurki(studentai[i].nd_rezultatai, studentai[i].nd_kiekis);
            } else {
                ndRezultatas = skaiciuotiMediana(studentai[i].nd_rezultatai, studentai[i].nd_kiekis);
            }
            
            double galutinis = skaiciuotiGalutini(ndRezultatas, studentai[i].egzaminas);
            
            cout << setw(15) << left << studentai[i].pavarde
                 << setw(15) << studentai[i].vardas
                 << setw(20) << fixed << setprecision(2) << galutinis << "\n";
        }
    }
    
    return 0;
}