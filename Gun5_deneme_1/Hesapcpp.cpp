#include"Hesap.h"
#include<iostream>

using namespace std;

void Hesap::hesap_olustur(string isim, string sifre, double bakiye)
{
	cout << "�sminizi giriniz : "; cin >> isim;
	set_isim(isim);
	cout << "�ifrenizi giriniz : "; cin >> sifre;
	set_sifre(sifre);
	cout << "Bakiyenizi giriniz : "; cin >> bakiye;
	set_bakiye(bakiye);
	
	cout << endl;
}

void Hesap::para_cek(double)
{
	
	cout << "�ekmek isted�iniz miktar� giriniz :"; cin >> cekilecek_para;
	if (cekilecek_para < bakiye)
	{
		bakiye -= cekilecek_para;
		cout << "Yeni bakiye : " << bakiye << endl;
		cout << "Hesabinizdan " << cekilecek_para << " �ekildi" << endl;
	}
	else
	{
		cout << "Yetersiz bakiye." << endl;
	}



}

void Hesap::para_yatir(double)
{
	cout << "Yat�rmak istedi�iniz miktar� giriniz :"; cin >> yatirilacak_para;
	bakiye += yatirilacak_para;
	cout << "Yeni bakiye : " << bakiye << endl;
	cout << "Hesab�n�za " << yatirilacak_para << " yat�r�ld�" << endl;
}

void Hesap::para_transfer(double gonderilecek_para)
{
	cout << "Transfer etmek istedi�iniz miktar� giriniz : "; cin >> gonderilecek_para;


	if (gonderilecek_para < bakiye)
	{
		bakiye -= gonderilecek_para;
		cout << "Komisyon oran�  :" << gonderilecek_para * komisyon_orani << endl;
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
	cout << Hesap::get_isim();
}

void Hesap::islem(int)
{
	int islem;
	do
	{
	
	cout << "��leminizi se�iniz : "; cin >> islem;

	
		switch (islem)
		{
		case 1:
		{
			cout << endl;
			cout << "Kullan�c� ismi : " << isim << endl;
			cout << "Kullan�c� �ifresi : " << sifre << endl;
			cout << "Kullan�c� bakiyesi : " << bakiye << endl;
			cout << endl;
			
		}
		
		break;
		case 2:
		{
			cout << endl;			
			para_cek(cekilecek_para);
			
		}break;

		case 3:
		{
			cout << endl;
			para_yatir(yatirilacak_para);

		}break;

		case 4:
		{
			para_transfer(gonderilecek_para);
		}break;

		case 5:
		{

		}break;
		case 6:
		{
			hesap_olustur(isim,sifre,bakiye);
		}break;


		default:
			break;
		}
	} while (islem != 7);

	cout << "��k�� yap�ld�." << endl;

	
}