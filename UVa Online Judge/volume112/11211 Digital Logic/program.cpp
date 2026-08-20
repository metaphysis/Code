#include <bits/stdc++.h>
using namespace std;

struct GateType {
    int cnt, y0, y1, y2;
};

struct GateInfo {
    int typ, a, b;
};

struct Candidate {
    int typ, i, j, val, hit;
};

class Solver {
private:
    int n;
    vector<GateType> types;
    vector<int> goals, vals, ids, used;
    vector<GateInfo> path;
    unordered_set<string> bad;
    bool goal[65536];

    int getVal(int a, int b, const GateType &gate) {
        int val = 0;
        for (int x = 0; x < 16; x++) {
            int cnt = ((a >> x) & 1) + ((b >> x) & 1);
            int bit = cnt == 0 ? gate.y0 : cnt == 1 ? gate.y1 : gate.y2;
            if (bit) val |= 1 << x;
        }
        return val;
    }

    bool isDone() {
        for (int x : goals)
            if (find(vals.begin(), vals.end(), x) == vals.end())
                return false;
        return true;
    }

    int getMissing() {
        int cnt = 0;
        for (int x : goals)
            if (find(vals.begin(), vals.end(), x) == vals.end())
                cnt++;
        return cnt;
    }

    string getKey() {
        vector<int> tmp = vals;
        sort(tmp.begin(), tmp.end());
        string key;
        for (int x : used)
            key.push_back(static_cast<char>(x));
        for (int x : tmp) {
            key.push_back(static_cast<char>(x & 255));
            key.push_back(static_cast<char>((x >> 8) & 255));
        }
        return key;
    }

    bool dfs(int dep, int lim) {
        if (isDone())
            return true;
        if (dep == lim)
            return false;
        if (getMissing() > lim - dep)
            return false;
        string key = getKey();
        if (bad.count(key))
            return false;
        vector<Candidate> cands;
        int size = static_cast<int>(vals.size());
        for (int t = 0; t < n; t++) {
            if (used[t] == 0)
                continue;
            unordered_set<int> seen;
            for (int i = 0; i < size; i++) {
                for (int j = i; j < size; j++) {
                    int val = getVal(vals[i], vals[j], types[t]);
                    if (find(vals.begin(), vals.end(), val) != vals.end())
                        continue;
                    if (seen.count(val))
                        continue;
                    seen.insert(val);
                    cands.push_back({t, i, j, val, goal[val] ? 1 : 0});
                }
            }
        }
        sort(cands.begin(), cands.end(), [](const Candidate &a, const Candidate &b) {
            return a.hit > b.hit;
        });
        for (const Candidate &cand : cands) {
            used[cand.typ]--;
            vals.push_back(cand.val);
            ids.push_back(5 + dep);
            path.push_back({cand.typ, ids[cand.i], ids[cand.j]});
            if (dfs(dep + 1, lim))
                return true;
            path.pop_back();
            ids.pop_back();
            vals.pop_back();
            used[cand.typ]++;
        }
        bad.insert(key);
        return false;
    }

public:
    void readCase(int gateCount, const vector<GateType> &gateTypes, const vector<int> &target) {
        n = gateCount;
        types = gateTypes;
        goals = target;
        vals.clear();
        ids.clear();
        path.clear();
        used.clear();
        bad.clear();
        memset(goal, 0, sizeof(goal));
        for (int x : goals)
            goal[x] = true;
        int src[4] = {0, 0, 0, 0};
        for (int x = 0; x < 16; x++) {
            for (int i = 0; i < 4; i++) {
                if ((x >> (3 - i)) & 1)
                    src[i] |= 1 << x;
            }
        }
        for (int i = 0; i < 4; i++) {
            vals.push_back(src[i]);
            ids.push_back(i + 1);
        }
        for (const GateType &gate : types)
            used.push_back(gate.cnt);
    }

    void solve() {
        for (int lim = 0; lim <= 6; lim++) {
            bad.clear();
            if (dfs(0, lim))
                return;
        }
    }

    void print(int caseNum) {
        cout << "Case " << caseNum << ": " << path.size() << '\n';
        for (int i = 0; i < static_cast<int>(path.size()); i++)
            cout << i + 5 << ' ' << path[i].typ + 1 << ' ' << path[i].a << ' ' << path[i].b << '\n';
        for (int i = 0; i < 4; i++) {
            int pos = find(vals.begin(), vals.end(), goals[i]) - vals.begin();
            cout << ids[pos] << (i == 3 ? '\n' : ' ');
        }
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNum = 1;
    while (cin >> n && n) {
        vector<GateType> types;
        for (int i = 0; i < n; i++) {
            int m, y0, y1, y2;
            cin >> m >> y0 >> y1 >> y2;
            types.push_back({m, y0, y1, y2});
        }
        int output[16];
        for (int i = 0; i < 16; i++)
            cin >> output[i];
        vector<int> goals(4, 0);
        for (int x = 0; x < 16; x++) {
            for (int i = 0; i < 4; i++) {
                if (output[x] & (1 << (3 - i)))
                    goals[i] |= 1 << x;
            }
        }
        Solver solver;
        solver.readCase(n, types, goals);
        solver.solve();
        solver.print(caseNum++);
    }
    return 0;
}
