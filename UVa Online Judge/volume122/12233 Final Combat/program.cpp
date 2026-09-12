#include <bits/stdc++.h>
using namespace std;

const int INF = 100000000;

int syJing, xxSu, sySu, yuJing, yuShen, shuShen;
int xxTime, syTime;
int jing[4], qi[4], shen[4];
int maxJing[4], maxShen[4], su[4];
int d1x[4], d2x[4], d1s[4], d2s[4];
int wad[4], ssd[4], ssq[4], ssp[4], q1[4], q2[4];
int dam[4][4];
int maxTime, heroId, posId, heroTime;
map<int, int> memo[13];
vector<string> ans;
string names[4] = {"Y", "H", "L", "M"};

int dfs(int tim, int hp, int mp, int sp) {
    if (hp <= 0) return -INF;
    if (tim > maxTime) return 0;
    hp = min(hp, maxJing[heroId]);
    mp = min(mp, 100);
    sp = min(sp, maxShen[heroId]);
    int key = hp * 110000 + mp * 1000 + sp;
    if (memo[tim].count(key)) return memo[tim][key];
    int dhp = 0, dqi = 0;
    if (tim % xxTime == 0) {
        if ((tim / xxTime) % 4 == posId) {
            dhp -= d1x[heroId];
            dqi += q2[heroId];
        }
        if ((tim / xxTime) % 4 == 0) dhp -= d2x[heroId];
    }
    if (tim % syTime == 0) {
        if ((tim / syTime) % 4 == posId) {
            dhp -= d1s[heroId];
            dqi += q2[heroId];
        }
        if ((tim / syTime) % 4 == 0) dhp -= d2s[heroId];
    }
    memo[tim][key] = -INF;
    int &res = memo[tim][key];
    if (tim == maxTime) {
        res = 0;
        if (tim % heroTime != 0) return res;
        if (hp > wad[heroId]) res = max(res, wad[heroId]);
        if (mp >= ssq[heroId]) {
            int back = ssp[heroId] == 1 ? -ssd[heroId] : 0;
            if (hp + back > 0) res = max(res, ssd[heroId]);
        }
        return res;
    }
    if (tim % heroTime != 0)
        return res = dfs(tim + 1, hp + dhp, mp + dqi, sp);
    res = max(res, dfs(tim + 1, hp + dhp, mp + dqi + q1[heroId], sp));
    res = max(res, dfs(tim + 1, hp + dhp - wad[heroId], mp + dqi + q1[heroId], sp) + wad[heroId]);
    if (sp >= yuShen && hp < maxJing[heroId])
        res = max(res, dfs(tim + 1, min(hp + yuJing, maxJing[heroId]) + dhp, mp + dqi, sp - yuShen));
    if (sp < maxShen[heroId])
        res = max(res, dfs(tim + 1, hp + dhp, mp + dqi, sp + shuShen));
    if (mp >= ssq[heroId]) {
        int back = ssp[heroId] == 1 ? -ssd[heroId] : 0;
        res = max(res, dfs(tim + 1, hp + dhp + back, mp + dqi - ssq[heroId], sp) + ssd[heroId]);
    }
    return res;
}

int solve(int lim) {
    for (int h = 0; h < 4; h++) {
        for (int p = 1; p <= 3; p++) {
            maxTime = lim;
            heroId = h;
            posId = p;
            heroTime = 5 - su[h];
            for (int t = 1; t <= maxTime; t++) memo[t].clear();
            dam[h][p] = dfs(1, jing[h], qi[h], shen[h]);
        }
    }
    ans.clear();
    for (int h1 = 0; h1 < 4; h1++) {
        for (int h2 = 0; h2 < 4; h2++) {
            if (h2 == h1) continue;
            for (int h3 = 0; h3 < 4; h3++) {
                if (h3 == h1 || h3 == h2) continue;
                if (dam[h1][1] + dam[h2][2] + dam[h3][3] >= syJing) {
                    ans.push_back(names[h1] + names[h2] + names[h3]);
                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    return ans.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 0;
    while (cin >> syJing) {
        if (syJing == 0) break;
        cin >> xxSu >> sySu >> yuJing >> yuShen >> shuShen;
        for (int i = 0; i < 4; i++) {
            cin >> maxJing[i] >> maxShen[i] >> su[i];
            cin >> d1x[i] >> d2x[i] >> d1s[i] >> d2s[i];
            cin >> wad[i] >> ssd[i] >> ssq[i] >> ssp[i];
            cin >> q1[i] >> q2[i] >> jing[i] >> qi[i] >> shen[i];
        }
        xxTime = 5 - xxSu;
        syTime = 5 - sySu;
        cout << "Case " << ++caseNo << ": ";
        bool win = false;
        for (int lim = 1; lim <= 12; lim++) {
            if (solve(lim)) {
                cout << lim;
                for (const string &str : ans) cout << " " << str;
                cout << "\n\n";
                win = true;
                break;
            }
        }
        if (!win) cout << "-1\n\n";
    }
    return 0;
}
