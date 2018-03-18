// Professor Lazy, Ph.D.
// UVa ID: 12464
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    unsigned long long a, b, n, tmp;
    while (cin >> a >> b >> n, a > 0)
    {
        int steps = 0;

        set<unsigned long long> check;
        map<int, int> appeared;
        map<int, int> record;
        
        appeared[a] = steps, record[steps++] = a;
        appeared[b] = steps, record[steps++] = b;
        
        int start = -1, cycle = -1;
        while (true)
        {
            if (a == 0) break;
            tmp = a;
            a = b;
            b = (1 + b) / tmp;            
            tmp = a * (unsigned long long)pow(10, 10) + b;
            if (check.find(tmp) != check.end())
            {
                start = appeared[b];
                cycle = steps - start;
                break;
            }
            check.insert(tmp);
            appeared[b] = steps, record[steps++] = b;
        }
        
        if (start >= 0)
        {
            if (n < start) cout << record[n] << '\n';
            else cout << record[start + (n - start) % cycle] << '\n';
        }
        else
            cout << record[n] << '\n';
        
    }

    return 0;
}
