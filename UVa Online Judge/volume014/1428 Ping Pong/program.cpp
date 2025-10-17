// Ping Pong
// UVa ID: 1428
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20005;      // 最大玩家数量
const int MAXVAL = 100005;   // 最大技能值

int T, N;                    // T:测试用例数, N:玩家数
int a[MAXN];                 // 存储玩家技能值
int leftLess[MAXN], leftGreater[MAXN], rightLess[MAXN], rightGreater[MAXN]; // 左右统计数组

// 树状数组
int BIT[MAXVAL];

// 更新树状数组
void update(int idx, int val) {
    while (idx < MAXVAL) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

// 查询前缀和
int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += BIT[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 1; i <= N; i++) {
            cin >> a[i];
        }

        // 从左到右扫描，计算左边小于和大于当前技能值的人数
        memset(BIT, 0, sizeof(BIT));
        for (int i = 1; i <= N; i++) {
            leftLess[i] = query(a[i] - 1);        // 查询小于a[i]的数量
            leftGreater[i] = (i - 1) - leftLess[i]; // 左边总人数减去小于的就是大于的
            update(a[i], 1);                      // 标记当前技能值已出现
        }

        // 从右到左扫描，计算右边小于和大于当前技能值的人数
        memset(BIT, 0, sizeof(BIT));
        for (int i = N; i >= 1; i--) {
            rightLess[i] = query(a[i] - 1);       // 查询小于a[i]的数量
            rightGreater[i] = (N - i) - rightLess[i]; // 右边总人数减去小于的就是大于的
            update(a[i], 1);                      // 标记当前技能值已出现
        }

        // 计算总比赛数
        long long ans = 0;
        for (int i = 1; i <= N; i++) {
            ans += (long long)leftLess[i] * rightGreater[i] + (long long)leftGreater[i] * rightLess[i];
        }

        cout << ans << "\n";
    }

    return 0;
}
