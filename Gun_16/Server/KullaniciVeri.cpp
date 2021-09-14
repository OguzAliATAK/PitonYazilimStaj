#include<iostream>
#include"KullaniciVeri.h"
#include<WS2tcpip.h>
#include"Menu.h"

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

void eksi()
{
	cout << "- deger girildi :" << endl;
	Sleep(950);
	exit(-1);
}


MusteriHesap::MusteriHesap(string isim, string soyad, string sifre, string banka_adi, int baslangic_para)
{
	veridondur();
	set_isim(isim);
	set_soyad(soyad);
	set_sifre(sifre);
	set_banka_adi(banka_adi);
}
void MusteriHesap::para_yatir(int numara ,double deger2)
{
	if (deger2 < 0)
	{
		cout << "Eksi deger giremezsiniz:" << endl;
	}
	else
	{
		bakiye = Hesaplar[numara].get_bakiye();
		cout << "Hesabiniza " << deger2 << " TL yatirildi" << endl;
		bakiye += deger2;
		cout << "Bakiye deger : " << bakiye << endl;
		Hesaplar[numara].set_bakiye(bakiye);
		cout << "Bakiye : " << Hesaplar[numara].get_bakiye() << " TL" << endl;	
	}

}
void MusteriHesap::para_cek(int numara ,double deger2)
{
	if (deger2 < 0)
	{
		eksi();
	}
	else if(Hesaplar[numara].get_bakiye() - deger2 >= 0)
	{
		bakiye = Hesaplar[numara].get_bakiye();
		cout << "Hesabinizdan " << deger2 << " TL cekildi" << endl;
		bakiye -= deger2;
		Hesaplar[numara].set_bakiye(bakiye);
		cout << "Kalan Bakiye : " << Hesaplar[numara].get_bakiye() << endl;
	}
}
void MusteriHesap::transfer(int numarakullanici, int numaragiden, double deger2)
{
	numarakullanici -= 1;
	cout << "Gonderen once : " << Hesaplar[numarakullanici].get_bakiye() << endl;
	cout << "Alici once  : " << Hesaplar[numaragiden].get_bakiye() << endl;
	if (deger2 < 0)
	{
		eksi();
	}

	if (Hesaplar[numarakullanici].get_banka_adi() == Hesaplar[numaragiden].get_banka_adi())
	{
		bakiye = Hesaplar[numarakullanici].get_bakiye();
		bakiye -= deger2;
		Hesaplar[numarakullanici].set_bakiye(bakiye);

		double alici;
		alici = Hesaplar[numaragiden].get_bakiye();
		alici += deger2;
		Hesaplar[numaragiden].set_bakiye(alici);
	}
	else
	{
		bakiye = Hesaplar[numarakullanici].get_bakiye();
		bakiye -= deger2+(deger2*komisyon);
		Hesaplar[numarakullanici].set_bakiye(bakiye);

		double alici;
		alici = Hesaplar[numaragiden].get_bakiye();
		alici += deger2;
		Hesaplar[numaragiden].set_bakiye(alici);
	}
	
	
	cout << "Gonderen yeni : "<< Hesaplar[numarakullanici].get_bakiye() << endl;
	cout << "Alici yeni : " << Hesaplar[numaragiden].get_bakiye() << endl;

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

void MusteriHesap::Kullanici_kontrol()
{
	MusteriHesap musteri;
	cout << "Kullanici sistemde tanimli degil" << endl;
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

void MusteriHesap::Hesap_Kontrol(int hesapumara ,string kullanicisifre)
{
	bool kontrol = true;
	do
	{
		for (unsigned i = 0; i < Hesaplar.size(); i++)
		{
			if (Hesaplar[i].get_HesapNo() == hesapumara)
			{
				if (Hesaplar[i].get_sifre() == kullanicisifre)
				{
					cout << "Sifre : " << kullanicisifre << endl;
					cout << "Giris yapan kullanici : " << Hesaplar[i].get_isim() << " " << Hesaplar[i].get_soyad() << endl;

					Veri_guncelle();
					kontrol = false;
				}
				else
				{
					cout << "Kullanici adi ve sifresi yanlis";
					Sleep(950);
					exit(-1);
				}
			}	
		}
	} while (kontrol);
}


void MusteriHesap::Admin_giris()
{
	string admin1, adminkontrol;
	string sifre1, sifrekontrol;
	int donus;
	admin1 = "Admin";
	sifre1 = "123";
	bool kontrol1 = true;
	do
	{
		cout << "Kullanici adini giriniz :"; cin >> adminkontrol;
		cout << "Sifeyi giriniz :"; cin >> sifrekontrol;
		if (admin1 == adminkontrol && sifre1 == sifrekontrol)
		{
			kontrol1 = false;
		}
		else
		{
			cout << "Kullanici adi veya sifre hatali!" << endl;
		}

	} while (kontrol1);

}

void MusteriHesap::VeriTabani_erisimi()
{

	cout << "************" << endl;
	cout << "Sistemdeki kullanici sayisi " << Hesaplar.size() << endl;
	cout << "************" << endl;
	for (unsigned int i = 0; i < Hesaplar.size(); i++)
	{
		if (Hesaplar[i].get_sifre() == "")
		{
			cout << "" << endl;
		}
		else
		{
			cout << Hesaplar[i];
			cout << "***********" << endl;
		}

	}

}

void MusteriHesap::vektor_ekle()
{
	HesapNumaralari.push_back(HesapNo);
	islemdeger.push_back("Para_yatir");
	Para_deger.push_back(deger);
}

void MusteriHesap::vektor()
{
	
	ifstream ifs("KullaniciKayit.txt");

	while (!ifs.eof() && !isEmpty(ifs)) {

		ifs >> musteri;

		Hesaplar.push_back(musteri);
	}MusteriHesap::Set_SuankiHesapNo(Hesaplar.size());

	int islem;
anamenu1:
	
	do
	{
		Menuler menu1;

		menu1.ana_menu();
		cout << "Isleminizi seciniz :"; cin >> islem; system("cls");
		switch (islem)
		{
		case 1: {

			/*
			
			int HesapNo;
			HesapNo = HesapNo_kontrol;
			HesapNo--;
			Hesaplar[HesapNo].para_yatir(deger);
			vektor_ekle();
			*/
			

		}break;
		case 2: {

			int HesapNo;
			HesapNo = HesapNo_kontrol;
			HesapNo--;
			//Hesaplar[HesapNo].para_cek(deger);
			vektor_ekle();
			Veri_guncelle();

		}break;
		case 3: {
			int HesapNo, diger;
			double deger;
			double yenibakiye = 0;
			double Kullanici_bakiye = 0;
			HesapNo = HesapNo_kontrol;
			cout << "Alici hesabi seciniz : "; cin >> diger;
			cout << "Transfer etmek istediginiz miktari giriniz : "; cin >> deger;

			if (Hesaplar[HesapNo].get_HesapNo() == Hesaplar[diger].get_HesapNo())
			{
				cout << "Kendinize para gonderemezsiniz" << endl;

			}
			else
			{
				HesapNo--;
					if (Hesaplar[HesapNo].get_bakiye() - deger >= 0)
					{
						if (Hesaplar[HesapNo].get_banka_adi() == Hesaplar[diger].get_banka_adi())
						{
							diger--;
							Kullanici_bakiye = Hesaplar[HesapNo].get_bakiye() - deger;
							yenibakiye = deger + Hesaplar[diger].get_bakiye();
							Hesaplar[diger].set_bakiye(yenibakiye);
							Hesaplar[HesapNo].set_bakiye(Kullanici_bakiye);
							cout << "Kalan Bakiye :" << Hesaplar[HesapNo].get_bakiye() << " TL" << endl;
							Veri_guncelle();
							cout << endl;
							cout << "islem basarli" << endl;

						}
						else if (Hesaplar[HesapNo].get_banka_adi() != Hesaplar[diger].get_banka_adi())
						{
							cout << "Komisyon orani : " << deger * komisyon << " TL " << endl;
							diger--;
							Kullanici_bakiye = Hesaplar[HesapNo].get_bakiye() - deger - (deger * komisyon);
							yenibakiye = deger + Hesaplar[diger].get_bakiye();
							Hesaplar[diger].set_bakiye(yenibakiye);
							Hesaplar[HesapNo].set_bakiye(Kullanici_bakiye);
							cout << "Kalan Bakiye :" << Hesaplar[HesapNo].get_bakiye() << " TL" << endl;
							Veri_guncelle();
							cout << endl;
							cout << "islem basarli" << endl;
						}
					}
					else
					{
						cout << "Bakiye yetersiz!" << endl;
					}
				
			}
		}break;
		case 4:
		{
			goto anamenu1;
		}break;


		case 7: break;
		default:
			break;
		}
	} while (islem != 7);

	Veri_guncelle();

}

