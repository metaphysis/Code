// Relaxed Golf
// UVa ID: 11126
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 2.800s
// https://blog.csdn.net/metaphysis/article/details/163173818

#include <bits/stdc++.h>
using namespace std;

int cards[7][5];          // cards[i][0] 为底部，cards[i][4] 为顶部
int drawPile[17];         // drawPile[0] 为顶部，drawPile[16] 为底部
unordered_set<int> visited;

int encodeState(const int col[7], int drawUsed, int discardTop) {
    int state = discardTop;
    state = (state << 5) | drawUsed;
    for (int i = 6; i >= 0; --i) state = (state << 3) | col[i];
    return state;
}

bool dfs(int col[7], int drawUsed, int discardTop) {
    // 所有列已空 -> 剩余抽牌可连续抽完
    bool allEmpty = true;
    for (int i = 0; i < 7; ++i) if (col[i] < 5) { allEmpty = false; break; }
    if (allEmpty) return true;

    int state = encodeState(col, drawUsed, discardTop);
    if (visited.find(state) != visited.end()) return false;
    visited.insert(state);

    // 从抽牌堆取牌
    if (drawUsed < 17) {
        int newDraw = drawUsed + 1;
        int newDiscard = drawPile[drawUsed];
        int newCol[7];
        for (int i = 0; i < 7; ++i) newCol[i] = col[i];
        if (dfs(newCol, newDraw, newDiscard)) return true;
    }

    // 从各列取牌
    for (int i = 0; i < 7; ++i) {
        if (col[i] < 5) {
            int rank = cards[i][4 - col[i]];
            if (abs(rank - discardTop) == 1 || abs(rank - discardTop) == 12) {
                int newCol[7];
                for (int j = 0; j < 7; ++j) newCol[j] = col[j];
                newCol[i]++;
                if (dfs(newCol, drawUsed, rank)) return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int caseNum = 1; caseNum <= N; ++caseNum) {
        // 读取列（底部到顶部）
        for (int r = 0; r < 5; ++r)
            for (int c = 0; c < 7; ++c)
                cin >> cards[c][r];

        // 读取抽牌堆（底部到顶部），反转后使顶部在索引0
        int temp[17];
        for (int i = 0; i < 17; ++i) cin >> temp[i];
        for (int i = 0; i < 17; ++i) drawPile[i] = temp[16 - i];

        visited.clear();
        int col[7] = {0};

        // 第一步必须从抽牌堆取牌
        int drawUsed = 1;
        int discardTop = drawPile[0];

        bool result = dfs(col, drawUsed, discardTop);
        cout << "Case #" << caseNum << ": " << (result ? "Yes" : "No") << "\n";
    }
    return 0;
}
