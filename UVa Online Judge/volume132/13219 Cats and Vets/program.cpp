#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;
using BigInt = cpp_int;

int main() {
    BigInt m, n;
    while (cin >> m >> n) {
        if (m == 2 && n == 2) cout << 2 << '\n';
        else if (n == 1 && m % 2 == 1) cout << (m + 1) / 2 << '\n';
        else {
            BigInt r = 3 * m + 4 * n;
            if (r % 6 != 0) r = r / 6 + 1;
            else r /= 6;
            cout << r << '\n';
        }
    }
    return 0;
}
