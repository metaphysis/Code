// Keeps Going and Going
// UVa ID: 606
// Verdict: Accepted
// Submission Date: 2026-05-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int N = 210;
map<string, vector<int>> p;          // 前缀数字
map<string, vector<string>> nxt;     // 后续列表
map<string, int> mix, id;            // mix标记是否含zip依赖，id为编号
int len[N][N];                       // 周期长度矩阵
map<pair<string, int>, int> mem;     // 记忆化缓存

// DFS标记是否包含zip依赖
int dfs(const string& s) {
    if (mix.count(s)) return mix[s];
    mix[s] = (nxt[s].size() == 2);   // zip列表有2个后续
    for (const string& t : nxt[s]) mix[s] |= dfs(t);
    return mix[s];
}

// 求解第pos个元素
int solve(const string& s, int pos) {
    auto key = make_pair(s, pos);
    if (mem.count(key)) return mem[key];
    int x = id[s], l = len[x][x];
    if (l > 0) pos %= l;             // 周期优化
    int res;
    if (pos < (int)p[s].size()) {
        res = p[s][pos];             // 命中前缀
    } else if (p[s].empty()) {
        // zip列表
        res = solve(nxt[s][pos & 1], pos / 2);
    } else {
        // 常量列表
        res = solve(nxt[s].back(), pos - p[s].size());
    }
    mem[key] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        p.clear(); nxt.clear(); mix.clear(); id.clear(); mem.clear();
        memset(len, 0, sizeof len);
        vector<string> names;
        // 读取定义
        for (int i = 0; i < n; i++) {
            string name, eq; cin >> name >> eq;
            names.push_back(name);
            id[name] = i;
            string line; getline(cin, line);
            stringstream ss(line); string token;
            vector<string> tok;
            while (ss >> token) tok.push_back(token);
            if (tok[0] == "zip") {
                nxt[name] = {tok[1], tok[2]};
            } else {
                nxt[name].push_back(tok.back());
                tok.pop_back();
                for (const string& t : tok) p[name].push_back(stoi(t));
            }
        }
        // 标记混合状态
        for (const string& name : names) dfs(name);
        // 计算周期长度
        for (int i = 0; i < (int)names.size(); i++) {
            string cur = names[i];
            if (mix[cur]) continue;
            int sum = 0;
            while (1) {
                string nxtName = nxt[cur].back();
                int j = id[nxtName];
                sum += p[cur].size();
                if (len[i][j]) break;
                len[i][j] = sum;
                cur = nxtName;
            }
        }
        // 处理查询
        while (q--) {
            string name; int l, r; cin >> name >> l >> r;
            for (int i = l; i <= r; i++) cout << solve(name, i) << " \n"[i == r];
        }
        if (T) cout << '\n';
    }
    return 0;
}
