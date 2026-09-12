#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;

bool check(long long y, long long b, long long lim) {
    vector<int> digit;
    long long n = y;
    while (n > 0) {
        long long d = n % b;
        if (d > 9) return false;
        digit.push_back(d);
        n /= b;
    }
    i128 val = 0;
    for (int i = (int)digit.size() - 1; i >= 0; i--) {
        val = val * 10 + digit[i];
        if (val >= lim) return true;
    }
    return false;
}

long long getSqrt(i128 x) {
    long long low = 0, high = 7000000000LL;
    while (low < high) {
        long long mid = (low + high + 1) / 2;
        if ((i128)mid * mid <= x) low = mid;
        else high = mid - 1;
    }
    return low;
}

long long solve(long long y, long long lim) {
    long long ans = 0, top = min(y, 1000000LL), b;
    int a, c, d;
    for (b = 2; b <= top; b++)
        if (check(y, b, lim)) ans = b;
    for (a = 1; a <= 9; a++)
        for (c = 0; c <= 9; c++) {
            if ((y - c) % a != 0) continue;
            b = (y - c) / a;
            if (b < 10) continue;
            if (check(y, b, lim)) ans = max(ans, b);
        }
    for (a = 1; a <= 9; a++)
        for (c = 0; c <= 9; c++)
            for (d = 0; d <= 9; d++) {
                i128 dis = (i128)c * c + (i128)4 * a * (y - d);
                long long s = getSqrt(dis);
                if ((i128)s * s != dis) continue;
                long long num = s - c, den = 2 * a;
                if (num <= 0 || num % den != 0) continue;
                b = num / den;
                if (b < 10) continue;
                if (check(y, b, lim)) ans = max(ans, b);
            }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long y, lim;
    while (cin >> y >> lim)
        cout << solve(y, lim) << '\n';
    return 0;
}
