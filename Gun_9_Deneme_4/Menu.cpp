#include<iostream>
#include"Menu.h"

using namespace std;


void Menuler::ana_menu()
{

	cout << "***********" << endl;
	cout << "1. Sistemdeki hesaplari goster" << endl;
	cout << "2. Hesaba para yatir" << endl;
	cout << "3. Hesaptan Para cek" << endl;
	cout << "4. Transfer* // alici hesaba para ulasmiyor" << endl;
	cout << "7. Cikis" << endl;
	cout << "***********" << endl;
}

void Menuler::kontrol_menusu()
{
	cout << "***********" << endl;
	cout << "1. Giris yap" << endl;
	cout << "2. Admin girisi // Kullanici adi : Admin //sifre : 123" << endl;
	cout << "3. Cikis" << endl;
	cout << "***********" << endl;

}