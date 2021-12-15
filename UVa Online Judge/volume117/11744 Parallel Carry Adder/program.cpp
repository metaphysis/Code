// Parallel Carry Adder
// UVa ID: 11744
// Verdict: Accepted
// Submission Date: 2021-12-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {
        if (cs) cout << '\n';
        string sa, sb;
        cin >> sa >> sb;
        long long a = stoll(sa, 0, 2), b = stoll(sb, 0, 2), c, d;
        cout << sa << ' ' << sb << '\n';
        while (true)
        {
            c = a ^ b, d = a & b;
            a = c, b = (d << 1);
            cout << bitset<31>(a).to_string() << ' ';
            if (b < (1LL << 31)) cout << bitset<31>(b).to_string() << '\n';
            else
            {
                cout << "overflow" << '\n';
                break;
            }
            if (b == 0) break;
        }
    }

    return 0;
}
