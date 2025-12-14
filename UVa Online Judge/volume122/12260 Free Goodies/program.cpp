// Free Goodies
// UVa ID: 12260
// Verdict: Accepted
// Submission Date: 2025-12-10
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Candy {
    int p, j;
};

bool cmp(const Candy& a, const Candy& b) {
    if (a.p != b.p) return a.p > b.p;
    return a.j < b.j;
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string first; cin >> first;
        vector<Candy> candies(n);
        int totalP = 0;
        
        for (int i = 0; i < n; i++) {
            cin >> candies[i].p >> candies[i].j;
            totalP += candies[i].p;
        }
        
        sort(candies.begin(), candies.end(), cmp);
        
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        vector<vector<int>> val(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            int num;
            if (first == "Petra") {
                num = i / 2;
            } else {
                num = (i + 1) / 2;
            }
            
            for (int j = 1; j <= num; j++) {
                dp[i][j] = dp[i - 1][j];
                val[i][j] = val[i - 1][j];
                
                int candJan = dp[i - 1][j - 1] + candies[i - 1].j;
                int candVal = val[i - 1][j - 1] + candies[i - 1].p;
                
                if (candJan > dp[i][j]) {
                    dp[i][j] = candJan;
                    val[i][j] = candVal;
                } else if (candJan == dp[i][j] && candVal < val[i][j]) {
                    val[i][j] = candVal;
                }
            }
        }
        
        int maxJan = 0, minVal = 0;
        int maxTake;
        if (first == "Petra") {
            maxTake = n / 2;
        } else {
            maxTake = (n + 1) / 2;
        }
        
        for (int j = 1; j <= maxTake; j++) {
            if (dp[n][j] > maxJan) {
                maxJan = dp[n][j];
                minVal = val[n][j];
            }
        }
        
        int petraVal = totalP - minVal;
        cout << petraVal << " " << maxJan << endl;
    }
    return 0;
}
