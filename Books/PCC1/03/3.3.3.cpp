const int MAXN = 10000;
int pi[MAXN];

// 计算前缀函数。
void compute(string &p) {
    int m = p.length();
    for (int i = 2, k = 0, pi[1] = 0; i <= m; i++) {
        while (k && p[k + 1] != p[i]) k = pi[k];
        if (p[k + 1] == p[i]) k++;
        pi[i] = k;
    }
}

// 在t中匹配p，返回匹配的个数。
int match(string &t, string &p) {
    int n = t.length(), m = p.length();
    compute(p);
    int cnt = 0;
    for (int i = 1, q = 0; i <= n; i++) {
        while (q && p[q + 1] != t[i]) q = pi[q];
        if (p[q + 1] == t[i]) q++;
        if (q == m) q = pi[q], cnt++;
    }
    return cnt;
}
