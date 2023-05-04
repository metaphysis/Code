// Low Power
// UVa ID: 1577
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
        int low = 0, high = b[t - 1] - b[0], r, middle;
        while (low <= high) {
            middle = (low + high) >> 1;
            int cnt = 0, idx = 0;
            while (idx < t - 1) {
                if (b[idx + 1] <= b[idx] + middle) idx += 2, cnt++;
                else idx++;
            }
            if (cnt >= k) { r = middle; high = middle - 1; }
            else low = middle + 1;
        }
        cout << r << '\n';
        
    }
    return 0;
}
