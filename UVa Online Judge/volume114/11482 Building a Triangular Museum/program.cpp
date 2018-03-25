// Building a Triangular Museum
// UVa ID: 11482
// Verdict: Accepted
// Submission Date: 2018-03-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[128][20480];

void copyAndShiftTriangle(int shift, int M)
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < 2 * M; j++)
            board[i][j + shift] = board[i][j];
}

void drawSingleTriangle(int M)
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < 2 * M; j++)
            board[i][j] = ' ';
    for (int i = 0; i < M; i++)
    {
        board[i][M + i] = '\\'; board[i][M - i - 1] = '/';
        if (i < M - 1) board[M - 1][M + i] = board[M - 1][M - i - 1] = '_';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, M, N;
    while (cin >> M >> N, M > 0)
    {
        cout << "Triangular Museum " << ++cases << '\n';
        drawSingleTriangle(M);
        int leftSpaces = M * (N - 1);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                for (int space = 0; space < leftSpaces; space++)
                    cout << ' ';
                for (int k = 0; k < (2 * i + 1) * M + (j + 1); k++)
                    cout << board[j][k];
                cout << '\n';
            }
            copyAndShiftTriangle(2 * (i + 1) * M, M);
            leftSpaces -= M;
        }
        cout << '\n';
    }

    return 0;
}
