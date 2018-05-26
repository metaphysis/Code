// Life Forms
// UVa ID: 11107
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, OFFSET = 100, CHARSET = 256;

void radixSort(int *s, int *a, int *b, int n, int m)
{
    static int cnt[MAXN];
    memset(cnt, 0, (max(n, m) + 1) * sizeof(int));
    for (int i = 0; i < n; i++) cnt[s[a[i]]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--cnt[s[a[i]]]] = a[i];
}

void suffixArray(int *s, int *sa, int n, int m)
{
    static int ranks[MAXN] = {}, a[MAXN] = {}, b[MAXN] = {};

    iota(ranks, ranks + max(n, m) + 1, 0);
    radixSort(s, ranks, sa, n, m);

    ranks[sa[0]] = 0;
    for (int i = 1; i < n; i++)
    {
        ranks[sa[i]] = ranks[sa[i - 1]];
        ranks[sa[i]] += (s[sa[i]] != s[sa[i - 1]]);
    }

    for (int i = 0; (1 << i) < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[j] = ranks[j] + 1;
            b[j] = (j + (1 << i) >= n) ? 0 : (ranks[j + (1 << i)] + 1);
            sa[j] = j;
        }

        radixSort(b, sa, ranks, n, n);
        radixSort(a, ranks, sa, n, n);

        ranks[sa[0]] = 0;
        for (int j = 1; j < n; j++)
        {
            ranks[sa[j]] = ranks[sa[j - 1]];
            ranks[sa[j]] += (a[sa[j - 1]] != a[sa[j]] || b[sa[j - 1]] != b[sa[j]]);
        }
    }
}

void getHeight(int *s, int *sa, int *height, int n)
{
    static int ranks[MAXN] = {};
    height[0] = 0;
    for (int i = 0; i < n; i++) ranks[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++, (k ? k-- : 0))
    {
        if (ranks[i])
            while (s[i + k] == s[sa[ranks[i] - 1] + k]) k++;
        height[ranks[i]] = k;
    }
}

// Check if the common substring meets the condition or not.
int belong[MAXN], flag[110] = {}, mark = 0;
bool validate(int *s, int *sa, int *height, int n, int total, int longest, bool print)
{
    int needed = n / 2 + 1, cnt = 0;
    for (int i = 1; i < total; i++)
        if (height[i] >= longest)
        {
            int start = i;
            while (start < total && height[start] >= longest)
                start++;
            if (start - i + 1 >= needed)
            { 
                mark++, cnt = 0;
                for (int j = i - 1; j < start; j++)
                    if (flag[belong[sa[j]]] != mark)
                        flag[belong[sa[j]]] = mark, cnt++;
                if (cnt >= needed)
                {
                    if (print)
                    {
                        for (int j = 0; j < longest; j++)
                            cout << (char)(s[sa[i - 1] + j] - OFFSET);
                        cout << '\n';
                    }
                    else return true;
                }
            }
            i = start - 1;
        }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, s[MAXN], sa[MAXN], height[MAXN], idx, low, high, longest;
    string line;

    while (cin >> n, n > 0)
    {
        if (cases++ > 0) cout << '\n';

        idx = 0, high = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> line;
            for (int j = 0; j < line.length(); j++)
            {
                belong[idx] = i;
                s[idx++] = line[j] + OFFSET;
            }
            s[idx++] = i;
            high = max(high, (int)line.length());
        }

        if (n == 1)
        {
            cout << line << '\n';
            continue;
        }

        suffixArray(s, sa, idx, CHARSET);
        getHeight(s, sa, height, idx);

        // Binary search.
        low = 0;
        while (low <= high)
        {
            longest = (low + high) / 2;
            if (validate(s, sa, height, n, idx, longest, false))
                low = longest + 1;
            else
                high = longest - 1;
        }
        longest = low - 1;
        if (longest > 0) validate(s, sa, height, n, idx, longest, true);
        else cout << '?' << '\n';
    }

    return 0;
}
