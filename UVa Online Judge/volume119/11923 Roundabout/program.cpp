// Roundabout
// UVa ID: 11923
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163217180

#include <bits/stdc++.h>
using namespace std;

int board[4][4];

int calcScoreForPos(int r, int c, int player) {
    int orig = board[r][c];
    board[r][c] = player;
    int total = 0;
    int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (int d = 0; d < 4; ++d) {
        int dr = dirs[d][0], dc = dirs[d][1];
        int left = 0, right = 0;
        int nr = r - dr, nc = c - dc;
        while (nr >= 0 && nr < 4 && nc >= 0 && nc < 4 && board[nr][nc] == player) {
            ++left;
            nr -= dr;
            nc -= dc;
        }
        nr = r + dr;
        nc = c + dc;
        while (nr >= 0 && nr < 4 && nc >= 0 && nc < 4 && board[nr][nc] == player) {
            ++right;
            nr += dr;
            nc += dc;
        }
        int L = left + 1 + right;
        int k = left + 1;
        if (L >= 3) {
            int minStart = max(1, k - 2);
            int maxStart = min(k, L - 2);
            if (minStart <= maxStart)
                total += (maxStart - minStart + 1) * 3;
        }
        if (L >= 4) {
            int minStart = max(1, k - 3);
            int maxStart = min(k, L - 3);
            if (minStart <= maxStart)
                total += (maxStart - minStart + 1) * 4;
        }
    }
    board[r][c] = orig;
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        string s;
        cin >> s;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                board[i][j] = 0;
        int score1 = 0, score2 = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == '0')
                continue;
            int player = (i % 2 == 0) ? 1 : 2;
            bool allPlayer = true;
            for (int r = 0; r < 4; ++r) {
                for (int c = 0; c < 4; ++c)
                    if (board[r][c] != player) {
                        allPlayer = false;
                        break;
                    }
                if (!allPlayer)
                    break;
            }
            if (allPlayer) {
                if (player == 1)
                    score1 += 50;
                else
                    score2 += 50;
                continue;
            }
            bool hasWhite = false;
            for (int r = 0; r < 4; ++r)
                for (int c = 0; c < 4; ++c)
                    if (board[r][c] == 0) {
                        hasWhite = true;
                        break;
                    }
            vector<pair<int, int>> candidates;
            if (hasWhite) {
                for (int r = 0; r < 4; ++r)
                    for (int c = 0; c < 4; ++c)
                        if (board[r][c] == 0)
                            candidates.push_back({r, c});
            } else {
                int opponent = (player == 1) ? 2 : 1;
                for (int r = 0; r < 4; ++r)
                    for (int c = 0; c < 4; ++c)
                        if (board[r][c] == opponent)
                            candidates.push_back({r, c});
            }
            int bestScore = -1, bestR = -1, bestC = -1;
            for (auto &p : candidates) {
                int r = p.first, c = p.second;
                int sc = calcScoreForPos(r, c, player);
                if (sc > bestScore || (sc == bestScore && (r < bestR || (r == bestR && c < bestC)))) {
                    bestScore = sc;
                    bestR = r;
                    bestC = c;
                }
            }
            board[bestR][bestC] = player;
            if (player == 1)
                score1 += bestScore;
            else
                score2 += bestScore;
        }
        cout << "Case " << caseNo << ": " << score1 << " " << score2 << "\n";
    }
    return 0;
}
