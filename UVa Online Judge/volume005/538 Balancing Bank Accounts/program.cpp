// Balancing Bank Accounts
// UVa ID: 538
// Verdict: Accepted
// Submission Date: 2016-12-21
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, t, cases = 0, amount;
    string name1, name2;
    
    while (cin >> n >> t, n > 0)
    {
        map<string, int> money;
        string names[30];

        for (int i = 1; i <= n; i++)
        {
            cin >> names[i];
            money[names[i]] = 0;
        }

        for (int i = 1; i <= t; i++)
        {
            cin >> name1 >> name2 >> amount;
            money[name1] -= amount;
            money[name2] += amount;
        }
        
        cout << "Case #" << ++cases << '\n';
        
        for (int i = 1; i < n; i++)
        {
            if (money[names[i]] > 0)
                cout << names[i] << ' ' << names[n] << ' ' << money[names[i]] << '\n';
            
            if (money[names[i]] < 0)
                cout << names[n] << ' ' << names[i] << ' ' << abs(money[names[i]]) << '\n';
        }
        cout << '\n';
    }
    
	return 0;
}
