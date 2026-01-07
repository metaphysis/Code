// Substitution Cipher
// UVa ID: 715
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXA = 26;

int A, K;
int mapping[MAXA];
bool used[MAXA], inconsistent = false;
vector<int> rules[MAXA];
string message, decrypted;

// 检查当前部分映射是否与所有约束一致
bool checkConstraints(int idx) {
    for (int u = 0; u <= idx; u++)
        for (auto v : rules[u])
            if (mapping[v] != -1)
                if (mapping[v] < mapping[u])
                    return false;
    return true;
}

// 合法解的个数
int cnt = 0;

// 回溯搜索
void dfs(int idx) {
    // 如果已经找到“足够多”的解仍保持一致则提前终止
    if (inconsistent || cnt >= 50) return;
    // 如果所有字母都已处理
    if (idx == A) {
        cnt++;
        string tmp;
        for (char ch : message) {
            if (islower(ch) && ch - 'a' < A) tmp += char('a' + mapping[ch - 'a']);
            else tmp += ch;
        }
        if (decrypted.length() && decrypted != tmp) inconsistent = true;
        else decrypted = tmp;
        return;
    }
    // 尝试将当前字母映射到所有可用明文字母
    for (int p = 0; p < A; p++) {
        if (!used[p]) {
            mapping[idx] = p;
            used[p] = true;
            // 检查约束
            if (checkConstraints(idx)) {
                dfs(idx + 1);
                if (inconsistent) return;
            }
            // 回溯
            mapping[idx] = -1;
            used[p] = false;
        }
    }
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int N; cin >> N;
    string words[1024];
    while (N--) {
        cin >> A >> K;
        for (int i = 0; i < K; ++i) cin >> words[i];
        cin.ignore(128, '\n');
        getline(cin, message);
        // 获取约束关系
        for (int i = 0; i < A; i++) rules[i].clear();
        for (int i = 0; i < K; i++)
            for (int j = i + 1; j < K; j++) {
                string a = words[i], b = words[j];
                int L = min(a.length(), b.length());
                for (int k = 0; k < L; k++)
                    if (a[k] != b[k]) {
                        rules[a[k] - 'a'].push_back(b[k] - 'a');
                        break;
                    }
            }
                
        // 回溯搜索
        inconsistent = false;
        cnt = 0;
        decrypted.clear();
        memset(mapping, -1, sizeof mapping);
        memset(used, false, sizeof used);
        dfs(0);
        
        // 输出结果
        if (inconsistent) cout << "Message cannot be decrypted.\n";
        else cout << decrypted << '\n';
    }
    return 0;
}
