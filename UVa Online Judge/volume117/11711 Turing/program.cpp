// Turing
// UVa ID: 11711
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Rule {
    int nextState;
    int writeBit;
    int delta; // +1 for R, -1 for L
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M && (N != 0 || M != 0)) {
        // 存储规则，索引为状态和读入位，nextState = -1 表示无规则
        Rule rule[1001][2];
        for (int i = 0; i <= 1000; ++i)
            for (int b = 0; b < 2; ++b)
                rule[i][b].nextState = -1;

        for (int i = 0; i < N; ++i) {
            int qPrev, cPrev, qNext, cNext;
            char mov;
            cin >> qPrev >> cPrev >> qNext >> cNext >> mov;
            rule[qPrev][cPrev].nextState = qNext;
            rule[qPrev][cPrev].writeBit = cNext;
            rule[qPrev][cPrev].delta = (mov == 'R') ? 1 : -1;
        }

        for (int t = 0; t < M; ++t) {
            int X, Y;
            cin >> X >> Y;

            int tape[1000] = {0};
            for (int i = 0; i < X; ++i) tape[i] = 1;

            int pos = 0, q = 0, step = 0;
            bool stopped = false;
            bool error = false;

            while (true) {
                if (step >= 10000) {
                    cout << "TLE\n";
                    error = true;
                    break;
                }

                int c = tape[pos];
                Rule &r = rule[q][c];
                if (r.nextState == -1) {
                    stopped = true;
                    break;
                }

                tape[pos] = r.writeBit;
                q = r.nextState;
                pos += r.delta;
                ++step;

                if (pos < 0 || pos >= 1000) {
                    cout << "MLE\n";
                    error = true;
                    break;
                }
            }

            if (error) continue;

            // 计算输出值：从位置0开始连续1的个数
            int result = 0;
            while (result < 1000 && tape[result] == 1) ++result;

            if (result == Y) cout << "AC\n";
            else cout << "WA\n";
        }
    }

    return 0;
}
