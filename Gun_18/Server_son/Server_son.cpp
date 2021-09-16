#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<vector>
#include<Windows.h>
#include <sstream>
#include"Kullanici_fonk.h"

#pragma comment (lib , "ws2_32.lib")

using namespace std;

void baslat()
{
	char buf[4096];
	vector<MusteriHesap> Hesaplar;
	vector<int> HesapNumaralari;
	vector<string> islemdeger;
	vector<double> Para_deger;
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
		listen(listening, 5);
		// Baglantı bekleme;
		sockaddr_in client;
		int clientSize = sizeof(client);

		SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &clientSize);

		char host[NI_MAXHOST]; // Kullanici Adi
		char service[NI_MAXSERV]; // Port Numarasi

		//ZeroMemory(host, NI_MAXHOST); // memset*
		//ZeroMemory(service, NI_MAXSERV);

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

		string durum_mesaj = "Islem basarili";
		string durum_mesaj_ngt = "Islem basarisiz";

		while (1)
		{
		b:

			cout << "bekleniyor " << endl;

			//ZeroMemory(buf, 4096);
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

				int byteRecieved = recv(ClientSocket, buf, 4096, 0);
				string alinan_hesapNo = string(buf, 0, byteRecieved);

				stringstream deger(alinan_hesapNo);
				int x;
				deger >> x;
				int byte_sifre = recv(ClientSocket, buf, 4096, 0);
				string alinan_sifre = string(buf, 0, byte_sifre);
				//send(ClientSocket, buf, byte_sifre + 1, 0);

				hesap_islem.Hesap_Kontrol(x, alinan_sifre);
				if (hesap_islem.mesaj3 == "1")
				{
					int mesajsinyali1 = send(ClientSocket, durum_mesaj.c_str(), durum_mesaj.size() + 1, 0);
					int mesajsinyali = send(ClientSocket, hesap_islem.mesaj3.c_str(), hesap_islem.mesaj3.size() + 1, 0);
				}
				else
				{

					int mesajsinyali3 = send(ClientSocket, durum_mesaj_ngt.c_str(), durum_mesaj_ngt.size() + 1, 0);
					int mesajsinyali2 = send(ClientSocket, hesap_islem.mesaj3.c_str(), hesap_islem.mesaj3.size() + 1, 0);
					goto b;
				}
				hesap_islem.mesaj3 = "a";
				
				do
				{
					hesap_islem.hesap_bilgi_gonder(x);
					int send_isim = send(ClientSocket, hesap_islem.islemler.c_str(), hesap_islem.islemler.size() + 1, 0);

					recv(ClientSocket, buf, 4096, 0);
					if (string(buf, 0, byteRecieved) == "1") // Para yatirma islemi
					{

						int byte_yatirilan = recv(ClientSocket, buf, 4096, 0);
						string degerpara = string(buf, 0, byte_yatirilan);
						stringstream deger1(degerpara);
						int y;
						deger1 >> y;
						x -= 1;
						hesap_islem.para_yatir(x, y);
						x += 1;
						if (hesap_islem.hata_kontrol == "0")
						{

						}

						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();

					}// Para yatirma islemi
					else if (string(buf, 0, byteRecieved) == "2") // Para cekme islemi
					{
						///	ZeroMemory(buf, 4096);
						int byte_cekilen = recv(ClientSocket, buf, 4096, 0);
						string cekilecek_deger = string(buf, 0, byte_cekilen);

						stringstream cekilecek_miktar(cekilecek_deger);
						int para_deger;
						cekilecek_miktar >> para_deger;

						x -= 1;
						hesap_islem.para_cek(x, para_deger);
						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();
						x += 1;
					} // Para cekme islemi

					else if (string(buf, 0, byteRecieved) == "3")
					{

						int byte_gelen_no = recv(ClientSocket, buf, 4096, 0);
						string gelen_hesap_no = string(buf, 0, byte_gelen_no);

						stringstream deger(gelen_hesap_no);
						int gonderilecek_hesap;
						deger >> gonderilecek_hesap;
						gonderilecek_hesap -= 1;

						int byte_havale_edilen = recv(ClientSocket, buf, 4096, 0);
						string havale_edilen = string(buf, 0, byte_havale_edilen);

						stringstream deger3(havale_edilen);
						int para1;
						deger3 >> para1;
						hesap_islem.transfer(x, gonderilecek_hesap, para1);
						int havale_gonder = send(ClientSocket, hesap_islem.havale_islem.c_str(), hesap_islem.havale_islem.size() + 1, 0);
						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();
					}

				} while (string(buf, 0, byteRecieved) != "4");

			}
			
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
	system("color 02");

	cout << "Server Baslatildi:" << endl;

	baslat();
	system("pause");
}