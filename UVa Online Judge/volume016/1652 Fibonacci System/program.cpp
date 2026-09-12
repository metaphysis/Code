#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 62);
long long ways[95][2], sum[95][2], cnt[95], one[95];

long long add(long long a, long long b) {
    if (a >= inf - b) return inf;
    return a + b;
}

void init() {
    ways[0][0] = ways[0][1] = 1;
    for (int len = 1; len <= 90; len++) {
        for (int pre = 0; pre <= 1; pre++) {
            ways[len][pre] = ways[len - 1][0];
            sum[len][pre] = sum[len - 1][0];
            if (pre == 0) {
                ways[len][pre] = add(ways[len][pre], ways[len - 1][1]);
                sum[len][pre] = add(sum[len][pre], add(sum[len - 1][1], ways[len - 1][1]));
            }
        }
    }
    cnt[1] = one[1] = 1;
    for (int len = 2; len <= 90; len++) {
        cnt[len] = ways[len - 2][0];
        one[len] = add(cnt[len], sum[len - 2][0]);
    }
}

long long firstOne(long long k, int len, int pre) {
    long long ans = 0, w0;
    while (len > 0 && k > 0) {
        w0 = ways[len - 1][0];
        if (k <= w0) pre = 0;
        else {
            ans = add(ans, sum[len - 1][0]);
            k -= w0;
            ans = add(ans, k);
            pre = 1;
        }
        len--;
    }
    return ans;
}

long long beforeOne(long long k, int len) {
    if (len == 1) return k;
    return add(k, firstOne(k, len - 2, 0));
}

string getNum(long long k, int len) {
    string s;
    long long w0;
    if (len == 1) return "1";
    s = "10";
    len -= 2;
    while (len > 0) {
        w0 = ways[len - 1][0];
        if (k < w0) s += '0';
        else {
            s += '1';
            k -= w0;
        }
        len--;
    }
    return s;
}

long long solve(long long n) {
    long long ans = 0, k;
    int len = 1;
    while (n >= cnt[len] * len) {
        n -= cnt[len] * len;
        ans += one[len];
        len++;
    }
    k = n / len;
    ans += beforeOne(k, len);
    n %= len;
    if (n > 0) {
        string s = getNum(k, len);
        for (int i = 0; i < n; i++) ans += s[i] - '0';
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    init();
    while (cin >> n) cout << solve(n) << '\n';
    return 0;
}
