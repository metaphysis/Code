#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long key;
    int left, right;
};

struct Query {
    long long row, col;
    int rows, cols;
};

bool isIntersect(long long leftA, long long rightA, long long topA, long long bottomA, long long leftB, long long rightB, long long topB, long long bottomB) {
    if (rightA < leftB || rightB < leftA) return false;
    if (bottomA < topB || bottomB < topA) return false;
    return true;
}

void solveCase(int caseNo) {
    int n;
    cin >> n;
    vector<Node> nodes(n);
    set<pair<long long, int>> keySet;
    for (int i = 0; i < n; i++) {
        cin >> nodes[i].key;
        nodes[i].left = -1;
        nodes[i].right = -1;
        if (i == 0) {
            keySet.insert({nodes[i].key, i});
            continue;
        }
        auto it = keySet.lower_bound({nodes[i].key, -1});
        bool hasLeft = it != keySet.begin();
        bool hasRight = it != keySet.end();
        int parent;
        if (!hasLeft) parent = it->second;
        else if (!hasRight) {
            parent = prev(it)->second;
        } else {
            int leftParent = prev(it)->second;
            int rightParent = it->second;
            parent = leftParent > rightParent ? leftParent : rightParent;
        }
        if (nodes[i].key < nodes[parent].key) nodes[parent].left = i;
        else nodes[parent].right = i;
        keySet.insert({nodes[i].key, i});
    }
    vector<long long> minX(n), maxX(n), leftShift(n), rightShift(n), posX(n);
    vector<int> height(n), posRow(n);
    for (int i = n - 1; i >= 0; i--) {
        minX[i] = 0;
        maxX[i] = 0;
        height[i] = 0;
        if (nodes[i].left != -1) {
            int child = nodes[i].left;
            leftShift[i] = -1 - maxX[child];
            minX[i] = min(minX[i], leftShift[i] + minX[child]);
            maxX[i] = max(maxX[i], leftShift[i] + maxX[child]);
            height[i] = max(height[i], height[child] + 1);
        }
        if (nodes[i].right != -1) {
            int child = nodes[i].right;
            rightShift[i] = 1 - minX[child];
            minX[i] = min(minX[i], rightShift[i] + minX[child]);
            maxX[i] = max(maxX[i], rightShift[i] + maxX[child]);
            height[i] = max(height[i], height[child] + 1);
        }
    }
    vector<int> nodeStack;
    posX[0] = 1 - minX[0];
    posRow[0] = 1;
    nodeStack.push_back(0);
    while (!nodeStack.empty()) {
        int u = nodeStack.back();
        nodeStack.pop_back();
        if (nodes[u].left != -1) {
            int child = nodes[u].left;
            posX[child] = posX[u] + leftShift[u];
            posRow[child] = posRow[u] + 2;
            nodeStack.push_back(child);
        }
        if (nodes[u].right != -1) {
            int child = nodes[u].right;
            posX[child] = posX[u] + rightShift[u];
            posRow[child] = posRow[u] + 2;
            nodeStack.push_back(child);
        }
    }
    int m;
    cin >> m;
    vector<Query> queries(m);
    for (int i = 0; i < m; i++) cin >> queries[i].row >> queries[i].col >> queries[i].rows >> queries[i].cols;
    cout << "Case #" << caseNo << ":\n";
    for (int queryIndex = 0; queryIndex < m; queryIndex++) {
        Query query = queries[queryIndex];
        vector<string> graph(query.rows, string(query.cols, ' '));
        long long queryLeft = query.col;
        long long queryRight = query.col + query.cols - 1;
        long long queryTop = query.row;
        long long queryBottom = query.row + query.rows - 1;
        vector<int> visitStack;
        visitStack.push_back(0);
        while (!visitStack.empty()) {
            int u = visitStack.back();
            visitStack.pop_back();
            long long treeLeft = posX[u] + minX[u];
            long long treeRight = posX[u] + maxX[u];
            long long treeTop = posRow[u];
            long long treeBottom = posRow[u] + 2LL * height[u];
            if (!isIntersect(treeLeft, treeRight, treeTop, treeBottom, queryLeft, queryRight, queryTop, queryBottom)) continue;
            long long nodeRow = posRow[u];
            long long nodeCol = posX[u];
            if (nodeRow >= queryTop && nodeRow <= queryBottom && nodeCol >= queryLeft && nodeCol <= queryRight) graph[nodeRow - queryTop][nodeCol - queryLeft] = 'o';
            if (nodes[u].left != -1) {
                int child = nodes[u].left;
                long long childCol = posX[child];
                if (nodeRow >= queryTop && nodeRow <= queryBottom && childCol >= queryLeft && childCol <= queryRight) graph[nodeRow - queryTop][childCol - queryLeft] = '+';
                long long lineRow = nodeRow + 1;
                if (lineRow >= queryTop && lineRow <= queryBottom && childCol >= queryLeft && childCol <= queryRight) graph[lineRow - queryTop][childCol - queryLeft] = '|';
                long long startCol = childCol + 1;
                long long endCol = nodeCol - 1;
                if (nodeRow >= queryTop && nodeRow <= queryBottom) {
                    for (long long col = startCol; col <= endCol; col++)
                        if (col >= queryLeft && col <= queryRight) graph[nodeRow - queryTop][col - queryLeft] = '-';
                }
                visitStack.push_back(child);
            }
            if (nodes[u].right != -1) {
                int child = nodes[u].right;
                long long childCol = posX[child];
                if (nodeRow >= queryTop && nodeRow <= queryBottom && childCol >= queryLeft && childCol <= queryRight) graph[nodeRow - queryTop][childCol - queryLeft] = '+';
                long long lineRow = nodeRow + 1;
                if (lineRow >= queryTop && lineRow <= queryBottom && childCol >= queryLeft && childCol <= queryRight) graph[lineRow - queryTop][childCol - queryLeft] = '|';
                long long startCol = nodeCol + 1;
                long long endCol = childCol - 1;
                if (nodeRow >= queryTop && nodeRow <= queryBottom) {
                    for (long long col = startCol; col <= endCol; col++)
                        if (col >= queryLeft && col <= queryRight) graph[nodeRow - queryTop][col - queryLeft] = '-';
                }
                visitStack.push_back(child);
            }
        }
        for (int i = 0; i < query.rows; i++)
            if (graph[i].find_first_not_of(' ') != string::npos) cout << graph[i] << '\n';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int caseNo = 1; caseNo <= testCases; caseNo++) solveCase(caseNo);
    return 0;
}
