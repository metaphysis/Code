// Pillars
// UVa ID: 10769
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.190s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Pillar {
    int b1, w1, b2, w2;
    Pillar(int b1, int w1, int b2, int w2) : b1(b1), w1(w1), b2(b2), w2(w2) {}
    bool operator<(const Pillar& other) const {
        if (b1 != other.b1) return b1 < other.b1;
        if (w1 != other.w1) return w1 < other.w1;
        if (b2 != other.b2) return b2 < other.b2;
        return w2 < other.w2;
    }
};

void solveTestCase(int H, vector<int>& blacks, vector<int>& whites) {
    map<int, vector<pair<int, int>>> whiteSums;
    for (size_t i = 0; i < whites.size(); ++i) {
        for (size_t j = 0; j < whites.size(); ++j) {
            if (i != j) {
                int sum = whites[i] + whites[j];
                whiteSums[sum].push_back({whites[i], whites[j]});
            }
        }
    }
    
    // 对每个 whiteSums 的 vector 按字典序排序
    for (auto& p : whiteSums) {
        sort(p.second.begin(), p.second.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second > b.second;
        });
    }
    
    Pillar best(-1, -1, -1, -1);
    
    for (size_t i = 0; i < blacks.size(); ++i) {
        for (size_t j = 0; j < blacks.size(); ++j) {
            if (i != j) {
                int needed = H - blacks[i] - blacks[j];
                if (whiteSums.count(needed)) {
                    auto& bestWhite = whiteSums[needed][0]; // 已经按字典序排好，第一个最大
                    Pillar candidate(blacks[i], bestWhite.first, blacks[j], bestWhite.second);
                    if (best < candidate) {
                        best = candidate;
                    }
                }
            }
        }
    }
    
    if (best.b1 == -1) {
        cout << "no solution" << endl;
    } else {
        cout << best.b1 << " " << best.w1 << " " << best.b2 << " " << best.w2 << endl;
    }
}

int main() {
    int H;
    while (cin >> H) {
        cin.ignore();
        string line;
        
        vector<int> blacks;
        getline(cin, line);
        size_t pos = 0;
        while (pos < line.length()) {
            size_t end = line.find(' ', pos);
            if (end == string::npos) end = line.length();
            blacks.push_back(stoi(line.substr(pos, end - pos)));
            pos = end + 1;
        }
        
        vector<int> whites;
        getline(cin, line);
        pos = 0;
        while (pos < line.length()) {
            size_t end = line.find(' ', pos);
            if (end == string::npos) end = line.length();
            whites.push_back(stoi(line.substr(pos, end - pos)));
            pos = end + 1;
        }
        
        solveTestCase(H, blacks, whites);
        
        // 跳过空行
        if (!getline(cin, line)) break;
    }
    return 0;
}
