#include <bits/stdc++.h>
using namespace std;

long long getCnt(int n) {
    long long res = 0;
    for (int base = 1, len = 1; base <= n; base *= 10, len++) {
        int end = min(n, base * 10 - 1);
        res += 1LL * (end - base + 1) * len;
    }
    return res;
}

long long getSum(int l, int r) {
    return getCnt(r) - getCnt(l - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p1, p2;
    while (cin >> p1 >> p2 && (p1 || p2)) {
        long long total = getSum(p1, p2);
        int left = p1, right = p2;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (2 * getSum(p1, mid) <= total)
                left = mid;
            else
                right = mid - 1;
        }
        cout << left << '\n';
    }
    return 0;
}
