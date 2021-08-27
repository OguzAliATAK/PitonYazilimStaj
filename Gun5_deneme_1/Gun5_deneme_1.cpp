#include<iostream>
#include"Hesap.h"
#include"menu.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");
	
	Menuler menu;
	Hesap hesap1;
	

	
	menu.menu();
	hesap1.islem(1);
	


	system("Pause");
	return 0;
}