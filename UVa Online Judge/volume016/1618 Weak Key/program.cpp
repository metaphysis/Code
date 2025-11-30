// Weak Key
// UVa ID: 1618
// Verdict: Accepted
// Submission Date: 2025-11-28
// UVa Run Time: 0.360s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

bool isWeakKey(const vector<int>& arr) {
    int n = arr.size();
    
    // 模式1: N_q > N_s > N_p > N_r
    for (int q = 1; q < n - 2; q++) {
        // 预处理：对于每个可能的s，快速判断是否存在满足条件的p和r
        int maxLeft = -INF;  // q左边最大值
        for (int p = 0; p < q; p++) {
            maxLeft = max(maxLeft, arr[p]);
        }
        
        // 对于每个s > q+1，如果arr[s] < arr[q]
        // 我们需要找到p使得arr[p] < arr[s]，且存在r在q和s之间使得arr[r] < arr[p]
        for (int s = q + 2; s < n; s++) {
            if (arr[s] < arr[q]) {
                // 在q左边找到小于arr[s]的最大值作为候选p
                int candidateP = -INF;
                for (int p = 0; p < q; p++) {
                    if (arr[p] < arr[s] && arr[p] > candidateP) {
                        candidateP = arr[p];
                    }
                }
                
                if (candidateP != -INF) {
                    // 检查q和s之间是否存在r使得arr[r] < candidateP
                    int minBetween = INF;
                    for (int r = q + 1; r < s; r++) {
                        minBetween = min(minBetween, arr[r]);
                    }
                    if (minBetween < candidateP) {
                        return true;
                    }
                }
            }
        }
    }
    
    // 模式2: N_q < N_s < N_p < N_r
    for (int q = 1; q < n - 2; q++) {
        int minLeft = INF;  // q左边最小值
        for (int p = 0; p < q; p++) {
            minLeft = min(minLeft, arr[p]);
        }
        
        for (int s = q + 2; s < n; s++) {
            if (arr[s] > arr[q]) {
                // 在q左边找到大于arr[s]的最小值作为候选p
                int candidateP = INF;
                for (int p = 0; p < q; p++) {
                    if (arr[p] > arr[s] && arr[p] < candidateP) {
                        candidateP = arr[p];
                    }
                }
                
                if (candidateP != INF) {
                    // 检查q和s之间是否存在r使得arr[r] > candidateP
                    int maxBetween = -INF;
                    for (int r = q + 1; r < s; r++) {
                        maxBetween = max(maxBetween, arr[r]);
                    }
                    if (maxBetween > candidateP) {
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        int k;
        cin >> k;
        vector<int> key(k);
        for (int i = 0; i < k; i++) cin >> key[i];
        
        if (isWeakKey(key)) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}
