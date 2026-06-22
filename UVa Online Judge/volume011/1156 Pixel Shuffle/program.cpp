// Pixel Shuffle
// UVa ID: 1156
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 2.570s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 应用单个变换（可能带 '-'），返回新坐标 (ni, nj)
pair<int,int> applyTransform(const string& w, int n, int i, int j) {
    bool inv = (w.back() == '-');
    string key = inv ? w.substr(0, w.size() - 1) : w;
    int half = n / 2;

    if (key == "id") {
        return {i, j};
    }
    else if (key == "rot") {
        if (!inv) // 逆时针 90°
            return {n - 1 - j, i};
        else     // 顺时针 90°
            return {j, n - 1 - i};
    }
    else if (key == "sym") { // 自身逆
        return {i, n - 1 - j};
    }
    else if (key == "bhsym") { // 自身逆
        if (i >= half) return {i, n - 1 - j};
        return {i, j};
    }
    else if (key == "bvsym") { // 自身逆
        if (i >= half) return {n - 1 - i + half, j};
        return {i, j};
    }
    else if (key == "div") {
        if (!inv) { // 正向：旧行 -> 新行
            int ni = (i % 2 == 0) ? i / 2 : half + i / 2;
            return {ni, j};
        } else {   // 逆：新行 -> 旧行
            int ni = (i < half) ? 2 * i : 2 * (i - half) + 1;
            return {ni, j};
        }
    }
    else if (key == "mix") {
        if (!inv) { // 正向
            if (i % 2 == 0) {
                if (j < half) return {i, 2 * j};
                else return {i + 1, 2 * (j - half)};
            } else {
                if (j < half) return {i - 1, 2 * j + 1};
                else return {i, 2 * (j - half) + 1};
            }
        } else { // 逆
            if (i % 2 == 0) { // 新行 2k
                if (j % 2 == 0) {
                    int c = j / 2;
                    return {i, c};
                } else {
                    int c = j / 2;
                    return {i + 1, c};
                }
            } else { // 新行 2k+1
                if (j % 2 == 0) {
                    int c = j / 2;
                    return {i - 1, c + half};
                } else {
                    int c = j / 2;
                    return {i, c + half};
                }
            }
        }
    }
    return {i, j}; // 不会执行
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    string line;
    getline(cin, line); // 跳过第一行后的换行

    bool first = true;
    for (int tc = 0; tc < T; ++tc) {
        int n;
        cin >> n;
        getline(cin, line); // 跳过 n 后的换行

        // 读取单词行，跳过可能的空行
        while (getline(cin, line)) {
            if (line.find_first_not_of(" \t") != string::npos) break;
        }

        vector<string> words;
        istringstream iss(line);
        string w;
        while (iss >> w) words.push_back(w);

        // 反转顺序以符合复合定义
        reverse(words.begin(), words.end());

        int N = n * n;
        vector<int> perm(N);

        // 计算每个旧位置的映射
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int ci = i, cj = j;
                for (const string& word : words) {
                    auto p = applyTransform(word, n, ci, cj);
                    ci = p.first; cj = p.second;
                }
                perm[i * n + j] = ci * n + cj;
            }
        }

        // 求置换的阶（所有循环长度的 LCM）
        vector<char> vis(N, 0);
        ll lcm = 1;
        for (int idx = 0; idx < N; ++idx) {
            if (!vis[idx]) {
                int cur = idx;
                int len = 0;
                while (!vis[cur]) {
                    vis[cur] = 1;
                    cur = perm[cur];
                    ++len;
                }
                lcm = lcm / std::gcd(lcm, (ll)len) * len;
            }
        }

        if (!first) cout << "\n";
        first = false;
        cout << lcm << "\n";
    }

    return 0;
}
