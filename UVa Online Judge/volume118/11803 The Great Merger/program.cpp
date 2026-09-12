#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> treeA, treeB, memo;

int getDp(int u, int v);

int matchTree(const vector<int> &leftSon, const vector<int> &rightSon) {
    int leftSize = leftSon.size(), rightSize = rightSon.size(), size = max(leftSize, rightSize);
    if (size == 0) return 0;
    vector<vector<int>> weight(size + 1, vector<int>(size + 1, 0));
    int maxWeight = 0;
    for (int i = 1; i <= leftSize; i++)
        for (int j = 1; j <= rightSize; j++) {
            weight[i][j] = getDp(leftSon[i - 1], rightSon[j - 1]);
            maxWeight = max(maxWeight, weight[i][j]);
        }
    vector<int> potentialRow(size + 1, 0), potentialCol(size + 1, 0), matchCol(size + 1, 0), pre(size + 1, 0);
    for (int i = 1; i <= size; i++) {
        matchCol[0] = i;
        int currentCol = 0;
        vector<int> dis(size + 1, INT_MAX), used(size + 1, 0);
        do {
            used[currentCol] = 1;
            int currentRow = matchCol[currentCol], delta = INT_MAX, nextCol = 0;
            for (int j = 1; j <= size; j++)
                if (!used[j]) {
                    int cost = maxWeight - weight[currentRow][j];
                    int value = cost - potentialRow[currentRow] - potentialCol[j];
                    if (value < dis[j]) {
                        dis[j] = value;
                        pre[j] = currentCol;
                    }
                    if (dis[j] < delta) {
                        delta = dis[j];
                        nextCol = j;
                    }
                }
            for (int j = 0; j <= size; j++)
                if (used[j]) {
                    potentialRow[matchCol[j]] += delta;
                    potentialCol[j] -= delta;
                } else if (j > 0) dis[j] -= delta;
            currentCol = nextCol;
        } while (matchCol[currentCol] != 0);
        do {
            int lastCol = pre[currentCol];
            matchCol[currentCol] = matchCol[lastCol];
            currentCol = lastCol;
        } while (currentCol != 0);
    }
    int result = 0;
    for (int j = 1; j <= size; j++)
        if (matchCol[j] <= leftSize && j <= rightSize)
            result += weight[matchCol[j]][j];
    return result;
}

int getDp(int u, int v) {
    if (memo[u][v] != -1) return memo[u][v];
    memo[u][v] = 1 + matchTree(treeA[u], treeB[v]);
    return memo[u][v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNum = 1; caseNum <= testCount; caseNum++) {
        int n, parent;
        cin >> n;
        treeA.assign(n + 1, vector<int>());
        for (int i = 1; i <= n; i++) {
            cin >> parent;
            treeA[parent].push_back(i);
        }
        int m;
        cin >> m;
        treeB.assign(m + 1, vector<int>());
        for (int i = 1; i <= m; i++) {
            cin >> parent;
            treeB[parent].push_back(i);
        }
        memo.assign(n + 1, vector<int>(m + 1, -1));
        int common = getDp(0, 0);
        int answer = n + m + 2 - 2 * common;
        cout << "Case " << caseNum << ": " << answer << '\n';
    }
    return 0;
}
