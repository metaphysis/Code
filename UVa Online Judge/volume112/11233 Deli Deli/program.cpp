// Deli Deli
// UVa ID: 11233
// Verdict: Accepted
// Submission Date: 2018-03-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int L, N;
    while (cin >> L >> N)
    {
        string single, plural;
        map<string, string> dict;
        for (int i = 0; i < L; i++)
        {
            cin >> single >> plural;
            dict[single] = plural;
        }
        for (int i = 0; i < N; i++)
        {
            cin >> single;
            if (dict.find(single) != dict.end())
            {
                cout << dict[single] << '\n';
                continue;
            }
            if (single.length() > 1 && single.back() == 'y' && single[single.length() - 2] != 'a' && 
                single[single.length() - 2] != 'e' && single[single.length() - 2] != 'i' &&
                single[single.length() - 2] != 'o' && single[single.length() - 2] != 'u')
            {
                single.pop_back();
                cout << single << "ies\n";
            }
            else if (single.back() == 'o' || single.back() == 's' || single.back() == 'x' || single.back() == 'h')
            {
                if (single.back() == 'h')
                {
                    if (single.length() >= 2 && (single[single.length() - 2] == 'c' || single[single.length() - 2] == 's'))
                        cout << single << "es\n";
                    else
                        cout << single << "s\n";
                }
                else
                    cout << single << "es\n";
            }
            else
            {
                cout << single << "s\n";
            }
            
        }
    }

    return 0;
}
