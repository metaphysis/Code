// Baggage
// UVa ID: 1697
// Verdict: Accepted
// Submission Date: 2025-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 打印移动指令
void print(int x, int y) {
    cout << x << " to " << y << endl;
}

// 递归处理函数
// l: 当前处理区间左边界
// r: 当前处理区间右边界
void dfs(int l, int r) {
    int len = r - l + 1;  // 当前区间长度
    
    // 长度小于等于2不需要处理
    if (len <= 2) return;
    
    // 处理基本情况
    if (len == 10) {  // n = 5
        print(r - 2, l - 2);
        print(l + 2, r - 2);
        print(r - 4, l + 2);
        print(l - 1, r - 4);
        print(r - 1, l - 1);
        return;
    }
    
    if (len == 12) {  // n = 6
        print(r - 2, l - 2);
        print(r - 5, r - 2);
        print(l + 1, r - 5);
        print(r - 6, l + 1);
        print(l - 1, r - 6);
        print(r - 1, l - 1);
        return;
    }
    
    if (len == 14) {  // n = 7
        print(l + 7, l - 2);
        print(l + 4, l + 7);
        print(l + 11, l + 4);
        print(l + 2, l + 11);
        print(l + 8, l + 2);
        print(l - 1, l + 8);
        print(l + 12, l - 1);
        return;
    }
    
    // 通用递归情况：长度 >= 16 (n >= 8)
    // 前两步：右边一对移到左边空位，左边一对移到上一步的空位
    print(r - 2, l - 2);
    print(l + 2, r - 2);
    
    // 递归处理中间部分（规模减少4）
    dfs(l + 4, r - 4);
    
    // 最后两步：完成排序
    print(l - 1, r - 5);
    print(r - 1, l - 1);
}

int main() {
    int n;
    bool first = true;
    
    while (cin >> n) {
        // 测试用例之间用空行分隔
        if (!first) cout << endl;
        first = false;
        
        // n = 3 的特殊情况
        if (n == 3) {
            print(2, -1);
            print(5, 2);
            print(3, -3);
        } else {
            // 递归处理一般情况
            dfs(1, 2 * n);
        }
    }
    
    return 0;
}
