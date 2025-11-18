// Transcribed Books
// UVa ID: 12184
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.180s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int c;
        cin >> c;
        vector<long long> diffs;
        vector<long long> a10s;
        
        for (int i = 0; i < c; i++) {
            long long sum = 0;
            for (int j = 0; j < 9; j++) {
                long long x;
                cin >> x;
                sum += x;
            }
            long long a10;
            cin >> a10;
            diffs.push_back(sum - a10);
            a10s.push_back(a10);
        }
        
        long long g = 0;
        for (long long d : diffs) {
            g = __gcd(g, abs(d));
        }
        
        if (g == 0 || g == 1) {
            cout << "impossible\n";
            continue;
        }
        
        // 检查 g 是否大于所有的 a10
        bool valid = true;
        for (long long a10 : a10s) {
            if (a10 >= g) {
                valid = false;
                break;
            }
        }
        
        if (valid) {
            cout << g << "\n";
        } else {
            cout << "impossible\n";
        }
    }
    return 0;
}
