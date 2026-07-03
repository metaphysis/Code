// You Who
// UVa ID: 649
// Verdict: Accepted
// Submission Date: 2026-07-02
// UVa Run Time: 0.510s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    bool firstCase = true;
    while (cin >> N) {
        // 读入认识关系
        vector<vector<bool>> know(N, vector<bool>(N, false));
        for (int i = 0; i < N; ++i) know[i][i] = true;

        for (int i = 0; i < N; ++i) {
            int id, k;
            cin >> id >> k;
            --id;
            for (int j = 0; j < k; ++j) {
                int v; cin >> v; --v;
                know[id][v] = know[v][id] = true;
            }
        }

        // 构建每个学生的不认识掩码
        vector<int> notKnow(N, 0);
        int fullMask = (1 << N) - 1;
        for (int i = 0; i < N; ++i) {
            int mask = 0;
            for (int j = 0; j < N; ++j)
                if (i != j && !know[i][j]) mask |= (1 << j);
            notKnow[i] = mask;
        }

        int target = (N + 1) / 2;          // 较大班级的人数
        int bestMax = N + 1;
        int bestMask = 0;

        // Gosper's hack: 枚举所有大小为 target 的子集
        int mask = (1 << target) - 1;
        int limit = 1 << N;
        while (mask < limit) {
            int comp = fullMask ^ mask;
            int maxDeg = 0;
            for (int i = 0; i < N; ++i) {
                int d;
                if (mask & (1 << i))
                    d = __builtin_popcount((unsigned)(notKnow[i] & mask));
                else
                    d = __builtin_popcount((unsigned)(notKnow[i] & comp));
                if (d > maxDeg) maxDeg = d;
            }
            if (maxDeg < bestMax) {
                bestMax = maxDeg;
                bestMask = mask;
            }
            // 生成下一个组合
            int c = mask & -mask;
            int r = mask + c;
            mask = (((r ^ mask) >> 2) / c) | r;
        }

        // 输出，两个用例之间空一行
        if (!firstCase) cout << '\n';
        firstCase = false;

        cout << bestMax << '\n';

        vector<int> classA, classB;
        for (int i = 0; i < N; ++i) {
            if (bestMask & (1 << i)) classA.push_back(i + 1);
            else classB.push_back(i + 1);
        }

        cout << classA.size();
        for (int id : classA) cout << ' ' << id;
        cout << '\n';

        cout << classB.size();
        for (int id : classB) cout << ' ' << id;
        cout << '\n';
    }

    return 0;
}
