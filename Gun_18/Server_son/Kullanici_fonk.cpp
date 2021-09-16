#include<iostream>
#include"Kullanici_fonk.h"
#include<WS2tcpip.h>

using namespace std;

int MusteriHesap::SuankiHesapNo = 0;

vector<MusteriHesap> Hesaplar;
MusteriHesap musteri;
ofstream otrans("Islem gecmisi.txt", ios::app);

vector<int> HesapNumaralari;
vector<string> islemdeger;
vector<double> Para_deger;


void MusteriHesap::veridondur()
{
	ofstream Kayit("KullaniciKayit.txt", ios::app);
	ifstream ifs("KullaniciKayit.txt");

	while (!ifs.eof() && !isEmpty(ifs)) {

		ifs >> musteri;

		Hesaplar.push_back(musteri);
	}MusteriHesap::Set_SuankiHesapNo(Hesaplar.size());
}

MusteriHesap::MusteriHesap(string isim, string soyad, string sifre, string banka_adi, int baslangic_para)
{
	veridondur();
	set_isim(isim);
	set_soyad(soyad);
	set_sifre(sifre);
	set_banka_adi(banka_adi);
}
void MusteriHesap::para_yatir(int numara, double deger2)
{
	if (deger2 < 0)
	{
		hata_kontrol = "0";
	}
	else
	{
		hata_kontrol = "1";
		bakiye_deger = Hesaplar[numara].get_bakiye();
		string bakiye_degers = to_string(bakiye_deger);

		bakiye = Hesaplar[numara].get_bakiye();

		bakiye += deger2;
		Hesaplar[numara].set_bakiye(bakiye);
	}

}
void MusteriHesap::para_cek(int numara, double deger2)
{

	if (deger2 < 0)
	{
		hata_kontrol = "0";
	}
	else if (Hesaplar[numara].get_bakiye() - deger2 >= 0)
	{
		hata_kontrol = "1";
		bakiye = Hesaplar[numara].get_bakiye();
		bakiye -= deger2;
		Hesaplar[numara].set_bakiye(bakiye);
	}
	else if (Hesaplar[numara].get_bakiye() - deger2 >= 0)
	{
		hata_kontrol = "0";
		cout << "Hatali islem..." << endl;
		Sleep(1500);
	}
}
void MusteriHesap::transfer(int numarakullanici, int numaragiden, double deger2)
{
	numarakullanici -= 1;
	if (deger2 < 0)
	{

	}
	if (deger2 < Hesaplar[numarakullanici].get_bakiye())
	{
		if (Hesaplar[numarakullanici].get_HesapNo() == Hesaplar[numaragiden].get_HesapNo())
		{
			cout << "Hata.." << endl;
			Sleep(1500);
		}
		else if (Hesaplar[numarakullanici].get_banka_adi() == Hesaplar[numaragiden].get_banka_adi())
		{
			bakiye = Hesaplar[numarakullanici].get_bakiye();
			bakiye -= deger2;
			Hesaplar[numarakullanici].set_bakiye(bakiye);

			havale_isim = Hesaplar[numaragiden].get_isim() + " " + Hesaplar[numaragiden].get_soyad();
			havale_edilen_para = deger2;
			havale_edilen_str = to_string(havale_edilen_para);

			havale_islem = "Havale yapilan kullanici : " + havale_isim + "  Gonderilen para  :" + havale_edilen_str;


			double alici;
			alici = Hesaplar[numaragiden].get_bakiye();
			alici += deger2;
			Hesaplar[numaragiden].set_bakiye(alici);
		}
		else
		{
			bakiye = Hesaplar[numarakullanici].get_bakiye();
			bakiye -= deger2 + (deger2 * komisyon);
			Hesaplar[numarakullanici].set_bakiye(bakiye);

			havale_isim = Hesaplar[numaragiden].get_isim() + " " + Hesaplar[numaragiden].get_soyad();
			havale_edilen_para = deger2;
			havale_edilen_str = to_string(havale_edilen_para);
			havale_islem = "Havale yapilan kullanici : " + havale_isim + "  Gonderilen para  :" + havale_edilen_str;

			double alici;
			alici = Hesaplar[numaragiden].get_bakiye();
			alici += deger2;
			Hesaplar[numaragiden].set_bakiye(alici);
		}
	}
}

