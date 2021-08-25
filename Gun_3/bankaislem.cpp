#include<iostream>
#include "bankaclass.h"


void Bankahesap::anamenu()
{
	cout << "********" << endl;
	cout << "1. Hesabý görüntüle." << endl;
	cout << "2. Hesaba para yatýr." << endl;
	cout << "3. Hesaptan para çek." << endl;
	cout << "4. Çýkýþ" << endl;
	cout << "Ýsim : " << Bankahesap::kullaniciadi << endl;
	cout << "********" << endl;

}



void Bankahesap::islemmenusu()
{
	int islem;
	int cekilecekpara;
	int yatirilacakpara;

	do
	{
		cout << "Yapmak istediðiniz iþlemi seçiniz : "; cin >> islem;
		switch (islem)
		{
		case 1: {

			cout << "Hesaptaki para : " << Bankahesap::hesaptakipara;
			cout << endl;

		}break;
		case 2: {
			cout << "Yatýrmak istediðiniz parayý giriniz : "; cin >> yatirilacakpara;
			Bankahesap::hesaptakipara += yatirilacakpara;
			cout << "****" << endl;
			cout << "Hesaptaki Bakiye : " << Bankahesap::hesaptakipara;
			cout << "****" << endl;
		}break;
		case 3: {
			cout << "Çekme istedðiniz para miktarýný giriniz : "; cin >> cekilecekpara;
			if (cekilecekpara < hesaptakipara)
			{
				Bankahesap::hesaptakipara -= cekilecekpara;
				cout << "****" << endl;
				cout << "Hesaptaki Bakiye : " << Bankahesap::hesaptakipara;
				cout << "****" << endl;
			}
			else
			{
				cout << "Baiye yetersiz!" << endl;
			}
		}break;
		case 4: cout << "Çýkýþ yapýldý." << endl;


		default:
			break;
		}
	} while (islem !=4);


	

}

void Bankahesap::sifrekontrol(string kullanici)
{

	cout << "Kontrol :" << endl;
}