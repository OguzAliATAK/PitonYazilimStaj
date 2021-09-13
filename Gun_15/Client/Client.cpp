#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<Windows.h>
#include"Musteri.h"

#pragma comment(lib, "ws2_32.lib ")

using namespace std;

int main()
{
	RECT r;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 600, 300, TRUE);

	system("color e5");
	Client1 clienta;


	clienta.soket_baslat();
	clienta.soket_islem();
	clienta.soket_kapat();

	system("pause");
	return 0;

}
