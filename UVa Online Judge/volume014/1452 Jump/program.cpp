// Jump
// UVa ID: 1452
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.110s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 找到第m个被移除的元素（m=1表示第一个被移除的）
int findMthRemoved(int n, int k, int m) {
    // 使用递推公式计算
    int pos = (k - 1) % (n - m + 1);
    for (int i = n - m + 2; i <= n; i++) {
        pos = (pos + k) % i;
    }
    return pos + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        int n, k;
        cin >> n >> k;
        
        // 最后三个被移除的元素分别是第n个、第n-1个、第n-2个被移除的
        int last = findMthRemoved(n, k, n);        // 最后一个被移除的
        int secondLast = findMthRemoved(n, k, n - 1);  // 倒数第二个被移除的
        int thirdLast = findMthRemoved(n, k, n - 2);   // 倒数第三个被移除的
        
        cout << thirdLast << " " << secondLast << " " << last << "\n";
    }
    
    return 0;
}
