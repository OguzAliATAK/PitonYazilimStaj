#include <string>
#include <vector>
#include <fstream>
#include<locale>
#include <iostream>

using namespace std;

int MAX = 9999999999;

class Hesapbilgi
{
private:
    static int Hesap_numarasi;

    bool open = true;
    int Hesap_numarasi2 = ++Hesap_numarasi;
    double Bakiye = 0;
    string isim, soyisim;

public:
    Hesapbilgi() {}
    Hesapbilgi(string, string, int);

    void yatirilacak_para(double);
    void cekilecek_para(double);
    void transfer(Hesapbilgi, double);

    static void setHesap_numarasi(int No) {
        if (No > 0)
            Hesap_numarasi = No;
    }

    int getHesapnumara();
    double getBakiye();

    string getisim();
    string getsoyisim();

    void setBakiye(double);

    void setisim(string);
    void setsoyisim(string);

    void close();
    bool isOpen();

    friend istream& operator >> (istream& in, Hesapbilgi& acc);
    friend ostream& operator << (ostream& out, Hesapbilgi& acc);

    friend ifstream& operator >> (ifstream& in, Hesapbilgi& acc);
    friend ofstream& operator << (ofstream& out, Hesapbilgi& acc);
};
//***********************//

int Hesapbilgi::Hesap_numarasi = 0;

Hesapbilgi::Hesapbilgi(string isim, string soyisim, int initial_balance)
{
    setisim(isim);
    setsoyisim(soyisim);
    Bakiye = initial_balance;
}

void Hesapbilgi::yatirilacak_para(double value) { Bakiye += value; }
void Hesapbilgi::cekilecek_para(double value) { Bakiye -= value; }
void Hesapbilgi::transfer(Hesapbilgi gonderlien_hesap, double gonderlin_para) { Bakiye -= gonderlin_para; gonderlien_hesap.Bakiye += gonderlin_para; }

int Hesapbilgi::getHesapnumara() { return Hesap_numarasi2; }
double Hesapbilgi::getBakiye() { return Bakiye; }

string Hesapbilgi::getisim() { return isim; }
string Hesapbilgi::getsoyisim() { return soyisim; }

void Hesapbilgi::setBakiye(double Bakiye) { if (Bakiye >= 0) this->Bakiye = Bakiye; }

void Hesapbilgi::setisim(string isim) { if (isim != "") this->isim = isim; }
void Hesapbilgi::setsoyisim(string soyisim) { if (soyisim != "") this->soyisim = soyisim; }

void Hesapbilgi::close() { open = false; }
bool Hesapbilgi::isOpen() { return open; }

istream& operator >> (istream& in, Hesapbilgi& hesap1) {
    string isim, soyisim;

    double Bakiye;

    cout << "İsminizi giriniz : "; cin >> isim;
    cout << "Soyisminizi giriniz: "; cin >> soyisim;

    cout << "Hesabınızdaki parayı giriniz: "; cin >> Bakiye;

    hesap1.setisim(isim);
    hesap1.setsoyisim(soyisim);

    hesap1.setBakiye(Bakiye);

    return in;
}

ostream& operator << (ostream& out, Hesapbilgi& hesap1) {
    out << "İsim : " << hesap1.getisim() << endl;
    out << "Soyade: " << hesap1.getsoyisim() << endl;

    out << "Bakiye : " << hesap1.getBakiye() << endl;
    out << "Hesap No: " << hesap1.getHesapnumara() << endl;
    out << "Durum: " << (hesap1.isOpen() ? "Aktif" : "KApalı") << endl;

    return out;
}

ifstream& operator >> (ifstream& in, Hesapbilgi& hesap1) {
    string isim, soyisim;

    int Hesap_numarasi2; bool open;
    double Bakiye;

    in >> isim >> soyisim;

    in >> Bakiye >> Hesap_numarasi2;
    in >> open;

    hesap1.setisim(isim);
    hesap1.setsoyisim(soyisim);

    hesap1.setBakiye(Bakiye);
    hesap1.open = open;
    hesap1.Hesap_numarasi2 = Hesap_numarasi2;

    return in;
}

