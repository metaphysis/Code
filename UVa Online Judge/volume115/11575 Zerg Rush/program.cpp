#include <bits/stdc++.h>
using namespace std;

struct Zerg {
    int player, hp, tr, tc;
    bool alive, attacked;
};

const int inf = 1000000000;
const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int br[4] = {-1, 0, 1, 0};
const int bc[4] = {0, 1, 0, -1};

vector<vector<int>> getDist(int n, int player, const vector<vector<int>>& board, const vector<Zerg>& zergs) {
    vector<vector<int>> dist(n, vector<int>(n, inf));
    queue<pair<int, int>> que;
    for (int pos = 0; pos < n * n; pos++) {
        int r = pos / n, c = pos % n, id = board[r][c];
        if (id != -1 && zergs[id].player == player) {
            dist[r][c] = 0;
            que.push({r, c});
        }
    }
    while (!que.empty()) {
        int r = que.front().first, c = que.front().second;
        que.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + br[d], nc = c + bc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
            if (dist[nr][nc] <= dist[r][c] + 1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            que.push({nr, nc});
        }
    }
    return dist;
}

void simulateTurn(int n, const int atk[2], const int armor[2], vector<vector<int>>& board, vector<Zerg>& zergs) {
    bool has[2] = {false, false};
    vector<int> damage(zergs.size(), 0);
    for (int id = 0; id < (int)zergs.size(); id++) {
        zergs[id].attacked = false;
        zergs[id].tr = zergs[id].tc = -1;
        if (zergs[id].alive) has[zergs[id].player] = true;
    }
    vector<vector<int>> dist0 = getDist(n, 0, board, zergs);
    vector<vector<int>> dist1 = getDist(n, 1, board, zergs);
    for (int pos = 0; pos < n * n; pos++) {
        int r = pos / n, c = pos % n, id = board[r][c];
        if (id == -1) continue;
        int player = zergs[id].player, enemyId = -1;
        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
            int nextId = board[nr][nc];
            if (nextId != -1 && zergs[nextId].player != player) {
                enemyId = nextId;
                break;
            }
        }
        if (enemyId != -1) {
            zergs[id].attacked = true;
            damage[enemyId] += 5 + atk[player] - armor[1 - player];
        } else if (has[1 - player]) {
            int bestDist = inf;
            for (int d = 0; d < 8; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                int curDist = player == 0 ? dist1[nr][nc] : dist0[nr][nc];
                if (curDist < bestDist) {
                    bestDist = curDist;
                    zergs[id].tr = nr;
                    zergs[id].tc = nc;
                }
            }
        }
    }
    for (int id = 0; id < (int)zergs.size(); id++) {
        if (!zergs[id].alive) continue;
        zergs[id].hp -= damage[id];
        if (zergs[id].hp <= 0) zergs[id].alive = false;
    }
    for (int pos = 0; pos < n * n; pos++) {
        int r = pos / n, c = pos % n, id = board[r][c];
        if (id != -1 && !zergs[id].alive) board[r][c] = -1;
    }
    vector<int> destWinner(n * n, -1), result(zergs.size(), 0), seen(zergs.size(), 0);
    vector<char> winner(zergs.size(), false);
    for (int pos = 0; pos < n * n; pos++) {
        int r = pos / n, c = pos % n, id = board[r][c];
        if (id == -1 || zergs[id].attacked || zergs[id].tr == -1) continue;
        int target = zergs[id].tr * n + zergs[id].tc;
        if (destWinner[target] == -1) {
            destWinner[target] = id;
            winner[id] = true;
        }
    }
    int run = 0;
    for (int start = 0; start < (int)zergs.size(); start++) {
        if (!winner[start] || result[start] != 0) continue;
        vector<int> path;
        int cur = start, base = 0;
        run++;
        while (true) {
            if (result[cur] != 0) {
                base = result[cur];
                break;
            }
            seen[cur] = run;
            path.push_back(cur);
            int occ = board[zergs[cur].tr][zergs[cur].tc];
            if (occ == -1) {
                base = 1;
                break;
            }
            if (!winner[occ]) {
                base = -1;
                break;
            }
            if (seen[occ] == run) {
                base = 1;
                break;
            }
            cur = occ;
        }
        for (int id : path) result[id] = base;
    }
    for (int pos = 0; pos < n * n; pos++) {
        int r = pos / n, c = pos % n, id = board[r][c];
        if (id != -1 && winner[id] && result[id] == 1) board[r][c] = -1;
    }
    for (int id = 0; id < (int)zergs.size(); id++)
        if (winner[id] && result[id] == 1) board[zergs[id].tr][zergs[id].tc] = id;
    for (int id = 0; id < (int)zergs.size(); id++)
        if (zergs[id].alive && zergs[id].hp < 35) zergs[id].hp++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNum = 0;
    while (cin >> n && n != 0) {
        int atk[2], armor[2], turn;
        cin >> atk[0] >> armor[0] >> atk[1] >> armor[1];
        vector<string> input(n);
        vector<vector<int>> board(n, vector<int>(n, -1));
        vector<Zerg> zergs;
        for (int r = 0; r < n; r++) {
            cin >> input[r];
            for (int c = 0; c < n; c++) {
                if (input[r][c] == '.') continue;
                int player = input[r][c] - '1';
                board[r][c] = zergs.size();
                zergs.push_back({player, 35, -1, -1, true, false});
            }
        }
        cin >> turn;
        for (int curTurn = 0; curTurn < turn; curTurn++) simulateTurn(n, atk, armor, board, zergs);
        if (caseNum++) cout << '\n';
        vector<string> output(n, string(n, '.'));
        for (int pos = 0; pos < n * n; pos++) {
            int r = pos / n, c = pos % n, id = board[r][c];
            if (id != -1) output[r][c] = char('1' + zergs[id].player);
        }
        for (int r = 0; r < n; r++) cout << output[r] << '\n';
    }
    return 0;
}
