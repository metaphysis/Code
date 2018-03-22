// List of Conquests
// UVa ID: 10420
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    cin >> n; cin.ignore(1024, '\n');
    
    string line, country;
    map<string, int> cnt;
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        istringstream iss(line);
        iss >> country;
        cnt[country]++;
    }
    for (auto p : cnt)
        cout << p.first << ' ' << p.second << '\n';

    return 0;
}
