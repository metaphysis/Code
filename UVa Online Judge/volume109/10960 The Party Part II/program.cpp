// The Party Part II
// UVa ID: 10960
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<int> parent, rank;
    UnionFind(int n) { parent.resize(n); rank.assign(n, 0); for (int i = 0; i < n; ++i) parent[i] = i; }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) ++rank[ra];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int n, i, c, u;
        cin >> n >> i >> c >> u;
        cin.ignore();
        vector<string> lines(u);
        set<char> peopleSet;
        for (int k = 0; k < u; ++k) {
            getline(cin, lines[k]);
            size_t eqPos = lines[k].find('=');
            if (eqPos != string::npos) {
                string rest = lines[k].substr(eqPos + 1);
                for (char ch : rest)
                    if (ch >= 'A' && ch <= 'Z') peopleSet.insert(ch);
            }
        }
        vector<char> persons(peopleSet.begin(), peopleSet.end());
        unordered_map<char, int> idx;
        for (int p = 0; p < (int)persons.size(); ++p) idx[persons[p]] = p;
        vector<UnionFind> uf;
        for (int x = 0; x < i; ++x) uf.emplace_back(persons.size());
        vector<vector<int>> mask(i, vector<int>(persons.size(), (1 << c) - 1));
        // 第一遍：处理 Same 合并
        for (const string& line : lines) {
            istringstream iss(line);
            string first;
            iss >> first;
            if (first == "Same") {
                string tmp; iss >> tmp; // colour
                iss >> tmp; // of
                iss >> tmp; // item
                int X; iss >> X;
                iss >> tmp; // =
                vector<char> people;
                char p;
                while (iss >> p) people.push_back(p);
                if (people.size() > 1) {
                    int firstIdx = idx[people[0]];
                    for (int q = 1; q < (int)people.size(); ++q) {
                        int otherIdx = idx[people[q]];
                        uf[X].unite(firstIdx, otherIdx);
                    }
                }
            }
        }
        // 第二遍：处理 Colour 和 Not
        for (const string& line : lines) {
            istringstream iss(line);
            string first;
            iss >> first;
            if (first == "Colour") {
                int Y; iss >> Y;
                string tmp; iss >> tmp; // for
                iss >> tmp; // item
                int X; iss >> X;
                iss >> tmp; // =
                vector<char> people;
                char p;
                while (iss >> p) people.push_back(p);
                for (char person : people) {
                    int id = idx[person];
                    int root = uf[X].find(id);
                    mask[X][root] &= (1 << Y);
                }
            } else if (first == "Not") {
                string tmp; iss >> tmp; // colour
                int Y; iss >> Y;
                iss >> tmp; // for
                iss >> tmp; // item
                int X; iss >> X;
                iss >> tmp; // =
                vector<char> people;
                char p;
                while (iss >> p) people.push_back(p);
                for (char person : people) {
                    int id = idx[person];
                    int root = uf[X].find(id);
                    mask[X][root] &= ~(1 << Y);
                }
            }
        }
        bool contradiction = false;
        for (int x = 0; x < i && !contradiction; ++x)
            for (int id = 0; id < (int)persons.size(); ++id) {
                int root = uf[x].find(id);
                if (mask[x][root] == 0) { contradiction = true; break; }
            }
        if (contradiction) cout << "Contradiction\n";
        else {
            for (char person : persons) {
                cout << person;
                for (int x = 0; x < i; ++x) {
                    int root = uf[x].find(idx[person]);
                    int m = mask[x][root];
                    cout << ' ';
                    if ((m & (m - 1)) == 0) { // 只有一位
                        int color = __builtin_ctz((unsigned)m);
                        cout << color;
                    } else {
                        cout << '?';
                    }
                }
                cout << '\n';
            }
        }
        if (tc != T) cout << '\n'; // 用例间空行
    }
    return 0;
}
