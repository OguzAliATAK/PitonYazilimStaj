#include<iostream>
#include<winsock.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>

#pragma comment(lib, "ws2_32.lib ")

using namespace std;


class Client_kurulum
{
public:
	string kullanicigiris;

	string Host = "127.0.0.1";
	int port = 5004;
	int kontrol;
	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int soket_durumu = WSAStartup(ver, &data);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET serversock = socket(AF_INET, SOCK_STREAM, 0);
	char buf[4096];

	void soket_baslat();
	void soket_islem();
	void soket_kapat();

	void kullanici_girisi();
	void Havale_islem();


};