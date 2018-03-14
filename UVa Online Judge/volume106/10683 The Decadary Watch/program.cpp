// The Decadary Watch
// UVa ID: 10683
// Verdict: Accepted
// Submission Date: 2017-12-28
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    
    while (getline(cin, line))
    {
        int tc = 0;
        tc += stoi(line.substr(0, 2)) * 3600000;
        tc += stoi(line.substr(2, 2)) * 60000;
        tc += stoi(line.substr(4, 2)) * 1000;
        tc += stoi(line.substr(6, 2)) * 10;
        
        int hh = tc / 8640000;
        tc %= 8640000;
        int mm = tc / 86400;
        tc %= 86400;
        int ss = tc / 864;
        tc %= 864;
        int cc = tc * 100 / 864;

        cout << hh;
        cout << setw(2) << setfill('0') << mm;
        cout << setw(2) << setfill('0') << ss;
        cout << setw(2) << setfill('0') << cc;
        cout << '\n';
    }

    return 0;
}
