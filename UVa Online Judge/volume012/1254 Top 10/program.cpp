// Top 10
// UVa ID: 1254
// Verdict: TLE
// Submission Date: 2018-05-30
// UVa Run Time: 
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 120010;

void countSort(int *s, int *a, int *b, int n, int m)
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

struct WORD
{
    int idx;
    string word;
    bool operator<(const WORD &w) const
    {
        if (word.length() != w.word.length()) return word.length() < w.word.length();
        if (word != w.word) return word < w.word;
        return idx < w.idx;
    }
};

vector<WORD> words;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, Q, n, m, s[MAXN], sa[MAXN], height[MAXN], charset = 200;
    int belong[MAXN];
    string word;

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> word;
        words.push_back((WORD){i, word});
    }

    sort(words.begin(), words.end());
    m = 0;
    for (int i = 0; i < N; i++)
    {
        for (char c : words[i].word)
        {
            belong[m] = i;
            s[m++] = c;
        }
        s[m++] = charset++;
    }

    cin >> Q;
    for (int i = 1; i <= Q; i++)
    {
        cin >> word;
        n = m;
        for (char c : word)
            s[n++] = c;
        s[n] = 0;

        suffixArray(s, sa, n, charset);
        getHeight(s, sa, height, n);

        int r = -1;
        for (int i = 0; i < n; i++)
            if (sa[i] == m)
            {
                r = i;
                break;
            }

        vector<int> candidate;
        for (int j = r; j >= 1 && height[j] >= word.length(); j--)
            candidate.push_back(belong[sa[j - 1]]);
        for (int j = r + 1; j < m && height[j] >= word.length(); j++)
            candidate.push_back(belong[sa[j]]);

        sort(candidate.begin(), candidate.end());
        candidate.erase(unique(candidate.begin(), candidate.end()), candidate.end());

        if (candidate.size() > 0)
        {
            for (int i = 0; i < min((int)candidate.size(), 10); i++)
            {
                if (i) cout << ' ';
                cout << words[candidate[i]].idx;
            }
            cout << '\n';
        }
        else 
            cout << "-1\n";
    }

    return 0;
}
