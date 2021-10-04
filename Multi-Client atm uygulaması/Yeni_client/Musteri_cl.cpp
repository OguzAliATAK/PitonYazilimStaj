#include<iostream>
#include<string>
#include<sstream>
#include"Musteri_cl.h"
#include"Menu.h"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Client_kurulum::kullanici_girisi()
{
	string hesapnumara, hesapsifre;
	cout << "Hesap nuamarasini giriniz : "; cin >> hesapnumara;
	int sendResult1 = send(sock, hesapnumara.c_str(), hesapnumara.size() + 1, 0);
	cout << "Sifrenizi giriniz  : "; cin >> hesapsifre;
	int sendResult2 = send(sock, hesapsifre.c_str(), hesapsifre.size() + 1, 0);
}

void Client_kurulum::Havale_islem()
{
	ZeroMemory(buf, 4096);
	string gonderilecek_numara;
	string para_deger;
	cout << "Havale yapacaginiz hesap numarasini giriniz :"; cin >> gonderilecek_numara;
	int Sendnumara = send(sock, gonderilecek_numara.c_str(), gonderilecek_numara.size() + 1, 0);

	do
	{
		cout << "Gonderilecek miktari giriniz : "; cin >> para_deger;
		stringstream Para_gonderen(para_deger);
		Para_gonderen >> kontrol;
		if (kontrol < 0)
		{
			cout << "Hatali islem" << endl;
		}

	} while (kontrol < 0);

	int SendPara_deger = send(sock, para_deger.c_str(), para_deger.size() + 1, 0);
	ZeroMemory(buf, 4096);
}

void Client_kurulum::soket_baslat()
{
	if (soket_durumu != 0)
	{
		cerr << "Baslatilamiyor " << soket_durumu << endl;
		return;
	}
	if (sock == INVALID_SOCKET)
	{
		cerr << "Hata : " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);

	inet_pton(AF_INET, Host.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Sunucu Mesgul veya aktif degil." << endl;
		Sleep(2950);
		exit(-1);
		closesocket(sock);
		WSACleanup();
		return;
	}
	cout << "Sunucu'ya baglandi" << endl;
	Sleep(1550);
}

void Client_kurulum::soket_islem()
{
	char buf[4096];

	Menuler menuarayuz;
	menuarayuz.kontrol_menusu();
	do
	{
	a:
		system("cls");
		menuarayuz.kontrol_menusu();
		cout << ">";
		cin >> kullanicigiris;
		if (kullanicigiris.size() > 0)
		{
			int sendResult = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				if (kullanicigiris == "1")
				{
					kullanici_girisi(); 
					int gelen_sinyal = recv(sock, buf, 4096, 0);

					if (string(buf, 0, gelen_sinyal) != "1")
					{
						int islem_durum = recv(sock, buf, 4096, 0);
						SetConsoleTextAttribute(hConsole, 12);
						cout << string(buf, 0, islem_durum) << endl;
						SetConsoleTextAttribute(hConsole, 11);
						cout << "Ana Menuye donuluyor " << endl;
						Sleep(1500);
						goto a;
					}
					int islem_durum = recv(sock, buf, 4096, 0);
					SetConsoleTextAttribute(hConsole, 10);
					cout << string(buf, 0, islem_durum) << endl;
					SetConsoleTextAttribute(hConsole, 11);
					Sleep(1500);
					do
					{
						system("cls");

						int gelen_isim = recv(sock, buf, 4096, 0);
						SetConsoleTextAttribute(hConsole, 15);
						cout << "Kullanici : " << string(buf, 0, gelen_isim) << endl;
						SetConsoleTextAttribute(hConsole, 11);

						menuarayuz.ana_menu();

						cout << "Isleminizi seciniz : "; cin >> kullanicigiris;
						int sendveri = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
						if (kullanicigiris == "1")
						{
							int girilen_deger;
							do
							{
								cout << "yatirmak istediginiz para miktarini giriniz :";
								cin >> kullanicigiris;
								stringstream geek(kullanicigiris);
								geek >> girilen_deger;
								if (girilen_deger < 0)
								{
									cout << "Hata" << endl;
									Sleep(500);
								}

							} while (girilen_deger < 0);

							int sendpara = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
							int gelen_mesaj = recv(sock, buf, 4096, 0);
							SetConsoleTextAttribute(hConsole, 10);
							cout << string(buf, 0, gelen_mesaj) << endl;
							SetConsoleTextAttribute(hConsole, 11);
							Sleep(1500);

						}
						else if (kullanicigiris == "2")
						{
							//ZeroMemory(buf, 4096);
							int girilen_deger;
							do
							{
								cout << "Cekmek istediginiz para miktarini giriniz :";
								cin >> kullanicigiris;
								stringstream geek(kullanicigiris);
								geek >> girilen_deger;
								if (girilen_deger < 0)
								{
									cout << "Hata" << endl;
									Sleep(500);
								}

							} while (girilen_deger < 0);

							int sendpara = send(sock, kullanicigiris.c_str(), kullanicigiris.size() + 1, 0);
							int gelen_mesaj = recv(sock, buf, 4096, 0);
							SetConsoleTextAttribute(hConsole, 10);
							cout << string(buf, 0, gelen_mesaj) << endl;
							SetConsoleTextAttribute(hConsole, 11);
							Sleep(1500);
						}
						else if (kullanicigiris == "3")
						{
							Havale_islem();
							int gelenasd = recv(sock, buf, 4096, 0);
							if (string(buf, 0, gelenasd) == "0")
							{
								cout << "Hatali islem " << endl;
								Sleep(3500);
							}
							else
							{
								SetConsoleTextAttribute(hConsole, 14);
								int havale_gelen = recv(sock, buf, 4096, 0);
								cout << string(buf, 0, havale_gelen) << endl;
								SetConsoleTextAttribute(hConsole, 10);
								int gelen_mesaj = recv(sock, buf, 4096, 0);
								cout << string(buf, 0, gelen_mesaj) << endl;
								SetConsoleTextAttribute(hConsole, 11);
								Sleep(4500);
							}
						}
					} while (kullanicigiris != "e");
				}
			}
		}
	} while (1);
}
void Client_kurulum::soket_kapat()
{
	closesocket(sock);
	WSACleanup();
}