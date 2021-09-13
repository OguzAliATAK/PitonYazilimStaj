#include<iostream>
#include<WS2tcpip.h>
#include<string>

#pragma comment(lib, "ws2_32.lib ")

using namespace std;


class Client1
{
public:

	string Host = "127.0.0.1";
	int port = 5004;

	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int wsresult = WSAStartup(ver, &data);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET serversock = socket(AF_INET, SOCK_STREAM, 0);

	void soket_baslat();
	void soket_islem();
	void soket_kapat();

	

};