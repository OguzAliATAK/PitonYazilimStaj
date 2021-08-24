#include <iostream>
using namespace std;

class kullanicilar {
public:

	string ad;
	string soyad;
	string sifre;
	int hesaptakipara;
};


void menu()
{
	cout << "**********" << endl;
	cout << "1. Bakiye sorgulama" << endl;
	cout << "2. Para yatırma " << endl;
	cout << "3. Para çekme" << endl;
	cout << "4. Hesap ayarları" << endl;
	cout << "5. Çıkış " << endl;
	cout << "**********" << endl;
}



void hesapayarlari()
{
	cout << "1. Şifre değiştir";
}
int main()
{
	kullanicilar kullanici1, kullanici2;

	string eski, yeni1;
	yeni1 = "0";
	setlocale(LC_ALL, "Turkish");
	double yatirilan_para;
	double cekilen_para;
	string degistir;

	kullanici1.ad = "Oguz";
	kullanici1.soyad = "ATAK";
	kullanici1.sifre = "1999";
	kullanici1.hesaptakipara = 680;
a:
	cout << "*************" << endl;
	cout << "İsim :" << kullanici1.ad << endl;
	cout << "Soyad :" << kullanici1.soyad << endl;
	cout << "Şifre :" << kullanici1.sifre << endl;
	cout << "Bakiye:" << kullanici1.hesaptakipara << endl;
	cout << "*************" << endl;


	string kullanici_ismi;
	string kullanici_soyad;
	string sifre;


	cout << "*************" << endl;


	do
	{
		cout << "İsminizi giriniz : ";
		cin >> kullanici_ismi;

		cout << "Soyadınızı girinz : ";
		cin >> kullanici_soyad;

		cout << "Şifrenizi giriniz : ";
		cin >> sifre;

		if (kullanici_ismi != kullanici1.ad || kullanici1.sifre != sifre)
		{
			cout << "Girdiğiniz bilgiler yanlış. Tekrar deneyin" << endl;
		}
		else
		{
			cout << endl;
		}



	} while (sifre != kullanici1.sifre || kullanici_ismi != kullanici1.ad);

	cout << endl;
	cout << endl;
b:

	int islem;

	menu();
	cout << endl;

	do
	{
		cout << "Yapmak istedğiniz işlemi tuşlayınız : ";
		cin >> islem;
		switch (islem)
		{
		case 1:
		{
			cout << "Hesaptaki para miktarı : " << kullanici1.hesaptakipara;
			cout << endl;
			break;
		}
		case 2:
		{
			cout << " Hesaptaki para miktarı : " << kullanici1.hesaptakipara;
			cout << endl;

			cout << "Yatırılacak para miktarını girin : ";
			cin >> yatirilan_para;
			kullanici1.hesaptakipara += yatirilan_para;
			break;
		}
		case 3:
		{
			cout << " Hesaptaki para miktarı : " << kullanici1.hesaptakipara;
			cout << endl;

			cout << "Çekilecek para miktarını girin";
			cin >> cekilen_para;
			cout << endl;
			if (cekilen_para < kullanici1.hesaptakipara)
			{
				kullanici1.hesaptakipara -= cekilen_para;
				cout << "Hesapta kalan para miktarı : " << kullanici1.hesaptakipara;
				cout << endl;

			}
			else
			{
				cout << "Yeterli Bakiye yok " << endl;
			}
			break;
		}
		case 4:
		{

			system("CLS");

			cout << "***********" << endl;
			int islem2;


			hesapayarlari();
			cout << endl;
			cout << "İşleminizi seçiniz : ";
			cin >> islem2;


			switch (islem2)
			{
			case 1:
			{
				do
				{

					cout << "Eski şifrenizi giriniz :";
					cin >> eski;

					if (eski == kullanici1.sifre)
					{
						cout << "Yeni şifrenizi giriniz : " << endl;
						cin >> yeni1;
						cout << endl;
						kullanici1.sifre = yeni1;
						cout << kullanici1.sifre;
						cout << endl;
						break;

					}
					else
					{
						cout << "Şifreniz yanlış : " << endl;
						goto b;

					}


				} while (eski != kullanici1.sifre);


				cout << "Şifreniz başarıyla değiştirildi ! " << endl;
				goto a;
				break;
			}
			default:
				break;
			}

			break;
		}


		default:
			break;
		}


	} while (islem != 5);





	system("PAUSE");
	return 0;
}