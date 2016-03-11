// Check the Check （将军）
// PC/UVa IDs: 110107/10196, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
#include <cstdlib>
	
using namespace std;
	
char status[8][8];	// 表示国际象棋棋子的位置。
	
// 检查坐标为（kingX，kingY）的王是否在坐标为（x，y）的卒攻击范围内，注意进攻方向的不同。
bool checkP (int x, int y, int kingX, int kingY)
{
	return (x - kingX) == 1 && abs(y - kingY) == 1;
}
	
// 检查坐标为（kingX，kingY）的王是否在坐标为（x，y）的马攻击范围内。
bool checkN (int x, int y, int kingX, int kingY)
{
	return (abs(x - kingX) == 2 && abs(y - kingY) == 1) ||
			(abs(x - kingX) == 1 && abs(y - kingY) == 2);
}
	
// 检查坐标为（kingX，kingY）的王是否在坐标为（x，y）的象攻击范围内。
bool checkB (int x, int y, int kingX, int kingY)
{
	int step, currentX = x, currentY = y, directX, directY;
	bool checked = false;
	
	// 检查象与王是否处于对角线。
	if (abs(x - kingX) == abs(y - kingY))
	{
		checked = true;
		
		// 判断相对方位。
		directX = (x < kingX) ? 1 : -1;
		directY = (y < kingY) ? 1 : -1;
	
		// 是否有棋子相隔。
		step = abs (x - kingX);
		while (step > 1)
		{
			currentX += directX;
			currentY += directY;
			if (status[currentX][currentY] != '.')
			{
				checked = false;
				break;
			}
			step--;
		}
	}
	return checked;
}
	
// 检查坐标为（kingX，kingY）的王是否在坐标为（x，y）的车攻击范围内。
bool checkR (int x, int y, int kingX, int kingY)
{
	int step, currentX = x, currentY = y, directX = 0, directY = 0;
	bool checked = false;
	
	// 车与王是否在同一行或者同一列，车与王之间是否有棋子相隔。
	if (x == kingX || y == kingY)
	{
		checked = true;
		
		// 判断相对方位。
		directX = (x == kingX) ? (0) : (x < kingX ? 1 : -1);
		directY = (y == kingY) ? (0) : (y < kingY ? 1 : -1);
		
		// 是否有棋子相隔。
		step = (directX == 0) ? abs(y - kingY) : abs(x - kingX);
		while (step > 1)
		{
			currentX += directX;
			currentY += directY;
			if (status[currentX][currentY] != '.')
			{
				checked = false;
				break;
			}
			step--;
		}
	}
	return checked;
}
	
// 检查坐标为（kingX，kingY）的王是否在坐标为（x，y）的王后攻击范围内。
bool checkQ (int x, int y, int kingX, int kingY)
{
	return checkR(x, y, kingX, kingY) || checkB(x, y, kingX, kingY);
}
	
// 检查给定棋盘状态是否存在将军局面。
void check (int gameCount)
{
	bool bChecked = false, wChecked = false;
	int bKingX = -1, bKingY = -1, wKingX = -1, wKingY = -1;
	int directX = 0, directY = 0, currentX = 0, currentY = 0, step = 0;
	
	// 查找白棋和黑棋王的位置。
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (status[i][j] == 'k')
			{
				bKingX = i;
				bKingY = j;
			}
			if (status[i][j] == 'K')
			{
				wKingX = i;
				wKingY = j;
			}
		}
		
	// 假如未找到王的坐标，表明为空棋盘。
	if (bKingX == -1)
		return;
		
	cout << "Game #" << gameCount << ": ";
	
	// 检查棋子与王的是否存在将军情况。
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			switch (status[i][j])
			{
				// 黑卒。
				case 'p':
					wChecked = checkP(wKingX, wKingY, i, j);
					break;
				// 白卒。
				case 'P':
					bChecked = checkP(i, j, bKingX, bKingY);
					break;
				// 黑马。
				case 'n':
					wChecked = checkN(i, j, wKingX, wKingY);
					break;
				// 白马。
				case 'N':
					bChecked = checkN(i, j, bKingX, bKingY);
					break;
				// 黑象。
				case 'b':
					wChecked = checkB(i, j, wKingX, wKingY);
					break;
				// 白象。
				case 'B':
					bChecked = checkB(i, j, bKingX, bKingY);
					break;
				// 黑车。
				case 'r':
					wChecked = checkR(i, j, wKingX, wKingY);
					break;
				// 白车。
				case 'R':
					bChecked = checkR(i, j, bKingX, bKingY);
					break;
				// 黑后。
				case 'q':
					wChecked = checkQ(i, j, wKingX, wKingY);
					break;
				// 白后。
				case 'Q':
					bChecked = checkQ(i, j, bKingX, bKingY);
					break;
				// 其他情况。
				default:
					break;
			}
			
			// 检查将军情况是否存在。
			if (bChecked)
			{
				cout << "black king is in check." << endl;
				return;
			}
			if (wChecked)
			{
				cout << "white king is in check." << endl;
				return;
			}
		}
	
	cout << "no king is in check." << endl;
}
	
int main (int ac, char *av[])
{
	string line;
	int gameCount = 1, temp = 0;
	
	while (getline(cin, line))
	{
		if (line != "")
		{
			for (int i = 0; i < 8; i++)
				status[temp][i] = line[i];
			temp++;
		}
		else
		{
			check(gameCount);
			gameCount++;
			temp = 0;
		}
	}
	
	return 0;
}
