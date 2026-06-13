// Arranging a Contest
// UVa ID: 11372
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Problem {
    string id;
    char difficulty, type;
    int favor;
};

bool cmpFavorID(const Problem& a, const Problem& b) {
    if (a.favor != b.favor) return a.favor > b.favor;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N && N) {
        vector<Problem> problems(N);
        string name;
        for (int i = 0; i < N; ++i)
            cin >> problems[i].id >> name >> problems[i].difficulty >> problems[i].type >> problems[i].favor;

        // 按难度和类型分组
        vector<Problem> byDiffType[3][4];
        for (auto& p : problems) {
            int d = (p.difficulty == 'E' ? 0 : (p.difficulty == 'M' ? 1 : 2));
            int t = (p.type == 'D' ? 0 : (p.type == 'G' ? 1 : (p.type == 'M' ? 2 : 3)));
            byDiffType[d][t].push_back(p);
        }

        // 每组内排序
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 4; ++j)
                sort(byDiffType[i][j].begin(), byDiffType[i][j].end(), cmpFavorID);

        vector<string> bestIds;
        int maxFavor = -1;

        // 枚举从 E(0) 中选 2 个的分配
        for (int ed = 0; ed <= 2; ++ed)
            for (int eg = 0; eg <= 2 - ed; ++eg)
                for (int em = 0; em <= 2 - ed - eg; ++em) {
                    int ex = 2 - ed - eg - em;
                    if (ex < 0) continue;
                    // 检查 E 中各类型数量足够
                    if (ed > (int)byDiffType[0][0].size() || eg > (int)byDiffType[0][1].size() ||
                        em > (int)byDiffType[0][2].size() || ex > (int)byDiffType[0][3].size())
                        continue;

                    // 枚举 H(2) 中选 2 个的分配
                    for (int hd = 0; hd <= 2; ++hd)
                        for (int hg = 0; hg <= 2 - hd; ++hg)
                            for (int hm = 0; hm <= 2 - hd - hg; ++hm) {
                                int hx = 2 - hd - hg - hm;
                                if (hx < 0) continue;
                                if (hd > (int)byDiffType[2][0].size() || hg > (int)byDiffType[2][1].size() ||
                                    hm > (int)byDiffType[2][2].size() || hx > (int)byDiffType[2][3].size())
                                    continue;

                                // 枚举 M(1) 中选 0~2 个，但 M 难度不贡献 E/H 计数
                                for (int mCnt = 0; mCnt <= 2; ++mCnt) {
                                    for (int md = 0; md <= mCnt; ++md)
                                        for (int mg = 0; mg <= mCnt - md; ++mg)
                                            for (int mm = 0; mm <= mCnt - md - mg; ++mm) {
                                                int mx = mCnt - md - mg - mm;
                                                if (mx < 0) continue;
                                                if (md > (int)byDiffType[1][0].size() || mg > (int)byDiffType[1][1].size() ||
                                                    mm > (int)byDiffType[1][2].size() || mx > (int)byDiffType[1][3].size())
                                                    continue;

                                                int totalD = ed + hd + md;
                                                int totalG = eg + hg + mg;
                                                int totalM = em + hm + mm;
                                                if (totalD < 2 || totalG < 1 || totalM < 1) continue;

                                                // 收集所有候选题目
                                                vector<Problem> candidates;
                                                auto addCandidates = [&](int diff, int type, int cnt) {
                                                    for (int i = 0; i < cnt; ++i)
                                                        candidates.push_back(byDiffType[diff][type][i]);
                                                };
                                                addCandidates(0, 0, ed); addCandidates(0, 1, eg);
                                                addCandidates(0, 2, em); addCandidates(0, 3, ex);
                                                addCandidates(2, 0, hd); addCandidates(2, 1, hg);
                                                addCandidates(2, 2, hm); addCandidates(2, 3, hx);
                                                addCandidates(1, 0, md); addCandidates(1, 1, mg);
                                                addCandidates(1, 2, mm); addCandidates(1, 3, mx);
                                                if ((int)candidates.size() != 6) continue;
                                                int curFavor = 0;
                                                vector<string> ids;
                                                for (auto& p : candidates) {
                                                    curFavor += p.favor;
                                                    ids.push_back(p.id);
                                                }
                                                sort(ids.begin(), ids.end());
                                                if (curFavor > maxFavor || (curFavor == maxFavor && ids < bestIds)) {
                                                    maxFavor = curFavor;
                                                    bestIds = ids;
                                                }
                                            }
                                }
                            }
                }

        if (maxFavor == -1) cout << "No solution.\n";
        else {
            for (int i = 0; i < 6; ++i) {
                if (i) cout << ' ';
                cout << bestIds[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
