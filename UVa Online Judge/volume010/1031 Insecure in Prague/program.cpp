// Insecure in Prague
// UVa ID: 1031
// Verdict: Accepted
// Submission Date: 2026-06-16
// UVa Run Time: 1.430s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string cipher, message;
int m, F[26], p[45], flag[45];
set<string> answers;

// 模拟第一次放置，返回位置序列
// 参数：s-起始位置，i-间隔，n-明文长度
vector<int> simulateFirst(int s, int i, int n) {
    vector<int> slots;
    memset(flag, -1, sizeof flag);
    for (int k = 0; k < n; k++) {
        flag[s] = k;
        slots.push_back(s);
        int skipped = 0;
        while (skipped < i) {
            s = (s + 1) % m;
            if (flag[s] == -1) skipped++;
        }
        do s = (s + 1) % m; while (flag[s] != -1);
    }
    return slots;
}

// 模拟第二次放置，检查是否能放置成功
// 参数：i-第一次放置的间隔，n-明文长度
bool simulateSecond(int i, int n) {
    // 构建空槽列表（未被第一次占用的位置）
    vector<int> empty;
    for (int k = 0; k < m; k++) if (p[k] == -1) empty.push_back(k);
    
    // 收集可能的起始位置（必须是空槽且字符匹配）
    vector<int> starts;
    for (int t = 0; t < m; t++)
        if (p[t] == -1 && cipher[t] == message.front())
            starts.push_back(t);
    
    for (int t : starts) {
        for (int j = i + 1; j < m; j++) {
            vector<int> slots = empty;
            int pos = 0;
            while (slots[pos] != t) ++pos;
            slots.erase(slots.begin() + pos);
            if (pos == slots.size()) pos = 0;
            
            int valid = 1;
            for (int k = 1; k < n; ++k) {
                pos = (pos + j) % slots.size();
                int dest = slots[pos];
                if (cipher[dest] != message[k]) { valid = 0; break; }
                slots.erase(slots.begin() + pos);
                if (pos == slots.size()) pos = 0;
            }
            if (valid) return true;
        }
    }
    return false;
}

void solve() {
    m = cipher.length();
    memset(F, 0, sizeof(F));
    for (char c : cipher) F[c - 'A']++;
    answers.clear();
    
    // 从大到小枚举明文长度
    for (int n = m / 2; n >= 1; n--) {
        for (int i = 0; i < m && answers.size() <= 1; i++) {
            // 只计算一次从0开始的放置序列，利用线性关系平移
            vector<int> slots = simulateFirst(0, i, n);
            for (int s = 0; s < m && answers.size() <= 1; s++) {
                message.clear();
                int f[26] = {0}, valid = 1;
                memset(p, -1, sizeof p);
                
                // 平移得到从s开始的放置位置
                for (int k = 0; k < n; k++) {
                    int idx = (slots[k] + s) % m;
                    p[idx] = k;
                    char c = cipher[idx];
                    message += c;
                    f[c - 'A']++;
                    // 频次剪枝
                    if (f[c - 'A'] * 2 > F[c - 'A']) { valid = 0; break; }
                }
                if (!valid) continue;
                if (simulateSecond(i, n)) answers.insert(message);
            }
        }
        if (answers.size()) return;
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    int cs = 1;
    while (getline(cin, line)) {
        if (line == "X") break;
        cipher = line;
        solve();
        cout << "Code " << cs++ << ": ";
        if (answers.size() == 1) cout << *answers.begin() << '\n';
        else cout << "Codeword not unique" << '\n';
    }
    return 0;
}
