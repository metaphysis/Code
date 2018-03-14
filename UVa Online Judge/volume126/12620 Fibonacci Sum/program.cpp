// Fibonacci Sum
// UVa ID: 12620
// Verdict: Accepted
// Submission Date: 2017-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    vector<int> f;

    f.push_back(1); f.push_back(1);

    int j = 1; 
    do
    {
        j += 1;
        f.push_back((f[j - 1] + f[j - 2]) % 100);
    }
    while (f[j - 1] != f[0] || f[j] != f[1]);

    f.pop_back(); f.pop_back();

    unsigned long long all = 0;
    for (auto fi : f) all += fi;
    
    int cases;
    unsigned long long N, M;
        
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> M;

        int n = N % f.size();
        if (n == 0) n = f.size();
        int m = M % f.size();
        if (m == 0) m = f.size();

        unsigned long long nextN = N + (f.size() - n);
        unsigned long long nextM = M - (m - 1);
        
        unsigned long long sum = 0;
        if (nextM < nextN)
        {
            n--, m--;
            for (int i = n; i <= m; i++) sum += f[i];
        }
        else
        {
            for (int i = n - 1; i < f.size(); i++) sum += f[i];
            for (int i = 0; i < m; i++) sum += f[i];
            sum += (nextM - nextN - 1) / f.size() * all;
        }
        
        cout << sum << '\n';
    }

    return 0;
}
