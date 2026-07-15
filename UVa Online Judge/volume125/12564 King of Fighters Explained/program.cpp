// King of Fighters Explained
// UVa ID: 12564
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

bool isOverlap(const Rect& a, const Rect& b) {
    return a.x1 < b.x2 && b.x1 < a.x2 && a.y1 < b.y2 && b.y1 < a.y2;
}

bool hasHit(const vector<Rect>& att, const vector<Rect>& weak) {
    for (const Rect& a : att)
        for (const Rect& w : weak)
            if (isOverlap(a, w)) return true;
    return false;
}

int main() {
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int a1, w1;
        cin >> a1 >> w1;
        vector<Rect> att1(a1), weak1(w1);
        for (int i = 0; i < a1; ++i) cin >> att1[i].x1 >> att1[i].y1 >> att1[i].x2 >> att1[i].y2;
        for (int i = 0; i < w1; ++i) cin >> weak1[i].x1 >> weak1[i].y1 >> weak1[i].x2 >> weak1[i].y2;

        int a2, w2;
        cin >> a2 >> w2;
        vector<Rect> att2(a2), weak2(w2);
        for (int i = 0; i < a2; ++i) cin >> att2[i].x1 >> att2[i].y1 >> att2[i].x2 >> att2[i].y2;
        for (int i = 0; i < w2; ++i) cin >> weak2[i].x1 >> weak2[i].y1 >> weak2[i].x2 >> weak2[i].y2;

        bool hitFirst  = hasHit(att2, weak1);
        bool hitSecond = hasHit(att1, weak2);

        string result;
        if (hitFirst && hitSecond) result = "Both";
        else if (hitFirst)         result = "First";
        else if (hitSecond)        result = "Second";
        else                       result = "Neither";

        cout << "Case " << caseNo << ": " << result << '\n';
    }
    return 0;
}
