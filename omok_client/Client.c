#include "head.h"

void ErrorHandling(char *message);

SOCKET clntSock;
WSADATA wsaData;
SOCKADDR_IN servAddr;

char sAddr[15];
int sPort;
int nRcv;
unsigned int Addr;


SOCKET ConnectSocket()

{
	struct hostent *host;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("����");

	clntSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clntSock == INVALID_SOCKET)
		ErrorHandling("����");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("61.81.99.200");
	servAddr.sin_port = 9000;

	while (1)
	{
		Sleep(400);

		if (connect(clntSock, (void *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		{		
			printf("������.....\n");
		}
		else
		{
			gotoxy(38, 0);
			printf("����(%s)�� ���ӿϷ�.....\n", inet_ntoa(servAddr.sin_addr));
			break;
		}
	}
	
	return clntSock;
}



void ErrorHandling(char *message) {
	WSACleanup();
	fputs(message, stderr);
	fputc('\n', stderr);
	_getch();
	exit(1);
}