#include <bits/stdc++.h>
using namespace std;

struct Key {
    unsigned long long low, high;
    bool operator == (const Key &other) const {
        return low == other.low && high == other.high;
    }
};

struct KeyHash {
    size_t operator () (const Key &key) const {
        return static_cast<size_t>(key.low ^ (key.high + 0x9e3779b97f4a7c15ULL + (key.low << 6) + (key.low >> 2)));
    }
};

struct Solver {
    int rowCount, colCount, diaCount;
    int rowNeed[10], colNeed[10], diaNeed[19];
    int colCnt[10], diaCnt[19], path[10];
    vector<vector<int> > cand;
    vector<vector<int> > diaLeft;
    unordered_map<Key, int, KeyHash> memo;

    Key getKey(int depth) {
        unsigned __int128 code = 0;
        int pos = 0;
        code |= static_cast<unsigned __int128>(depth) << pos;
        pos += 4;
        for (int i = 0; i < colCount; ++i) {
            code |= static_cast<unsigned __int128>(colCnt[i]) << pos;
            pos += 4;
        }
        for (int i = 0; i < diaCount; ++i) {
            code |= static_cast<unsigned __int128>(diaCnt[i]) << pos;
            pos += 4;
        }
        Key key;
        key.low = static_cast<unsigned long long>(code);
        key.high = static_cast<unsigned long long>(code >> 64);
        return key;
    }

    bool feasible(int depth) {
        int leftRow = rowCount - depth;
        for (int i = 0; i < colCount; ++i) {
            if (colCnt[i] > colNeed[i])
                return false;
            if (colNeed[i] - colCnt[i] > leftRow)
                return false;
        }
        for (int i = 0; i < diaCount; ++i) {
            if (diaCnt[i] > diaNeed[i])
                return false;
            if (diaNeed[i] - diaCnt[i] > diaLeft[depth][i])
                return false;
        }
        return true;
    }

    void put(int depth, int mask, int delta) {
        for (int j = 0; j < colCount; ++j) {
            if (((mask >> j) & 1) == 0)
                continue;
            colCnt[j] += delta;
            int dia = rowCount - 1 - depth + j;
            diaCnt[dia] += delta;
        }
    }

    int dfs(int depth) {
        if (!feasible(depth))
            return 0;
        if (depth == rowCount)
            return 1;
        Key key = getKey(depth);
        unordered_map<Key, int, KeyHash>::iterator it = memo.find(key);
        if (it != memo.end())
            return it->second;
        int ways = 0;
        for (int mask : cand[depth]) {
            put(depth, mask, 1);
            if (feasible(depth + 1)) {
                ways += dfs(depth + 1);
                if (ways >= 10000) {
                    ways = 10000;
                    put(depth, mask, -1);
                    break;
                }
            }
            put(depth, mask, -1);
        }
        memo[key] = ways;
        return ways;
    }

    void build(int depth) {
        if (depth == rowCount)
            return;
        for (int mask : cand[depth]) {
            put(depth, mask, 1);
            if (feasible(depth + 1) && dfs(depth + 1) == 1) {
                path[depth] = mask;
                build(depth + 1);
                put(depth, mask, -1);
                return;
            }
            put(depth, mask, -1);
        }
    }

    void init() {
        diaCount = rowCount + colCount - 1;
        cand.assign(rowCount, vector<int>());
        for (int i = 0; i < rowCount; ++i) {
            for (int mask = 0; mask < (1 << colCount); ++mask) {
                if (__builtin_popcount(static_cast<unsigned>(mask)) == rowNeed[i])
                    cand[i].push_back(mask);
            }
        }
        diaLeft.assign(rowCount + 1, vector<int>(diaCount, 0));
        for (int depth = rowCount - 1; depth >= 0; --depth) {
            diaLeft[depth] = diaLeft[depth + 1];
            for (int j = 0; j < colCount; ++j) {
                int dia = rowCount - 1 - depth + j;
                ++diaLeft[depth][dia];
            }
        }
        memset(colCnt, 0, sizeof(colCnt));
        memset(diaCnt, 0, sizeof(diaCnt));
        memset(path, 0, sizeof(path));
        memo.clear();
        memo.reserve(200000);
    }

    int solve() {
        init();
        return dfs(0);
    }

    vector<string> getBoard() {
        build(0);
        vector<string> board(rowCount, string(colCount, '.'));
        for (int i = 0; i < rowCount; ++i)
            for (int j = 0; j < colCount; ++j)
                if ((path[i] >> j) & 1)
                    board[i][j] = 'X';
        return board;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount, colCount;
    bool firstCase = true;
    while (cin >> rowCount >> colCount) {
        Solver solver;
        solver.rowCount = rowCount;
        solver.colCount = colCount;
        for (int i = 0; i < rowCount; ++i)
            cin >> solver.rowNeed[i];
        for (int i = 0; i < colCount; ++i)
            cin >> solver.colNeed[i];
        for (int i = 0; i < rowCount + colCount - 1; ++i)
            cin >> solver.diaNeed[i];
        int ways = solver.solve();
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        if (ways == 1) {
            vector<string> board = solver.getBoard();
            for (string row : board)
                cout << row << '\n';
        } else {
            cout << ways << '\n';
        }
    }
    return 0;
}
