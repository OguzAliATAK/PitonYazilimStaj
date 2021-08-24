#include<iostream>
#include<string>
#include<locale>
#include<math.h>
using namespace std;



void girileceksayilar(int a)
{

	
	string str1 = ":";
	string str2;
	int fonk;
	int deger;
	fonk = 0;


	cout << a << str1;
	cout << endl;
	int  dizi2[6];


	cout << "Fonksiyon :   "  << "dizi2[0] - dizi2[1] + (dizi2[2] * dizi2[3]) / (dizi2[4] * dizi2[5])" << endl;
	

	

	for (int  i = 0; i < 6; i++)
	{
		 
		cout << i + 1 << ". değeri giriniz : ";
		cin >> dizi2[i];

	}

	for (int i = 0; i < 6; i++)
	{
		cout << endl;
		cout << i + 1 << ". değeri: "<< dizi2[i] ;

	}
	fonk = (dizi2[0] - dizi2[1] + (dizi2[2] * dizi2[3]) / (dizi2[4] * dizi2[5]));

	cout << endl;
	cout << fonk;
	cout << endl;

	if (a != fonk)
	{
		cout << "************" << endl;
		cout << "Girdiğiniz sayılar fonksayona göre hedef sayıya eşit değil. " << endl;
		cout << "Girdiğiniz değerlere göre fonksiyonun değeri : " << fonk << endl;
		cout << "************" << endl;
	}

	if (a == fonk)
	{
		cout << "************" << endl;
		cout << "Girdiğiniz sayılar fonksayona göre hedef sayıya eşittir. " << endl;
		cout << "************" << endl;
	}



	
	

}

int main()
{
	setlocale(LC_ALL, "Turkish");
	int hedefsayi;
	int islem;
	string toplam;
a:

	

	
	cout << "Hedef sayıyı giriniz :";
	cin >> hedefsayi;
	girileceksayilar(hedefsayi);

	cout << "Yeniden değer girmek için 1'e basınız." << endl;
	cin >> islem;
	switch (islem)
	{
	case 1: goto a;
	default:
		break;
	}

	cout << endl;

	system("PAUSE");






}