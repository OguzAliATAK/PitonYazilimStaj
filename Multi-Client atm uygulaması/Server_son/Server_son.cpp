#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<thread>
#include<vector>
#include<Windows.h>
#include <sstream>
#include"Kullanici_fonk.h"

#pragma comment (lib , "ws2_32.lib") // qt.pro

using namespace std;
int Kullanici_sayisi = 1;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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

		WSADATA wsData;
		WORD ver = MAKEWORD(2, 2);

		int wsOk = WSAStartup(ver, &wsData);
		if (wsOk != 0)
		{
			cerr << "Server baslatilamadi!" << endl;
			return;
		}

		SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
		if (listening == INVALID_SOCKET)
		{
			cerr << "Soket olusturulamadi" << endl;
			return;
		}

		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(5004);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;

		bind(listening, (sockaddr*)&hint, sizeof(hint));
		listen(listening, 5);

		sockaddr_in client;
		int clientSize = sizeof(client);

		SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &clientSize);

		char host[NI_MAXHOST]; // Kullanici Adi
		char service[NI_MAXSERV]; // Port Numarasi
		
	yeni:
		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		}

		closesocket(listening);

		string durum_mesaj = "Islem basarili";
		string durum_mesaj_ngt = "Islem basarisiz";

		while (1)
		{
		b:
			
		
			int byteRecieved = recv(ClientSocket, buf, 4096, 0);

			if (byteRecieved == SOCKET_ERROR)
			{
				break;
			}
			if (byteRecieved == 0)
			{
				break;
			}
	

			if (string(buf, 0, byteRecieved) == "1") // Kullanici girisi 
			{

				int byteRecieved = recv(ClientSocket, buf, 4096, 0);
				string alinan_hesapNo = string(buf, 0, byteRecieved);

				stringstream deger(alinan_hesapNo);
				int Hesap_Numara;
				deger >> Hesap_Numara;
				int byte_sifre = recv(ClientSocket, buf, 4096, 0);
				string alinan_sifre = string(buf, 0, byte_sifre);
				hesap_islem.Hesap_Kontrol(Hesap_Numara, alinan_sifre);
				if (hesap_islem.kontrol_mesaj == "1")
				{
					int mesajsinyali = send(ClientSocket, hesap_islem.kontrol_mesaj.c_str(), hesap_islem.kontrol_mesaj.size() + 1, 0);
					int mesajsinyali1 = send(ClientSocket, durum_mesaj.c_str(), durum_mesaj.size() + 1, 0);

				}
				else
				{
					int mesajsinyali2 = send(ClientSocket, hesap_islem.kontrol_mesaj.c_str(), hesap_islem.kontrol_mesaj.size() + 1, 0);
					int mesajsinyali3 = send(ClientSocket, durum_mesaj_ngt.c_str(), durum_mesaj_ngt.size() + 1, 0);
					goto b;
				}

				hesap_islem.kontrol_mesaj = "a";
				SetConsoleTextAttribute(hConsole, 14);
				cout << "Giris yapan port : " << service << endl;
				
				cout << "Kullanici sayisi : " << Kullanici_sayisi << endl;
				Kullanici_sayisi++;
				
				do
				{
					
					SetConsoleTextAttribute(hConsole, 11);
					ZeroMemory(buf, 4096);

					hesap_islem.hesap_bilgi_gonder(Hesap_Numara);
					int send_isim = send(ClientSocket, hesap_islem.islemler.c_str(), hesap_islem.islemler.size() + 1, 0);

					recv(ClientSocket, buf, 4096, 0);
					if (string(buf, 0, byteRecieved) == "1") // Para yatirma islemi
					{
						int byte_yatirilan = recv(ClientSocket, buf, 4096, 0);
						string degerpara = string(buf, 0, byte_yatirilan);
						stringstream deger1(degerpara);
						double yatirilan_miktar;
						deger1 >> yatirilan_miktar;
						Hesap_Numara -= 1;
						hesap_islem.para_yatir(Hesap_Numara, yatirilan_miktar);
						Hesap_Numara += 1;

						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();
						cout << "Port : " << service << " - Para yatir " << endl;
						
						int islem_durum = send(ClientSocket, durum_mesaj.c_str(), durum_mesaj.size() + 1, 0);

					}// Para yatirma islemi

					else if (string(buf, 0, byteRecieved) == "2") // Para cekme islemi
					{
						int byte_cekilen = recv(ClientSocket, buf, 4096, 0);
						string cekilecek_deger = string(buf, 0, byte_cekilen);

						stringstream cekilecek_miktar(cekilecek_deger);
						double para_deger;
						cekilecek_miktar >> para_deger;

						Hesap_Numara -= 1;
						hesap_islem.para_cek(Hesap_Numara, para_deger);
						hesap_islem.vektor_ekle();
						hesap_islem.Veri_guncelle();
						Hesap_Numara += 1;
						cout << "Port : " << service << " - Para cek " << endl;

						if (hesap_islem.hata_kontrol == "0")
						{
							cout << "Hata " << endl;
							int islem_durum1 = send(ClientSocket, durum_mesaj_ngt.c_str(), durum_mesaj_ngt.size() + 1, 0);
						}
						else if (hesap_islem.hata_kontrol == "1")
						{
							int islem_durum = send(ClientSocket, durum_mesaj.c_str(), durum_mesaj.size() + 1, 0);
						}

						
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
						double havale_edilen_para;
						deger3 >> havale_edilen_para;
						hesap_islem.transfer(Hesap_Numara, gonderilecek_hesap, havale_edilen_para);
						gonderilecek_hesap += 1;
						if (hesap_islem.hata_kontrol == "0")
						{
							cout << "Port : " << service << " Basarisiz havale islemi  " << endl;
							int hata_gonder = send(ClientSocket, hesap_islem.hata_kontrol.c_str(), hesap_islem.hata_kontrol.size() + 1, 0);
						}
						else
						{
							int havale_gonder = send(ClientSocket, hesap_islem.havale_islem.c_str(), hesap_islem.havale_islem.size() + 1, 0);
							hesap_islem.vektor_ekle();
							hesap_islem.Veri_guncelle();
							cout << "Port : " << service << " Basarili havale islemi  " << endl;
							int havale_gonder1 = send(ClientSocket, hesap_islem.havale_islem.c_str(), hesap_islem.havale_islem.size() + 1, 0);
							int islem_durum = send(ClientSocket, durum_mesaj.c_str(), durum_mesaj.size() + 1, 0);
						}
						hesap_islem.hata_kontrol = "1";
					}
					Sleep(50);
					if (string(buf, 0, byteRecieved) == "e")
					{
						hesap_islem.sifre_yenile();
						hesap_islem.Veri_guncelle();
						SetConsoleTextAttribute(hConsole, 12);
						cout << "Cikis yapan port : " << service << endl;
						SetConsoleTextAttribute(hConsole, 11);
						Kullanici_sayisi--;
						
					}

					else if (string(buf, 0, byteRecieved) == "")
					{
						hesap_islem.sifre_yenile();
						hesap_islem.Veri_guncelle();
						SetConsoleTextAttribute(hConsole, 12);
						cout << "Cikis yapan port : " << service << endl;
						SetConsoleTextAttribute(hConsole, 11);
						Kullanici_sayisi--;
						
						goto yeni;
					}
					SetConsoleTextAttribute(hConsole, 11);
				} while (string(buf, 0, byteRecieved) != "e");
			}
		}
		Sleep(40);
	} while (1);
}

void main()
{
	MusteriHesap hesap_islem;
	hesap_islem.veridondur();
	RECT r;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &r);
	MoveWindow(console, r.right, r.top, 600, 500, TRUE);
	system("title Sunucu");
	system("color 02");

	cout << "Server Baslatildi:" << endl;

	thread kullanici1(baslat);
	thread kullanici2(baslat);
	thread kullanici3(baslat);
	thread kullanici4(baslat);

	kullanici1.join();


	return;
	system("pause");
}