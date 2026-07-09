// Recording a Tape
// UVa ID: 778
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 去除字符串首尾空格
static string trim(const string& s) {
    size_t l = s.find_first_not_of(" \t\n\r");
    if (l == string::npos) return "";
    size_t r = s.find_last_not_of(" \t\n\r");
    return s.substr(l, r - l + 1);
}

// 将形如 "20m 44s" 的字符串转为秒数
static int parseSongDuration(const string& line) {
    size_t mPos = line.find('m');
    size_t sPos = line.find('s');
    int minutes = 0, seconds = 0;
    if (mPos != string::npos) {
        string minStr = line.substr(0, mPos);
        minStr.erase(remove(minStr.begin(), minStr.end(), ' '), minStr.end());
        minutes = stoi(minStr);
    }
    if (sPos != string::npos) {
        string secStr = line.substr(mPos + 1, sPos - mPos - 1);
        secStr.erase(remove(secStr.begin(), secStr.end(), ' '), secStr.end());
        seconds = stoi(secStr);
    }
    return minutes * 60 + seconds;
}

// 输出一首歌的时长（原格式）
static void printSong(int totalSec) {
    int m = totalSec / 60;
    int s = totalSec % 60;
    cout << m << "m " << s << "s";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        line = trim(line);
        if (line == "%") break;   // 整个输入结束
        // 读取可用磁带时长
        vector<int> available;
        istringstream iss(line);
        int val;
        while (iss >> val) available.push_back(val);
        // 读取歌曲列表
        vector<int> songs;
        while (getline(cin, line)) {
            line = trim(line);
            if (line == "%") break;   // 当前实例结束
            songs.push_back(parseSongDuration(line));
        }
        int total = 0;
        for (int d : songs) total += d;
        int n = (int)songs.size();
        sort(available.begin(), available.end());
        // 尝试每个磁带
        for (int tapeMin : available) {
            int tapeSec = tapeMin * 60;
            if (tapeSec < total) continue;          // 总时长必须能装下
            int cap = tapeSec / 2;                  // 每面容量
            // DP: dp[s] = 是否可达，preSum[s] 记录上一个和，preIdx[s] 记录使用的歌曲索引
            vector<bool> dp(cap + 1, false);
            vector<int> preSum(cap + 1, -1);
            vector<int> preIdx(cap + 1, -1);
            dp[0] = true;
            for (int i = 0; i < n; ++i) {
                int d = songs[i];
                for (int s = cap; s >= d; --s)
                    if (!dp[s] && dp[s - d]) {
                        dp[s] = true;
                        preSum[s] = s - d;
                        preIdx[s] = i;
                    }
            }
            int lower = max(0, total - cap);
            int chosenSum = -1;
            for (int s = lower; s <= cap; ++s)
                if (dp[s]) {
                    chosenSum = s;
                    break;
                }
            if (chosenSum == -1) continue;   // 该磁带不可行，尝试下一个
            // 回溯得到 A 面的歌曲索引
            vector<int> sideA;
            int cur = chosenSum;
            while (cur > 0) {
                int idx = preIdx[cur];
                sideA.push_back(idx);
                cur = preSum[cur];
            }
            // 标记 A 面已选
            vector<bool> used(n, false);
            for (int idx : sideA) used[idx] = true;
            // 输出结果
            cout << tapeMin << "\n";
            cout << "Side A\n";
            for (int idx : sideA) {
                printSong(songs[idx]);
                cout << "\n";
            }
            cout << "Side B\n";
            for (int i = 0; i < n; ++i)
                if (!used[i]) {
                    printSong(songs[i]);
                    cout << "\n";
                }
            cout << "%\n";
            break;   // 找到最短磁带后跳出循环
        }
    }
    return 0;
}
