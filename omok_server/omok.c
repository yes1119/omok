#include "head.h"

#define COMMAND_SIZE 256
#define SIZE 18     //바둑판 가로 세로 사이즈
HANDLE COUT = 0;    // 콘솔 출력 장치
HANDLE CIN = 0;        // 콘솔 입력 장치
int flag = 0;          // 0=흑 , 1=백
int netp = 0;           //네트워크 차례 출력
int aip = 0;           //컴퓨터 차례 출력
int colorchoice=0;  //선공 후공 선택
int arr[SIZE][SIZE]; //출력바둑판(바둑돌이놓이는곳)
int arr2[SIZE][SIZE]; //내부바둑판(0 =공백 , 1 = 흑 , 2 = 백)
char message[BUFSIZE]; 
SOCKET client_sock; //클라이언트 소켓

//===마우스 and 좌표 관련 함수,변수========
COORD pos; 
WORD key;
DWORD mode;
int be_input();
int get_input(WORD *vkey, COORD *pos);
void gotoxy(int x, int y);
HANDLE hConsole; // 콘솔 핸들
CONSOLE_CURSOR_INFO cursorInfo;
//====================================

//=====초기 셋팅====
int menuprint();
void mousesetting();
void setting();
void print();
void netprint();
void aiprint();
void color(int colornum);
//=================

void netplaying(); //게임실행(네트워크)
void playing(); //게임실행
void aiplaying(); //게임실행(컴퓨터)
int whoiswin(); // 승자결정


void main()
{
	system("mode con:cols=100 lines=30");
	system("title 오목");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	
	menuprint();
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

void gotoxy(int x, int y)      // 좌표 보내기 gotoxy
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void setting()
{

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

	//바둑판 내부 전부 0으로 설정
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
	int a=2;
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
	if (flag == 1)
	{
		a = "○";
	}
	else
		a = "●";
	
		color(11);
		gotoxy(38, 0);
		printf("┏━━━━━━━━━━━━━━━┓");
		gotoxy(38, 1);
		printf("┃                              ┃");
		gotoxy(38, 2);
		printf("┃      (%s)차례 입니다         ┃",a);
		gotoxy(38, 3);
		printf("┃                              ┃");
		gotoxy(38, 4);
		printf("┗━━━━━━━━━━━━━━━┛");
		gotoxy(0, 0);
		printf("\n");
		SetConsoleCursorInfo(hConsole, &cursorInfo); // 커서안보이기설정
	
}

void netprint()
{
	
	int a = 2;
	int b = 2;
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

	if (colorchoice == 1)
	{
		a = "●";
		b = "○";
	}
	else
	{
		a = "○";
		b = "●";
	}
	
	netp++;
	if (netp % 2 ==1)
	{
		c = "●";
	}
	else
	{
		c = "○";
	}
		

	color(11);
	gotoxy(38, 0);
	printf("┏━━━━━━━━━━━━━━━┓");
	gotoxy(38, 1);
	printf("┃                              ┃");
	gotoxy(38, 2);
	printf("┃    나(%s)      상대방(%s)    ┃", a,b);
	gotoxy(38, 3);
	printf("┃                              ┃");
	gotoxy(38, 4);
	printf("┃    ------------------------  ┃");
	gotoxy(38, 5);
	printf("┃                              ┃");
	gotoxy(38, 6);
	printf("┃       %s차례 입니다          ┃",c);
	gotoxy(38, 7);
	printf("┃                              ┃");
	gotoxy(38, 8);
	printf("┗━━━━━━━━━━━━━━━┛");
	SetConsoleCursorInfo(hConsole, &cursorInfo); // 설정
	
}

void aiprint()
{
	int c = 0;
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
	if (aip % 2 == 0)
	{
		c = "●";
	}
	else
		c = "○";

	
	color(11);
	gotoxy(38, 0);
	printf("┏━━━━━━━━━━━━━━━┓");
	gotoxy(38, 1);
	printf("┃                              ┃");
	gotoxy(38, 2);
	printf("┃    나(%s)      컴퓨터(%s)    ┃", "●", "○");
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
	SetConsoleCursorInfo(hConsole, &cursorInfo); // 설정
	aip++;
}

int whoiswin()
{
	int who = 2; //0일때 흑 승 1일때 백 승
	int c = 0; //대각선 승패 확인을 위한 변수
			  	   
	for (int a = 0; a < SIZE; a++)  //가로	
	{
		for (int b = 0; b < SIZE - 4; b++)
		{
			if (arr2[a][b] == arr2[a][b + 1] &&
				arr2[a][b + 1] == arr2[a][b + 2] &&
				arr2[a][b + 2] == arr2[a][b + 3] &&
				arr2[a][b + 3] == arr2[a][b + 4] &&
				arr2[a][b] != 0)
			{
				who = flag;
				c = 1;
			}
		}
	}
	if (c == 0)//대각선1 \n방향
	{
		for (int a = 0; a < SIZE - 4; a++)
		{
			for (int b = 0; b < SIZE - 4; b++)
			{
				if (arr2[a][b] == arr2[a + 1][b + 1] &&
					arr2[a + 1][b + 1] == arr2[a + 2][b + 2] &&
					arr2[a + 2][b + 2] == arr2[a + 3][b + 3] &&
					arr2[a + 3][b + 3] == arr2[a + 4][b + 4] &&
					arr2[a][b] != 0) 
				{
					who = flag;
					c = 1;
				}
			}
		}
	}
	if (c == 0) 
	{
		for (int a = 0; a < SIZE-4; a++)
		{
			for (int b = 4 ; b< SIZE; b++)
			{
				if (arr2[a][b] == arr2[a + 1][b - 1] && 
					arr2[a + 1][b - 1] == arr2[a + 2][b - 2] && 
					arr2[a + 2][b - 2] == arr2[a + 3][b - 3] && 
					arr2[a + 3][b - 3] == arr2[a + 4][b - 4] && 
					arr2[a][b] != 0) //대각선 2 ／방향
				{
					who = flag;
					c = 1;
				}

				else if (arr2[a][b] == arr2[a + 1][b] &&
					arr2[a + 1][b] == arr2[a + 2][b] &&
					arr2[a + 2][b] == arr2[a + 3][b] &&
					arr2[a + 3][b] == arr2[a + 4][b] &&
					arr2[a][b] != 0) //세로
				{
					who = flag;
					c = 1;
				}
			
			}
		}
	}
	
	//오목 완성시
	if (who == 1)
	{
		color(11);
		gotoxy(50, 10);
		if (colorchoice == 1 || colorchoice==0)
		{
			printf("흑(●) 승리");
			return 1;
		}
		else if (colorchoice == 2)
		{
			printf("백(○) 승리");
			return 2;
		}
	
	}
	else if(who==0)
	{
		color(11);
		gotoxy(50, 10);
		if (colorchoice ==1 || colorchoice == 0)
		{
			printf("백(○) 승리");
			return 2;
		}
		else if (colorchoice == 2)
		{
			printf("흑(●) 승리");
			return 1;
		}
	}

}

void color(int colornum)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colornum);
}

