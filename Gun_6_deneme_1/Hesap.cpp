#include"Hesap.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void Hesap::hesap_olustur(string isim, string sifre, double bakiye)
{
	cout << "Ýsminizi giriniz : "; cin >> isim;
	set_isim(isim);
	cout << "Þifrenizi giriniz : "; cin >> sifre;
	set_sifre(sifre);
	cout << "Bakiyenizi giriniz : "; cin >> bakiye;
	set_bakiye(bakiye);
	hesap_no++;
	set_hesap_no(hesap_no);

	cout << endl;
}

void Hesap::para_cek(double)
{

	cout << "Cekmek istedginiz miktari giriniz :"; cin >> cekilecek_para;
	if (cekilecek_para < bakiye)
	{
		bakiye -= cekilecek_para;
		cout << "Yeni bakiye : " << bakiye << endl;
		cout << "Hesabinizdan " << cekilecek_para << " cekildi" << endl;
	}
	else
	{
		cout << "Yetersiz bakiye." << endl;
	}



}

void Hesap::para_yatir(double)
{
	cout << "Yatirmak istediðiniz miktarý giriniz :"; cin >> yatirilacak_para;
	bakiye += yatirilacak_para;
	cout << "Yeni bakiye : " << bakiye << endl;
	cout << "Hesabiniza " << yatirilacak_para << " yatirildi" << endl;
}

void Hesap::para_transfer(int gonderliecek_hesap_no , double gonderilecek_para)
{

	cout << "Para transfer etmek istediginiz hesap numarasini giriniz : "; cin >> gonderliecek_hesap_no;
	
	cout << "Transfer etmek istediginiz miktari giriniz : "; cin >> gonderilecek_para;
	if (gonderilecek_para < bakiye)
	{
		bakiye -= gonderilecek_para;
		cout << "Komisyon oraný  :" << gonderilecek_para * komisyon_orani << endl;
		komisyon = gonderilecek_para * komisyon_orani;
		bakiye -= komisyon;

		cout << "Kalan bakiye : " << bakiye << endl;
	}
	else
	{
		cout << "Yetersiz bakiye." << endl;
	}

}

void Hesap::hesap_bilgi()
{
	
}

void Hesap::hesap_goster(string isim, string sifre, double bakiye)
{

	if (isim != "")
	{
		cout << endl;
		cout << "Kullanici ismi : " << isim << endl;
		cout << "Kullanici sifresi : " << sifre << endl;
		cout << "Kullanici bakiyesi : " << bakiye << endl;
		cout << "Kullanici hesap No : " << hesap_no << endl;
		cout << endl;
	}
	else
	{
		cout << "Kullanici bilgileri girilmemis." << endl;
	}	
}

void Hesap::texte_yaz(string isim, string sifre, double bakiye)
{
	fstream kayit_dosyasi;
	kayit_dosyasi.open("KullaniciKayit.txt", ios::out);
	if (kayit_dosyasi.is_open())
	{
		
		kayit_dosyasi << get_isim() << endl;
		kayit_dosyasi << get_sifre() << endl;
		kayit_dosyasi << get_bakiye() << endl;
		kayit_dosyasi << get_hesap_no() << endl;
	}
	kayit_dosyasi.close();
}

void Hesap::texten_oku(string isim, string sifre, double bakiye)
{
	
}


void Hesap::islem(int)
{
	int islem;
	do
	{
		cout << "Ýsleminizi seciniz : "; cin >> islem;
		switch (islem)
		{
		case 1:
		{
			hesap_olustur(isim, sifre, bakiye);
			texte_yaz(isim, sifre, bakiye);
		}

		break;
		case 2:
		{
			para_cek(cekilecek_para);

		}break;

		case 3:
		{
			para_yatir(yatirilacak_para);

		}break;

		case 4:
		{
			para_transfer(alici_hesap,gonderilecek_para);
		}break;

		case 5:
		{

		}break;
		case 6:
		{
			texten_oku(isim, sifre, bakiye);
			texte_yaz(isim, sifre, bakiye);
			hesap_goster(isim, sifre, bakiye);

		}break;

		default:
			texte_yaz(isim, sifre, bakiye);
			break;
		}
	} while (islem != 7);
	cout << "Cikis yapildi." << endl;
}