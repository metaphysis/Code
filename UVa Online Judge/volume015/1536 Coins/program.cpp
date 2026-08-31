#include <bits/stdc++.h>
using namespace std;

long long getMaxN(int k) {
    long long power, maxN;
    power = 1;
    for (int i = 1; i <= k; i++)
        power = min(1000LL, power * 3);
    maxN = (power + 3) / 2;
    return maxN;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, coinCount, k;
    cin >> testCount;
    while (testCount--) {
        cin >> coinCount >> k;
        if (coinCount <= getMaxN(k))
            cout << "POSSIBLE\n";
        else
            cout << "IMPOSSIBLE\n";
    }
    return 0;
}