void MusteriHesap::hesap_bilgi_gonder(int hesapnumara)
{
	int i;
	for (i = 0; i < Hesaplar.size(); i++)
	{
		if (Hesaplar[i].get_HesapNo() == hesapnumara)
		{
			giden_isim = Hesaplar[i].get_isim();
			giden_soyad = Hesaplar[i].get_soyad();
			double giden_bk = Hesaplar[i].get_bakiye();
			giden_bakiye = to_string(giden_bk);
			islemler = giden_isim + " " + giden_soyad + " Bakiye : " + giden_bakiye;
		}
	}
}
void MusteriHesap::Hesap_Kontrol(int hesapnumara, string kullanicisifre)
{
	bool kontrol = true;
	int i;
	if (hesapnumara > Hesaplar.size())
	{
		mesaj3 = "0";
	}

	for (i = 0; i < Hesaplar.size(); i++)
	{
		if (Hesaplar[i].get_HesapNo() == hesapnumara)
		{
			if (Hesaplar[i].get_sifre() == kullanicisifre)
			{
				Veri_guncelle();
				mesaj3 = "1";
				kullanicisifre = mesaj3;
				int mesajsinyal = send(ClientSocket, kullanicisifre.c_str(), kullanicisifre.size() + 1, 0);
				kontrol = false;
			}
			else
			{
				mesaj3 = "0";
			}
		}
	}
}

void MusteriHesap::close() { open = false; }
bool MusteriHesap::isOpen() { return open; }

ostream& operator << (ostream& out, MusteriHesap& Hesap1) {
	if (Hesap1.get_bakiye() >= 0)
	{
		out << "Banka Adi : " << Hesap1.get_banka_adi() << endl;
		out << "Isim: " << Hesap1.get_isim() << endl;
		out << "Soyad: " << Hesap1.get_soyad() << endl;
		out << "Sifre: " << Hesap1.get_sifre() << endl;
		out << "Bakiye: " << Hesap1.get_bakiye() << " TL" << endl;
		out << "Hesap No: " << Hesap1.get_HesapNo() << endl;
	}
	return out;
}
ifstream& operator >> (ifstream& in, MusteriHesap& Hesap1) {

	string isim, soyad, sifre;
	string banka_adi;
	int HesapNo;
	double bakiye;

	in >> banka_adi >> isim >> soyad >> sifre;
	in >> bakiye >> HesapNo;
	Hesap1.set_banka_adi(banka_adi);
	Hesap1.set_isim(isim);
	Hesap1.set_soyad(soyad);
	Hesap1.set_sifre(sifre);
	Hesap1.set_bakiye(bakiye);
	Hesap1.HesapNo = HesapNo;
	return in;

}
ofstream& operator << (ofstream& out, MusteriHesap& Hesap1) {
	if (Hesap1.get_bakiye() > 0)
	{
		out << Hesap1.get_banka_adi() << endl;
		out << Hesap1.get_isim() << endl;
		out << Hesap1.get_soyad() << endl;
		out << Hesap1.get_sifre() << endl;
		out << Hesap1.get_bakiye() << endl;
		out << Hesap1.get_HesapNo() << endl;

		return out;
	}
}

void MusteriHesap::Veri_guncelle()
{
	ofstream ofsn("KullaniciKayit.txt");

	for (unsigned int i = 0; i < Hesaplar.size(); i++) {
		if (i != 0)
			ofsn << "\n";
		ofsn << Hesaplar[i];
	}

	for (unsigned int i = 0; i < HesapNumaralari.size(); i++) {
		if (i != 0)
			otrans << "\n";
		otrans << HesapNumaralari[i] << " " << islemdeger[i] << " " << Para_deger[i] << endl;
	}
}



void MusteriHesap::vektor_ekle()
{
	HesapNumaralari.push_back(HesapNo);
	islemdeger.push_back("Para_yatir");
	Para_deger.push_back(deger);
}