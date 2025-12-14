// Movement of Reading Head
// UVa ID: 680
// Verdict: Accepted
// Submission Date: 2025-12-13
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int testCases;
    cin >> testCases;
    for (int tc = 1; tc <= testCases; ++tc) {
        int K, N, P;
        cin >> K >> N;
        vector<int> L(K + 1);          // 文件长度，索引从1开始
        for (int i = 1; i <= K; ++i) cin >> L[i];
        vector<int> PF(K + 1);         // 起始块号，索引从1开始
        for (int i = 1; i <= K; ++i) cin >> PF[i];
        cin >> P;

        // 计算每个文件在存储空间S中的起始位置（0-based）
        vector<int> startPos(K + 1, 0);
        for (int i = 2; i <= K; ++i) startPos[i] = startPos[i - 1] + L[i - 1];

        // 当前每个文件要读取的块号（1-based）
        vector<int> curBlock = PF;

        // 读取头当前位置（绝对位置，0-based）
        int currentPos = startPos[1] + (PF[1] - 1);
        long long totalMove = 0;

        // 模拟P次读取
        for (int t = 1; t <= P; ++t) {
            // 确定当前读取的文件索引（0-based，对应文件F_{idx+1}）
            int fileIdx = (t - 1) % K + 1;  // 转换为1-based文件索引

            // 计算下一个要读取的块的绝对位置
            int nextPos = startPos[fileIdx] + (curBlock[fileIdx] - 1);

            if (t > 1) {
                totalMove += abs(nextPos - currentPos);
                currentPos = nextPos;
            } else {
                // 第一次读取，读取头已经在目标位置，不需要移动
                currentPos = nextPos;
            }

            // 更新该文件的下一个读取块号
            if (curBlock[fileIdx] == L[fileIdx]) curBlock[fileIdx] = 1;
            else curBlock[fileIdx] += 1;
        }

        cout << totalMove << endl;
    }
    int endMarker;
    cin >> endMarker;  // 读入-1，表示输入结束
    return 0;
}
