// Equations in Disguise
// UVa ID: 11199
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
string exps[24];
map<char, char> cache;

bool cmp(string &a, string b)
{
    if (a.length() != b.length()) return a.length() < b.length();
    return a < b;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";
        int available[16]
        for (int i = 0; i < n; i++)
            cin >> exps[i];
        sort(exps, exps + n, cmp);
        //for (int i = 0; i < n; i++)
        //    cout << exps[i] << '\n';
        string equal = exps[0];
        sort(equal.begin(), equal.end());
        equal.erase(unique(equal.begin(), equal.end()), equal.end());
        cout << equal << '\n';
        for (int i = 0; i < equal.length(); i++)
        {
            
        }
    }

    return 0;
}
