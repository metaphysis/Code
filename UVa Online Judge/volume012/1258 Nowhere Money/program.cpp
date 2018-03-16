// Nowhere Money
// UVa ID: 1258
// Verdict: Accepted
// Submission Date: 2018-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long fibs[91] = {1, 1};
    for (int i = 2; i < 91; i++)
        fibs[i] = fibs[i - 1] + fibs[i - 2];
    
    long long n;
    while (cin >> n)
    {
        cout << n << '\n';
        vector<int> slots;
        while (n)
        {
            for (int i = 90; i >= 1; i--)
                if (n >= fibs[i])
                {
                    slots.push_back(i);
                    n -= fibs[i];
                    break;
                }
        }
        
        // If you follow the output specification, you will get PE., output a space after every term and got AC.
        for (int i = 0; i < slots.size(); i++)
        {
            //if (i) cout << ' ';
            cout << slots[i] << ' ';
        }
        cout << '\n';
        for (int i = 0; i < slots.size(); i++)
        {
            //if (i) cout << ' ';
            cout << fibs[slots[i]] << ' ';
        }
        cout << '\n' << '\n';
    }

    return 0;
}
