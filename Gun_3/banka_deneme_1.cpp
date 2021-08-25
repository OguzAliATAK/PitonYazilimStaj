#include<iostream>
#include<locale>
#include "bankaclass.h"


using namespace std;

int main()
{
	setlocale(LC_ALL,"Turkish");
	string kullan;
	string giris;
	Bankahesap kullanici1,kullanici2;
	kullanici1.kullaniciadi = "Oğuz ";
	kullanici1.hesaptakipara = 6854;

	kullanici2.kullaniciadi = "Mehmet";
	kullanici2.hesaptakipara = 1515;

	kullanici1.anamenu();
	kullanici1.islemmenusu();
	kullanici1.sifrekontrol( kullan);



}