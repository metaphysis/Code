// Matrix
// UVa ID: 10358
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.590s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int dx[] = {0, 1, -1, 0, 0}, dy[] = {0, 0, 0, 1, -1};

int n;
vector<string> board(8);
int dp[8][8][8][8][8][8][2][100];

bool isWall(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return true;
    return board[x][y] == '#';
}

bool isPhone(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return false;
    return board[x][y] == 'P';
}

bool canMove(int x, int y, int nx, int ny) {
    if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) return false;
    if (isWall(nx, ny)) return false;
    return true;
}

bool caught(int mx, int my, int a1x, int a1y, int a2x, int a2y) {
    return (mx == a1x && my == a1y) || (mx == a2x && my == a2y);
}

bool canEscape(int mx, int my, int a1x, int a1y, int a2x, int a2y) {
    return isPhone(mx, my) && !caught(mx, my, a1x, a1y, a2x, a2y);
}

int dfs(int mx, int my, int a1x, int a1y, int a2x, int a2y, int turn, int depth) {
    if (depth > 40) return 0;
    
    if (dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] != -1) 
        return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth];
    
    if (canEscape(mx, my, a1x, a1y, a2x, a2y)) 
        return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 1;
    if (caught(mx, my, a1x, a1y, a2x, a2y)) 
        return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 2;
    
    if (turn == 0) {
        bool canWin = false, allLose = true;
        for (int d = 0; d < 5; d++) {
            int nmx = mx + dx[d], nmy = my + dy[d];
            if (!canMove(mx, my, nmx, nmy)) continue;
            int r = dfs(nmx, nmy, a1x, a1y, a2x, a2y, 1, depth + 1);
            if (r == 1) canWin = true;
            if (r != 2) allLose = false;
        }
        if (canWin) return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 1;
        if (allLose) return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 2;
        return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 0;
    } 
    else {
        bool canCatch = false, allEscape = true;
        for (int d1 = 0; d1 < 5; d1++) {
            int na1x = a1x + dx[d1], na1y = a1y + dy[d1];
            if (!canMove(a1x, a1y, na1x, na1y)) continue;
            for (int d2 = 0; d2 < 5; d2++) {
                int na2x = a2x + dx[d2], na2y = a2y + dy[d2];
                if (!canMove(a2x, a2y, na2x, na2y)) continue;
                int r = dfs(mx, my, na1x, na1y, na2x, na2y, 0, depth + 1);
                if (r == 2) canCatch = true;
                if (r != 1) allEscape = false;
            }
        }
        if (canCatch) return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 2;
        if (allEscape) return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 1;
        return dp[mx][my][a1x][a1y][a2x][a2y][turn][depth] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    cin.ignore();
    
    for (int t = 0; t < n; t++) {
        for (int i = 0; i < 8; i++) getline(cin, board[i]);
        string line;
        getline(cin, line);

        int mx, my, a1x = -1, a1y, a2x, a2y, agentCnt = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] == 'M') mx = i, my = j;
                else if (board[i][j] == 'A')
                    if (agentCnt++ == 0) a1x = i, a1y = j;
                    else a2x = i, a2y = j;
        
        memset(dp, -1, sizeof(dp));
        int r = dfs(mx, my, a1x, a1y, a2x, a2y, 0, 0);
        
        if (r == 1) cout << "You can escape.\n";
        else if (r == 2) cout << "You are eliminated.\n";
        else cout << "You are trapped in the Matrix.\n";
    }
    
    return 0;
}
