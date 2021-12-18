// Cool Word
// UVa ID: 12820
// Verdict: Accepted
// Submission Date: 2021-12-18
// UVa Run Time: 0.040s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    string word;
    while (cin >> n)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            map<char, int> f;
            for (auto c : word) f[c]++;
            if (f.size() < 2) continue;
            set<int> ns;
            for (auto p : f) ns.insert(p.second);
            if (ns.size() == f.size()) cnt++;
        }
        cout << "Case " << ++cases << ": " << cnt << '\n';
    }

    return 0;
}
