#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class MusteriHesap
{
private:
	static int SuankiHesapNo;

	bool open = true;
	int HesapNo = ++SuankiHesapNo;
	double bakiye = 0;
	string isim, soyad, sifre;

public:

	string isim_kontrol;
	string sifre_kontrol;
	int HesapNo_kontrol;

	MusteriHesap() {}
	MusteriHesap(string, string, string, int);

	void para_yatir(double);
	void para_cek(double);
	void transfer(MusteriHesap, double);

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
	double get_bakiye()
	{
		return bakiye;
	}
	int get_HesapNo()
	{
		return HesapNo;
	}

	void Kullanici_kontrol();
	void Veri_guncelle();
	void Hesap_Kontrol();
	void Ana_menu_islem();
	void Admin_giris();

	void VeriTabani_erisimi();

	void close();
	bool isOpen();

	friend istream& operator >> (istream& in, MusteriHesap& Hesap1);
	friend ostream& operator << (ostream& out, MusteriHesap& Hesap1);

	friend ifstream& operator >> (ifstream& in, MusteriHesap& Hesap1);
	friend ofstream& operator << (ofstream& out, MusteriHesap& Hesap1);

	void vektor();
	void islem(int);


};