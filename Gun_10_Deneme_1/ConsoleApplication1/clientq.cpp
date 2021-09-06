#include<iostream>
#include<WS2tcpip.h>
#include<string>

#pragma comment(lib, "ws2_32.lib ")

using namespace std;

void main()
{

	string Host = "127.0.0.1";
	int port = 5004;

	// Baslangic

	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int wsresult = WSAStartup(ver, &data);
	if (wsresult != 0)
	{
		cerr << "Baslatilamiyor " << wsresult << endl;
		return;
	}
	// Scoket olusturma

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
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

	//
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	
	char buf[4096];
	string Kullanici_girisi;

	do
	{

		cout << ">";
		cin >> Kullanici_girisi;

		if (Kullanici_girisi.size() > 0)
		{
			//send the text
			int sendResult = send(sock, Kullanici_girisi.c_str(), Kullanici_girisi.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesRecieved = recv(sock, buf, 4096, 0);
				if (bytesRecieved)
				{
					cout << string(buf, 0, bytesRecieved) << endl;
				}
			}
		}


	} while (Kullanici_girisi.size() > 0);

	//
	closesocket(sock);
	WSACleanup();


}
