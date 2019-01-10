#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

void countSort(int *s, int *a, int *b, int n, int m)
{
    static int cnt[MAXN];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[s[a[i]]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--cnt[s[a[i]]]] = a[i];
}

void suffixArray(int *s, int *sa, int n, int m)
{
    static int ranks[MAXN] = {}, a[MAXN] = {}, b[MAXN] = {};

    iota(ranks, ranks + MAXN, 0);
    countSort(s, ranks, sa, n, m);

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

        countSort(b, sa, ranks, n, n);
        countSort(a, ranks, sa, n, n);

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

int main(int argc, char *argv[])
{
    return 0;
}
