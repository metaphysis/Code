#include <bits/stdc++.h>
using namespace std;

long double calcWalk(int l) {
    long double sum, ways, cost;
    int k;
    sum = 0;
    ways = 0;
    cost = 1;
    for (k = 1; k <= l; k++) {
        cost *= l - 1;
        ways += l * cost;
        sum += k * l * cost;
    }
    return sum / ways;
}

long double calcPath(int l) {
    long double sum, ways, cnt;
    int k;
    sum = 0;
    ways = 0;
    cnt = l * (l - 1);
    for (k = 1; k <= l - 1; k++) {
        ways += cnt;
        sum += k * cnt;
        if (k < l - 1) cnt *= l - k - 1;
    }
    return sum / ways;
}

long double calcCycle(int l) {
    long double sum, ways, cnt;
    int k;
    sum = 0;
    ways = 0;
    cnt = (l - 1) * (l - 2);
    for (k = 3; k <= l; k++) {
        ways += cnt;
        sum += k * cnt;
        if (k < l) cnt *= l - k;
    }
    return sum / ways;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l;
    long double f1, f2, f3;
    while (cin >> l && l) {
        f1 = calcWalk(l);
        f2 = calcPath(l);
        f3 = calcCycle(l);
        cout << fixed << setprecision(4) << f1 << " " << f2 << " " << f3 << "\n";
    }
    return 0;
}
