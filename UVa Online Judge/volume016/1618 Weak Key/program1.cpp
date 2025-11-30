// Weak Key
// UVa ID: 1618
// Verdict: Accepted
// Submission Date: 2025-11-28
// UVa Run Time: 0.240s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

bool isWeakKey(const vector<int>& arr) {
    int n = arr.size();
    
    // 预处理每个区间的最小值和最大值
    vector<vector<int>> minInRange(n, vector<int>(n, INF));
    vector<vector<int>> maxInRange(n, vector<int>(n, -INF));
    
    for (int i = 0; i < n; i++) {
        minInRange[i][i] = maxInRange[i][i] = arr[i];
        for (int j = i + 1; j < n; j++) {
            minInRange[i][j] = min(minInRange[i][j - 1], arr[j]);
            maxInRange[i][j] = max(maxInRange[i][j - 1], arr[j]);
        }
    }
    
    // 预处理每个位置左边的有序数组
    vector<multiset<int>> leftSets(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            leftSets[i].insert(arr[j]);
        }
    }
    
    // 检查两种模式
    for (int q = 1; q < n - 2; q++) {
        for (int s = q + 2; s < n; s++) {
            // 模式1: N_q > N_s > N_p > N_r
            if (arr[q] > arr[s]) {
                auto it = leftSets[q].lower_bound(arr[s]);
                if (it != leftSets[q].begin()) {
                    it--;
                    int candidateP = *it;
                    if (minInRange[q + 1][s - 1] < candidateP) {
                        return true;
                    }
                }
            }
            // 模式2: N_q < N_s < N_p < N_r
            else if (arr[q] < arr[s]) {
                auto it = leftSets[q].upper_bound(arr[s]);
                if (it != leftSets[q].end()) {
                    int candidateP = *it;
                    if (maxInRange[q + 1][s - 1] > candidateP) {
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
        
        cout << (isWeakKey(key) ? "YES" : "NO") << endl;
    }
    
    return 0;
}

