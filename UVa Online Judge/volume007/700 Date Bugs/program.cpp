// Date Bugs
// UVa ID: 700
// Verdict: Accepted
// Submission Date: 2016-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case #" << ++cases << ":" << endl;

        int y, a, b;
        vector<int> actual;
        
        cin >> y >> a >> b;
        for (int j = y; j < 10000; j += (b - a)) actual.push_back(j);
        
        for (int i = 2; i <= n; i++)
        {
            cin >> y >> a >> b;

            if (actual.size() == 0) continue;
            
            for (int j = actual.size() - 1; j >= 0; j--)
            {
                int year = actual[j];
                if (year >= b) year = a + (year - b) % (b - a);
                if (year != y) actual.erase(actual.begin() + j);
            }
        }
        
        if (actual.size() > 0)
            cout << "The actual year is " << actual.front() << ".\n";
        else
            cout << "Unknown bugs detected.\n";

        cout << '\n';
    }
    
	return 0;
}
