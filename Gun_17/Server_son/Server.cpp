#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<vector>
#include<Windows.h>
#include <sstream>
#include"Server.h"
#include"Kullanici_fonk.h"


using namespace std;

MusteriHesap hesap_islem;


void Server_mesaj::server_baslat()
{
	
}

void Server_mesaj::server_islem()
{
	if (wsOk != 0)
	{
		cerr << "Server baslatilamadi!" << endl;
		return;
	}
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
	while (1)
	{
		system("cls");
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
			//string client_mesaj = "Server'dan Client'a";
			//int senddata = send(ClientSocket, client_mesaj.c_str(), client_mesaj.size() + 1, 0);
			int byteRecieved = recv(ClientSocket, buf, 4096, 0);
			string alinan_hesapNo = string(buf, 0, byteRecieved);

			stringstream deger(alinan_hesapNo);
			int x;
			deger >> x;
			int byte_sifre = recv(ClientSocket, buf, 4096, 0);
			string alinan_sifre = string(buf, 0, byte_sifre);
			send(ClientSocket, buf, byte_sifre + 1, 0);

			hesap_islem.Hesap_Kontrol(x, alinan_sifre);

			hesap_islem.Veri_guncelle();
			recv(ClientSocket, buf, 4096, 0);

			do
			{

				if (string(buf, 0, byteRecieved) == "1") // Para yatirma islemi
				{
					//	ZeroMemory(buf, 4096);
					int byte_yatirilan = recv(ClientSocket, buf, 4096, 0);
					string degerpara = string(buf, 0, byte_yatirilan);
					stringstream deger1(degerpara);
					int y;
					deger1 >> y;
					x -= 1;
					hesap_islem.para_yatir(x, y);
					hesap_islem.vektor_ekle();
					hesap_islem.Veri_guncelle();
					x += 1;

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
					hesap_islem.vektor_ekle();
					hesap_islem.Veri_guncelle();
					gonderilecek_hesap += 1;
				}

				recv(ClientSocket, buf, 4096, 0);

			} while (string(buf, 0, byteRecieved) != "4");

		}
		else
		{
			cout << "Ana Menuye donuldu" << endl;
			send(ClientSocket, buf, byteRecieved + 1, 0);
		}

		//ZeroMemory(buf, 4096);
	}

}