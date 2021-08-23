#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include<locale>
#include<string>
#include<fstream>
#include<list>
#include<locale>


using namespace std;


void deneme()
{
	struct Deneme
	{
		string isim;
		string soyisim;
		int yas;
	};

	struct Deneme2
	{
		string okul;
		Deneme deneme2_1;

	};

	Deneme2 deneme2 = { "Üniversite",{"Oğuz","ATAK",21} };
	cout << deneme2.deneme2_1.isim << endl;
	cout << deneme2.deneme2_1.soyisim << endl;
	cout << deneme2.deneme2_1.yas << endl;
	cout << deneme2.okul << endl;

	
}

void faktoriyel(int girilecekdeger)
{
	a:
	int toplam = 1;
	int isle2;

	for (int i = 1; i <= girilecekdeger; i++)
	{
		toplam *= i;
	}
	cout << toplam;
	cout << endl;
	cout << "Tekrar hesaplama için 1'e basınız" << endl;
	cout << "Çıkmak için 2'ye basınız." << endl;
	cin >> isle2;

	switch (isle2)
	{
	case 1: system("CLS"); goto a; break;
	case 2: cout << "Çıkış yapıldı " << endl;

	default:cout << endl;
		break;
	}
}

void ekokhesaplama()
{
	a:
	int sayi1, sayi2,isle,isle2;

	cout << "Ekokunu hesaplamak istediğiniz sayıları giriniz." << endl;
	cout << "sayı 1 :"; cin >> sayi1; cout << endl;
	cout << "Sayı 2 :"; cin >> sayi2; cout << endl;

	isle = (sayi1 > sayi2) ? sayi1 : sayi2;

	do
	{
		if (isle % sayi1 == 0 && isle % sayi2 == 0)
		{
			cout << "Girdiğiniz iki sayının ekoku : " << isle;
			cout << endl;
			break;
		}
		else
		{
			++isle;
		}

	} while (1);

	cout << "Tekrar hesaplama için 1'e basınız" << endl;
	cout << "Çıkmak için 2'ye basınız." << endl;
	cin >> isle2;

	switch (isle2)
	{
	case 1: system("CLS"); goto a; break;
	case 2: cout << "Çıkış yapıldı " << endl;


	default:cout << endl;
		break;
	}


}

void oyun()
{

	int sayi1, deger1, deneme;
	int islem2;
	deneme = 0;
a:
	srand(time(NULL));
	sayi1 = rand() % 100 + 1;
	cout << "Bilgisayardaki sayı" << sayi1 << endl;
	do
	{

		cout << "100 ile 0 arasında bir değer giriniz:" << endl;
		cin >> deger1;

		if (sayi1 < deger1) {
			cout << "Daha kucuk deger girin." << endl;
		}
		else if (sayi1 > deger1) {
			cout << "Daha büyük deger girin." << endl;
		}

		deneme++;
		cout << " Deneme sayısı " << deneme << endl;


	} while (deger1 != sayi1);

	cout << "Girilen değer doğru!" << endl;
	cout << "**********************" << endl;


	cout << "Tekrar oynamak için 1'e basınız." << endl;
	cout << "Çıkmak için 2'ye basınız." << endl;
	cin >> islem2;

	switch (islem2)
	{
	case 1: goto a; break;
	case 2: break;
	default:
		break;
	}

}

void siralama()
{

	int sayimiktari;
	int sayi;
	int enbuyuksayi = 0;
	int enkucuksayi = 110;

	cout << "Girmek istediğiniz sayı adedini yazınız."; cin >> sayimiktari;

	for (int i = 1; i <= sayimiktari; i++)
	{
		cout << i << ". sayı : "; cin >> sayi;

		if (sayi > enbuyuksayi)
		{
			enbuyuksayi = sayi;
		}

		for (int j = 1; j <= sayimiktari; j++)
		{
			if (sayi < enkucuksayi)
			{
				enkucuksayi = sayi;
			}
		}


	}


	cout << "En büyük sayı : " << enbuyuksayi << endl;
	cout << "En küçük sayı : " << enkucuksayi << endl;


}

