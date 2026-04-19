// Binary Tree
// UVa ID: 12685
// Verdict: Accepted
// Submission Date: 2026-04-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 21092013;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testcase;
    cin >> testcase;
    for (int caseNo = 1; caseNo <= testcase; ++caseNo) {
        string S, T;
        cin >> S >> T;
        
        // 记录从根到起始节点的路径（反向存储，栈顶是最后一步）
        stack<char> pathStack;
        for (char c : S) {
            if (c == 'L' || c == 'R') pathStack.push(c);
            else if (!pathStack.empty()) pathStack.pop();
        }
        
        int total = 1;      // 可达节点总数
        int leftSon = 1;    // 可以向左扩展的节点数
        int rightSon = 1;   // 可以向右扩展的节点数
        
        for (char c : T) {
            if (c == 'L') {
                total = (total + leftSon) % MOD;
                rightSon = (rightSon + leftSon) % MOD;
            } else if (c == 'R') {
                total = (total + rightSon) % MOD;
                leftSon = (leftSon + rightSon) % MOD;
            } else { // 'U'
                if (!pathStack.empty()) {
                    total = (total + 1) % MOD;
                    if (pathStack.top() == 'L') rightSon = (rightSon + 1) % MOD;
                    else leftSon = (leftSon + 1) % MOD;
                    pathStack.pop();
                }
            }
        }
        
        cout << "Case " << caseNo << ": " << total << '\n';
    }
    return 0;
}
