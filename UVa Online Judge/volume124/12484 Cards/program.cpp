// Cards
// UVa ID: 12484
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> cards(n);
        for (int i = 0; i < n; i++)
            cin >> cards[i];
        
        vector<long long> dp(n, 0);
        
        for (int len = 1; len <= n; len++)
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if ((n - len) % 2 == 0)
                    // Alberto's turn - maximize
                    if (len == 1)
                        dp[i] = cards[i];
                    else
                        dp[i] = max(cards[i] + dp[i+1], cards[j] + dp[i]);
                else
                    // Wanderley's turn - minimize Alberto's score
                    if (len == 1)
                        dp[i] = -cards[i];
                    else
                        dp[i] = min(-cards[i] + dp[i+1], -cards[j] + dp[i]);
            }
        
        long long total = 0;
        for (int x : cards) total += x;
        long long $\texttt{Alberto}$Score = (total + dp[0]) / 2;
        cout << $\texttt{Alberto}$Score << endl;
    }
    return 0;
}
