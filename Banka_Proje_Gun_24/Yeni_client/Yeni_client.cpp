#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<Windows.h>
#include"Musteri_cl.h"

#pragma comment(lib, "ws2_32.lib ")

using namespace std;

int main()
{
	RECT r;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &r); 
	MoveWindow(console, r.left, r.top, 500, 350, TRUE);
	system("title Client");

	Client1 clienta;

	clienta.soket_baslat();
	clienta.soket_islem();
	clienta.soket_kapat();

	system("pause");
	return 0;
}