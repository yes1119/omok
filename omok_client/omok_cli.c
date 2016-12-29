#include "head.h"

#define COMMAND_SIZE 256
#define SIZE 18     //바둑판 가로 세로 사이즈
HANDLE COUT = 0;    // 콘솔 출력 장치
HANDLE CIN = 0;        // 콘솔 입력 장치
int arr[SIZE][SIZE]; //출력바둑판(바둑돌이놓이는곳)
int arr2[SIZE][SIZE]; //출력바둑판(바둑돌이놓이는곳)
int first;        // 돌의 색깔
int next;        // 돌의 색깔
int count=1;       //차례 카운트
int signal = 1;   // 클라이언트와 서로번갈아가며 두기위한 변수
char message[BUFSIZE];//서버로부터받는 메세지
SOCKET server_sock; //서버소켓


void print();
void setting();
void color(int colornum);
void netplaying();


//===마우스 and 좌표 관련 함수,변수========
COORD pos;
WORD key;
DWORD mode;
int be_input();
int get_input(WORD *vkey, COORD *pos);
void gotoxy(int x, int y);
void mousesetting();
//====================================

void main()
{
	server_sock = ConnectSocket();
	netplaying();

	closesocket(server_sock);
	WSACleanup();
	color(15);
	printf("서버와의 연결 종료\n");
	_getch();
}

void mousesetting()
{
	CIN = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	// 마우스 활성화
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
}

void setting()
{
	signal = 1;
	count = 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i > 0 && j == 0)
			{
				arr[i][j] = "┠";
			}
			else if (i == 0 && j > 0)
			{
				arr[i][j] = "┰";
			}
			else if (i > 0 && j == SIZE - 1)
			{
				arr[i][j] = "┨";
			}
			else if (i == SIZE - 1 && j > 0)
			{
				arr[i][j] = "┸";
			}
			else
				arr[i][j] = "╂";
		}
	}
	arr[0][0] = "┎";
	arr[0][SIZE - 1] = "┒";
	arr[SIZE - 1][SIZE - 1] = "┚";
	arr[SIZE - 1][0] = "┖";

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			arr2[i][j] = 0;
		}
	}

}

void print()
{
	int num = 0;
	int c = 2;
	gotoxy(0, 0);
	for (int i = 0; i < SIZE; i++)
	{
		color(96);
		for (int j = 0; j < SIZE; j++)
		{
			printf("%s", arr[i][j]);

		}
		printf("\n");
	}
	if (count % 2 == 1)
		c = "●";
	else
		c = "○";

	count++;

	color(11);
	gotoxy(38, 0);
	printf("┏━━━━━━━━━━━━━━━┓");
	gotoxy(38, 1);
	printf("┃                              ┃");
	gotoxy(38, 2);
	printf("┃    나(%s)      상대방(%s)    ┃", next, first);
	gotoxy(38, 3);
	printf("┃                              ┃");
	gotoxy(38, 4);
	printf("┃    ------------------------  ┃");
	gotoxy(38, 5);
	printf("┃                              ┃");
	gotoxy(38, 6);
	printf("┃       %s차례 입니다          ┃", c);
	gotoxy(38, 7);
	printf("┃                              ┃");
	gotoxy(38, 8);
	printf("┗━━━━━━━━━━━━━━━┛");

}

int be_input()
{
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CIN, &input_record, 1, &input_count);
	return input_count;
}

int get_input(WORD *vkey, COORD *pos)
{
	INPUT_RECORD input_record;
	DWORD input_count;

	ReadConsoleInput(CIN, &input_record, 1, &input_count);
	switch (input_record.EventType)
	{
	case MOUSE_EVENT:
		if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			GetConsoleScreenBufferInfo(COUT, &csbi);

			*pos = input_record.Event.MouseEvent.dwMousePosition;
			pos->X -= csbi.srWindow.Left;
			pos->Y -= csbi.srWindow.Top;

			return MOUSE_EVENT;
		}
		break;

	}

	FlushConsoleInputBuffer(CIN);
	return 0;
}

void netplaying()
{
	int nRcv;         //리시브
	int event;        // 마우스 이벤트에 이용
	int x;            // 마우스의 x좌표 저장소
	int y;            // 마우스의 y좌표 저장소
	int a, b;         // 리시브 받을때 x y 변수
	int num;          // 게임종료 여부 확인하기 위한 변수
	char m1[2];       // 보내는메세지

	mousesetting();
	setting(); //오목판 그리기 18*18
	

	nRcv = recv(server_sock, message, sizeof(message) - 1, 0);
	message[nRcv] = '\0';
	if (message[0] - '0' == 1)
	{
		first = "●";
		next = "○";
		printf(" 후공(○) 입니다)");
	}
	else
	{
		signal += 1;
		first = "○";
		next = "●";
		printf(" 선공(●) 입니다)");
	}
	
	print(); //오목판 출력 18*18



	while (1) //마우스 클릭할때마다 이벤트 발생
	{
		
		if (be_input())
		{
			if (get_input(&key, &pos) != 0 && signal % 2 == 0)
			{
				
				MOUSE_EVENT;
				x = pos.X;
				y = pos.Y;
				gotoxy(x, y);
				if (arr2[y][x / 2] == 0)
				{
					signal++;				
					arr[y][x / 2] = next;
					arr2[y][x / 2] = 1;
					m1[0] = y + '0';
					m1[1] = x / 2 + '0';
					print();
					send(server_sock, m1, (int)strlen(m1), 0); //메세지를보낸다	
				}
			
				Sleep(300);

			}
		}
		
		else if(signal%2==1)
		{
			signal++;
			nRcv = recv(server_sock, message, sizeof(message) - 1, 0);

			if (nRcv == SOCKET_ERROR)
			{
				printf("Receive Error..\n");
				break;
			}
			message[nRcv] = '\0';

			if (strcmp(message, "exit") == 0)
			{
				printf("Close Server Connection..\n");
				break;
			}

			int a = message[0] - '0';
			int b = message[1] - '0';
			arr[a][b] = first;
			arr2[a][b] = 1;
			print();
			if (message[2] - '0' == 1)
			{
				color(11);
				gotoxy(50, 10);
				printf("흑(●) 승리");
				nRcv = recv(server_sock, message, sizeof(message) - 1, 0);
				message[nRcv] = '\0';

				if (message[0] - '0' == 10)
				{
					system("cls");
					netplaying();
				}
				else
				{
					getch();
					system("cls");
					closesocket(server_sock); //서버와 연결 종료;
					WSACleanup();
					return;
				}
			}
			else if (message[2] - '0' == 2)
			{
				color(11);
				gotoxy(50, 10);
				printf("백(○) 승리");
				nRcv = recv(server_sock, message, sizeof(message) - 1, 0);
				message[nRcv] = '\0';

				if (message[0] - '0' == 10)
				{
					system("cls");
					netplaying();
				}
				else
				{
					getch();
					system("cls");
					closesocket(server_sock); //서버와 연결 종료;
					WSACleanup();
					return;
				}
			}
		}

		
	}
}

void gotoxy(int x, int y)   // 좌표 보내기 gotoxy
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void color(int colornum)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colornum);
}