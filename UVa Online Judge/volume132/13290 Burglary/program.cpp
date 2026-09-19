#include <bits/stdc++.h>
using namespace std;

struct PathInfo {
    int leftJar, rightJar, candySum, leftOpt, rightOpt;
};

PathInfo buildPath(int firstCol, int secondCol, const string& shelf, const vector<int>& jarCount, const vector<int>& jarSum) {
    int leftCol = min(firstCol, secondCol), rightCol = max(firstCol, secondCol), totalJar = static_cast<int>(jarSum.size()) - 1;
    PathInfo path;
    path.leftJar = jarCount[leftCol - 1] + 1;
    path.rightJar = jarCount[rightCol];
    path.candySum = jarSum[path.rightJar] - jarSum[path.leftJar - 1];
    path.leftOpt = 0;
    path.rightOpt = 0;
    if (shelf[leftCol - 1] == '-' && jarCount[leftCol] > 0) path.leftOpt = jarCount[leftCol];
    if (shelf[rightCol - 1] == '-' && jarCount[rightCol] < totalJar) path.rightOpt = jarCount[rightCol] + 1;
    return path;
}

int getSingleGain(const PathInfo& path, const vector<int>& jarSum) {
    int gain = path.candySum;
    if (path.leftOpt > 0) gain += jarSum[path.leftOpt] - jarSum[path.leftOpt - 1];
    if (path.rightOpt > 0) gain += jarSum[path.rightOpt] - jarSum[path.rightOpt - 1];
    return gain;
}

int getPairGain(const PathInfo& firstPath, const PathInfo& secondPath, const vector<int>& jarSum) {
    if (max(firstPath.leftJar, secondPath.leftJar) <= min(firstPath.rightJar, secondPath.rightJar)) return -1;
    int gain = firstPath.candySum + secondPath.candySum, opts[4] = {firstPath.leftOpt, firstPath.rightOpt, secondPath.leftOpt, secondPath.rightOpt};
    for (int i = 0; i < 4; ++i) {
        int jarId = opts[i];
        bool repeated = false;
        if (jarId == 0) continue;
        if (firstPath.leftJar <= jarId && jarId <= firstPath.rightJar) continue;
        if (secondPath.leftJar <= jarId && jarId <= secondPath.rightJar) continue;
        for (int j = 0; j < i; ++j) if (opts[j] == jarId) repeated = true;
        if (!repeated) gain += jarSum[jarId] - jarSum[jarId - 1];
    }
    return gain;
}

int solve(int n, int m, const vector<string>& shelves, const vector<vector<int>>& ladders) {
    int bottomCount = static_cast<int>(ladders[n - 1].size());
    vector<vector<int>> dp(bottomCount, vector<int>(bottomCount, 0));
    vector<int> topCols(1, 1);
    for (int row = n - 1; row >= 0; --row) {
        const vector<int>& upperCols = row == 0 ? topCols : ladders[row - 1];
        const vector<int>& lowerCols = ladders[row];
        int upperCount = static_cast<int>(upperCols.size()), lowerCount = static_cast<int>(lowerCols.size());
        vector<int> jarCount(m + 1, 0), jarSum(1, 0);
        for (int col = 1; col <= m; ++col) {
            jarCount[col] = jarCount[col - 1];
            if (shelves[row][col - 1] != '-') {
                ++jarCount[col];
                jarSum.push_back(jarSum.back() + shelves[row][col - 1] - '0');
            }
        }
        vector<vector<PathInfo>> paths(upperCount, vector<PathInfo>(lowerCount));
        for (int a = 0; a < upperCount; ++a) for (int c = 0; c < lowerCount; ++c) paths[a][c] = buildPath(upperCols[a], lowerCols[c], shelves[row], jarCount, jarSum);
        vector<vector<int>> curDp(upperCount, vector<int>(upperCount, 0));
        for (int a = 0; a < upperCount; ++a) {
            for (int b = 0; b < upperCount; ++b) {
                PathInfo stopPath = buildPath(upperCols[a], upperCols[b], shelves[row], jarCount, jarSum);
                curDp[a][b] = getSingleGain(stopPath, jarSum);
                for (int c = 0; c < lowerCount; ++c) {
                    for (int d = 0; d < lowerCount; ++d) {
                        int gain = getPairGain(paths[a][c], paths[b][d], jarSum);
                        if (gain >= 0) curDp[a][b] = max(curDp[a][b], dp[c][d] + gain);
                    }
                }
            }
        }
        dp.swap(curDp);
    }
    return dp[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<string> shelves(n);
        vector<vector<int>> ladders(n);
        string ladderLine;
        for (int row = 0; row < n; ++row) {
            cin >> shelves[row] >> ladderLine;
            for (int col = 0; col < m; ++col) if (ladderLine[col] == '|') ladders[row].push_back(col + 1);
        }
        cout << solve(n, m, shelves, ladders) << '\n';
    }
    return 0;
}
