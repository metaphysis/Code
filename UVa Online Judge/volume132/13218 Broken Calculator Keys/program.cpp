#include <bits/stdc++.h>
using namespace std;

long long getAnswer(long long p, long long q) {
    if (p == 0) return 0;
    long long g = __gcd(p, q), rp = p / g, rq = q / g, a = rp * rp, b = rq * rq, sum = 0;
    while (b != 0) {
        sum += a / b;
        long long t = a % b;
        a = b;
        b = t;
    }
    long long steps = sum - 1;
    if (rp > rq) steps += 2;
    return 1 + 2 * steps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long p, q;
    while (cin >> p >> q) cout << getAnswer(p, q) << '\n';
    return 0;
}
