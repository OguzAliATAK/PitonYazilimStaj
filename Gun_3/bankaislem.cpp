#include<iostream>
#include "bankaclass.h"


void Bankahesap::anamenu()
{
	cout << "********" << endl;
	cout << "1. Hesab� g�r�nt�le." << endl;
	cout << "2. Hesaba para yat�r." << endl;
	cout << "3. Hesaptan para �ek." << endl;
	cout << "4. ��k��" << endl;
	cout << "�sim : " << Bankahesap::kullaniciadi << endl;
	cout << "********" << endl;

}



void Bankahesap::islemmenusu()
{
	int islem;
	int cekilecekpara;
	int yatirilacakpara;

	do
	{
		cout << "Yapmak istedi�iniz i�lemi se�iniz : "; cin >> islem;
		switch (islem)
		{
		case 1: {

			cout << "Hesaptaki para : " << Bankahesap::hesaptakipara;
			cout << endl;

		}break;
		case 2: {
			cout << "Yat�rmak istedi�iniz paray� giriniz : "; cin >> yatirilacakpara;
			Bankahesap::hesaptakipara += yatirilacakpara;
			cout << "****" << endl;
			cout << "Hesaptaki Bakiye : " << Bankahesap::hesaptakipara;
			cout << "****" << endl;
		}break;
		case 3: {
			cout << "�ekme isted�iniz para miktar�n� giriniz : "; cin >> cekilecekpara;
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
		case 4: cout << "��k�� yap�ld�." << endl;


		default:
			break;
		}
	} while (islem !=4);


	

}

void Bankahesap::sifrekontrol(string kullanici)
{

	cout << "Kontrol :" << endl;
}