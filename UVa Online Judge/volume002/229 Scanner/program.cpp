// Scanner
// UVa IDs: 229
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

char body[10][15];
int row[10], topRightDiagonal[24], column[15], topLeftDiagonal[24];
int r[10], trd[24], c[15], tld[24];
bool flag;

void backtrack(int cell)
{
    if (cell == 150)
    {
        flag = true;
        return;
    }

    int i = cell / 15, j = cell % 15;

    // cell can be #
    if (r[i] < row[i] &&
        c[j] < column[j] &&
        trd[i + j] < topRightDiagonal[i + j] &&
        tld[9 - (i - j)] < topLeftDiagonal[9 - (i - j)])
    {
        body[i][j] = '#';

        r[i]++;
        trd[i + j]++;
        c[j]++;
        tld[9 - (i - j)]++;

        backtrack(cell + 1);

        if (!flag)
        {
            body[i][j] = '.';

            r[i]--;
            trd[i + j]--;
            c[j]--;
            tld[9 - (i - j)]--;
        }
    }

    // cell can be .
    if (!flag &&
        r[i] + (14 - j) >= row[i] &&
        c[j] + (9 - i) >= column[j] &&
        (min(10 - i, j) + trd[i + j]) >= topRightDiagonal[i + j] &&
        (min(9 - i, 14 - j) + tld[9 - (i - j)]) >= topLeftDiagonal[9 - (i - j)])
        backtrack(cell + 1);
}

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;

    while (cases--)
    {
        for (int i = 0; i < 10; i++)
            cin >> row[i];

        for (int i = 0; i < 24; i++)
            cin >> topRightDiagonal[i];

        for (int i = 0; i < 15; i++)
            cin >> column[i];

        for (int i = 0; i < 24; i++)
            cin >> topLeftDiagonal[i];

        memset(body, '.', sizeof(body));
        memset(r, 0, sizeof(r));
        memset(trd, 0, sizeof(trd));
        memset(c, 0, sizeof(c));
        memset(tld, 0, sizeof(tld));

        flag = false;
        backtrack(0);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 15; j++)
                cout << body[i][j];
            cout << endl;
        }

        if (cases)
            cout << endl;
    }

    return 0;
}
