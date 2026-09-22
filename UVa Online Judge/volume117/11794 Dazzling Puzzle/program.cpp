#include <bits/stdc++.h>
using namespace std;

struct Puzzle {
    int n, total, blank, bfsTag, baseRow, baseCol, areaH, areaW;
    bool trans;
    vector<int> board, pos, fixedCell, seen, pre, preDir, bfsQue;
    string answer;
    int dr[4] = {0, 0, -1, 1};
    int dc[4] = {-1, 1, 0, 0};
    string moveChar = "lrud";

    Puzzle(int size, const vector<int>& init) {
        n = size;
        total = n * n;
        board = init;
        pos.resize(total);
        fixedCell.assign(total, 0);
        seen.assign(total, 0);
        pre.resize(total);
        preDir.resize(total);
        bfsQue.resize(total);
        bfsTag = 0;
        for (int i = 0; i < total; i++) pos[board[i]] = i;
        blank = pos[0];
        answer.reserve(8 * n * n * n);
    }

    int getId(int x, int y) {
        if (trans) return (baseRow + y) * n + baseCol + x;
        return (baseRow + x) * n + baseCol + y;
    }

    pair<int, int> getCoord(int id) {
        int x = id / n - baseRow, y = id % n - baseCol;
        if (trans) swap(x, y);
        return {x, y};
    }

    bool inWindow(int id) {
        pair<int, int> p = getCoord(id);
        return p.first >= 0 && p.first < 3
            && p.second >= areaW - 2 && p.second < areaW;
    }

    void makeMove(int dir) {
        int row = blank / n, col = blank % n;
        int nextId = (row + dr[dir]) * n + col + dc[dir];
        int value = board[nextId];
        swap(board[blank], board[nextId]);
        pos[value] = blank;
        pos[0] = nextId;
        blank = nextId;
        answer += moveChar[dir];
    }

    void swapWith(int id) {
        int diff = id - blank, dir = 0;
        if (diff == -1) dir = 0;
        else if (diff == 1) dir = 1;
        else if (diff == -n) dir = 2;
        else dir = 3;
        makeMove(dir);
    }

