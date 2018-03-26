// In Braille
// UVa ID: 12364
// Verdict: Accepted
// Submission Date: 2018-03-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[3][512];

string symbol[3], dots[3] = {
    ".* *. *. ** ** *. ** ** *. .* ",
    "** .. *. .. .* .* *. ** ** *. ",
    ".. .. .. .. .. .. .. .. .. .. "
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    char letter;
    string line;

    while (cin >> n, n > 0)
    {
        cin >> letter; cin.ignore(1024, '\n');
        if (letter == 'S')
        {
            getline(cin, line);
            for (int k = 0; k < line.length(); k++)
            {
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        board[i][j + 3 * k] = dots[i][j + 3 * (line[k] - '0')];
            }
            int width = 3 * line.length() - 1;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < width; j++)
                    cout << board[i][j];
                cout << '\n';
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                getline(cin, symbol[i]);
                while (symbol[i].back() == ' ') symbol[i].pop_back();
                symbol[i].push_back(' ');
            }

            for (int k = 0; k < symbol[0].length(); k += 3)
            {
                for (int d = 0; d < 10; d++)
                {
                    bool same = true;
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            if (dots[i][j + 3 * d] != symbol[i][j + k])
                            {
                                same = false;
                                break;
                            }
                    if (same)
                    {
                        cout << d;
                        break;
                    }
                }
            }
            cout << '\n';
        }
    }

    return 0;
}
