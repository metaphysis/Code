#include <bits/stdc++.h>
using namespace std;

long double calcWin(const vector<long double> &prob, int num, int n) {
    int r = n - 1, lower = num, total = 1 << lower;
    long double result = 0.0L;
    for (int mask = 0; mask < total; mask++) {
        int bits = __builtin_popcount(mask);
        if (bits > r) continue;
        long double product = 1.0L, sum = 0.0L;
        for (int i = 0; i < lower; i++) {
            if (mask & (1 << i)) {
                product *= prob[i];
                sum += prob[i];
            }
        }
        long double rest = 1.0L - prob[num] - sum;
        if (rest < 0.0L && rest > -1e-18L) rest = 0.0L;
        long double ways = 1.0L;
        for (int i = 0; i < bits; i++) ways *= r - i;
        long double value = ways * product * powl(rest, r - bits);
        if (bits & 1) result -= value;
        else result += value;
    }
    return result;
}

int buildProb(long double target, int n, int m, vector<long double> &prob) {
    prob.assign(m, 0.0L);
    long double used = 0.0L;
    for (int num = 0; num < m; num++) {
        long double left = 0.0L, right = 1.0L - used;
        prob[num] = left;
        long double leftWin = calcWin(prob, num, n);
        prob[num] = right;
        long double rightWin = calcWin(prob, num, n);
        if (leftWin < target - 1e-16L) return 1;
        if (rightWin > target + 1e-16L) return -1;
        for (int loop = 0; loop < 100; loop++) {
            long double mid = (left + right) / 2.0L;
            prob[num] = mid;
            long double currentWin = calcWin(prob, num, n);
            if (currentWin > target) left = mid;
            else right = mid;
        }
        prob[num] = (left + right) / 2.0L;
        used += prob[num];
    }
    return 0;
}

vector<long double> solveCase(int n, int m) {
    if (m == 1) return vector<long double>(1, 1.0L);
    long double left = 0.0L, right = 1.0L;
    vector<long double> answer(m, 0.0L), current;
    buildProb(right, n, m, answer);
    for (int loop = 0; loop < 120; loop++) {
        long double mid = (left + right) / 2.0L;
        int state = buildProb(mid, n, m, current);
        if (state == -1) {
            left = mid;
        } else {
            right = mid;
            if (state == 0) answer = current;
        }
    }
    buildProb(right, n, m, answer);
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<long double> answer = solveCase(n, m);
        for (long double probability : answer)
            cout << fixed << setprecision(5) << static_cast<double>(probability) << '\n';
    }
    return 0;
}
