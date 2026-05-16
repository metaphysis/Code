// Cutting Up
// UVa ID: 366
// Verdict: Accepted
// Submission Date: 2026-05-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int l, h, w;
    while (cin >> l >> h >> w) {
        if (l == 0 && h == 0 && w == 0) break;
        vector<pair<int, int>> pieces;
        pieces.push_back({w, h});
        int cuts = 0;
        while (true) {
            vector<pair<int, int>> needToCut;
            for (auto p : pieces)
                if (p.first * p.second > 1)
                    needToCut.push_back(p);
            if (needToCut.empty()) break;
            sort(needToCut.begin(), needToCut.end(), [](pair<int, int> a, pair<int, int> b) {
                return a.first * a.second > b.first * b.second;
            });
            vector<pair<int, int>> newPieces;
            int take = min(l, (int)needToCut.size());
            for (int i = 0; i < take; i++) {
                auto p = needToCut[i];
                if (p.first >= p.second) {
                    newPieces.push_back({p.first / 2, p.second});
                    newPieces.push_back({p.first - (p.first / 2), p.second});
                } else {
                    newPieces.push_back({p.first, p.second / 2});
                    newPieces.push_back({p.first, p.second - (p.second / 2)});
                }
            }
            for (int i = take; i < (int)needToCut.size(); i++)
                newPieces.push_back(needToCut[i]);
            pieces = newPieces;
            cuts++;
        }
        cout << h << " by " << w << " takes " << cuts << " cuts\n\n";
    }
    return 0;
}
