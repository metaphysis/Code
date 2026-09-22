#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, h, w, b;
    while (cin >> n >> h >> w >> b) {
        if (n == 0 && h == 0 && w == 0 && b == 0) break;
        vector<int> bookH(b), bookW(b), used(b, 0);
        for (int i = 0; i < b; ++i) cin >> bookH[i] >> bookW[i];
        int base = b + 1, freeArea = n * h * w;
        for (int shelfId = 0; shelfId < n; ++shelfId) {
            vector<vector<int>> dp(b + 1, vector<int>(w + 1, 0));
            for (int i = 1; i <= b; ++i) {
                int bookId = i - 1, bookScore = bookH[bookId] * bookW[bookId] * base - 1;
                for (int cap = 0; cap <= w; ++cap) {
                    dp[i][cap] = dp[i - 1][cap];
                    if (!used[bookId] && bookH[bookId] <= h && bookW[bookId] <= cap) dp[i][cap] = max(dp[i][cap], dp[i - 1][cap - bookW[bookId]] + bookScore);
                }
            }
            if (dp[b][w] == 0) break;
            int cap = w;
            for (int i = b; i >= 1; --i) {
                int bookId = i - 1;
                if (dp[i][cap] != dp[i - 1][cap]) {
                    used[bookId] = 1;
                    freeArea -= bookH[bookId] * bookW[bookId];
                    cap -= bookW[bookId];
                }
            }
        }
        cout << freeArea << '\n';
    }
    return 0;
}
