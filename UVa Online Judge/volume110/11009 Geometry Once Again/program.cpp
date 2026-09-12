#include <bits/stdc++.h>
using namespace std;

long double getSize(long double a, long double b) {
    long double q, value;
    q = sqrtl(9.0L * a * a + 24.0L * b * b);
    value = a * a + 5.0L * b * b - b * q;
    return 2.0L * sqrtl(value);
}

int main() {
    long double a, b, size, sum;
    int start, end, k;
    while (cin >> a >> start >> end) {
        if (a == 0.0L && start == 0 && end == 0) break;
        sum = 0.0L;
        for (k = start; k <= end; k++) {
            b = a + k;
            size = getSize(a, b);
            sum += size;
        }
        cout << (long long)(sum + 0.5L) << '\n';
    }
    return 0;
}