    bool routeBlank(int goal, int banA, int banB, bool local) {
        int centerRow = 0, centerCol = 0;
        if (local) {
            centerRow = banA / n;
            centerCol = banA % n;
            if (abs(blank / n - centerRow) > 2 || abs(blank % n - centerCol) > 2) return false;
        }
        ++bfsTag;
        int head = 0, tail = 0, found = -1;
        bfsQue[tail++] = blank;
        seen[blank] = bfsTag;
        pre[blank] = -1;
        while (head < tail) {
            int cur = bfsQue[head++];
            if ((goal >= 0 && cur == goal) || (goal < 0 && inWindow(cur))) {
                found = cur;
                break;
            }
            int row = cur / n, col = cur % n;
            for (int dir = 0; dir < 4; dir++) {
                int nextRow = row + dr[dir], nextCol = col + dc[dir];
                if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n) continue;
                if (local && (abs(nextRow - centerRow) > 2 || abs(nextCol - centerCol) > 2)) continue;
                int nextId = nextRow * n + nextCol;
                if (fixedCell[nextId] || nextId == banA || nextId == banB || seen[nextId] == bfsTag) continue;
                seen[nextId] = bfsTag;
                pre[nextId] = cur;
                preDir[nextId] = dir;
                bfsQue[tail++] = nextId;
            }
        }
        if (found < 0) return false;
        vector<int> path;
        for (int cur = found; pre[cur] != -1; cur = pre[cur]) path.push_back(preDir[cur]);
        for (int i = (int)path.size() - 1; i >= 0; i--) makeMove(path[i]);
        return true;
    }

    void bringTile(int value, int goalX, int goalY, bool stopInWindow) {
        while (true) {
            int tileId = pos[value];
            pair<int, int> p = getCoord(tileId);
            int x = p.first, y = p.second;
            if (stopInWindow && inWindow(tileId)) return;
            if (x == goalX && y == goalY) return;
            int nextX = x, nextY = y;
            if (y < goalY) ++nextY;
            else if (y > goalY) --nextY;
            else if (x < goalX) ++nextX;
            else --nextX;
            int nextId = getId(nextX, nextY);
            if (!routeBlank(nextId, tileId, -1, true)) routeBlank(nextId, tileId, -1, false);
            swapWith(tileId);
        }
    }

    int encodeLocal(const vector<int>& state) {
        int code = 0, mul = 1;
        for (int value : state) {
            code += value * mul;
            mul *= 4;
        }
        return code;
    }

    void solveLocal(const vector<int>& cells, const vector<int>& values,
                    const vector<int>& goals) {
        int cellCount = cells.size(), stateCount = 1 << (2 * cellCount);
        vector<int> state(cellCount, 3), localPre(stateCount, -2);
        vector<int> localMove(stateCount, -1), que;
        vector<vector<int>> adj(cellCount);
        for (int i = 0; i < cellCount; i++) {
            if (board[cells[i]] == 0) state[i] = 0;
            for (int j = 0; j < (int)values.size(); j++) {
                if (board[cells[i]] == values[j]) state[i] = j + 1;
            }
            for (int j = 0; j < cellCount; j++) {
                int distance = abs(cells[i] / n - cells[j] / n)
                    + abs(cells[i] % n - cells[j] % n);
                if (distance == 1) adj[i].push_back(j);
            }
        }
        int start = encodeLocal(state), finish = -1;
        localPre[start] = -1;
        que.push_back(start);
        for (int head = 0; head < (int)que.size(); head++) {
            int code = que[head], temp = code, zero = -1;
            for (int i = 0; i < cellCount; i++) {
                state[i] = temp % 4;
                temp /= 4;
                if (state[i] == 0) zero = i;
            }
            bool done = true;
            for (int i = 0; i < (int)goals.size(); i++) {
                if (state[goals[i]] != i + 1) done = false;
            }
            if (done) {
                finish = code;
                break;
            }
            for (int next : adj[zero]) {
                swap(state[zero], state[next]);
                int nextCode = encodeLocal(state);
                if (localPre[nextCode] == -2) {
                    localPre[nextCode] = code;
                    localMove[nextCode] = next;
                    que.push_back(nextCode);
                }
                swap(state[zero], state[next]);
            }
        }
        vector<int> path;
        for (int cur = finish; localPre[cur] != -1; cur = localPre[cur]) path.push_back(localMove[cur]);
        for (int i = (int)path.size() - 1; i >= 0; i--) swapWith(cells[path[i]]);
    }

    void solveRow(int row, int col, int height, int width, bool turn) {
        baseRow = row;
        baseCol = col;
        areaH = height;
        areaW = width;
        trans = turn;
        for (int y = 0; y < areaW - 2; y++) {
            int goal = getId(0, y), value = goal + 1;
            bringTile(value, 0, y, false);
            fixedCell[goal] = 1;
        }
        int goalA = getId(0, areaW - 2), goalB = getId(0, areaW - 1);
        int valueA = goalA + 1, valueB = goalB + 1;
        bringTile(valueA, 0, areaW - 2, false);
        fixedCell[goalA] = 1;
        bringTile(valueB, 1, areaW - 1, true);
        if (!inWindow(blank)) routeBlank(-1, pos[valueA], pos[valueB], false);
        fixedCell[goalA] = 0;
        vector<int> cells;
        for (int x = 0; x < 3; x++) {
            for (int y = areaW - 2; y < areaW; y++) cells.push_back(getId(x, y));
        }
        solveLocal(cells, {valueA, valueB}, {0, 1});
        fixedCell[goalA] = 1;
        fixedCell[goalB] = 1;
    }

    string solve() {
        for (int layer = 0; layer < n - 2; layer++) {
            int size = n - layer;
            solveRow(layer, layer, size, size, false);
            solveRow(layer + 1, layer, size, size - 1, true);
        }
        vector<int> cells, values;
        for (int row = n - 2; row < n; row++) {
            for (int col = n - 2; col < n; col++) cells.push_back(row * n + col);
        }
        for (int i = 0; i < 3; i++) values.push_back(cells[i] + 1);
        solveLocal(cells, values, {0, 1, 2});
        return answer;
    }
};

bool isSolvable(const vector<int>& board, int n) {
    int total = n * n, parity = 0, count = 0, zeroRow = 0;
    vector<int> bit(total + 1, 0);
    for (int i = 0; i < total; i++) {
        int value = board[i], sum = 0;
        if (value == 0) {
            zeroRow = i / n;
            continue;
        }
        for (int j = value; j > 0; j -= j & -j) sum += bit[j];
        parity ^= (count - sum) & 1;
        for (int j = value; j <= total; j += j & -j) ++bit[j];
        ++count;
    }
    if (n % 2 == 1) return parity == 0;
    return ((parity + n - zeroRow) & 1) == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int n;
        cin >> n;
        vector<int> board(n * n);
        bool solved = true;
        for (int i = 0; i < n * n; i++) {
            cin >> board[i];
            if (board[i] != (i + 1) % (n * n)) solved = false;
        }
        cout << "Case " << caseId << ": ";
        if (solved) cout << "solved\n";
        else if (!isSolvable(board, n)) cout << "impossible\n";
        else {
            Puzzle puzzle(n, board);
            cout << puzzle.solve() << '\n';
        }
    }
    return 0;
}
