#include "head.h"
void ErrorHandling(char *message);

WSADATA wsaData;
SOCKET servSock, clntSock;   //SOCKET은 사실 UINT_PTR 형이다.
SOCKADDR_IN servAddr, clntAddr;

char message[BUFSIZE]; //Message Buffer
int strLen;
int fromLen, nRcv;

SOCKET ConnectSocket()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("Load WinSock 2.2 DLL Error");

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
		ErrorHandling("Socket Error");

	memset(&servAddr, 0, sizeof(SOCKADDR_IN));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = 9000;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //61.81.99.213

	
	printf("접속대기중......");

	if (bind(servSock, (void *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("Bind Error");

	if (listen(servSock, 2) == SOCKET_ERROR)
		ErrorHandling("Listen Error");

	fromLen = sizeof(clntAddr);

	clntSock = accept(servSock, (void *)&clntAddr, &fromLen);
	
	if (clntSock == INVALID_SOCKET) 
	{
		ErrorHandling("연결 실패");
	}

	else 
	{
		gotoxy(38, 0);
		printf("클라이언트(%s) 접속완료.....\n", inet_ntoa(clntAddr.sin_addr));
		printf("\n");
	}

	closesocket(servSock);
	return clntSock;
}


void ErrorHandling(char *message)
{
	WSACleanup();
	fputs(message, stderr);
	fputc('\n', stderr);
	_getch();
	exit(1);
}


