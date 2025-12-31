// Computer Dialogue
// UVa ID: 10030
// Verdict: Accepted
// Submission Date: 2025-12-24
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct File {
    string fullName;
    string name;
    string ext;
};

void solve() {
    int N, M;
    cin >> N >> M;
    vector<File> files(N);
    unordered_map<string, unordered_set<string>> nameToExts;
    unordered_map<string, unordered_set<string>> extToNames;

    for (int i = 0; i < N; ++i) {
        string full;
        cin >> full;
        files[i].fullName = full;
        size_t dotPos = full.find('.');
        if (dotPos == string::npos) {
            files[i].name = full;
            files[i].ext = "";
        } else {
            files[i].name = full.substr(0, dotPos);
            files[i].ext = full.substr(dotPos + 1);
        }
        nameToExts[files[i].name].insert(files[i].ext);
        extToNames[files[i].ext].insert(files[i].name);
    }

    vector<bool> isCandidate(N, true);

    // 模拟消息交换
    for (int msg = 0; msg < M; ++msg) {
        // 检查当前候选集合，找出会被排除的文件
        unordered_map<string, int> nameCount;
        unordered_map<string, int> extCount;
        for (int i = 0; i < N; ++i) {
            if (isCandidate[i]) {
                nameCount[files[i].name]++;
                extCount[files[i].ext]++;
            }
        }

        // 决定排除哪些文件
        vector<bool> newCandidate = isCandidate;
        if (msg % 2 == 0) { // B的回合（扩展名方）
            for (int i = 0; i < N; ++i) {
                if (isCandidate[i] && extCount[files[i].ext] == 1) {
                    // B能唯一确定，所以这个文件不会在下一轮候选
                    newCandidate[i] = false;
                }
            }
        } else { // A的回合（名称方）
            for (int i = 0; i < N; ++i) {
                if (isCandidate[i] && nameCount[files[i].name] == 1) {
                    // A能唯一确定，所以这个文件不会在下一轮候选
                    newCandidate[i] = false;
                }
            }
        }
        isCandidate = move(newCandidate);
    }

    vector<string> candidates;
    for (int i = 0; i < N; ++i) {
        if (isCandidate[i]) candidates.push_back(files[i].fullName);
    }

    cout << candidates.size() << '\n';
    for (const string& name : candidates) cout << name << '\n';
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
        if (T) cout << '\n'; // 测试用例之间空行
    }
    return 0;
}
