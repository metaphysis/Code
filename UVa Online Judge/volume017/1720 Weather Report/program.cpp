// Weather Report
// UVa ID: 1720
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.100s

#include <bits/stdc++.h>
using namespace std;

void buildMap(int pos, int left, int n, long double value, const long double prob[], const long long fact[], long long counts[], map<long double, long long> &items) {
    if (pos == 3) {
        counts[3] = left;
        long double weight = value * powl(prob[3], counts[3]);
        long long ways = fact[n] / (fact[counts[0]] * fact[counts[1]] * fact[counts[2]] * fact[counts[3]]);
        items[weight] += ways;
        return;
    }
    for (int current = 0; current <= left; current++) {
        counts[pos] = current;
        buildMap(pos + 1, left - current, n, value * powl(prob[pos], current), prob, fact, counts, items);
    }
}

long double solve(int n, const long double prob[]) {
    long long fact[21] = {1};
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    long long counts[4] = {0, 0, 0, 0};
    map<long double, long long> items;
    buildMap(0, n, n, 1.0L, prob, fact, counts, items);
    long long total = 1;
    for (int i = 0; i < n; i++) total *= 4;
    long double answer = 0.0L;
    while (total > 1) {
        map<long double, long long>::iterator first = items.begin();
        long double firstWeight = first->first;
        long long firstCount = first->second;
        if (firstCount >= 2) {
            long long pairs = firstCount / 2;
            long long remain = firstCount % 2;
            items.erase(first);
            if (remain > 0) items[firstWeight] = remain;
            items[firstWeight * 2.0L] += pairs;
            answer += pairs * firstWeight * 2.0L;
            total -= pairs;
        } else {
            map<long double, long long>::iterator second = next(first);
            long double secondWeight = second->first;
            long long secondCount = second->second;
            long long pairs = min(firstCount, secondCount);
            items.erase(first);
            if (secondCount == pairs) items.erase(second);
            else second->second -= pairs;
            long double merged = firstWeight + secondWeight;
            items[merged] += pairs;
            answer += pairs * merged;
            total -= pairs;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long double prob[4];
    while (cin >> n >> prob[0] >> prob[1] >> prob[2] >> prob[3])
        cout << fixed << setprecision(6) << (double)solve(n, prob) << '\n';
    return 0;
}
