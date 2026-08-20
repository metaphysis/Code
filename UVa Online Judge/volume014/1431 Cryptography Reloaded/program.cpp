#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

cpp_int sqrtInt(const cpp_int &x) {
    if (x < 2) return x;
    cpp_int low = 0, high = 1;
    while (high * high <= x) high <<= 1;
    while (low + 1 < high) {
        cpp_int mid = (low + high) >> 1;
        if (mid * mid <= x) low = mid;
        else high = mid;
    }
    return low;
}

int solve() {
    string ns, ds, es;
    int caseNo = 1;
    while (cin >> ns >> ds >> es) {
        cpp_int n(ns), d(ds), kVal, phi, sum, delta, root, pAns = 0, qAns = 0;
        int e = stoi(es);
        if (n == 0 && d == 0 && e == 0) break;
        kVal = d * e - 1;
        bool found = false;
        for (int k = 1; k < e; k++) {
            if (kVal % k != 0) continue;
            phi = kVal / k;
            sum = n - phi + 1;
            delta = sum * sum - 4 * n;
            if (delta < 0) continue;
            root = sqrtInt(delta);
            if (root * root != delta) continue;
            if ((sum - root) % 2 != 0) continue;
            pAns = (sum - root) / 2;
            qAns = (sum + root) / 2;
            if (pAns > 1 && pAns < qAns && pAns * qAns == n) {
                found = true;
                break;
            }
        }
        cout << "Case #" << caseNo++ << ": " << pAns << " " << qAns << "\n";
    }
    return 0;
}

int main() {
    string ns, ds, es;
    int caseNo = 1;
    while (cin >> ns >> ds >> es) {
        cpp_int n(ns), d(ds), kVal, phi, sum, delta, root, pAns = 0, qAns = 0;
        int e = stoi(es);
        if (n == 0 && d == 0 && e == 0) break;
        kVal = d * e - 1;
        bool found = false;
        for (int k = 1; k < e; k++) {
            if (kVal % k != 0) continue;
            phi = kVal / k;
            sum = n - phi + 1;
            delta = sum * sum - 4 * n;
            if (delta < 0) continue;
            root = sqrtInt(delta);
            if (root * root != delta) continue;
            if ((sum - root) % 2 != 0) continue;
            pAns = (sum - root) / 2;
            qAns = (sum + root) / 2;
            if (pAns > 1 && pAns < qAns && pAns * qAns == n) {
                found = true;
                break;
            }
        }
        cout << "Case #" << caseNo++ << ": " << pAns << " " << qAns << "\n";
    }
    return 0;
}
