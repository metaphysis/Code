#include <bits/stdc++.h>
using namespace std;

// n表示棋盘的大小，cnt记录符合要求的布局数量
int n, cnt = 0;

// 递归实现回溯搜索
// 参数D为回溯的层次，L表示左侧的禁止列，M表示已选择列，R表示右侧禁止列
void dfs(int D, int L, int M, int R) {
    // 回溯层次达到n表明这是一种符合要求的放置方案
    if (D == n) { cnt++; return; }
    // 查找当前行的可选列
    for (int i = 0; i < n; i++)
        // 通过位运算技巧选择可行列
        if (((1 << i) & (L | M | R)) == 0)
            // 记录已选列、左侧禁止列、右侧禁止列，然后继续下一层回溯
            dfs(D + 1, (L | (1 << i)) << 1, M | (1 << i), (R | (1 << i)) >> 1);
}

int main() {
    clock_t start, finish;
    start = clock();
    while (cin >> n) {
        cnt = 0;
        dfs(0, 0, 0, 0);
        cout << "N = " << n << ": " << cnt << '\n';
    }
    finish = clock();
    cout << (double)(finish - start) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
