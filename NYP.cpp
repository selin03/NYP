#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // remove_if
#include <cstdlib>   // rand, srand
#include <ctime>     // time

using namespace std;

// Temel Karakter Sinifi
class Karakter {
protected:
    string isim;
    int can;

public:
    Karakter(string isim, int can) : isim(isim), can(can) {}

    virtual void saldir(Karakter& hedef) = 0; // Soyut metot

    int getCan() const {
        return max(can, 0);
    }

    string getIsim() const {
        return isim;
    }

    void azaltCan(int miktar) {
        can -= miktar;
    }

    virtual ~Karakter() = default;
};

// Oyuncu Sinifi (Kalitim)
class Oyuncu : public Karakter {
private:
    bool healKullanildi;

public:
    Oyuncu(string isim, int can)
        : Karakter(isim, can), healKullanildi(false) {
    }

    void saldir(Karakter& hedef) override {
        int hasar = rand() % 7 + 12; // 12 ile 18 arasinda random hasar
        // Kritik vurma kontrolü
        if (rand() % 100 < 5) { // %5 ihtimalle kritik vurma
            hasar = static_cast<int>(hasar * 1.8); // Kritik vuruş: hasar * 1.8
            cout << isim << ", KRITIK VURUS! ";
        }
        hedef.azaltCan(hasar);
        cout << isim << ", " << hedef.getIsim() << "'e " << hasar << " hasar verdi!" << endl;
        if (hedef.getCan() <= 0) {
            cout << hedef.getIsim() << " yenildi!" << endl;
        }
    }

    void ozelSaldiri(Karakter& hedef) {
        int hasar = rand() % 9 + 22; // 22 ile 30 arasinda random hasar
        // Kritik vurma kontrolü
        if (rand() % 100 < 5) { // %5 ihtimalle kritik vurma
            hasar = static_cast<int>(hasar * 1.8); // Kritik vuruş: hasar * 1.8
            cout << isim << ", KRITIK VURUS! ";
        }
        cout << isim << ", ozel saldirisini kullandi!" << endl;
        hedef.azaltCan(hasar);
        cout << hedef.getIsim() << " " << hasar << " hasar aldi!" << endl;
    }

    void heal() {
        if (!healKullanildi) {
            can += 20;
            healKullanildi = true;
            cout << isim << "'in cani 20 puan arttirildi! Yeni can: " << can << endl;
        }
        else {
            cout << "Heal ozelligini zaten kullandiniz!" << endl;
        }
    }
};

// Ork Sinifi (Dusman Kalitim)
class Ork : public Karakter {
public:
    Ork(string isim, int can) : Karakter(isim, can) {}

    void saldir(Karakter& hedef) override {
        int hasar = rand() % 7 + 7; // 7 ile 13 arasinda random hasar
        // Kritik vurma kontrolü
        if (rand() % 100 < 5) { // %5 ihtimalle kritik vurma
            hasar = static_cast<int>(hasar * 1.8); // Kritik vuruş: hasar * 1.8
            cout << isim << ", KRITIK VURUS! ";
        }
        hedef.azaltCan(hasar);
        cout << isim << ", " << hedef.getIsim() << "'e " << hasar << " hasar verdi!" << endl;
        if (hedef.getCan() <= 0) {
            cout << hedef.getIsim() << " yenildi!" << endl;
        }
    }
};

// Goblin Sinifi (Dusman Kalitim)
class Goblin : public Karakter {
public:
    Goblin(string isim, int can) : Karakter(isim, can) {}

    void saldir(Karakter& hedef) override {
        int hasar = rand() % 5 + 6; // 6 ile 10 arasinda random hasar
        // Kritik vurma kontrolü
        if (rand() % 100 < 5) { // %5 ihtimalle kritik vurma
            hasar = static_cast<int>(hasar * 1.8); // Kritik vuruş: hasar * 1.8
            cout << isim << ", KRITIK VURUS! ";
        }
        hedef.azaltCan(hasar);
        cout << isim << ", " << hedef.getIsim() << "'e " << hasar << " hasar verdi!" << endl;
        if (hedef.getCan() <= 0) {
            cout << hedef.getIsim() << " yenildi!" << endl;
        }
    }
};

// Oyun Sinifi
class Oyun {
private:
    Oyuncu oyuncu;
    vector<Karakter*> dusmanlar;

public:
    Oyun()
        : oyuncu("Kahraman", 100) {
        dusmanlar.push_back(new Ork("Ork", 70));
        dusmanlar.push_back(new Goblin("Goblin", 40));
    }

    ~Oyun() {
        for (auto dusman : dusmanlar) {
            delete dusman;
        }
    }

    void baslat() {
        cout << "Oyun Basladi!" << endl;
        while (oyuncu.getCan() > 0 && !dusmanlar.empty()) {
            cout << "\n--- Yeni Tur ---" << endl;
            cout << "Senin Canin: " << oyuncu.getCan() << endl;

            for (size_t i = 0; i < dusmanlar.size(); ++i) {
                cout << "Dusman " << i + 1 << ": " << dusmanlar[i]->getIsim()
                    << ", Can: " << dusmanlar[i]->getCan() << endl;
            }

            int secim, hedefIndex;
            cout << "Secim Yap: Saldir (1), Ozel Saldiri (2), Heal (3): ";
            cin >> secim;

            if (secim == 3) {
                oyuncu.heal();
                continue;
            }

            cout << "Hangi dusmana saldiracaksin? (1-" << dusmanlar.size() << "): ";
            cin >> hedefIndex;

            if (hedefIndex < 1 || hedefIndex > static_cast<int>(dusmanlar.size())) {
                cout << "Gecersiz hedef!" << endl;
                continue;
            }

            Karakter* hedef = dusmanlar[hedefIndex - 1];

            if (secim == 1) {
                oyuncu.saldir(*hedef);
            }
            else if (secim == 2) {
                oyuncu.ozelSaldiri(*hedef);
            }
            else {
                cout << "Gecersiz secim!" << endl;
                continue;
            }

            // Dusmanlar saldirir
            for (auto dusman : dusmanlar) {
                if (dusman->getCan() > 0) {
                    dusman->saldir(oyuncu);
                }
            }

            // Olen dusmanlari kaldir
            dusmanlar.erase(
                remove_if(dusmanlar.begin(), dusmanlar.end(), [](Karakter* d) {
                    if (d->getCan() <= 0) {
                        delete d;
                        return true;
                    }
                    return false;
                    }),
                dusmanlar.end()
            );

            if (oyuncu.getCan() <= 0) {
                cout << "Kaybettiniz!" << endl;
                return;
            }
        }

        cout << "Tebrikler! Tum dusmanlari yendiniz!" << endl;
    }
};

// Ana Fonksiyon
int main() {
    srand(static_cast<unsigned>(time(0))); // Random hasarlar icin seed
    Oyun oyun;
    oyun.baslat();
    return 0;
}