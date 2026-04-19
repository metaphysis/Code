// Words Adjustment
// UVa ID: 10941
// Verdict: Accepted
// Submission Date: 2026-03-01
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 检查 a 和 b 是否互为前缀
bool isPrefix(const string& a, const string& b) {
    int n = min(a.size(), b.size());
    for (int i = 0; i < n; i++)
        if (a[i] != b[i]) return false;
    return true;
}

// 返回较长字符串去掉共同前缀后的剩余部分
string getRemainder(const string& a, const string& b) {
    int n = min(a.size(), b.size());
    return (a.size() > b.size() ? a : b).substr(n);
}

int solve(string x, string y, vector<string>& words) {
    // 检查是否互为前缀
    if (!isPrefix(x, y)) return -1;
    
    // 获取需要匹配的剩余部分
    string remain = getRemainder(x, y);
    if (remain.empty()) return 0;
    
    // BFS：状态为当前需要匹配的剩余字符串
    unordered_map<string, int> dist;
    queue<string> q;
    
    dist[remain] = 0;
    q.push(remain);
    
    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        int steps = dist[cur];
        
        if (cur.empty()) return steps;
        
        for (string& w : words) {
            // 检查 w 和 cur 是否互为前缀
            if (isPrefix(cur, w)) {
                string next = getRemainder(cur, w);
                if (!dist.count(next)) {
                    dist[next] = steps + 1;
                    q.push(next);
                }
            }
        }
    }
    
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int caseNum;
    cin >> caseNum;
    
    while (caseNum--) {
        string x, y;
        cin >> x >> y;
        
        int k;
        cin >> k;
        
        vector<string> words(k);
        for (int i = 0; i < k; i++) cin >> words[i];
        
        int result = solve(x, y, words);
        cout << result << "\n";
    }
    
    return 0;
}
