#include<iostream>


using namespace std;


class Hesap {
private:

	string isim;
	string sifre;
	int hesap_no;
	double bakiye;
	double gonderilecek_para;
	double cekilecek_para;
	double yatirilacak_para;

public:
	
	double komisyon_orani = 0.02;
	double komisyon = 0;
	int para_miktari = 0;
	
	Hesap()
	{

	}
	

	Hesap(string, string, double);
	


	void set_isim(string isim)
	{
		this->isim = isim;
	}
	void set_sifre(string sifre)
	{
		this->sifre = sifre;
	}
	void set_hesap_no(double hesap_no)
	{
		this->hesap_no = hesap_no;
	}
	void set_gonderilecek_para(double gonderilecek_para)
	{
		this->gonderilecek_para = gonderilecek_para;
	}
	void set_cekilecek_para(double cekilecek_para)
	{
		this->cekilecek_para = cekilecek_para;
	}
	void set_yatirilacak_para(double yatirilacak_para)
	{
		this->yatirilacak_para = yatirilacak_para;
	}
	void set_bakiye(double bakiye)
	{
		this->bakiye = bakiye;
	}


	string get_isim()
	{
		return isim;
	}
	string get_sfire()
	{
		return sifre;
	}
	int get_hesap_no()
	{
		return hesap_no;
	}
	double get_gonderilecek_para()
	{
		return gonderilecek_para;
	}
	double get_cekilecek_para()
	{
		return cekilecek_para;
	}
	double get_yatirilacak_para()
	{
		return yatirilacak_para;
	}
	double get_bakiye()
	{
		return bakiye;
	}

	void hesap_olustur(string, string, double);
	void hesap_bilgi();
	void para_cek(double);
	void para_yatir(double);
	void para_transfer( double);
	void islem(int);


};