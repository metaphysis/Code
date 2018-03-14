// Langton's Ant
// UVa ID: 11664
// Verdict: Accepted
// Submission Date: 2018-03-03
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int grid[16][16], n;

void fillGrid(string c)
{
    int cnt = n * n;
    vector<int> bits;
    while (cnt--)
    {
        bits.push_back((c.back() - '0') % 2);
        string cc;
        int r = 0;
        for (int i = 0; i < c.length(); i++)
        {
            r = r * 10 + c[i] - '0';
            cc += (char)(r / 2 + '0');
            r %= 2;
        }
        while (cc.front() == '0' && cc.length() > 1) cc.erase(cc.begin());
        c = cc;
    }
    for (int i = 0; i < bits.size(); i++)
        grid[i / n][n - 1 - (i % n)] = bits[i];
}

void display()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << grid[i][j];
        cout << '\n';
    }
    cout << "----------\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int x, y, d, row, cln;
    int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    string c;

    while (cin >> n >> c >> x >> y, n > 0)
    {
        fillGrid(c);

        d = 0, row = n - y, cln = x - 1;

        while (true)
        {
            //display();

            if (row == 0 && cln == (n - 1))
            {
                cout << "Yes\n";
                break;
            }

            if (grid[row][cln] == 0)
            {
                grid[row][cln] = 1;
                d = (d + 3) % 4;
                row += offset[d][0], cln += offset[d][1];
            }
            else
            {
                grid[row][cln] = 0;
                d = (d + 1) % 4;
                row += offset[d][0], cln += offset[d][1];
            }
            
            if (row < 0 || row >= n || cln < 0 || cln >= n)
            {
                cout << "Kaputt!\n";
                break;
            }
        }
    }

    return 0;
}
