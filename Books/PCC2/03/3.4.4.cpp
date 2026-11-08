int z[1 << 20];

void Z(const string &s) {
    int n = s.length();
    z[0] = n;
    // [l, r) 是当前已知的、与前缀相同的最右匹配区间
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(z[i - l], r - i);
        else z[i] = 0;
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
}
