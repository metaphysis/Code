// DNA Sequencing
// UVa ID: 760
// Verdict: Accepted
// Submission Date: 2018-05-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 610;

void radixSort(int *s, int *a, int *b, int n, int m)
{
    static int cnt[MAXN];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[s[a[i]]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--cnt[s[a[i]]]] = a[i];
}

void suffixArray(int *s, int *sa, int n, int m)
{
    for (int i = 0; i < n; i++) cout << setw(4) << right << s[i];
    cout << '\n';
    static int ranks[MAXN] = {}, a[MAXN] = {}, b[MAXN] = {};

    iota(ranks, ranks + MAXN, 0);
    radixSort(s, ranks, sa, n, m);

    for (int i = 0; i < n; i++) cout << setw(3) << right << sa[i];
    cout << '\n';

    for (int i = 0; i < n; i++) ranks[sa[i]] = i;
    for (int i = 0; i < n; i++) cout << setw(3) << right << (ranks[i] + 1);
    cout << '\n';

    for (int i = 0; (1 << i) < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[j] = ranks[j] + 1;
            b[j] = (j + (1 << i) >= n) ? 0 : (ranks[j + (1 << i)] + 1);
            sa[j] = j;
            cout << "a[" << j << "] = " << a[j] << " b[" << j << "] = " << b[j] << '\n';
        }

        radixSort(b, sa, ranks, n, n);
        radixSort(a, ranks, sa, n, n);

        for (int i = 0; i < n; i++) cout << setw(3) << right << sa[i];
        cout << '\n';

        for (int i = 0; i < n; i++) ranks[sa[i]] = i;
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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int s[MAXN] = {}, sa[MAXN] = {}, height[MAXN] = {};
    string s1, s2;

    while (cin >> s1 >> s2)
    {
        if (cases++ > 0) cout << '\n';

        set<string> common;

        memset(s, 0, sizeof(s));
        memset(height, 0, sizeof(height));
        memset(sa, 0, sizeof(sa));

        int n = 0, m = 128, separator = 0, longest = 1;
        for (int i = 0; i < s1.length(); i++) s[n++] = s1[i];
        separator = n, s[n++] = 1;
        for (int i = 0; i < s2.length(); i++) s[n++] = s2[i];

        suffixArray(s, sa, n, m);
        getHeight(s, sa, height, n);

        for (int i = 1; i <= n; i++)
            if (height[i] >= longest)
            {
                if ((separator < sa[i - 1] && separator > sa[i]) ||
                    (separator > sa[i - 1] && separator < sa[i]))
                {
                    if (height[i] > longest) common.clear();
                    longest = height[i];
                    if (separator > sa[i])
                        common.insert(s1.substr(sa[i], longest));
                    else
                        common.insert(s1.substr(sa[i - 1], longest));
                }
            }

        if (common.size() > 0)
        {
            for (auto substring : common)
                cout << substring << '\n';
        }
        else
            cout << "No common sequence.\n";
    }

    return 0;
}
