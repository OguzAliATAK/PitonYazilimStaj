#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<vector>

#pragma comment (lib , "ws2_32.lib")

using namespace std;

class Server_mesaj
{
public:

	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &wsData);
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST]; // Kullanici Adi
	char service[NI_MAXSERV]; // Port Numarasi
	char buf[4096];

	void server_baslat();
	void server_islem();
	


};