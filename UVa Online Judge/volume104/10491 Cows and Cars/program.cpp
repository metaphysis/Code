// Cows and Cars
// UVa ID: 10491
// Verdict: Accepted
// Submission Date: 2018-04-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double ncows, ncars, nshows;
    while (cin >> ncows >> ncars >> nshows)
    {
        double rate = (ncows * ncars + ncars * (ncars - 1)) / ((ncows + ncars) * (ncows + ncars - nshows - 1));
        cout << fixed << setprecision(5) << rate << '\n';
    }

    return 0;
}