void mousesetting()
{
	CIN = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	// 마우스 활성화
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
}

void playing() //컴퓨터 1대 play
{
	mousesetting();
	setting(); //오목판 그리기 18*18
	print(); //오목판 출력 18*18
	flag = 0;

	int event;        // 마우스 이벤트에 이용
	int x;            // 마우스의 x좌표 저장소
	int y;            // 마우스의 y좌표 저장소
	int num;          // 게임종료 여부 확인하기 위한 변수

	while (1) //마우스 클릭할때마다 이벤트 발생
	{
		if (be_input())
		{
			if (get_input(&key, &pos) != 0)
			{
				MOUSE_EVENT;
				x = pos.X;
				y = pos.Y;
				gotoxy(x, y);
				if (flag == 0 && arr2[y][x / 2] == 0)
				{
					arr[y][x / 2] = "●";
					arr2[y][x / 2] = 1;
					flag = 1;
				}
				else if (flag == 1 && arr2[y][x / 2] == 0)
				{
					arr[y][x / 2] = "○";
					arr2[y][x / 2] = 2;
					flag = 0;
				}

				//승패 비교
				print();
				if (whoiswin() == 1 || whoiswin() == 2)
				{
					
					printf("한판더 ? (y/n)");
					if (getch() == 'y')
					{
						system("cls");
						playing();
					}
					else
						break;		
				}
				Sleep(300);

			}
		}
	}

}

