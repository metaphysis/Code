#include <iostream>
#include <cmath>
using namespace std;

long long minimumSteps(long long d) {
    if (d == 0) return 0;
    long long k = static_cast<long long>(sqrt(static_cast<long double>(d)));
    while ((k + 1) * (k + 1) <= d) ++k;
    while (k * k > d) --k;
    if (d == k * k) return 2 * k - 1;
    if (d <= k * k + k) return 2 * k;
    return 2 * k + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        long long x, y;
        cin >> x >> y;
        cout << minimumSteps(y - x) << '\n';
    }
    return 0;
}
