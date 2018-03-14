// Sumsets
// UVa ID: 10125
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct sum
{
    int i, j, v;
    bool operator<(const sum &s) const
    {
        return v < s.v;
    }
} sums[1000010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    long long data[1010];
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> data[i];

        sort(data, data + n);
        
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                sums[cnt].i = i, sums[cnt].j = j, sums[cnt].v = data[i] + data[j], cnt++;
        
        sort(sums, sums + cnt);
        
        sum test = sum{0, 0, 0};

        int found = -1;
        for (int i = n - 1; i >= 0; i--)
            for (int j = 0; j < n; j++)
            {
                if (i == j) continue;
                test.v = data[i] - data[j];
                int u = lower_bound(sums, sums + cnt, test) - sums;
                for (int k = u; k < cnt; k++)
                {
                    if (test.v != sums[k].v) break;
                    if (i != sums[k].i && i != sums[k].j && j != sums[k].i && j != sums[k].j)
                    {
                        found = i;
                        goto print;
                    }
                }
            }
            
        print:
        if (found >= 0) cout << data[found] << '\n';
        else cout << "no solution\n";
    }
    
    return 0;
}
