#include <bits/stdc++.h>
using namespace std;

struct Member {
    long double s, t;
};

Member member[10005];
int n;
long double rest, limitS;

long double getValue(long double lambda) {
    long double minCost = 1e100L;
    for (int i = 0; i < n; i++) {
        long double cost = member[i].t + lambda * member[i].s;
        minCost = min(minCost, cost);
    }
    return rest * minCost - lambda * limitS;
}

long double getMinS(long double lambda) {
    long double minCost = 1e100L, minS = 1e100L;
    for (int i = 0; i < n; i++) {
        long double cost = member[i].t + lambda * member[i].s;
        if (cost < minCost) {
            minCost = cost;
            minS = member[i].s;
        } else if (fabsl(cost - minCost) < 1e-18L) minS = min(minS, member[i].s);
    }
    return minS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(2);
    while (testCount--) {
        long long d, l, w;
        cin >> n >> d >> l >> w;
        long double sumS = 0, sumT = 0, minS = 1e100L;
        for (int i = 0; i < n; i++) {
            cin >> member[i].s >> member[i].t;
            sumS += member[i].s;
            sumT += member[i].t;
            minS = min(minS, member[i].s);
        }
        rest = (long double)l - (long double)n * d;
        long double baseS = (long double)d * sumS;
        long double baseT = (long double)d * sumT;
        limitS = (long double)w - baseS;
        if (rest < 0 || limitS < 0 || rest * minS > limitS + 1e-12L) {
            cout << "No solution\n";
            continue;
        }
        if (rest == 0) {
            cout << (double)baseT << '\n';
            continue;
        }
        long double avgS = limitS / rest;
        long double low = 0, high = 1;
        while (getMinS(high) > avgS) high *= 2;
        long double answer = getValue(0);
        for (int i = 0; i < 120; i++) {
            long double mid = (low + high) / 2;
            answer = max(answer, getValue(mid));
            if (getMinS(mid) > avgS) low = mid;
            else high = mid;
        }
        answer = max(answer, getValue(low));
        answer = max(answer, getValue(high));
        answer += baseT;
        cout << (double)answer << '\n';
    }
    return 0;
}
