#include<iostream>
#include"Hesap.h"
#include"Menu.h"

using namespace std;

int MusteriHesap::SuankiHesapNo = 0;

vector<MusteriHesap> Hesaplar;
MusteriHesap musteri;
ofstream otrans("a.txt", ios::app);

vector<int> HesapNumaralari;
vector<string> islemdeger;
vector<double> Para_deger;


MusteriHesap::MusteriHesap(string isim, string soyad, string sifre, int baslangic_para)
{
	set_isim(isim);
	set_soyad(soyad);
	set_sifre(sifre);

}

void MusteriHesap::para_yatir(double deger)
{
	bakiye += deger;
}
void MusteriHesap::para_cek(double deger)
{
	bakiye -= deger;
}
void MusteriHesap::transfer(MusteriHesap diger, double deger)
{
	bakiye -= deger; diger.bakiye += deger;
}

void MusteriHesap::close() { open = false; }
bool MusteriHesap::isOpen() { return open; }


/*
istream& operator >> (istream& in, MusteriHesap& Hesap1) {
	string isim,soyad,sifre;
	double bakiye;

	cout << "Isminizi giriniz: "; cin >> isim;
	cout << "Soyadinizi giriniz:"; cin >> soyad;
	cout << "Sifrenizi giriniz: "; cin >> sifre;
	cout << "Bakiyenizi giriniz: "; cin >> bakiye;

	Hesap1.set_isim(isim);
	Hesap1.set_soyad(soyad);
	Hesap1.set_sifre(sifre);
	Hesap1.set_bakiye(bakiye);

	return in;
}
*/
ostream& operator << (ostream& out, MusteriHesap& Hesap1) {
	if (Hesap1.get_isim() != "")
	{
		out << "Isim: " << Hesap1.get_isim() << endl;
		out << "Soyad: " << Hesap1.get_soyad() << endl;
		out << "Sifre: " << Hesap1.get_sifre() << endl;
		out << "Bakiye: " << Hesap1.get_bakiye() << endl;
		out << "Hesap No: " << Hesap1.get_HesapNo() << endl;
	}

	return out;
}
ifstream& operator >> (ifstream& in, MusteriHesap& Hesap1) {
	string isim, soyad;
	string sifre;
	int HesapNo;
	double bakiye;

	in >> isim >> soyad >> sifre;
	in >> bakiye >> HesapNo;

	Hesap1.set_isim(isim);
	Hesap1.set_soyad(soyad);
	Hesap1.set_sifre(sifre);
	Hesap1.set_bakiye(bakiye);
	Hesap1.HesapNo = HesapNo;


	return in;
}
ofstream& operator << (ofstream& out, MusteriHesap& Hesap1) {
	out << Hesap1.get_isim() << endl;
	out << Hesap1.get_soyad() << endl;
	out << Hesap1.get_sifre() << endl;
	out << Hesap1.get_bakiye() << endl;
	out << Hesap1.get_HesapNo() << endl;

	return out;
}

bool isEmpty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