ofstream& operator << (ofstream& out, Hesapbilgi& Hesap1) {
    out << Hesap1.getisim() << endl;
    out << Hesap1.getsoyisim() << endl;
    out << Hesap1.getBakiye() << endl;
    out << Hesap1.getHesapnumara() << endl;
    out << Hesap1.isOpen();

    return out;
}

bool isEmpty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

bool Valid(unsigned int Hesap_numarasi2, vector<Hesapbilgi> hesaplar) {
    if (Hesap_numarasi2 <= hesaplar.size() && Hesap_numarasi2 > 0 && hesaplar[Hesap_numarasi2].isOpen())
        return true;
    return false;
}

int main()
{
    setlocale(LC_ALL, "Turkish");
    vector<Hesapbilgi> Hesaplar;

    ofstream otrans("Islemdosyasi.txt", ios::app);

    ofstream ofs("Kullanicilar.txt", ios::app);
    ifstream ifs("Kullanicilar.txt");

    vector<int> Hesapnumara;
    vector<string> types;
    vector<double> values;

    while (!ifs.eof() && !isEmpty(ifs)) {
        Hesapbilgi hesap1;
        ifs >> hesap1;

        Hesaplar.push_back(hesap1);
    }

    Hesapbilgi::setHesap_numarasi(Hesaplar.size());

    while (1) {


        cout << endl;

        cout << "   1. Banka Hesabı aç" << endl;
        cout << "   2. Banka hesabını kapat" << endl;
        cout << "   3. Sistemdeki hesapları göster" << endl;
        cout << "   4. Hesaba para yatır" << endl;
        cout << "   5. HEsaptan para çek" << endl;
        cout << "   6. Başka bir hesaba para aktar" << endl;
        cout << "   7. Bakiyeyi göster" << endl;
        cout << "   8.Çıkış" << endl;
        cout << endl;

        string tercih;
        cout << "İşleminizi seçiniz: "; cin >> tercih;

        if (tercih == "1") {
            Hesapbilgi hesap1;
            cin >> hesap1;

            if (Hesaplar.size() != 0)
                ofs << endl;

            Hesaplar.push_back(hesap1);
            ofs << hesap1;

            cout << "Hesap oluşturuldu" << endl;
            cout << "Hesap numaranız " << hesap1.getHesapnumara() << endl;
        }

        else if (tercih == "2") {
            int Hesap_numarasi2;
            cout << "Hesap numaranızı giriniz "; cin >> Hesap_numarasi2;

            Hesap_numarasi2--;

            if (Valid(Hesap_numarasi2, Hesaplar)) {
                cout << "Hesap silindi!" << endl;
                Hesaplar[Hesap_numarasi2].close();
            }
            else
                cout << "Böyle bir kullanıcı yok" << endl;
        }

        else if (tercih == "3") {
            cout << endl;

            for (unsigned int i = 0; i < Hesaplar.size(); i++)
                cout << Hesaplar[i] << endl;
        }

        else if (tercih == "4") {
            int Hesap_numarasi2;
            double value;
            cout << "Hesap numaranızı giriniz: "; cin >> Hesap_numarasi2;
            cout << "Yatıracağınız miktarı seçiniz "; cin >> value;

            Hesap_numarasi2--;

            if (Valid(Hesap_numarasi2, Hesaplar)) {
                if (value < MAX) {
                    cout << value << " Para yatırılan hesap : " << Hesaplar[Hesap_numarasi2].getisim() << endl;

                    Hesaplar[Hesap_numarasi2].yatirilacak_para(value);
                    cout << "Bakiye : " << Hesaplar[Hesap_numarasi2].getBakiye() << endl;

                    Hesapnumara.push_back(Hesap_numarasi2);
                    types.push_back("Yatır");
                    values.push_back(value);
                }
                else
                    cout << "*!" << endl;
            }
            else
                cout << "Hata ! " << endl;
        }

        else if (tercih == "5") {
            int Hesap_numarasi2;
            double value;
            cout << "Hesap numarasını giriniz : "; cin >> Hesap_numarasi2;
            cout << "Çekeceğiniz miktarı giriniz : "; cin >> value;

            Hesap_numarasi2--;

            if (Valid(Hesap_numarasi2, Hesaplar)) {
                if (Hesaplar[Hesap_numarasi2].getBakiye() - value >= 0) {
                    cout << value << " TL  " << Hesaplar[Hesap_numarasi2].getisim() << "hesabından çekildi" << endl;

                    Hesaplar[Hesap_numarasi2].cekilecek_para(value);
                    cout << "Bakiye" << Hesaplar[Hesap_numarasi2].getBakiye() << endl;

                    Hesapnumara.push_back(Hesap_numarasi2);
                    types.push_back("Withdrawal");
                    values.push_back(value);
                }
                else
                    cout << "Yeterli bakiye yok" << endl;
            }
            else
                cout << "Hata" << endl;
        }

        else if (tercih == "6") {
            int Hesap_numarasi2, Alici_hesap;
            double gonderliecek_para_miktari;
            cout << "Hesap numarasını giriniz: "; cin >> Hesap_numarasi2;
            cout << "Para göndermek istedğiniz hesap numarasını giriniz: "; cin >> Alici_hesap;
            cout << "Göndermek istediğiniz ücreti giriniz : "; cin >> gonderliecek_para_miktari;

            //Hesap_numarasi2--;

            if (Valid(Hesap_numarasi2, Hesaplar) && Valid(Alici_hesap, Hesaplar))
            {

                if (Hesaplar[Alici_hesap].getBakiye() + gonderliecek_para_miktari > MAX)
                    cout << "*****" << endl;
                else
                {
                    if (Hesaplar[Hesap_numarasi2].getBakiye() - gonderliecek_para_miktari >= 0) {
                        cout << Hesaplar[Alici_hesap].getisim() << " * " << gonderliecek_para_miktari << endl;
                        cout << "*";
                        Hesaplar[Hesap_numarasi2].transfer(Hesaplar[Alici_hesap], gonderliecek_para_miktari);
                        cout << Hesaplar[Hesap_numarasi2].getisim() << "Bakiye : " << Hesaplar[Hesap_numarasi2].getBakiye() << endl;
                        cout << Hesaplar[Alici_hesap].getisim() << "Bakiye : " << Hesaplar[Hesap_numarasi2].getBakiye() << endl;
                    }

                    else
                        cout << "Bakiye yeterli değil" << endl;
                }
            }

            else
                cout << "Hata!" << endl;
        }

        else if (tercih == "7") {
            int Hesap_numarasi2;
            cout << "Hesap numarasını giriniz: "; cin >> Hesap_numarasi2;

            Hesap_numarasi2--;

            cout << endl;

            if (Valid(Hesap_numarasi2, Hesaplar))
                cout << Hesaplar[Hesap_numarasi2];
            else
                cout << "Hata!" << endl;
        }
        else if (tercih == "8") {
            break;
        }

        else {
            cout << "Geçerli bir işlem seçiniz" << endl;
        }

        cout << endl;

        system("pause");
        system("cls");
    }

    ofstream ofsn("Kullanicilar.txt");

    for (unsigned int i = 0; i < Hesaplar.size(); i++) {
        if (i != 0)
            ofsn << "\n";
        ofsn << Hesaplar[i];
    }

    for (unsigned int i = 0; i < Hesapnumara.size(); i++) {
        if (i != 0)
            otrans << "\n";
        otrans << Hesapnumara[i] << " " << types[i] << " " << values[i] << endl;
    }
}