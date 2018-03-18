// Happy Number
// UVa ID: 10591
// Verdict: Accepted
// Submission Date: 2018-03-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long n, next;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        cout << "Case #" << c << ": " << n << ' ';
    
        set<int> sum;
        bool happy = false;

        while (true)
        {
            next = 0;
            while (n) 
            {
                next += (n % 10) * (n % 10);
                n /= 10;
            }

            if (next == 1)
            {
                happy = true;
                break;
            }

            if (sum.find(next) != sum.end())
                break;
            sum.insert(next);
            n = next;
        }
        
        if (happy) cout << "is a Happy number.\n";
        else cout << "is an Unhappy number.\n";
    }

    return 0;
}
