#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include<WS2tcpip.h>

using namespace std;

class MusteriHesap
{
private:
	static int SuankiHesapNo;

	bool open = true;
	int HesapNo = ++SuankiHesapNo;
	double bakiye = 0;
	string isim, soyad, sifre, banka_adi;
public:

	string mesaj3 = "a";
	string para_mesaj = "0";
	double bakiye_deger = 0;
	string isim_kontrol;
	string sifre_kontrol;
	int  HesapNo_kontrol;
	double deger;
	double komisyon = 0.002;


	MusteriHesap() {}
	MusteriHesap(string, string, string, string, int);

	void para_yatir(int, double);
	void para_cek(int, double);
	void transfer(int, int, double);

	static void Set_SuankiHesapNo(int No)
	{
		if (No > 0)
		{
			SuankiHesapNo = No;
		}
	}


	void set_isim(string isim)
	{
		this->isim = isim;
	}
	void set_soyad(string soyad)
	{
		this->soyad = soyad;
	}
	void set_sifre(string sifre)
	{
		this->sifre = sifre;
	}
	void set_banka_adi(string banka_adi)
	{
		this->banka_adi = banka_adi;
	}
	void set_bakiye(double bakiye)
	{
		this->bakiye = bakiye;
	}


	string get_isim()
	{
		return isim;
	}
	string get_soyad()
	{
		return soyad;
	}
	string get_sifre()
	{
		return sifre;
	}
	string get_banka_adi()
	{
		return banka_adi;
	}
	double get_bakiye()
	{
		return bakiye;
	}
	int get_HesapNo()
	{
		return HesapNo;
	}

	void Veri_guncelle();
	void Hesap_Kontrol(int, string);
	void Admin_giris();
	void vektor_ekle();
	void veridondur();
	void hesapsayisi();

	void VeriTabani_erisimi();

	bool isEmpty(ifstream& pFile)
	{
		return pFile.peek() == ifstream::traits_type::eof();
	}

	void close();
	bool isOpen();

	friend ostream& operator << (ostream& out, MusteriHesap& Hesap1);

	friend ifstream& operator >> (ifstream& in, MusteriHesap& Hesap1);
	friend ofstream& operator << (ofstream& out, MusteriHesap& Hesap1);

	string mesaj2 = "22222";

	string degerler;

	char buf[4096];

	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &clientSize);

};