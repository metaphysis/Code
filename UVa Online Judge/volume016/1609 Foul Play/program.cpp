// Foul Play
// UVa ID: 1609
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<string> win;
int n;
vector<bool> used;

void scheduleRound(vector<int> teams) {
    if (teams.size() == 1) return;
    
    // 分类队伍
    vector<int> black, gray, white;
    for (int team : teams) {
        if (team == 1) continue;
        if (win[1][team] == '0') black.push_back(team);
        else {
            // 检查是否是灰色队伍（能打败某个黑色队伍）
            bool isGray = false;
            for (int b : black) {
                if (win[team][b] == '1') {
                    isGray = true;
                    break;
                }
            }
            if (isGray) gray.push_back(team);
            else white.push_back(team);
        }
    }
    
    vector<int> nextRound;
    used.assign(n + 1, false);
    
    // 阶段1：用灰色队伍消灭黑色队伍
    for (int b : black) {
        if (used[b]) continue;
        bool eliminated = false;
        for (int& g : gray) {
            if (!used[g] && win[g][b] == '1') {
                cout << g << " " << b << endl;
                used[g] = used[b] = true;
                nextRound.push_back(g);
                eliminated = true;
                break;
            }
        }
        // 如果找不到灰色队伍，用白色队伍
        if (!eliminated) {
            for (int& w : white) {
                if (!used[w] && win[w][b] == '1') {
                    cout << w << " " << b << endl;
                    used[w] = used[b] = true;
                    nextRound.push_back(w);
                    eliminated = true;
                    break;
                }
            }
        }
    }
    
    // 阶段2：安排队伍1的比赛
    if (!used[1]) {
        for (int team : teams) {
            if (team != 1 && !used[team] && win[1][team] == '1') {
                cout << "1 " << team << endl;
                used[1] = used[team] = true;
                nextRound.push_back(1);
                break;
            }
        }
    }
    
    // 阶段3：剩下的黑色队伍自相残杀
    vector<int> remainingBlack;
    for (int b : black) if (!used[b]) remainingBlack.push_back(b);
    for (int i = 0; i < remainingBlack.size(); i += 2) {
        if (i + 1 < remainingBlack.size()) {
            int a = remainingBlack[i], b = remainingBlack[i + 1];
            cout << a << " " << b << endl;
            used[a] = used[b] = true;
            if (win[a][b] == '1') nextRound.push_back(a);
            else nextRound.push_back(b);
        }
    }
    
    // 阶段4：剩下的队伍任意配对
    vector<int> remaining;
    for (int team : teams) if (!used[team]) remaining.push_back(team);
    for (int i = 0; i < remaining.size(); i += 2) {
        if (i + 1 < remaining.size()) {
            int a = remaining[i], b = remaining[i + 1];
            cout << a << " " << b << endl;
            if (win[a][b] == '1') nextRound.push_back(a);
            else nextRound.push_back(b);
        }
    }
    
    scheduleRound(nextRound);
}

int main() {
    while (cin >> n) {
        win.resize(n + 1);
        used.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> win[i];
            win[i] = " " + win[i];
        }
        
        vector<int> teams(n);
        for (int i = 0; i < n; i++) teams[i] = i + 1;
        
        scheduleRound(teams);
    }
    return 0;
}
