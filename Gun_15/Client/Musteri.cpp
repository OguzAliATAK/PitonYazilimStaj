#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include"Menu.h"
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
		Sleep(950);
		exit(-1);
		closesocket(sock);
		WSACleanup();
		return;
	}
	cout << "Server'a baglandi" << endl;
}

void Client1::soket_islem()
{
	Menuler menu1;
	menu1.kontrol_menusu();
	char buf[4096];
	char bufhesap[4096];
	string kullanicigiris,sifre;
	int hesapno;
	cout << ">";
	cin >> kullanicigiris;
	do
	{
		
		if (kullanicigiris.size() > 0)
		{
			int sendResult = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				//int bytesRecieved = recv(sock, buf, 4096, 0);
				if (kullanicigiris == "1")
				{
					ZeroMemory(buf, 4096);
					string hesapnumara, hesapsifre;
					cout << "Hesap nuamarasini giriniz : "; cin >> hesapnumara;
					int sendResult1 = send(sock, hesapnumara.c_str(), hesapnumara.size() + 1, 0);

					cout << "Sifrenizi giriniz  : "; cin >> hesapsifre;
					
					int sendResult2 = send(sock, hesapsifre.c_str(), hesapsifre.size() + 1, 0);
					ZeroMemory(buf, 4096);

					cout << "> "; cin >> kullanicigiris;

					if (kullanicigiris == "10")
					{
						ZeroMemory(buf, 4096);
						string yatirilacak_para;
						string islem = "cekilecek para miktari:";
						cout << "Cekilecek para miktarini giriniz : ";
						cin >> yatirilacak_para;
						
						int sendResult3 = send(sock, yatirilacak_para.c_str(), yatirilacak_para.size() + 1, 0);
						
					}

				}
				else if (kullanicigiris == "2")
				{
					
				}
				else if (kullanicigiris == "3")
				{
					exit(-1);
				}
				ZeroMemory(buf, 4096);
			}
		}

	} while (1);
}

void Client1::soket_kapat()
{
	closesocket(sock);
	WSACleanup();
}