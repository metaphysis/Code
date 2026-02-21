// Working at the Restaurant
// UVa ID: 12198
// Verdict: Accepted
// Submission Date: 2026-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, cases = 0;
    while (cin >> n, n) { // 读取 N，为 0 则结束
        if (cases++) cout << '\n';
        int stack1 = 0, stack2 = 0; // 两个堆的盘子数量
        for (int i = 0; i < n; ++i) {
            string cmd;
            int m;
            cin >> cmd >> m;
            if (cmd == "DROP") {
                // 总是将新盘子放到堆1
                cout << "DROP 1 " << m << '\n';
                stack1 += m;
            } else { // cmd == "TAKE"
                // 先从堆2取（如果堆2有盘子）
                if (stack2 > 0) {
                    int takeFromStack2 = min(m, stack2);
                    if (takeFromStack2 > 0) {
                        cout << "TAKE 2 " << takeFromStack2 << '\n';
                        stack2 -= takeFromStack2;
                        m -= takeFromStack2;
                    }
                }
                // 如果还需要更多盘子（此时堆2一定为空）
                if (m > 0) {
                    // 将堆1所有盘子移动到堆2
                    if (stack1 > 0) {
                        cout << "MOVE 1->2 " << stack1 << '\n';
                        stack2 = stack1; // 移动后堆2的数量变为原来的堆1数量
                        stack1 = 0;
                    }
                    // 从堆2取需要的数量
                    cout << "TAKE 2 " << m << '\n';
                    stack2 -= m;
                }
            }
        }
    }
    return 0;
}
