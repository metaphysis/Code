const int MAXN = 1000010;

int rank[MAXN], height[MAXN];

void getHeight(int *s, int *sa, int n)
{
    height[0] = 0;
    for (int i = 0; i < n; i++) ranks[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++, (k ? k-- : 0))
    {
        if (ranks[i])
            while (s[i + k] == s[sa[ranks[i] - 1] + k]) k++;
        height[ranks[i]] = k;
    }
}

int log2t[MAXN], st[20][MAXN];
void prepare(int n)
{
    log2t[1] = 0;
    for (int i = 2; i <= n; i++) log2t[i] = log2t[i >> 1] + 1;
    for (int i = 0; i < n; i++) st[i][0] = i;
    for (int j = 1; j <= log2t[n]; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            int L = st[i][j - 1], R = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (height[L] < height[R] ? L : R);
        }
}

int query(int L, int R)
{
    int j = log2t[R - L + 1];
    L = st[L][j], R = st[R - (1 << j) + 1][j];
    return (height[L] < height[R] ? L : R);
}

int lcp(int L, int R)
{
    L = rank[L], R = rank[R];
    if (L > R) swap(L, R);
    return height[query(L + 1, R)];
}
