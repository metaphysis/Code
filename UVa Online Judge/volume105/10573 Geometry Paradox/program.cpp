// Geometry Paradox
// UVa ID: 10573
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(4);

    int n;
    cin >> n;
    cin.ignore(1024, '\n');

    string line;
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        istringstream iss(line);
        
        int flag = 0;
        double r1, r2;

        iss >> r1;
        if (iss >> r2) flag = 1;

        if (flag)
            cout << 2.0 * PI * r1 * r2 << '\n';
        else
            cout << PI * r1 * r1 * 0.125 << '\n';
    }

    return 0;
}
