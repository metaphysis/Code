#include <bits/stdc++.h>

using namespace std;

const int MAXN = 256;

int ta[MAXN], tb[MAXN], tv[MAXN], ts[MAXN];

int cmp(int *s, int a, int b, int offset)
{
    return s[a] == s[b] && s[a + offset] == s[b + offset];
}

void print(int *a, int n, string name)
{
    cout << name << ":";
    for (int i = 0; i < n; i++) cout << ' ' << a[i];
    cout << '\n';
}

void da(int *s, int *sa, int n, int m)
{
    int *x = ta, *y = tb, *t;

    print(s, 10, "s");

    for (int i = 0; i < m; i++) ts[i] = 0;
    for (int i = 0; i < n; i++) ts[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) ts[i] += ts[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--ts[x[i]]] = i;
    for (int i, j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (p = 0, i = n - j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;

        cout << "p = " << p << '\n';
        print(sa, 10, "sa");
        print(y, 10, "y");

        for (i = 0; i < n; i++) tv[i] = x[y[i]];
        print(tv, 10, "tv");

        for (i = 0; i < m; i++) ts[i] = 0;
        for (i = 0; i < n; i++) ts[tv[i]]++;
        for (i = 1; i < m; i++) ts[i] += ts[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--ts[tv[i]]] = y[i];

        print(sa, 10, "sa");

        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;

        print(x, 10, "x");
        cout << "p = " << p << '\n';
    }
}

void getHeight(int *s, int *sa, int *r, int *h, int n)
{
    for (int i = 1; i <= n; i++) r[sa[i]] = i;
    for (int i = 0, j, k = 0; i < n; h[r[i++]] = k)
        for (k ? k-- : 0, j = sa[r[i] - 1]; s[i + k] == s[j + k]; k++)
            ;
}

int main(int argc, char *argv[])
{
    string S = "edcbaabcde";
    int s[10], sa[10];
    for (int i = 0; i < S.length(); i++) s[i] = S[i];
    da(s, sa, 10, 128);
}
