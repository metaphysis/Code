// Antiarithmetic?
// UVa ID: 10730
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.080s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, number, idx[10010];
    char colon;

    while (cin >> n, n > 0)
    {
        cin >> colon;
        
        for (int i = 0; i < n; i++)
        {
            cin >> number;
            idx[number] = i;
        }
        
        bool flag = true;
        for (int i = 0; i < n; i++)
            for (int diff = 1; diff < (n - i); diff++)
            {
                if (i - diff >= 0 && i + diff < n)
                {
                    if ((idx[i - diff] < idx[i] && idx[i] < idx[i + diff]) ||
                        (idx[i - diff] > idx[i] && idx[i] > idx[i + diff]))
                        {
                            flag = false;
                            break;
                        }
                }    
            }
            
        cout << (flag ? "yes" : "no") << '\n';
    }
    
    return 0;
}
