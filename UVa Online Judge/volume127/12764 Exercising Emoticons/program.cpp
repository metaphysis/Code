// Exercising Emoticons
// UVa ID: 12764
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 10个帧，每个帧3行，每行4个字符（点表示空格）
string frame[10][3] = {
    {"\\./.", ".|..", "/o\\."}, // 0
    {".o..", "/|\\.", "/.\\."}, // 1
    {"....", "....", "__\\o"}, // 2
    {"....", "....", "\\_\\o"}, // 3
    {"_o_.", ".|..", "/.\\."}, // 4
    {"\\o/.", ".|..", "/.\\."}, // 5
    {"\\o_.", "\\|..", ".|.."}, // 6
    {"\\o/.", "\\|/.", "...."}, // 7
    {"....", ".__o", "/..|"}, // 8
    {".o..", "(.).", "/.\\."} // 9
};

int main() {
    // 将帧中的点替换为空格
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < frame[i][j].size(); k++)
                if (frame[i][j][k] == '.')
                    frame[i][j][k] = ' ';
    
    int M;
    cin >> M;
    while (M--) {
        string seq;
        cin >> seq;
        int N = seq.size();
        string line0, line1, line2;
        for (int i = 0; i < N; ++i) {
            int d = seq[i] - '0';
            if (i > 0) { // 帧间加空格
                line0 += ' ';
                line1 += ' ';
                line2 += ' ';
            }
            line0 += frame[d][0];
            line1 += frame[d][1];
            line2 += frame[d][2];
        }
        cout << line0 << '\n';
        cout << line1 << '\n';
        cout << line2 << '\n';
        cout << '\n'; // 每部电影后空行
    }
    return 0;
}
