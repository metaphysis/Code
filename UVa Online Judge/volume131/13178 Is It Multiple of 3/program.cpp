// Is It Multiple of 3
// UVa ID: 13178
// Verdict: Accepted
// Submission Date: 2023-06-17
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<int, long long> cache;

long long getSubSum(int n) {
    if (cache.count(n)) return cache[n];
    long long s = 0;
    if (n == 2) s = 45;
    else {
        for (int i = 1; i <= 9; i++) {
            s += 1LL * i * pow(10, n - 3);
            s += getSubSum(n - 1);
        }
    }
    return cache[n] = s;
}

long long getSum(string n) {
    long long s = 0;
    if (n.length() > 1) {
        long long p = pow(10, n.length() - 1);
        int h = n.front() - '0';
        for (int i = 1; i < h; i++) {
            s += i * p;
            s += getSubSum(n.length());
        }
        s += 1LL * h * (stoi(n.substr(1)) + 1);
        return s + getSum(n.substr(1));
    } else {
        int nn = stoi(n);
        for (int i = 1; i <= nn; i++) s += i;
    }
    return s;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    string n;
    cin >> T;
    while (T--) {
        cin >> n;
        long long s = getSum(n);
        if (s % 3 == 0) cout << "YES";
        else cout << "NO";
        cout << '\n';
    }
    return 0;
}
