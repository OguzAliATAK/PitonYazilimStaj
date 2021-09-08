#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include"Musteri.h"

#pragma comment(lib, "ws2_32.lib ")

using namespace std;

int main()
{
	system("color e5");
	Client1 clienta;

	clienta.soket_baslat();
	clienta.soket_islem();
	clienta.soket_kapat();

	system("pause");
	return 0;

}
