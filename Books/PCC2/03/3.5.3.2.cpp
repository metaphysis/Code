#include <bits/stdc++.h>

using namespace std;

const int MAXN = 256;

int ta[MAXN], tb[MAXN], tv[MAXN], ts[MAXN];

int cmp(int *s, int a, int b, int offset) {
    return s[a] == s[b] && s[a + offset] == s[b + offset];
}

void da(int *s, int *sa, int n, int m) {
    int *x = ta, *y = tb, *t;
    for (int i = 0; i < m; i++) ts[i] = 0;
    for (int i = 0; i < n; i++) ts[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) ts[i] += ts[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--ts[x[i]]] = i;
    for (int i, k = 1, p = 1; p < n; k *= 2, m = p) {
        for (p = 0, i = n - k; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= k)
                y[p++] = sa[i] - k;
        for (i = 0; i < n; i++) tv[i] = x[y[i]];
        for (i = 0; i < m; i++) ts[i] = 0;
        for (i = 0; i < n; i++) ts[tv[i]]++;
        for (i = 1; i < m; i++) ts[i] += ts[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--ts[tv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], k) ? p - 1 : p++;
    }
}

void getHeight(int *s, int *sa, int *r, int *h, int n) {
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
