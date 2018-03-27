// Dancing the Cheeky-Cheeky
// UVa ID: 11452
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        int half = line.length() / 2, third = line.length() / 3;
        for (int i = half; i > third; i--)
        {
            bool same = true;
            for (int j = 0; j < i; j++)
                if (line[j] != line[i + j])
                {
                    same = false;
                    break;
                }
            if (same)
            {
                for (int j = 2 * i; j < line.length(); j++)
                    if (line[j - 2 * i] != line[j])
                    {
                        same = false;
                        break;
                    }
                if (same)
                {
                    int printed = 0;
                    for (int j = line.length() - 2 * i; j < i; j++)
                    {
                        cout << line[j];
                        printed++;
                        if (printed >= 8) break;
                    }
                    while (printed < 8)
                    {
                        for (int j = 0; j < i; j++)
                        {
                            cout << line[j];
                            printed++;
                            if (printed >= 8) break;
                        }
                    }
                    cout << "...\n";
                    break;
                }
            }
        }
    }

    return 0;
}
