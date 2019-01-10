const int MAXN = 1000010;

int wa[MAXN], wb[MAXN], wv[MAXN], ws[MAXN];

int cmp(int *s, int a, int b, int offset)
{
    return s[a] == s[b] && s[a + offset] == s[b + offset];
}

void da(int *s, int *sa, int n, int m)
{
    int *x = wa, *y = wb, *t;
    for (int i = 0; i < m; i++) ws[i] = 0;
    for (int i = 0; i < n; i++) ws[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) ws[i] += ws[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
    for (int i, j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (p = 0, i = n - j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        for (i = 0; i < n; i++) wv[i] = x[y[i]];
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < n; i++) ws[wv[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
}

void getHeight(int *s, int *sa, int *r, int *h, int n)
{
    for (int i = 1; i <= n; i++) r[sa[i]] = i;
    for (int i = 0, j, k = 0; i < n; h[r[i++]] = k)
        for (k ? k-- : 0, j = sa[r[i] - 1]; s[i + k] == s[j + k]; k++)
            ;
}