bool Valid(unsigned int HesapNo, vector<MusteriHesap> Hesaplar) {
	if (HesapNo <= Hesaplar.size() && HesapNo >= 0 && Hesaplar[HesapNo].isOpen())
		return true;
	return false;
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

void MusteriHesap::Hesap_Kontrol()
{
	bool kontrol = true;
	do
	{
		cout << "Hesap Numaranizi giriniz :"; cin >> HesapNo_kontrol;
		cout << "Sifrenizi giriniz :"; cin >> sifre_kontrol;

		for (unsigned i = 0; i < Hesaplar.size(); i++)
		{
			if (Hesaplar[i].get_HesapNo() == HesapNo_kontrol)
			{
				if (Hesaplar[i].get_sifre() == sifre_kontrol)
				{
					cout << "Hosgeldiniz" << endl;
					
					kontrol = false;

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
			cout << "Kullanici adi ve sifre hatali!" << endl;
		}

	} while (kontrol1);


}

void MusteriHesap::VeriTabani_erisimi()
{
	system("cls");
	for (unsigned int i = 0; i < Hesaplar.size(); i++)
	{
		if (Hesaplar[i].get_isim() != "")
		{
			cout << Hesaplar[i];
			cout << "***********" << endl;
		}

	}
	
}

void MusteriHesap::Ana_menu_islem()
{
	int islem2;
	Menuler menu1;
donus:
	menu1.kontrol_menusu();
	cout << "Isleminizi giriniz :"; cin >> islem2; system("cls");

	switch (islem2)
	{
	case 1:
	{
		Hesap_Kontrol();
	}break;
	case 2:
	{
		Admin_giris();
		VeriTabani_erisimi();
		system("Pause");
		system("cls");
		goto donus;
	}break;
	default: {
		do
		{
			goto donus;
		} while (true);

	}break;

	}
}

void MusteriHesap::vektor()
{
	ofstream Kayit("KullaniciKayit.txt", ios::app);
	ifstream ifs("KullaniciKayit.txt");

	while (!ifs.eof() && !isEmpty(ifs)) {

		ifs >> musteri;

		Hesaplar.push_back(musteri);
	}MusteriHesap::Set_SuankiHesapNo(Hesaplar.size());

	int islem;
	Ana_menu_islem();
	system("cls");

	do
	{
		Menuler menu1;

		menu1.ana_menu();
		cout << "Isleminizi seciniz :"; cin >> islem; system("cls");
		switch (islem)
		{
			/*
			* case 1: {
			MusteriHesap musteri;
			cin >> musteri;
			if (Hesaplar.size() != 0)
			{
				Kayit << endl;

			}Hesaplar.push_back(musteri);
			Kayit << musteri;
			cout << "Hesap Olusturuldu" << endl;
			cout << "Hesap Numaraniz : " << musteri.get_HesapNo() << endl;



		}break;
			*/


		case 1: {
			for (unsigned int i = 0; i < Hesaplar.size(); i++)
			{
				if (Hesaplar[i].get_isim() != "")
				{
					cout << Hesaplar[i];
					cout << "***********" << endl;
				}

			}
		}break;
		case 2: {
			Veri_guncelle();
			int HesapNo;
			double deger;
			HesapNo = HesapNo_kontrol;
			if (Valid(HesapNo, Hesaplar))
			{
				cout << "Yatirmak istediginiz miktari giriniz "; cin >> deger;

				HesapNo--;
				cout << "Hesabiniza " << deger << " TL yatirildi" << endl;

				Hesaplar[HesapNo].para_yatir(deger);
				cout << "Yeni bakiyeniz : " << Hesaplar[HesapNo].get_bakiye() << endl;

				HesapNumaralari.push_back(HesapNo);
				islemdeger.push_back("Para_yatir");
				Para_deger.push_back(deger);
				Veri_guncelle();
			}
			else
			{
				Kullanici_kontrol();
			}


		}break;
		case 3: {
			Veri_guncelle();
			int HesapNo;
			double deger;
			HesapNo = HesapNo_kontrol;
			

			HesapNo--;
			if (Valid(HesapNo, Hesaplar))
			{
				cout << "Cekmek istediginiz miktari giriniz "; cin >> deger;
				if (Hesaplar[HesapNo].get_bakiye() - deger >= 0)
				{
					cout << "Hesabinizdan " << deger << " TL cekildi" << endl;
					Hesaplar[HesapNo].para_cek(deger);
					cout << "Yeni bakiyeniz : " << Hesaplar[HesapNo].get_bakiye() << endl;

					HesapNumaralari.push_back(HesapNo);
					islemdeger.push_back("Para_cek");
					Para_deger.push_back(deger);
					Veri_guncelle();
				}
				else
				{
					cout << "Bakiye yetersiz" << endl;

				}
			}
			else
			{
				Kullanici_kontrol();
			}

		}break;
		case 4: {
			int HesapNo, diger;
			double deger;
			cout << "Gonderici hesabi seciniz : "; cin >> HesapNo;
			cout << "Alici hesabi seciniz : "; cin >> diger;
			cout << "Transfer etmek istediginiz miktari giriniz : "; cin >> deger;

			HesapNo--;
			if (Valid(HesapNo, Hesaplar) && Valid(diger, Hesaplar))
			{
				if (Hesaplar[HesapNo].get_bakiye() - deger >= 0)
				{

					cout << Hesaplar[diger].get_isim() << "hesabina " << deger << " TL gonderildi." << endl;

					Hesaplar[HesapNo].transfer(Hesaplar[diger], deger);
					cout << Hesaplar[HesapNo].get_isim() << "'nin bakiyesi : " << Hesaplar[HesapNo].get_bakiye() << endl;
					cout << Hesaplar[diger].get_isim() << "'nin bakiyesi : " << Hesaplar[diger].get_bakiye() << endl;
					Veri_guncelle();
				}
				else
				{
					cout << "Bakiye yetersiz!" << endl;
				}
				Kullanici_kontrol();
			}

		}break;
		case 5: {
		}break;


		case 7: break;
		default:
			break;
		}
	} while (islem != 7);

	Veri_guncelle();

}

