// Hexagonal Puzzle
// UVa ID: 12639
// Verdict: Accepted
// Submission Date: 2026-05-31
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> pieces(7, vector<int>(6));
bool used[7];
int centerIdx;
int order[6];   // order[0]=块1, order[1]=块2, ..., order[5]=块6
int rot[6];     // 每个周围块的旋转量

// 获取块 idx 旋转 r 后第 side 条边的数字
int getVal(int idx, int r, int side) {
    return pieces[idx][(side + r) % 6];
}

bool dfs(int pos) {
    if (pos == 6) {
        // 检查闭环：块6边1 ↔ 块1边4
        int b6 = order[5], b1 = order[0];
        return getVal(b6, rot[5], 1) == getVal(b1, rot[0], 4);
    }
    
    for (int i = 0; i < 7; i++) {
        if (i == centerIdx || used[i]) continue;
        used[i] = true;
        order[pos] = i;
        
        for (int r = 0; r < 6; r++) {
            // 约束1：与中心匹配（中心边pos 对应 周围块pos+1的边 (pos+3)%6）
            int centerVal = pieces[centerIdx][pos];
            int surrSide = (pos + 3) % 6;
            if (getVal(i, r, surrSide) != centerVal) continue;
            
            // 约束2：与前一个周围块匹配
            if (pos >= 1) {
                int prev = order[pos - 1];
                int prevRot = rot[pos - 1];
                int prevSide, curSide;
                
                // 根据pos确定邻接边对
                if (pos == 1) {      // 块1边2 ↔ 块2边5
                    prevSide = 2; curSide = 5;
                } else if (pos == 2) { // 块2边3 ↔ 块3边0
                    prevSide = 3; curSide = 0;
                } else if (pos == 3) { // 块3边4 ↔ 块4边1
                    prevSide = 4; curSide = 1;
                } else if (pos == 4) { // 块4边5 ↔ 块5边2
                    prevSide = 5; curSide = 2;
                } else {               // pos == 5, 块5边0 ↔ 块6边3
                    prevSide = 0; curSide = 3;
                }
                
                if (getVal(prev, prevRot, prevSide) != getVal(i, r, curSide)) continue;
            }
            
            rot[pos] = r;
            if (dfs(pos + 1)) {
                used[i] = false;
                return true;
            }
        }
        used[i] = false;
    }
    return false;
}

bool solve() {
    for (centerIdx = 0; centerIdx < 7; centerIdx++) {
        memset(used, 0, sizeof(used));
        used[centerIdx] = true;
        if (dfs(0)) return true;
    }
    return false;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        for (int i = 0; i < 6; i++) ss >> pieces[0][i];
        for (int i = 1; i < 7; i++)
            for (int j = 0; j < 6; j++)
                cin >> pieces[i][j];
        
        cout << (solve() ? "YES" : "NO") << endl;
        cin.ignore();
    }
    return 0;
}