void zaroyunu()
{
b:
	int n;
	cout << "Kaç el oynamak istiyorsunuz : "; cin >> n;

	srand(time(NULL));
	int skor;
	skor = 0;

	for (int i = 1; i <= n; i++)
	{

		int zar1 = rand() % 6 + 1;
		int zar2 = rand() % 6 + 1;

		cout << i << ". oyun " << "1. Kullanıcının değerleri :" << zar1 << endl;
		cout << i << ". oyun " << "2. Kullanıcının değerleri :" << zar2 << endl;
		cout << endl;
		if (zar1 > zar2)
		{
			skor++;
		}
		else if (zar2 > zar1)
		{
			skor--;
		}

	}

	if (skor > 0)
	{
		cout << "1. Oyuncu kazandı " << endl;
	}
	else if (skor < 0)
	{
		cout << "İkinci oyuncu kazandı " << endl;
	}

	else if (skor == 0)
	{
		cout << "berabere " << endl;
	}


	int islem3;
	cout << "tekrar oynamak için 1'e Çıkmak için 2'ye basınız :"; cin >> islem3;

	switch (islem3)
	{
	case 1: goto b; system("CLS");  break;
	case 2: cout << "Çıkış yaptınız ..." << endl; break;
	default:
		break;
	}

}

void asal()
{
	a:
	int sayi;
	int isle2;
	cout << "Kontrol etmek istediğiniz sayıyı giriniz. "; cin >> sayi;

	if (sayi == 0 || sayi == 1)
	{
		cout << "girdiğiniz sayı asal değildir." << endl;
		
	}

	for (int i = 2; i < sayi; i++)
	{
		if (sayi % i == 0)
		{
			cout << "Girdiğiniz sayı asal değildir.";
			cout << endl;
			break;
		}
		else
		{
			cout << "Girdiğiniz sayı asaldır" << endl;
			break;
		}


	}
	cout << "Tekrar hesaplama için 1'e basınız" << endl;
	cout << "Çıkmak için 2'ye basınız." << endl;
	cin >> isle2;

	switch (isle2)
	{
	case 1: system("CLS"); goto a; break;
	case 2: cout << "Çıkış yapıldı " << endl;

	default:cout << endl;
		break;
	}



}

void texta()
{
	ofstream dosya;
	string str1;
	cout << "Not defteri içinde yazılmasınız istedğiniz kelime : " << endl;
	cin >> str1;
	
	dosya.open("Merhaba.txt");
	dosya <<str1;
	dosya.close();
}



int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	system("color e5");
	MoveWindow(console, r.left, r.top, 700, 350, TRUE);
	SetConsoleTitle(TEXT("karma"));
	//HANDLE konsolrengi = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(konsolrengi, 6);
	//cout << "Test" << endl;
	//cout << endl;

c:
	//
	setlocale(LC_ALL, "Turkish");

	int islem, faktoriyeldeger1;
	int geri;
	int i = 1;
	cout << "**********************" << endl;
	cout << "1. Faktöriyel hesabı " << endl;
	cout << "2. Sayı bulma oyunu " << endl;
	cout << "3. Girilen sayılardan en büyük değeri bulan program" << endl;
	cout << "4. İki kişilik zar atma oyunu" << endl;
	cout << "5. Girilen iki sayının ekokunu hesaplama" << endl;
	cout << "6. Asal sayı testi" << endl;
	cout << "7. Notepad dosyası oluşturur" << endl;
	cout << "8. Basit Struct örneği " << endl;
	cout << "**********************" << endl;


	cout << "Yapmak istediğiniz işlemi seçiniz : "; cin >> islem;
	switch (islem)
	{
	case 1: cout << "Faktöriyelini almak istediğiniz sayıyı giriniz :  "; cin >> faktoriyeldeger1; faktoriyel(faktoriyeldeger1); break;
	case 2: oyun(); break;
	case 3: siralama(); break;
	case 4: zaroyunu(); break;
	case 5: ekokhesaplama(); break;
	case 6: asal(); break;
	case 7: texta(); break;
	case 8: deneme(); break;
	default:
		break;
	}

	cout << endl;
	cout << "uygulamayı baştan başlatmak istiyor musunuz ? evet için 1'i hayır için 2'yi tuşlayınız. "; cin >> geri;

	switch (geri)
	{
	case 1: system("CLS"); goto c; break;
	case 2: cout << "Çıkış yaptınız..." << endl; break;
	default:
		break;
	}

	cout << endl;
	system("pause");
}



