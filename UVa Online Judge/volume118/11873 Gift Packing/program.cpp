#include <bits/stdc++.h>
using namespace std;

int main() {
    long long radius, caseNo = 1;
    long long p, q, r, s, t;
    while (cin >> radius && radius) {
        p = 6LL * radius;
        q = 6LL * radius * radius;
        r = 8LL * radius * radius;
        s = 2LL * radius * radius;
        t = 32LL * radius * radius * radius * radius;
        cout << "Case " << caseNo++ << ": " << p << " " << q << " " << r << " " << s << " " << t << "\n";
    }
    return 0;
}
