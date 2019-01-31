// 4 Values Whose Sum is 0
// UVa ID: 1152
// Verdict: Accepted
// Submission Date: 2019-01-28
// UVa Run Time: 1.930s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4010;

long long A[MAXN], B[MAXN], C[MAXN], D[MAXN];
long long AB[MAXN * MAXN], CD[MAXN * MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> A[i] >> B[i] >> C[i] >> D[i];
            
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                AB[i * n + j] = A[i] + B[j];
                CD[i * n + j] = C[i] + D[j];
            }

        sort(AB, AB + n * n);
        sort(CD, CD + n * n);
        
        int last = n * n, pairs = 0;
        for (int i = 0; i < last; i++)
        {
            long long T = -AB[i];
            if (T < CD[0] || T > CD[last - 1]) continue;
            int k1 = lower_bound(CD, CD + last, T) - CD;
            int k2 = upper_bound(CD + k1, CD + last, T) - CD;
            pairs += k2 - k1;
        }
        if (cs > 1) cout << '\n';
        cout << pairs << '\n';
    }

    return 0;
}
