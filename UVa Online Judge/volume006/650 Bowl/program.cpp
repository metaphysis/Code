// Bowl
// UVa ID: 650
// Verdict: Accepted
// Submission Date: 2026-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int NORMAL = 0, STRIKE = 1, SPARE = 2, UNDONE = 3, BONUS = 4;
const int DEFINED = 0, UNDEFINED = -1;

struct Frame {
    int pin1, pin2, type, marks, status;
    string tag;
};

string name;
vector<Frame> fs;
vector<int> standing;

string format1(string s, int width) {
    while (s.size() < width) s += ' ';
    return s;
}

string format2(string s, int width) {
    while (s.size() < width) s = ' ' + s;
    return s;
}

void solve() {
    // 解析输入
    while (standing.size()) {
        int r1 = standing[0];
        standing.erase(standing.begin());
        if (r1 == 0) {
            Frame f; f.pin1 = 10, f.pin2 = 0, f.type = STRIKE, f.tag = "X";
            fs.push_back(f);
        } else {
            if (standing.size()) {
                int r2 = standing[0];
                standing.erase(standing.begin());
                Frame f; f.pin1 = 10 - r1, f.pin2 = r1 - r2;
                if (f.pin1 == 0) f.tag = '-'; else f.tag = to_string(f.pin1);
                if (r2 == 0) f.type = SPARE, f.tag += "/";
                else {
                    f.type = NORMAL;
                    if (r1 == r2) f.tag += '-';
                    else f.tag += to_string(r1 - r2);
                }
                fs.push_back(f);
            } else {
                // 第二投分数为 -1 表示未投掷
                Frame f; f.pin1 = 10 - r1, f.pin2 = UNDEFINED, f.type = UNDONE;
                if (f.pin1 == 0) f.tag = '-';
                else f.tag = to_string(f.pin1);
                fs.push_back(f);
            }
        }
        // 第10帧后为奖励的两次投掷
        if (fs.size() == 10) break;
    }
    // 1次奖励投掷
    if (standing.size() == 1) {
        Frame f; f.pin1 = 10 - standing[0], f.pin2 = UNDEFINED, f.type = BONUS;
        if (f.pin1 == 0) f.tag = '-';
        else if (f.pin1 == 10) f.tag = 'X';
        else f.tag = to_string(f.pin1);
        fs.push_back(f);
    }
    // 2次奖励投掷
    if (standing.size() == 2) {
        if (standing[0] == 0) {
            Frame f; f.pin1 = 10, f.pin2 = 10 - standing[1], f.type = BONUS, f.tag = "X";
            if (f.pin2 == 0) f.tag += '-';
            else {
                if (f.pin2 == 0) f.tag += '-';
                else if (f.pin2 == 10) f.tag += 'X';
                else f.tag += to_string(f.pin2);
            }
            fs.push_back(f);
        } else {
            Frame f; f.pin1 = 10 - standing[0], f.pin2 = standing[0] - standing[1];
            if (f.pin1 == 0) f.tag += '-';
            else f.tag = to_string(f.pin1);
            if (f.pin2 == 0) f.tag += '-';
            else if (f.pin1 + f.pin2 == 10) f.tag += '/';
            else f.tag += to_string(f.pin2);
            fs.push_back(f);
        }
    }
    // 计分
    for (int i = 0; i < fs.size(); i++) {
        fs[i].marks = fs[i].pin1 + fs[i].pin2;
        fs[i].status = DEFINED;
        if (fs[i].type == UNDONE) { fs[i].status = UNDEFINED; break; }
        if (i == 9) {
            if (fs[i].type == STRIKE) {
                // 有奖励帧
                if (fs.size() == 11) {
                    // 有奖励帧，说明第一投有分数
                    fs[i].marks += fs[10].pin1;
                    // 检查是否进行了第二投，若未投，则分数为未定义状态
                    if (fs[10].pin2 != UNDEFINED) fs[i].marks += fs[10].pin2;
                    else fs[i].status = UNDEFINED;
                // 未投奖励帧，最后一帧的分数为未定义状态
                } else fs[i].status = UNDEFINED;
            }
            if (fs[i].type == SPARE) {
                // 检查是否进行了奖励投掷
                if (fs.size() == 11) fs[i].marks += fs[10].pin1;
                else fs[i].status = UNDEFINED;
            }
        } else if (fs[i].type == STRIKE) {
            // 全中，检查后续的第一投
            if (i + 1 < fs.size()) {
                fs[i].marks += fs[i + 1].pin1;
                // 下一帧也是全中，检查是否存在后续一帧
                if (fs[i + 1].pin1 == 10) {
                    if (i + 2 < fs.size()) fs[i].marks += fs[i + 2].pin1;
                    else fs[i].status = UNDEFINED;
                // 若下一帧不是全中，检查下一帧是否进行了第二投    
                } else {
                    if (fs[i + 1].pin2 != UNDEFINED) fs[i].marks += fs[i + 1].pin2;
                    else fs[i].status = UNDEFINED;
                }
            } else fs[i].status = UNDEFINED;
        } else if (fs[i].type == SPARE) {
            // 检查是否存在下一帧
            if (i + 1 < fs.size()) fs[i].marks += fs[i + 1].pin1;
            else fs[i].status = UNDEFINED;
        }
        if (i) if (fs[i].status == DEFINED) fs[i].marks += fs[i - 1].marks;
    }
    // 输出
    string line;
    line += name;
    for (int i = name.length() + 1; i <= 13; i++) line += ' ';
    for (int i = 0; i < min((int)fs.size(), 10); i++)
        line += format1(fs[i].tag, 3) + ' ';
    while (line.size() && line.back() == ' ') line.pop_back();
    if (fs.size() == 11) line += fs[10].tag;
    cout << line << '\n';
    line.clear();
    for (int i = 1; i <= 12; i++) line += ' ';
    for (int i = 0; i < min((int)fs.size(), 10); i++)
        if (fs[i].status == DEFINED)
            line += format2(to_string(fs[i].marks), 4);
    while (line.size() && line.back() == ' ') line.pop_back();
    cout << line << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    int cases = 0;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (cases++) cout << '\n';
        stringstream ss(line);
        ss >> name;
        standing.clear();
        int r; while (ss >> r) standing.push_back(r);
        if (standing.empty()) {
            cout << name << '\n';
            cout << '\n';
            continue;
        }
        fs.clear();
        solve();
    }
    return 0;
}
