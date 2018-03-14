// Polynomial Remains
// UVa ID: 10586
// Verdict: Accepted
// Submission Date: 2017-03-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, k;
    
    while (cin >> n >> k, n >= 0)
    {
        vector<int> poly(n + 1, 0);
        for (int i = 0; i <= n; i++)
            cin >> poly[i];

        reverse(poly.begin(), poly.end());
        
        for (int i = 0; i <= (n - k); i++)
        {
            poly[i + k] -= poly[i];
            poly[i] = 0;
        }
        
        while (poly.size() > 1 && poly.front() == 0) poly.erase(poly.begin());
        
        reverse(poly.begin(), poly.end());
        
        for (int i = 0; i < poly.size(); i++)
        {
            if (i > 0) cout << ' ';
            cout << poly[i];
        }
        cout << '\n';
    }
    
    return 0;
}
