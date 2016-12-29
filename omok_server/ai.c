#include "head.h"

#define BOARDSIZE 18
#define BLACK_COLOR 1
#define WHITE_COLOR 2



MY_COORD aiturn(int board[18][18],int start)
{

	int ai_board[18][18] = { 0, };
	int eval = 0;
	int num_of_coord = 0;

	MY_COORD coord[324] = { 9999, };
	srand(time(NULL));
	int randnum = 0;
	
	//��ǻ�Ͱ� ���϶�
	if (start == 1)
	{
		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				if (board[i][j] == 1)
				{	
					randnum = rand() % 8 + 1;

					if (randnum == 1)
					{
						ai_board[i][j + 1] = 999;
					}
					else if (randnum == 2)
					{
						ai_board[i][j - 1] = 999;
					}
					else if (randnum == 3)
					{
						ai_board[i + 1][j + 1] = 999;
					}
					else if (randnum == 4)
					{
						ai_board[i + 1][j] = 999;
					}
					else if (randnum == 5)
					{
						ai_board[i + 1][j - 1] = 999;
					}
					else if (randnum == 6)
					{
						ai_board[i - 1][j] = 999;
					}
					else if (randnum == 7)
					{
						ai_board[i - 1][j - 1] = 999;
					}
					else if (randnum == 8)
					{
						ai_board[i - 1][j + 1] = 999;
					}
				}
			}
		}
	}   
	//����ġ �α�
	else
	{
		//���� ����� ��
		for (int x = 0; x < 18; x++)
		{
			for (int y = 0; y < 18; y++)
			{
				if (board[x][y] == 0)
				{
					//////////////////����//////////////
					#pragma region ��ĭ ����(�ΰ��϶�����)
					// 3ĭ�Ǵ� �� ����
					//���Ʒ�
					if (sero_up(board, x, y, BLACK_COLOR) + sero_down(board, x, y, BLACK_COLOR) >= 2)
					{
						ai_board[x][y] += 60;
					}
					//�¿�
					if (garo_right(board, x, y, BLACK_COLOR) + garo_left(board, x, y, BLACK_COLOR) >= 2)
					{
						ai_board[x][y] += 60;
					}
					//�밢�� ������ �Ʒ� ���� ��
					if (degak_right_down(board, x, y, BLACK_COLOR) + degak_left_up(board, x, y, BLACK_COLOR) >= 2)
					{
						ai_board[x][y] += 60;
					}
					//�밢�� ���ʾƷ� ������ ��
					if (degak_left_down(board, x, y, BLACK_COLOR) + degak_right_up(board, x, y, BLACK_COLOR) >= 2)
					{
						ai_board[x][y] += 60;
					}
					#pragma endregion

					#pragma region ��ĭ ����(�����϶�����)
					// 4ĭ�Ǵ� �� ����
					//���Ʒ�
					if (sero_up(board, x, y, BLACK_COLOR) + sero_down(board, x, y, BLACK_COLOR) >= 3)
					{
						if (board[x - sero_up(board, x, y, WHITE_COLOR)][y] == 0 && board[x + sero_down(board, x, y, WHITE_COLOR)][y] == 0)
						{
							ai_board[x][y] += 15000;
						}
						ai_board[x][y] += 65;
					}
					//�¿�
					if (garo_right(board, x, y, BLACK_COLOR) + garo_left(board, x, y, BLACK_COLOR) >= 3)
					{
						if (board[x][y - garo_left(board, x, y, WHITE_COLOR)] == 0 && board[x][y + garo_right(board, x, y, WHITE_COLOR)] == 0)
						{
							ai_board[x][y] += 15000;
						}
						ai_board[x][y] += 65;
					}
					//�밢�� ������ �Ʒ� ���� ��
					if (degak_right_down(board, x, y, BLACK_COLOR) + degak_left_up(board, x, y, BLACK_COLOR) >= 3)
					{
						if (board[x - degak_left_up(board, x, y, WHITE_COLOR)][y - degak_left_up(board, x, y, WHITE_COLOR)] == 0 && board[x + degak_right_down(board, x, y, WHITE_COLOR)][y + degak_right_down(board, x, y, WHITE_COLOR)] == 0)
						{
							ai_board[x][y] += 15000;
						}
						ai_board[x][y] += 65;
					}
					//�밢�� ���ʾƷ� ������ ��
					if (degak_left_down(board, x, y, BLACK_COLOR) + degak_right_up(board, x, y, BLACK_COLOR) >= 3)
					{
						if (board[x - degak_right_up(board, x, y, WHITE_COLOR)][y + degak_right_up(board, x, y, WHITE_COLOR)] == 0 && board[x + degak_left_down(board, x, y, WHITE_COLOR)][y - degak_left_down(board, x, y, WHITE_COLOR)] == 0)
						{
							ai_board[x][y] += 15000;
						}
						ai_board[x][y] += 65;
					}
#pragma endregion

					#pragma region �ټ�ĭ ����(�װ��϶�����)
					//���Ʒ�
					if (sero_up(board, x, y, BLACK_COLOR) + sero_down(board, x, y, BLACK_COLOR) >= 4)
					{
						ai_board[x][y] += 50000;
					}
					//�¿�
					if (garo_right(board, x, y, BLACK_COLOR) + garo_left(board, x, y, BLACK_COLOR) >= 4)
					{
						ai_board[x][y] += 50000;
					}
					//�밢�� ������ �Ʒ� ���� ��
					if (degak_right_down(board, x, y, BLACK_COLOR) + degak_left_up(board, x, y, BLACK_COLOR) >= 4)
					{
						ai_board[x][y] += 50000;
					}
					//�밢�� ���ʾƷ� ������ ��
					if (degak_left_down(board, x, y, BLACK_COLOR) + degak_right_up(board, x, y, BLACK_COLOR) >= 4)
					{
						ai_board[x][y] += 50000;
					}
#pragma endregion

					///////////////////����//////////////
					#pragma region ��ĭ ����(�ΰ�����)
					//���Ʒ�
					if (sero_up(board, x, y, WHITE_COLOR) + sero_down(board, x, y, WHITE_COLOR) >= 1)
					{
						ai_board[x][y] += 10;
					}
					//�¿�
					if (garo_right(board, x, y, WHITE_COLOR) + garo_left(board, x, y, WHITE_COLOR) >= 1)
					{
						ai_board[x][y] += 10;
					}
					//�밢�� ������ �Ʒ� ���� ��
					if (degak_right_down(board, x, y, WHITE_COLOR) + degak_left_up(board, x, y, WHITE_COLOR) >= 1)
					{
						ai_board[x][y] += 10;
					}
					//�밢�� ���ʾƷ� ������ ��
					if (degak_left_down(board, x, y, WHITE_COLOR) + degak_right_up(board, x, y, WHITE_COLOR) >= 1)
					{
						ai_board[x][y] += 10;
					}
					#pragma endregion

					#pragma region ��ĭ ����(��������)
					//���Ʒ�
					if (sero_up(board, x, y, WHITE_COLOR) + sero_down(board, x, y, WHITE_COLOR) >= 2)
					{
						//����ִ� ��ĭ �����
						if (board[x - sero_up(board, x, y, WHITE_COLOR)][y] != BLACK_COLOR && board[x + sero_down(board, x, y, WHITE_COLOR)][y] != BLACK_COLOR)
						{
							ai_board[x][y] += 160;
						}
						ai_board[x][y] += 200;
					}
					//�¿�
					if (garo_right(board, x, y, WHITE_COLOR) + garo_left(board, x, y, WHITE_COLOR) >= 2)
					{
						if (board[x][y - garo_left(board, x, y, WHITE_COLOR)] != BLACK_COLOR && board[x][y + garo_right(board, x, y, WHITE_COLOR)] != BLACK_COLOR)
						{
							ai_board[x][y] += 160;
						}
						ai_board[x][y] += 200;
					}
					//�밢�� ������ �Ʒ� ���� ��
					if (degak_right_down(board, x, y, WHITE_COLOR) + degak_left_up(board, x, y, WHITE_COLOR) >= 2)
					{
						if (board[x - degak_left_up(board, x, y, WHITE_COLOR)][y - degak_left_up(board, x, y, WHITE_COLOR)] != BLACK_COLOR && board[x + degak_right_down(board, x, y, WHITE_COLOR)][y + degak_right_down(board, x, y, WHITE_COLOR)] != BLACK_COLOR)
						{
							ai_board[x][y] += 160;
						}
						ai_board[x][y] += 200;
					}
					//�밢�� ���ʾƷ� ������ ��
					if (degak_left_down(board, x, y, WHITE_COLOR) + degak_right_up(board, x, y, WHITE_COLOR) >= 2)
					{
						if (board[x - degak_right_up(board, x, y, WHITE_COLOR)][y + degak_right_up(board, x, y, WHITE_COLOR)] != BLACK_COLOR && board[x + degak_left_down(board, x, y, WHITE_COLOR)][y - degak_left_down(board, x, y, WHITE_COLOR)] != BLACK_COLOR)
						{
							ai_board[x][y] += 160;
						}
						ai_board[x][y] += 200;
					}
#pragma endregion

					#pragma region ��ĭ ����(�װ�����)
					//���Ʒ�
					if (sero_up(board, x, y, WHITE_COLOR) + sero_down(board, x, y, WHITE_COLOR) >= 3)
					{
						//����ִ� ��ĭ �����
						if (board[x - sero_up(board, x, y, WHITE_COLOR)][y] != BLACK_COLOR && board[x + sero_down(board, x, y, WHITE_COLOR)][y] != BLACK_COLOR)
						{
							ai_board[x][y] += 30000;
						}
						ai_board[x][y] += 950;
					}
					//�¿�
					if (garo_right(board, x, y, WHITE_COLOR) + garo_left(board, x, y, WHITE_COLOR) >= 3)
					{
						if (board[x][y - garo_left(board, x, y, WHITE_COLOR)] != BLACK_COLOR && board[x][y + garo_right(board, x, y, WHITE_COLOR)] != BLACK_COLOR)
						{
							ai_board[x][y] += 30000;
						}
						ai_board[x][y] += 950;
					}
					//�밢�� ������ �Ʒ� ���� ��
					if (degak_right_down(board, x, y, WHITE_COLOR) + degak_left_up(board, x, y, WHITE_COLOR) >= 3)
					{
						if (board[x - degak_left_up(board, x, y, WHITE_COLOR)][y - degak_left_up(board, x, y, WHITE_COLOR)] != BLACK_COLOR && board[x + degak_right_down(board, x, y, WHITE_COLOR)][y + degak_right_down(board, x, y, WHITE_COLOR)] != BLACK_COLOR)
						{
							ai_board[x][y] += 30000;
						}
						ai_board[x][y] += 950;
					}
					//�밢�� ���ʾƷ� ������ ��
					if (degak_left_down(board, x, y, WHITE_COLOR) + degak_right_up(board, x, y, WHITE_COLOR) >= 3)
					{
						if (board[x - degak_right_up(board, x, y, WHITE_COLOR)][y + degak_right_up(board, x, y, WHITE_COLOR)] != BLACK_COLOR && board[x + degak_left_down(board, x, y, WHITE_COLOR)][y - degak_left_down(board, x, y, WHITE_COLOR)] != BLACK_COLOR)
						{
							ai_board[x][y] += 30000;
						}

						ai_board[x][y] += 950;
					}
#pragma endregion

					#pragma region �ټ�ĭ ����(�ټ�������)
										//���Ʒ�
										if (sero_up(board, x, y, WHITE_COLOR) + sero_down(board, x, y, WHITE_COLOR) >= 4)
										{
											ai_board[x][y] += 99999;
										}
										//�¿�
										if (garo_right(board, x, y, WHITE_COLOR) + garo_left(board, x, y, WHITE_COLOR) >= 4)
										{
											ai_board[x][y] += 99999;
										}
										//�밢�� ������ �Ʒ� ���� ��
										if (degak_right_down(board, x, y, WHITE_COLOR) + degak_left_up(board, x, y, WHITE_COLOR) >= 4)
										{
											ai_board[x][y] += 99999;
										}
										//�밢�� ���ʾƷ� ������ ��
										if (degak_left_down(board, x, y, WHITE_COLOR) + degak_right_up(board, x, y, WHITE_COLOR) >= 4)
										{
											ai_board[x][y] += 99999;
										}
					#pragma endregion
				}
			}
		}
	}

	//����ġ�� ���� ū �� ã��
	for (int x = 0; x < 18; x++)
	{
		for (int y = 0; y < 18; y++)
		{
			if (board[x][y] == 0 && eval < ai_board[x][y])
			{
				eval = ai_board[x][y];
			}
		}
	}

	// ���� ���� ���� �ʰ� �������� �ٲ� 
	for (int x = 0; x < 18; x++)
	{
		for (int y = 0; y < 18; y++)
		{
			if (board[x][y] == 0 && ai_board[x][y] == eval)
			{
				coord[num_of_coord].x = x;
				coord[num_of_coord].y = y;
				num_of_coord++;
			}
		}
	}


	return coord[rand() % (num_of_coord)];
}


