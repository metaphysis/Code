// Consistent Verdicts
// UVa ID: 12435
// Verdict: Accepted
// Submission Date: 2025-11-24
// UVa Run Time: 0.500s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        int n;
        cin >> n;
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++)
            cin >> x[i] >> y[i];
        
        vector<long long> dist;
        dist.reserve(n * (n - 1) / 2);
        
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                long long dx = x[i] - x[j];
                long long dy = y[i] - y[j];
                dist.push_back(dx * dx + dy * dy);
            }
        
        sort(dist.begin(), dist.end());
        int uniqueCount = unique(dist.begin(), dist.end()) - dist.begin();
        
        cout << "Case " << caseNum << ": " << uniqueCount + 1 << endl;
    }
    return 0;
}
