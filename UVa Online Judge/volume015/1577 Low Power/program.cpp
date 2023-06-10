// Low Power
// UVa ID: 1577
// Verdict: Accepted
// Submission Date: 2023-06-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, k, b[1000100];
    while (cin >> n >> k) {
        int t = 2 * n * k;
        for (int i = 0; i < t; i++) cin >> b[i];
        sort(b, b + t);
        int low = b[1] - b[0], high = b[t - 1] - b[0], r, middle;
        while (low <= high) {
            middle = (low + high) >> 1;
            int cnt = 0, idx = 0, used = 0;
            while (idx < t - 1) {
                if (b[idx + 1] <= b[idx] + middle) idx += 2, cnt++, used += 2;
                else idx++, used++;
                if (used > 2 * cnt * k || cnt == n) break;
            }
            if (cnt == n) { r = middle; high = middle - 1; }
            else low = middle + 1;
        }
        cout << r << '\n';
        
    }
    return 0;
}
