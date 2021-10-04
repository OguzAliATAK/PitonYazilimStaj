#include"Server.h"

using namespace std;


void Sunucu::durum_kontrol()
{

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
}

void Sunucu::Sunucu_dinle()
{
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(5004);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, 5);

	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &clientSize);
}

void Sunucu::Sunucu_kabul()
{

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	}

	closesocket(listening);

}