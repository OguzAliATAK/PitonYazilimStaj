#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include"Musteri.h"

#pragma comment(lib, "ws2_32.lib ")

using namespace std;

void Client1::soket_baslat()
{
	if (wsresult != 0)
	{
		cerr << "Baslatilamiyor " << wsresult << endl;
		return;
	}
	// Scoket olusturma


	if (sock == INVALID_SOCKET)
	{
		cerr << "Hata : " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	//fill

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, Host.c_str(), &hint.sin_addr);

	//
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Server'a baglanilamadi" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

}

void Client1::soket_islem()
{
	char buf[4096];
	string kullanicigiris;
	do
	{
		cout << ">";
		cin >> kullanicigiris;
		if (kullanicigiris.size() > 0)
		{
			//send the text
			int sendResult = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesRecieved = recv(sock, buf, 4096, 0);
			}
		}

	} while (kullanicigiris != "15");
}

void Client1::soket_kapat()
{
	closesocket(sock);
	WSACleanup();
}
