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

