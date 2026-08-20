#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> fa;

    Dsu(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
    }

    int findRoot(int x) {
        if (fa[x] == x) return x;
        return fa[x] = findRoot(fa[x]);
    }

    bool mergeSet(int x, int y) {
        x = findRoot(x);
        y = findRoot(y);
        if (x == y) return false;
        fa[x] = y;
        return true;
    }
};

int encodeState(const vector<int>& state) {
    int code = 0;
    for (int value : state) code = code * 9 + value;
    return code;
}

vector<int> decodeState(int code, int c) {
    vector<int> state(c);
    for (int i = c - 1; i >= 0; i--) {
        state[i] = code % 9;
        code /= 9;
    }
    return state;
}

int normalizeState(vector<int>& state) {
    map<int, int> idMap;
    int nextId = 1;
    for (int& value : state) {
        if (value == 0) continue;
        if (!idMap.count(value)) idMap[value] = nextId++;
        value = idMap[value];
    }
    return encodeState(state);
}

void mergeLabel(vector<int>& state, int oldLabel, int newLabel) {
    for (int& value : state)
        if (value == oldLabel) value = newLabel;
}

bool checkFixedEdges(int r, int c, const vector<vector<int>>& hor, const vector<vector<int>>& ver) {
    Dsu dsu(r * c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j + 1 < c; j++)
            if (hor[i][j] && !dsu.mergeSet(i * c + j, i * c + j + 1)) return false;
    for (int i = 0; i + 1 < r; i++)
        for (int j = 0; j < c; j++)
            if (ver[i][j] && !dsu.mergeSet(i * c + j, (i + 1) * c + j)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int r, c, md;
        cin >> r >> c >> md;
        string line;
        getline(cin, line);
        vector<string> maze(2 * r - 1);
        for (string& row : maze) getline(cin, row);
        vector<vector<int>> hor(r, vector<int>(max(0, c - 1)));
        vector<vector<int>> ver(max(0, r - 1), vector<int>(c));
        for (int i = 0; i < r; i++)
            for (int j = 0; j + 1 < c; j++)
                hor[i][j] = maze[2 * i][2 * j + 1] == '-';
        for (int i = 0; i + 1 < r; i++)
            for (int j = 0; j < c; j++)
                ver[i][j] = maze[2 * i + 1][2 * j] == '|';
        if (!checkFixedEdges(r, c, hor, ver)) {
            cout << "Impossible\n";
            continue;
        }
        unordered_map<int, long long> dp, nextDp;
        dp[0] = 1;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                nextDp.clear();
                for (const auto& item : dp) {
                    vector<int> base = decodeState(item.first, c);
                    long long ways = item.second;
                    int leftCount = 1, upCount = 1;
                    if (j > 0 && !hor[i][j - 1]) leftCount = 2;
                    if (i > 0 && !ver[i - 1][j]) upCount = 2;
                    for (int leftChoice = 0; leftChoice < leftCount; leftChoice++)
                        for (int upChoice = 0; upChoice < upCount; upChoice++) {
                            bool useLeft = j > 0 && (hor[i][j - 1] || leftChoice == 1);
                            bool useUp = i > 0 && (ver[i - 1][j] || upChoice == 1);
                            int leftLabel = j > 0 ? base[j - 1] : 0;
                            int upLabel = base[j];
                            if (useLeft && useUp && leftLabel == upLabel) continue;
                            vector<int> state = base;
                            int newLabel = 1;
                            for (int value : state) newLabel = max(newLabel, value + 1);
                            state[j] = newLabel;
                            if (useLeft) mergeLabel(state, leftLabel, newLabel);
                            if (useUp) mergeLabel(state, upLabel, newLabel);
                            bool upAlive = useUp;
                            for (int k = 0; k < c; k++) {
                                if (k != j && base[k] == upLabel) {
                                    upAlive = true;
                                    break;
                                }
                            }
                            if (upLabel != 0 && !upAlive) continue;
                            int newCode = normalizeState(state);
                            nextDp[newCode] = (nextDp[newCode] + ways) % md;
                        }
                }
                dp.swap(nextDp);
            }
        long long answer = 0;
        for (const auto& item : dp) {
            vector<int> state = decodeState(item.first, c);
            int label = 0;
            bool valid = true;
            for (int value : state)
                if (value != 0) {
                    if (label == 0) label = value;
                    else if (label != value) valid = false;
                }
            if (valid) answer = (answer + item.second) % md;
        }
        cout << answer << '\n';
    }
    return 0;
}