void netplaying()
{
	system("cls");
	color(15);
	int nRcv;         //리시브
	int event;        // 마우스 이벤트에 이용
	int x;            // 마우스의 x좌표 저장소
	int y;            // 마우스의 y좌표 저장소
	int num;          // 게임종료 여부 확인하기 위한 변수
	
	int first;        // 돌의 색깔
	int next;        // 돌의 색깔
	int signal = 1;     // 클라이언트와 서로번갈아가며 두기위한 변수
	char m1[3];       // 보내는메세지
	flag = 0;


	printf("선공(●) ====>1번 후공(○)====>2번)");
	scanf_s("%d", &colorchoice);
	m1[0] = colorchoice + '0';
	if (colorchoice == 1)
	{
		first = "●";
		next = "○";
		printf(" 선공(●) 입니다)");		
	}
	else
	{
		signal += 1;
		first = "○";
		next = "●";
		printf(" 후공(○) 입니다)");
	}
	
	send(client_sock, m1, (int)strlen(m1), 0); //메세지를보낸다

		
	mousesetting();
	setting(); //오목판 그리기 18*18
	netprint(); //오목판 출력 18*18
	

	while (1) //마우스 클릭할때마다 이벤트 발생
	{
		if (be_input())
		{
			if (get_input(&key, &pos) != 0 && signal % 2 == 1) //내가 돌을 놓을때
			{
				
				MOUSE_EVENT;
				x = pos.X;
				y = pos.Y;
				gotoxy(x, y);
				if (flag == 0 && arr2[y][x / 2] == 0)
				{
					signal++;
					arr[y][x / 2] = first;
					arr2[y][x / 2] = 1;
					flag = 1;
					m1[0] = y + '0';
					m1[1] = x / 2 + '0';
					m1[2] = whoiswin()+'0';
					netprint();
					send(client_sock, m1, (int)strlen(m1), 0); //메세지를보낸다

					if (m1[2] - '0' == 1 || m1[2] - '0' == 2)
					{	
						gotoxy(50, 12);
						color(11);
						printf("한판더 ? (y/n)");
						if (getch() == 'y')
						{
							m1[0] = 10 + '0';
							send(client_sock, m1, (int)strlen(m1), 0); //메세지를보낸다
							netplaying();
						}
						else
						{
							system("cls");
							 closesocket(client_sock);
							 WSACleanup();
							 break;
						}
					}
				}	
				Sleep(300);

			}
		}
	
		else if (signal % 2 ==0) //상대방이 돌을 놓을때
		{
			signal++;
			nRcv = recv(client_sock, message, sizeof(message) - 1, 0);

			if (nRcv == SOCKET_ERROR)
			{
				printf("리시브 에러\n");
				break;
			}
			message[nRcv] = '\0';

			if (strcmp(message, "exit") == 0)
			{
				printf("서버와의 연결이 끊겼습니다\n");
				break;
			}

			int a = message[0] - '0';
			int b = message[1] - '0';
			arr[a][b] = next;
			arr2[a][b] = 2;
			flag = 0;
			
			netprint();
			
			if (whoiswin() == 1 || whoiswin() == 2)
			{
				m1[2] = whoiswin() + '0';
				send(client_sock, m1, (int)strlen(m1), 0); //메세지를보낸다
				
				gotoxy(50, 12);
				color(11);
				printf("한판더 ? (y/n)");
				if (getch() == 'y')
				{
					m1[0] = 10 + '0';
					send(client_sock, m1, (int)strlen(m1), 0); //메세지를보낸다
					netplaying();
				}
				else
				{
					system("cls");
					// 소켓닫을 때	
					closesocket(client_sock);
					WSACleanup();
					break;
				}
			}
		}
	}
}

void aiplaying() //컴퓨터 1대 play 일단 흑돌부터 둠
{
	system("cls");
	color(15);

	int first;        // 돌의 색깔
	int next;        // 돌의 색깔
	int event;        // 마우스 이벤트에 이용
	int x;            // 마우스의 x좌표 저장소
	int y;            // 마우스의 y좌표 저장소
	int num;          // 게임종료 여부 확인하기 위한 변수
	MY_COORD cd;
	int start = 1;
	flag = 0;
	aip = 0;
	mousesetting();
	setting(); //오목판 그리기 18*18
	aiprint(); //오목판 출력 18*18



	while (1) //마우스 클릭할때마다 이벤트 발생
	{
		if (be_input())
		{
			if (get_input(&key, &pos) != 0)
			{
				MOUSE_EVENT;
				x = pos.X;
				y = pos.Y;
				gotoxy(x, y);
				
				if (arr2[y][x / 2] == 0 &&flag==0) 
				{
					arr[y][x / 2] = "●";
					arr2[y][x / 2] = 1;
					flag = 1;
					aiprint();
					Sleep(300);
				}
			}
		}

		else if (flag==1)
		{
			//ai가 입력한 좌표를반환받는다.
			cd = aiturn(arr2, start);
			arr[cd.x][cd.y] = "○";
			arr2[cd.x][cd.y] = 2;
			flag = 0;
			start = 0;
			aiprint();
			
		}
		
		if (whoiswin() == 1 || whoiswin() == 2)
		{

			printf("한판더 ? (y/n)");
			if (getch() == 'y')
			{
				system("cls");
				aiplaying();
			}
			else
				break;
		}

	}

}

int menuprint(void)
{
	int select;
	while (1)
	{
		color(15);
		system("cls");
		printf("\n\n");
		printf("              ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("              ┃                          오목                      ┃\n");
		printf("              ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n\n");
		printf("       ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("       ┃ [1]그냥ㄱ    [2]네트워크연결     [3]컴퓨터랑 하기     [4]종료    ┃\n");
		printf("       ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

		select = getch();

		system("cls");
		if (select == '1')
		{
			playing();
			
		}
		else if (select == '2')
		{
			client_sock = ConnectSocket();  //클라이언트와 연결
			netplaying();
		}
		else if (select == '3')
		{
			aiplaying();
		}
		else if (select == '4')
		{
			exit(0);
		}
		else
		{
			printf("\n잘못누름"); getch();
		}
		
	}
	return 0;
}