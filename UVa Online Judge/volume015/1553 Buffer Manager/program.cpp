#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, i, start, bestStart;
    long long currentSum, minSum;
    string part, buffer;
    while (cin >> n >> k) {
        buffer.clear();
        while (static_cast<int>(buffer.size()) < n) {
            cin >> part;
            buffer += part;
        }
        currentSum = 0;
        minSum = LLONG_MAX;
        start = 0;
        bestStart = -1;
        for (i = 0; i < n; i++) {
            if (buffer[i] == '*') {
                currentSum = 0;
                start = i + 1;
            } else {
                currentSum += buffer[i] - '0';
            }
            if (i - start + 1 > k) {
                currentSum -= buffer[start] - '0';
                start++;
            }
            if (i - start + 1 == k && currentSum < minSum) {
                minSum = currentSum;
                bestStart = start;
            }
        }
        if (bestStart == -1)
            cout << 0 << '\n';
        else
            cout << bestStart + 1 << '\n';
    }
    return 0;
}
