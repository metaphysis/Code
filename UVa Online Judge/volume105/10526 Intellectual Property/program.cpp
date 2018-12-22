// Intellectual Property
// UVa ID: 10526
// Verdict: Accepted
// Submission Date: 2018-12-21
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100200;

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
    static int ranks[MAXN] = {}, a[MAXN] = {}, b[MAXN] = {};

    iota(ranks, ranks + MAXN, 0);
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

struct INFRINGEMENT
{
    int length, position;
    INFRINGEMENT (int length = 0, int position = 0): length(length), position(position) {}
    bool operator==(const INFRINGEMENT &i) const
    {
        return i.position >= position && i.position + i.length <= position + length;
    }
};

bool cmp1(const INFRINGEMENT &i1, const INFRINGEMENT &i2)
{
    if (i1.position != i2.position) return i1.position < i2.position;
    return i1.length > i2.length;
}

bool cmp2(const INFRINGEMENT &i1, const INFRINGEMENT &i2)
{
    if (i1.length != i2.length) return i1.length > i2.length;
    return i1.position < i2.position;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, k;
    int s[MAXN] = {}, sa[MAXN] = {}, height[MAXN] = {}, covered[MAXN] = {};
    string s1, s2, line;

    while (cin >> k)
    {
        if (k == 0) break;

        memset(s, 0, sizeof(s));
        memset(height, 0, sizeof(height));
        memset(sa, 0, sizeof(sa));

        cin.ignore(256, '\n');
        getline(cin, line);
        int n1 = 0, n2 = 0, m = 128;
        while (getline(cin, line), line != "END TDP CODEBASE")
        {
            for (auto c : line) s[n1++] = c;
            s[n1++] = '\n';
        }
        s[n1++] = 1, n2 = n1;
        getline(cin, line);
        while (getline(cin, line), line != "END JCN CODEBASE")
        {
            for (auto c : line) s[n2++] = c;
            s[n2++] = '\n';
        }

        suffixArray(s, sa, n2, m);
        getHeight(s, sa, height, n2);

        vector<INFRINGEMENT> infringes;
        for (int i = 0; i < n2; i++)
        {
            if (sa[i] > (n1 - 1))
            {
                for (int j = i, h = n2; j >= 1 && height[j]; j--)
                {
                    h = min(h, height[j]);
                    if (sa[j - 1] < (n1 - 1))
                    {
                        infringes.push_back(INFRINGEMENT(h, sa[i]));
                        break;
                    }
                }
                for (int j = i + 1, h = n2; j < n2 && height[j]; j++)
                {
                    h = min(h, height[j]);
                    if (sa[j] < (n1 - 1))
                    {
                        infringes.push_back(INFRINGEMENT(h, sa[i]));
                        break;
                    }
                }
            }
        }

        sort(infringes.begin(), infringes.end(), cmp1);
        infringes.erase(unique(infringes.begin(), infringes.end()), infringes.end());
        sort(infringes.begin(), infringes.end(), cmp2);

        if (cases) cout << '\n';
        cout << "CASE " << ++cases << '\n';
        for (int i = 0; i < infringes.size() && i < k; i++)
        {
            for (int j = 0; j < infringes[i].length; j++)
                covered[infringes[i].position + j] = 1;
            cout << "INFRINGING SEGMENT " << (i + 1);
            cout << " LENGTH " << infringes[i].length;
            cout << " POSITION " << (infringes[i].position - n1) << '\n';
            for (int j = 0; j < infringes[i].length; j++)
                cout << (char)s[infringes[i].position + j];
            cout << '\n';
        }   
    }

    return 0;
}
