#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include"Musteri_cl.h"
#include"Menu.h"

#pragma comment(lib, "ws2_32.lib ")

using namespace std;


void Client1::kullanici_girisi()
{
	ZeroMemory(buf, 4096);
	string hesapnumara, hesapsifre;
	cout << "Hesap nuamarasini giriniz : "; cin >> hesapnumara;
	int sendResult1 = send(sock, hesapnumara.c_str(), hesapnumara.size() + 1, 0);

	cout << "Sifrenizi giriniz  : "; cin >> hesapsifre;

	int sendResult2 = send(sock, hesapsifre.c_str(), hesapsifre.size() + 1, 0);
	ZeroMemory(buf, 4096);
	
}

void Client1::Havale_islem()
{
	ZeroMemory(buf, 4096);
	string gonderilecek_numara;
	string para_deger;
	cout << "Havale yapacagýnýz hesap numarasini giriniz :"; cin >> gonderilecek_numara;
	int Sendnumara = send(sock, gonderilecek_numara.c_str(), gonderilecek_numara.size() + 1, 0);

	cout << "Gonderilecek miktari giriniz : "; cin >> para_deger;
	int SendPara_deger = send(sock, para_deger.c_str(), para_deger.size() + 1, 0);
	ZeroMemory(buf, 4096);
}

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
	char buf[4096];
	string kullanicigiris, sifre;
	int hesapno;
	Menuler menuarayuz;
	menuarayuz.kontrol_menusu();
	do
	{
		system("cls");
		menuarayuz.kontrol_menusu();
		cout << ">";
		cin >> kullanicigiris;
		if (kullanicigiris.size() > 0)
		{
			int sendResult = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				//int bytesRecieved = recv(sock, buf, 4096, 0);
					if (kullanicigiris == "1")
					{
						system("cls");
						kullanici_girisi();
						Sleep(500);
						menuarayuz.ana_menu();
						ZeroMemory(buf, 4096);
						cout << "Isleminizi seciniz : "; cin >> kullanicigiris;
						int sendveri = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
						if (kullanicigiris == "1")
						{
							ZeroMemory(buf, 4096);
							cout << "yatirmak istediginiz para miktarini giriniz :";
							cin >> kullanicigiris;
							int sendpara = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
						}
						else if (kullanicigiris == "2")
						{
							ZeroMemory(buf, 4096);
							cout << "Cekmek istediginiz para miktarini giriniz :";
							cin >> kullanicigiris;

							int sendpara = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
						}
						else if (kullanicigiris == "3")
						{
							Havale_islem();
						}

					}
					else if (kullanicigiris == "3")
					{
						cout << "Cikis yapiliyor";
						Sleep(750);
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