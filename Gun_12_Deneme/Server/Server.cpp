#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<string>
#include"Menu.h"

#pragma comment (lib , "ws2_32.lib")

using namespace std;

void baslat()
{
	Menuler menu1;
	do
	{
		int connfd = 0;

		// Soketi baslat;
		WSADATA wsData;
		WORD ver = MAKEWORD(2, 2);

		int wsOk = WSAStartup(ver, &wsData);
		if (wsOk != 0)
		{
			cerr << "Server baslatilamadi!" << endl;
			return;
		}
		// Soket olusturma;
		SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
		if (listening == INVALID_SOCKET)
		{
			cerr << "Soket olusturulamadi" << endl; 
			return;
		}
		// ip adresini ve portu çek ;
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(5004);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;
	
		bind(listening, (sockaddr*)&hint, sizeof(hint));
		// Dinleme kısmı;;
		listen(listening, SOMAXCONN);
		// Baglantı bekleme;
		sockaddr_in client;
		int clientSize = sizeof(client);

		SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &clientSize);

		char host[NI_MAXHOST]; // Kullanici Adi
		char service[NI_MAXSERV]; // Port Numarasi

		ZeroMemory(host, NI_MAXHOST); // menset*
		ZeroMemory(service, NI_MAXSERV);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			
			cout << host << ", Port'a baglandi " << service << endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			cout << host << " Porta baglandi " <<
				ntohs(client.sin_port) << endl;
		}
		closesocket(listening);

		char buf[4096];
		while (1)
		{
			ZeroMemory(buf, 4096);
			// 
			int byteRecieved = recv(ClientSocket, buf, 4096, 0);
			if (byteRecieved == SOCKET_ERROR)
			{
				cerr << "Kullanici cikis yapti !" << endl;
				break;
			}
			if (byteRecieved == 0)
			{
				system("cls");
				cout << "Kullanici cikis yapti" << endl;
				break;
			}
			cout << string(buf, 0, byteRecieved) << endl;
			send(ClientSocket, buf, byteRecieved + 1, 0);
			ZeroMemory(buf, 4096);
		}
	} while (1);
}

void main()
{
	system("color e5");
	cout << "Server Baslatildi:" << endl;
	baslat();
	system("pause");
}