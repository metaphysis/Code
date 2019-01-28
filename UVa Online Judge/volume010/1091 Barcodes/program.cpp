// Barcodes
// UVa ID: 1091
// Verdict: Accepted
// Submission Date: 2019-01-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int bar[160], m, cases = 0;
    string flag = "00110";
    string characters = "0123456789-";
    map<string, int> encoding = {
        {"00001", 0},
        {"10001", 1},
        {"01001", 2},
        {"11000", 3},
        {"00101", 4},
        {"10100", 5},
        {"01100", 6},
        {"00011", 7},
        {"10010", 8},
        {"10000", 9},
        {"00100", 10}
    };

    while (cin >> m, m > 0)
    {
        cout << "Case " << ++cases << ": ";
        for (int i = 0; i < m; i++) cin >> bar[i];
        if (m < 29 || (m - 29) % 6 != 0)
        {
            cout << "bad code\n";
            continue;
        }

        int wide, narrow;
        wide = 0, narrow = 0x3f3f3f3f;
        for (int i = 0; i < m; i++)
            wide = max(wide, bar[i]), narrow = min(narrow, bar[i]);
        double middle = (narrow + wide) / 2.0;
        wide = 0, narrow = 0x3f3f3f3f;
        for (int i = 0; i < m; i++)
        {
            int v = 0;
            if (bar[i] < middle)
                v = bar[i] * 2;
            else
                v = bar[i];
            wide = max(wide, v), narrow = min(narrow, v);
        }
        if (wide * 95 > narrow * 105)
        {
            cout << "bad code\n";
            continue;
        }

        string code;
        narrow = bar[0], wide = 2 * narrow;
        for (int i = 0; i < m; i++)
        {
            if (bar[i] < middle)
                code += '0';
            else
                code += '1';
        }

        bool good = code.substr(0, 5) == flag && code.substr(code.length() - 5) == flag;
        if (!good)
        {
            reverse(code.begin(), code.end());
            good = code.substr(0, 5) == flag && code.substr(code.length() - 5) == flag;
        }
        if (!good)
        {
            cout << "bad code\n";
            continue;
        }

        for (int i = 5; i < code.length(); i += 6)
            if (code[i] != '0')
            {
                good = false;
                break;
            }
        if (!good)
        {
            cout << "bad code\n";
            continue;
        }

        vector<int> digits;
        for (int i = 6; i < code.length() - 5; i += 6)
        {
            string block = code.substr(i, 5);
            if (encoding.find(block) == encoding.end())
            {
                good = false;
                break;
            }
            digits.push_back(encoding[block]);
        }
        if (!good)
        {
            cout << "bad code\n";
            continue;
        }

        int n = digits.size() - 2, mod = 0;
        for (int i = 1; i <= n; i++)
            mod += ((n - i) % 10 + 1) * digits[i - 1];
        mod %= 11;
        if (mod != digits[n])
        {
            cout << "bad C\n";
            continue;
        }
        
        n = digits.size() - 1, mod = 0;
        for (int i = 1; i <= n; i++)
            mod += ((n - i) % 9 + 1) * digits[i - 1];
        mod %= 11;
        if (mod != digits[n])
        {
            cout << "bad K\n";
            continue;
        }
        
        for (int i = 0; i < digits.size() - 2; i++)
            cout << characters[digits[i]];
        cout << '\n';
    }

    return 0;
}
