// Suffix-Replacement Grammars
// UVa ID: 1089
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.560s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXL = 25;
const long long INF = (1LL << 60);

vector<string> suffixList[MAXL];
map<string, int> idMap[MAXL];

void addNode(const string& s) {
    int len = s.size();
    if (len >= MAXL) return;
    if (idMap[len].count(s)) return;
    int label = idMap[len].size();
    idMap[len][s] = label;
    suffixList[len].push_back(s);
}

long long solveCase(const string& S, const string& T, const vector<pair<string, string>>& rules) {
    int L = S.size();
    // 清空之前的数据
    for (int i = 0; i < MAXL; ++i) {
        suffixList[i].clear();
        idMap[i].clear();
    }
    // 收集所有可能出现的后缀：规则 X、Y 的所有后缀，以及 S、T 的所有后缀
    for (const auto& rule : rules) {
        const string& X = rule.first;
        const string& Y = rule.second;
        for (int i = 0; i < (int)X.size(); ++i)
            addNode(X.substr(i));
        for (int i = 0; i < (int)Y.size(); ++i)
            addNode(Y.substr(i));
    }
    for (int i = 0; i < L; ++i) {
        addNode(S.substr(i));
        addNode(T.substr(i));
    }

    vector<vector<long long>> preDist; // 长度 k-1 的距离矩阵

    for (int k = 1; k <= L; ++k) {
        int n = suffixList[k].size();
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        for (int i = 0; i < n; ++i) dist[i][i] = 0;

        // 填充初始边
        for (int i = 0; i < n; ++i) {
            const string& si = suffixList[k][i];
            for (int j = 0; j < n; ++j) {
                const string& sj = suffixList[k][j];
                // 直接规则
                for (const auto& rule : rules) {
                    if (rule.first == si && rule.second == sj) {
                        dist[i][j] = min(dist[i][j], 1LL);
                        break;
                    }
                }
                // 间接转移：首字符相同
                if (k > 1 && si[0] == sj[0]) {
                    string subI = si.substr(1);
                    string subJ = sj.substr(1);
                    auto itI = idMap[k - 1].find(subI);
                    auto itJ = idMap[k - 1].find(subJ);
                    if (itI != idMap[k - 1].end() && itJ != idMap[k - 1].end()) {
                        int pi = itI->second;
                        int pj = itJ->second;
                        dist[i][j] = min(dist[i][j], preDist[pi][pj]);
                    }
                }
            }
        }

        // Floyd 求传递闭包
        for (int mid = 0; mid < n; ++mid)
            for (int i = 0; i < n; ++i) {
                if (dist[i][mid] >= INF) continue;
                for (int j = 0; j < n; ++j)
                    if (dist[mid][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][mid] + dist[mid][j]);
            }

        preDist = move(dist); // 作为下一长度的前驱矩阵
    }

    int st = idMap[L][S];
    int ed = idMap[L][T];
    long long ans = preDist[st][ed];
    return (ans >= INF ? -1 : ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S, T;
    int NR;
    int caseNo = 1;
    while (cin >> S) {
        if (S == ".") break;
        cin >> T >> NR;
        vector<pair<string, string>> rules;
        for (int i = 0; i < NR; ++i) {
            string X, Y;
            cin >> X >> Y;
            rules.emplace_back(X, Y);
        }
        long long ans = solveCase(S, T, rules);
        cout << "Case " << caseNo++ << ": ";
        if (ans == -1) cout << "No solution\n";
        else cout << ans << "\n";
    }
    return 0;
}
