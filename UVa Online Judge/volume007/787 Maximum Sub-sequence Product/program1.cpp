// Maximum Sub-sequence Product
// UVa ID: 787
// Verdict: Accepted
// Submission Date: 2026-08-31
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

cpp_int maximum_product(const cpp_int data[], int n) {
    cpp_int maximum = data[0], max_current = data[0], min_current = data[0];
    for (int i = 1; i < n; i++) {
        cpp_int next_max = max_current * data[i];
        cpp_int next_min = min_current * data[i];
        max_current = max(data[i], max(next_max, next_min));
        min_current = min(data[i], min(next_max, next_min));
        maximum = max(maximum, max_current);
    }
    return maximum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 0;
    cpp_int data[110];
    string number;
    while (cin >> number) {
        if (number == "-999999") {
            cout << maximum_product(data, n) << '\n';
            n = 0;
        } else {
            stringstream ss(number);
            ss >> data[n++];
        }
    }
    return 0;
}