// ���� ���� Ȯ��
int sero_up(int board[18][18], int x, int y, int _color) 
{
	int i, count;
	count = 0;

	for (i = x - 1; i >= 0; i--)
	{
		if (board[i][y] != _color) 
		{
			break;
		}
		else
		{
			count++;
		}
	}

	return count;
}

// ���� �Ʒ��� Ȯ��
int sero_down(int board[18][18], int x, int y, int _color)
{
	int i, count;

	count = 0;

	
	for (i = x + 1; i < 18; i++) 
	{
		if (board[i][y] != _color) 
		{
			break;
		}
		else 
		{
			count++;
		}
	}

	return count;
}

//���� ������ Ȯ��
int garo_right(int board[18][18], int x, int y, int _color)
{
	int i, count;
	count = 0;

	for (i = y + 1; i <18 ; i++)
	{
		if (board[x][i] != _color)
		{
			break;
		}
		else
		{
			count++;
		}
	}

	return count;
}

//���� ���� Ȯ��
int garo_left(int board[18][18], int x, int y, int _color)
{
	int i, count;
	count = 0;

	for (i = y - 1; i >= 0; i--)
	{
		if (board[x][i] != _color)
		{
			break;
		}
		else
		{
			count++;
		}
	}

	return count;
}

//�밢�� ������ �Ʒ�
int degak_right_down(int board[18][18], int x, int y, int _color)
{
	int i, j, count;
	count = 0;

	for ((i = x + 1, j = y + 1); (i < 18 && j < 18); (i++, j++)) 
	{
		if (board[i][j] != _color)
		{
			break;
		}
		else {
			count++;
		}
	}

	return count;
}

//�밢�� ���� ��
int degak_left_up(int board[18][18], int x, int y, int _color)
{
	int i, j, count;
	count = 0;

	for ((i = x - 1, j = y - 1); (i >= 0 && j >= 0); (i--, j--)) 
	{
		if (board[i][j] != _color)
		{
			break;
		}
		else
		{
			count++;
		}
	}

	return count;
}

//�밢�� ������ ��
int degak_right_up(int board[18][18], int x, int y, int _color)
{
	int i, j, count;
	count = 0;

	for ((i = x - 1, j = y + 1); (i >= 0 && j < 18); (i--, j++))
	{
		if (board[i][j] != _color)
		{
			break;
		}
		else
		{
			count++;
		}
	}

	return count;
}

//�밢�� ���� �Ʒ� 
int degak_left_down(int board[18][18], int x, int y, int _color)
{
	int i, j, count;
	count = 0;

	for ((i = x + 1, j = y - 1); (i < 18 && j >= 0); (i++, j--))
	{
		if (board[i][j] != _color)
		{
			break;
		}
		else
		{
			count++;
		}
	}

	return count;
}


