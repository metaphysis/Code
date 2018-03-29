// Named Extension Dialing
// UVa ID: 886
// Verdict: Accepted
// Submission Date: 2018-03-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char digits[26] = {
    // A, B, C, D, E, F
    '2', '2', '2', '3', '3', '3',
    // G, H, I, J, K, L
    '4', '4', '4', '5', '5', '5',
    // M, N, O, P, Q, R, S
    '6', '6', '6', '7', '7', '7', '7',
    // T, U, V, W, X, Y, Z
    '8', '8', '8', '9', '9', '9', '9'
};

bool prefix(string &s, string &t)
{
    if (s.length() > t.length()) return false;
    for (int i = 0, j = 0; i < s.length() && i < t.length(); i++)
        if (s[i] != t[i])
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string firstname, lastname, extension;
    string input;
    vector<pair<string, string>> dict;

    while (cin >> input)
    {
        if (isalpha(input.front()))
        {
            firstname = input;
            cin >> lastname >> extension;
            string key;
            key += digits[toupper(firstname.front()) - 'A'];
            for (auto c : lastname)
                key += digits[toupper(c) - 'A'];
            dict.push_back(make_pair(key, extension));
        }
        else
        {
            bool printed = false;
            for (int i = 0; i < dict.size(); i++)
            {
                if (input == dict[i].second)
                {
                    if (printed) cout << ' ';
                    else printed = true;
                    cout << dict[i].second;
                }
            }
            
            if (!printed)
            {
                for (int i = 0; i < dict.size(); i++)
                {
                    if (prefix(input, dict[i].first))
                    {
                        if (printed) cout << ' ';
                        else printed = true;
                        cout << dict[i].second;
                    }
                }
            }

            if (!printed) cout << 0;
            cout << '\n';
        }
    }

    return 0;
}
