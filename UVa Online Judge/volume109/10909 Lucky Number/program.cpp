// Lucky Number
// UVa ID: 10909
// Verdict: Accepted
// Submission Date: 2022-01-08
// UVa Run Time: 0.300s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

int marked[MAXN], fenwick[MAXN], lucky[MAXN];

inline int lowbit(int x) { return x & (-x); }

void add(int x, int delta)
{
    for (int i = x; i < MAXN; i += lowbit(i))
        fenwick[i] += delta;
}

int get(int x)
{
    int sum = 0;
    for (int i = x; i; i -= lowbit(i))
        sum += fenwick[i];
    return sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    for (int i = 1; i < MAXN; i++)
    {
        marked[i] = 1;
        add(i, 1);
    }
    int cnt = MAXN - 1;
    for (int i = 2; i < MAXN; i++)
    {
        if (!marked[i]) continue;
        int jump = 2 * i - 1;
        for (int j = jump, k = 0; j - k <= cnt; j += jump, k++)
        {
            int target = j - k;
            int left = 0, right = MAXN - 1, middle, idx;
            while (left <= right)
            {
                middle = (left + right) >> 1;
                if (get(middle) >= target) { idx = middle, right = middle - 1; }
                else left = middle + 1;
            }
            marked[idx] = 0;
            add(idx, -1);
            cnt--;
        }
    }

    cnt = 0;
    for (int i = 0; i < MAXN; i++)
        if (marked[i])
            lucky[cnt++] = 2 * i - 1;
    
    int n;
    while (cin >> n)
    {
        cout << n;
        if (n & 1) cout << " is not the sum of two luckies!\n";
        else
        {
            int idx = lower_bound(lucky, lucky + cnt, n / 2) - lucky;
            while (idx >= 0)
            {
                if (binary_search(lucky, lucky + cnt, n - lucky[idx]))
                {
                    cout << " is the sum of " << min(lucky[idx], n - lucky[idx]);
                    cout << " and " << max(lucky[idx], n - lucky[idx]) << ".\n";
                    break;
                }
                idx--;
            }
            if (idx < 0) cout << " is not the sum of two luckies!\n";
        }
    }
    return 0;
}
