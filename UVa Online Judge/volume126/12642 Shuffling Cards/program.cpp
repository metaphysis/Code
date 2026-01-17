// Shuffling Cards
// UVa ID: 12642
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1200;

int n;
int perm[MAXN];        // 原始置换 f
int cur[MAXN];         // 当前置换
int tmp[MAXN];         // 临时数组
int cyclePos[MAXN];    // 每个位置在所属环中的序号（从0开始）
int cycleId[MAXN];     // 每个位置所属环的编号
vector<int> cycles[MAXN]; // 存储每个环的元素
bool visited[MAXN];

// 找出所有环并存储
void decomposeCycles() {
    memset(visited, false, sizeof visited);
    int cid = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int cur = i;
            while (!visited[cur]) {
                visited[cur] = true;
                cycleId[cur] = cid;
                cyclePos[cur] = cycles[cid].size();
                cycles[cid].push_back(cur);
                cur = perm[cur];
            }
            cid++;
        }
    }
}

int main() {
    ll r;
    while (cin >> n >> r) {
        for (int i = 1; i <= n; i++) cin >> perm[i];
        // 如果 r=0，置换为单位置换
        if (r == 0) {
            for (int i = 1; i <= n; i++) {
                if (i > 1) cout << ' ';
                cout << i;
            }
            cout << '\n';
            continue;
        }
        // 初始化环数组
        for (int i = 0; i < n; i++) cycles[i].clear();
        decomposeCycles();
        // 计算最终位置
        for (int i = 1; i <= n; i++) {
            int cid = cycleId[i];
            int pos = cyclePos[i];
            ll cycleLength = cycles[cid].size();
            int rr = r % cycleLength;
            // 在环中移动 r 步
            int newPos = (pos + rr) % cycleLength;
            int target = cycles[cid][newPos];
            cur[i] = target;
        }
        // 输出结果
        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << ' ';
            cout << cur[i];
        }
        cout << '\n';
    }
    return 0;
}
