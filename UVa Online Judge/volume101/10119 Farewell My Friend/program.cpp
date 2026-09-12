#include <bits/stdc++.h>
using namespace std;

const int moveX[4] = {-1, 1, 0, 0};
const int moveY[4] = {0, 0, -1, 1};

class Solver {
private:
    int n, viewK, minDist;
    vector<string> base, work;
    vector<int> candidates;
    vector<char> reach;
    queue<int> que;

    int id(int x, int y) {
        return x * n + y;
    }

    void markReach(int start) {
        fill(reach.begin(), reach.end(), 0);
        while (!que.empty()) que.pop();
        reach[start] = 1;
        que.push(start);
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            int x = cur / n, y = cur % n;
            for (int d = 0; d < 4; d++) {
                int nx = x + moveX[d], ny = y + moveY[d];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                int next = id(nx, ny);
                if (work[nx][ny] != '.' || reach[next]) continue;
                reach[next] = 1;
                que.push(next);
            }
        }
    }

    void prepare() {
        vector<char> fromLiz(n * n, 0), fromLilly(n * n, 0);
        markReach(id(0, 0));
        fromLiz = reach;
        markReach(id(n - 1, n - 1));
        fromLilly = reach;
        candidates.clear();
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                int cur = id(x, y);
                int d1 = x + y, d2 = 2 * n - 2 - x - y;
                if (work[x][y] == '.' && (fromLiz[cur] || fromLilly[cur]) && d1 >= minDist && d2 >= minDist) candidates.push_back(cur);
            }
        }
    }

    bool canSee(int x, int y, const vector<char> &liz) {
        for (int d = 0; d < 4; d++) {
            int nx = x + moveX[d], ny = y + moveY[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n || work[nx][ny] != 'O') continue;
            for (int step = 2; step <= viewK; step++) {
                int tx = x + moveX[d] * step, ty = y + moveY[d] * step;
                if (tx < 0 || tx >= n || ty < 0 || ty >= n) break;
                if (work[tx][ty] == '*') break;
                if (liz[id(tx, ty)]) return true;
            }
        }
        return false;
    }

    bool safe() {
        vector<char> liz(n * n, 0), lilly(n * n, 0);
        int start = id(0, 0), target = id(n - 1, n - 1);
        while (!que.empty()) que.pop();
        liz[start] = 1;
        que.push(start);
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            int x = cur / n, y = cur % n;
            for (int d = 0; d < 4; d++) {
                int nx = x + moveX[d], ny = y + moveY[d];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                int next = id(nx, ny);
                if (work[nx][ny] != '.' || liz[next]) continue;
                if (next == target) return false;
                liz[next] = 1;
                que.push(next);
            }
        }
        while (!que.empty()) que.pop();
        lilly[target] = 1;
        que.push(target);
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            int x = cur / n, y = cur % n;
            if (canSee(x, y, liz)) return false;
            for (int d = 0; d < 4; d++) {
                int nx = x + moveX[d], ny = y + moveY[d];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                int next = id(nx, ny);
                if (work[nx][ny] != '.' || lilly[next]) continue;
                lilly[next] = 1;
                que.push(next);
            }
        }
        return true;
    }

    bool blockAll(int start) {
        for (int i = start; i < (int)candidates.size(); i++) {
            int cur = candidates[i];
            work[cur / n][cur % n] = '*';
        }
        bool result = safe();
        for (int i = start; i < (int)candidates.size(); i++) {
            int cur = candidates[i];
            work[cur / n][cur % n] = '.';
        }
        return result;
    }

    bool search(int start, int left) {
        if (left == 0) return safe();
        if ((int)candidates.size() - start < left) return false;
        int limit = (int)candidates.size() - left;
        for (int i = start; i <= limit; i++) {
            int cur = candidates[i];
            work[cur / n][cur % n] = '*';
            if (blockAll(i + 1) && search(i + 1, left - 1)) return true;
            work[cur / n][cur % n] = '.';
        }
        return false;
    }

public:
    Solver(int n, int viewK, int minDist, const vector<string> &grid) : n(n), viewK(viewK), minDist(minDist), base(grid), work(grid), reach(n * n) {}

    int solve() {
        prepare();
        if (!blockAll(0)) return -1;
        for (int depth = 0; depth <= (int)candidates.size(); depth++) {
            work = base;
            if (search(0, depth)) return depth;
            for (int cur : candidates) work[cur / n][cur % n] = '.';
        }
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, viewK, minDist;
    while (cin >> n >> viewK >> minDist) {
        if (n == 0 && viewK == 0 && minDist == 0) break;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) cin >> grid[i];
        Solver solver(n, viewK, minDist, grid);
        cout << solver.solve() << '\n';
    }
    return 0;
}
