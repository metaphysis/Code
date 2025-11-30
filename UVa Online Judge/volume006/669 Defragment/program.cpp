// Defragment
// UVa ID: 669
// Verdict: Accepted
// Submission Date: 2025-11-27
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10010;
int belong[MAXN], where[MAXN];
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, K, S;
        cin >> N >> K;
        memset(where, 0, sizeof where);
        memset(belong, 0, sizeof belong);
        int dataId = 0;
        for (int dt = 1; dt <= K; dt++) {
            cin >> S;
            int clusterId;
            vector<int> clusters;
            for (int i = 1; i <= S; i++) {
                cin >> clusterId;
                dataId++;
                // 构建双向链表
                // 簇 dataId 的数据目前位于簇 clusterId
                where[dataId] = clusterId;
                // 位于簇 clusterId 的数据属于簇 dataId
                belong[clusterId] = dataId;
            }
        }
        int defragmented = 0;
        while (true) {
            // 寻找空簇
            int dataToMove = -1, empty = -1, done = 0;
            for (int i = 1; i <= dataId; i++) {
                // 计数归位数据的数量
                if (where[i] == i) { done++; continue; }
                // 当前簇未存储数据
                if (!belong[i]) { empty = i; break; }
                // 存有未归位数据
                dataToMove = i;
            }
            // 所有数据已经归位
            if (done == dataId) break;
            // 找到空簇，开始处理
            if (empty != -1) {
                while (true) {
                    if (!where[empty]) break;
                    cout << where[empty] << ' ' << empty << '\n';
                    // 记录空簇
                    int tmp = where[empty];
                    // 设置数据已经归位
                    where[empty] = empty;
                    belong[empty] = empty;
                    // 设置空簇
                    empty = tmp;
                }
                // 正确设置空簇的状态
                belong[empty] = 0;
            } else {
                // 没有找到空簇，说明所有应该存储数据的簇被占用，
                // 未归位的簇构成一个环或多个环，任选一个未归位的簇开始处理
                // 先寻找一个空簇作为中转，根据题目约束，该簇肯定存在
                for (int i = 1; i <= N; i++)
                    if (!belong[i]) {
                        empty = i;
                        break;
                    }
                // 将环的起始簇移动到中转位置
                cout << dataToMove << ' ' << empty << '\n';
                // 记录环的起始簇
                int start = dataToMove;
                // 沿着环移动数据
                while (true) {
                    // 如果数据来源是环的起点，移动后退出
                    if (where[dataToMove] == start) {
                        cout << empty << ' ' << dataToMove << '\n';
                        // 设置数据已归位
                        where[dataToMove] = dataToMove;
                        belong[dataToMove] = dataToMove;
                        // 可以不设置空簇的状态，因为寻找的空簇就满足此条件
                        // belong[empty] = 0;
                        break;
                    }
                    cout << where[dataToMove] << ' ' << dataToMove << '\n';
                    // 设置数据已归位
                    int tmp = where[dataToMove];
                    where[dataToMove] = dataToMove;
                    belong[dataToMove] = dataToMove;
                    dataToMove = tmp;
                }
            }
            defragmented = 1;
        }
        if (!defragmented) cout << "No optimization needed\n";
        if (T) cout << '\n';
    }
    return 0;
}
