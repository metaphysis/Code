#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8;

int board[MAXN] = {0}, columnUsed[MAXN] = {0}, cntOfSolutions = 0;

bool checkBoard(int row, int selected)
{
    for (int cln = 0; cln < row; cln++)
        if (abs(row - cln) == abs(selected - board[cln]))
            return false;
    return true;
}

void printBoard()
{
    for (int row = 0; row < MAXN; row++)
    {
        for (int cln = 0; cln < MAXN; cln++)
            cout << (board[row] == cln ? " Q" : " *");
        cout << '\n';
    }
    cout << '\n';
}

void dfs(int row)
{
    if (row == MAXN)
    {
        printBoard();
        cntOfSolutions++;
        return;
    }

    for (int cln = 0; cln < MAXN; cln++)
    {
        if (columnUsed[cln] || !checkBoard(row, cln)) continue;
        columnUsed[cln] = 1, board[row] = cln;
        dfs(row + 1);
        columnUsed[cln] = 0;
    }
}


int main(int argc, char *argv[])
{
    dfs(0);
    cout << cntOfSolutions << '\n';
    return 0;
}
