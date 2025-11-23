// Allergy Test
// UVa ID: 11691
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int numCases;
    cin >> numCases;
    while (numCases--) {
        int k;
        cin >> k;
        vector<int> d(k);
        for (int i = 0; i < k; i++) cin >> d[i];
        
        sort(d.begin(), d.end(), greater<int>());
        
        int ans = INT_MAX;
        for (int leftLen = 0; leftLen < d[0]; leftLen++) {
            int rightLen = d[0] - leftLen - 1;
            int totalDays = d[0];
            int leftSpace = leftLen;
            int rightSpace = rightLen;
            
            for (int i = 1; i < k; i++) {
                int useLeft = min(leftSpace, d[i] - 1);
                int useRight = min(rightSpace, d[i] - 1);
                
                if (useLeft > useRight) {
                    leftSpace = d[i] - useLeft - 1;
                    totalDays += leftSpace + 1;
                } else {
                    rightSpace = d[i] - useRight - 1;
                    totalDays += rightSpace + 1;
                }
            }
            ans = min(ans, totalDays);
        }
        
        cout << ans << endl;
    }
    return 0;
}
