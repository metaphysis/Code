// Gift Exchanging
// UVa ID: 10417
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.440s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int t, n;
int cnt[5];
double prob[12][5];
vector<int> assignment;
double totalProb;
double giftProb[5];

void dfs(int person, vector<int>& currentCount) {
    if (person == n) {
        bool valid = true;
        for (int i = 0; i < 5; i++) {
            if (currentCount[i] != cnt[i]) {
                valid = false;
                break;
            }
        }
        if (!valid) return;
        
        double p = 1.0;
        for (int i = 0; i < n; i++) {
            p *= prob[i][assignment[i]];
        }
        totalProb += p;
        
        for (int g = 0; g < 5; g++) {
            if (cnt[g] > 0) {
                int friendGiftCount = 0;
                for (int i = 0; i < n; i++) {
                    if (assignment[i] == g && i == 0) {
                        friendGiftCount++;
                    }
                }
                giftProb[g] += p * (friendGiftCount * 1.0 / cnt[g]);
            }
        }
        return;
    }
    
    for (int g = 0; g < 5; g++) {
        if (currentCount[g] < cnt[g]) {
            assignment[person] = g;
            currentCount[g]++;
            dfs(person + 1, currentCount);
            currentCount[g]--;
        }
    }
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < 5; i++) cin >> cnt[i];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 5; j++) cin >> prob[i][j];
        
        assignment.resize(n);
        totalProb = 0.0;
        for (int i = 0; i < 5; i++) giftProb[i] = 0.0;
        
        vector<int> currentCount(5, 0);
        dfs(0, currentCount);
        
        int bestGift = -1;
        double bestProb = -1.0;
        for (int g = 0; g < 5; g++) {
            if (cnt[g] > 0) {
                double p = giftProb[g] / totalProb;
                if (p > bestProb) {
                    bestProb = p;
                    bestGift = g;
                }
            }
        }
        
        cout << bestGift + 1 << " " << fixed << setprecision(3) << bestProb << endl;
    }
    return 0;
}
