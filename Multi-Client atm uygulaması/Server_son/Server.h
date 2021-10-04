#include<iostream>
#include<WS2tcpip.h>

using namespace std;


class Sunucu
{
public:

	char buf[4096];
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST]; // Kullanici Adi
	char service[NI_MAXSERV]; // Port Numarasi

	void durum_kontrol();
	void Sunucu_dinle();
	void Sunucu_kabul();
};