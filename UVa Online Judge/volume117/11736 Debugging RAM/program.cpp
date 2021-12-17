// Debugging RAM
// UVa ID: 11736
// Verdict: Accepted
// Submission Date: 2021-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string si[210], byte, variable;
    map<string, unsigned long long> value;
    int b, v, ti[210];
    while (cin >> b >> v)
    {
        for (int i = 0; i < v; i++) cin >> si[i] >> ti[i];
        for (int i = 0; i < v; i++)
        {
            variable.clear();
            for (int j = 0; j < ti[i]; j++)
            {
                cin >> byte;
                variable += byte;
            }
            value[si[i]] = stoull(variable, 0, 2);
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> variable;
            cout << variable << '=';
            if (value.count(variable)) cout << value[variable];
            cout << '\n';
        }
        value.clear();
    }

    return 0;
}
