#include <bits/stdc++.h>
using namespace std;

struct Solver {
    int rowCnt, colCnt, edgeCnt, wordCnt, best;
    vector<pair<int, int> > edges;
    vector<vector<int> > rowEdges, colEdges, candidates;
    vector<vector<unsigned long long> > cover;
    unordered_map<string, int> memo;

    bool isInside(double px, double py, const vector<pair<int, int> >& points) {
        bool in = false;
        int n = points.size();
        for (int i = 0, j = n - 1; i < n; j = i++) {
            double xi = points[i].first, yi = points[i].second;
            double xj = points[j].first, yj = points[j].second;
            if ((yi > py) != (yj > py) && px < (xj - xi) * (py - yi) / (yj - yi) + xi)
                in = !in;
        }
        return in;
    }

    bool isCovered(const vector<unsigned long long>& state, int id) {
        return (state[id >> 6] >> (id & 63)) & 1ULL;
    }

    int getGain(int id, const vector<unsigned long long>& state) {
        int gain = 0;
        for (int i = 0; i < wordCnt; i++)
            gain += __builtin_popcountll(cover[id][i] & ~state[i]);
        return gain;
    }

    bool isFull(const vector<unsigned long long>& state) {
        for (int i = 0; i < wordCnt; i++) {
            unsigned long long mask = ~0ULL;
            if (i == wordCnt - 1 && edgeCnt % 64 != 0)
                mask = (1ULL << (edgeCnt % 64)) - 1;
            if ((state[i] & mask) != mask)
                return false;
        }
        return true;
    }

    string makeKey(const vector<unsigned long long>& state) {
        return string(reinterpret_cast<const char*>(state.data()), wordCnt * sizeof(unsigned long long));
    }

    int matchingLowerBound(const vector<unsigned long long>& state) {
        vector<char> usedRow(rowCnt, 0), usedCol(colCnt, 0);
        int matching = 0;
        for (int i = 0; i < edgeCnt; i++) {
            if (isCovered(state, i))
                continue;
            int r = edges[i].first, c = edges[i].second;
            if (!usedRow[r] && !usedCol[c]) {
                usedRow[r] = 1;
                usedCol[c] = 1;
                matching++;
            }
        }
        return (matching + 1) / 2;
    }

    void makeInitialBest() {
        vector<unsigned long long> state(wordCnt, 0);
        int used = 0;
        while (!isFull(state)) {
            int id = -1, gain = -1;
            for (int i = 0; i < edgeCnt; i++) {
                int cur = getGain(i, state);
                if (cur > gain) {
                    gain = cur;
                    id = i;
                }
            }
            for (int i = 0; i < wordCnt; i++)
                state[i] |= cover[id][i];
            used++;
        }
        best = used;
    }

    void dfs(vector<unsigned long long>& state, int used, int remain) {
        if (used >= best)
            return;
        if (remain == 0) {
            best = used;
            return;
        }
        int lowerBound = matchingLowerBound(state);
        if (used + lowerBound >= best)
            return;
        string key = makeKey(state);
        unordered_map<string, int>::iterator it = memo.find(key);
        if (it != memo.end() && it->second <= used)
            return;
        memo[key] = used;
        int target = -1, minCandidate = INT_MAX;
        for (int i = 0; i < edgeCnt; i++) {
            if (isCovered(state, i))
                continue;
            int count = 0;
            for (int id : candidates[i])
                if (getGain(id, state) > 0)
                    count++;
            if (count < minCandidate) {
                minCandidate = count;
                target = i;
                if (count == 1)
                    break;
            }
        }
        vector<pair<int, int> > order;
        for (int id : candidates[target]) {
            int gain = getGain(id, state);
            if (gain > 0)
                order.push_back(make_pair(-gain, id));
        }
        sort(order.begin(), order.end());
        vector<unsigned long long> next(wordCnt);
        for (pair<int, int> item : order) {
            int id = item.second;
            int gain = getGain(id, state);
            next = state;
            for (int i = 0; i < wordCnt; i++)
                next[i] |= cover[id][i];
            dfs(next, used + 1, remain - gain);
        }
    }

    int solve(const vector<pair<int, int> >& points) {
        bool has[101][101] = {};
        int maxX = 0, maxY = 0;
        for (pair<int, int> p : points) {
            maxX = max(maxX, p.first);
            maxY = max(maxY, p.second);
        }
        for (int x = 1; x < maxX; x++)
            for (int y = 1; y < maxY; y++)
                if (isInside(x + 0.5, y + 0.5, points))
                    has[x][y] = true;
        int rowId[101] = {}, colId[101] = {};
        rowCnt = colCnt = 0;
        for (int x = 1; x <= 100; x++)
            for (int y = 1; y <= 100; y++)
                if (has[x][y]) {
                    if (!rowId[x])
                        rowId[x] = rowCnt++;
                    if (!colId[y])
                        colId[y] = colCnt++;
                }
        edges.clear();
        for (int x = 1; x <= 100; x++)
            for (int y = 1; y <= 100; y++)
                if (has[x][y])
                    edges.push_back(make_pair(rowId[x], colId[y]));
        edgeCnt = edges.size();
        if (edgeCnt == 0)
            return 0;
        rowEdges.assign(rowCnt, vector<int>());
        colEdges.assign(colCnt, vector<int>());
        for (int i = 0; i < edgeCnt; i++) {
            rowEdges[edges[i].first].push_back(i);
            colEdges[edges[i].second].push_back(i);
        }
        wordCnt = (edgeCnt + 63) >> 6;
        cover.assign(edgeCnt, vector<unsigned long long>(wordCnt, 0));
        candidates.assign(edgeCnt, vector<int>());
        for (int i = 0; i < edgeCnt; i++) {
            int r = edges[i].first, c = edges[i].second;
            for (int id : rowEdges[r]) {
                candidates[i].push_back(id);
                cover[i][id >> 6] |= 1ULL << (id & 63);
            }
            for (int id : colEdges[c]) {
                if (edges[id].first == r)
                    continue;
                candidates[i].push_back(id);
                cover[i][id >> 6] |= 1ULL << (id & 63);
            }
        }
        memo.clear();
        memo.reserve(1 << 16);
        makeInitialBest();
        vector<unsigned long long> state(wordCnt, 0);
        dfs(state, 0, edgeCnt);
        return best;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int, int> > points;
    int x, y, testCase = 1;
    Solver solver;
    while (cin >> x >> y) {
        if (x == 0 && y == 0) {
            if (points.empty())
                break;
            cout << testCase++ << " " << solver.solve(points) << "\n";
            points.clear();
        } else {
            points.push_back(make_pair(x, y));
        }
    }
    return 0;
}
