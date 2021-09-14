#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<vector>
#include<Windows.h>
#include <sstream>
#include"KullaniciVeri.h"
#include"Menu.h"

#pragma comment (lib , "ws2_32.lib")

using namespace std;

void veri_cek()
{
}


void baslat()
{
	vector<MusteriHesap> Hesaplar;
	vector<int> HesapNumaralari;
	vector<string> islemdeger;
	vector<double> Para_deger;
	Menuler menu1;
	MusteriHesap hesap_islem;
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
			system("cls");
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
		ZeroMemory(buf, 4096);
		while (1)
		{
			ZeroMemory(buf, 4096);
			int a = 0;
			// 
			int byteRecieved = recv(ClientSocket, buf, 4096, 0);

			if (byteRecieved == SOCKET_ERROR)
			{
				system("cls");
				cerr << "Kullanici cikis yapti !" << endl;
				system("cls");
				cerr << "Kullanici girisi bekleniyor " << endl;
				break;
			}
			if (byteRecieved == 0)
			{
				system("cls");
				cout << "Kullanici cikis yapti" << endl;
				break;
			}

			if (string(buf, 0, byteRecieved) == "1") // Kullanici girisi 
			{
					ZeroMemory(buf, 4096);
					int byteRecieved = recv(ClientSocket, buf, 4096, 0);
					string alinan_hesapNo = string(buf, 0, byteRecieved);
					cout << alinan_hesapNo << endl;

					stringstream deger(alinan_hesapNo);
					int x;
					deger >> x;

					ZeroMemory(buf, 4096);
					recv(ClientSocket, buf, 4096, 0);
					string alinan_sifre = string(buf, 0, byteRecieved);
					send(ClientSocket, buf, byteRecieved + 6, 0);

					hesap_islem.Hesap_Kontrol(x, alinan_sifre);

					ZeroMemory(buf, 4096);
					recv(ClientSocket, buf, 4096, 0);

					if (string(buf, 0, byteRecieved) == "1") // Para yatirma islemi
					{
						
						ZeroMemory(buf, 4096);
						recv(ClientSocket, buf, 4096, 0);
						string degerpara = string(buf, 0, byteRecieved);
						
						stringstream deger1(degerpara);
						int y;
						deger1 >> y;
						x -= 1;
							
						hesap_islem.para_yatir(x,y);
						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();
						
					}// Para yatirma islemi
					else if (string(buf, 0, byteRecieved) == "2") // Para cekme islemi
					{
						ZeroMemory(buf, 4096);
						recv(ClientSocket, buf, 4096, 0);
						string cekilecek_deger = string(buf, 0, byteRecieved);

						stringstream cekilecek_miktar(cekilecek_deger);
						int para_deger;
						cekilecek_miktar >> para_deger;

						x -= 1;
						hesap_islem.para_cek(x,para_deger);
						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();
					} // Para cekme islemi

					else if (string(buf, 0, byteRecieved) == "3")
					{
						ZeroMemory(buf, 4096);
						int byteRecieved = recv(ClientSocket, buf, 4096, 0);
						string gelen_hesap_no = string(buf, 0, byteRecieved);
						cout << gelen_hesap_no << endl;

						stringstream deger(gelen_hesap_no);
						int gonderilecek_hesap;
						deger >> gonderilecek_hesap;
						gonderilecek_hesap -= 1;

						ZeroMemory(buf, 4096);
						recv(ClientSocket, buf, 4096, 0);

						string havale_edilen = string(buf, 0, byteRecieved);
						cout << havale_edilen << endl;

						stringstream deger3(havale_edilen);
						int para1;
						deger3 >> para1;
						hesap_islem.transfer(x,gonderilecek_hesap, para1);
						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();

						ZeroMemory(buf, 4096);
						recv(ClientSocket, buf, 4096, 0);
					}



					else
					{
						cout << "Gecerli islem secilmedi";
					}
					

			}
			else if (string(buf, 0, byteRecieved) == "2")
			{
				hesap_islem.VeriTabani_erisimi();
			}

			cout << "Ana Menuye donuldu" << endl;
			send(ClientSocket, buf, byteRecieved + 1, 0);

			ZeroMemory(buf, 4096);
		}
	} while (1);
}

void main()
{
	MusteriHesap hesapislem;
	hesapislem.veridondur();
	RECT r;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.right, r.top, 600, 500, TRUE);
	system("color e5");

	cout << "Server Baslatildi:" << endl;

	baslat();
	system("pause");
}