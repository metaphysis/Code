#include <bits/stdc++.h>
using namespace std;

string solveCase(int rows, int cols, int need) {
    int cellCount = rows * cols, startPos = -1, targetPos = -1;
    int dr[] = {0, -1, 1, 0}, dc[] = {1, 0, 0, -1};
    char moveDir[] = "ENSW";
    vector<string> grid(rows);
    vector<int> waterPos, waterAt(cellCount, -1);
    for (int i = 0; i < rows; ++i) {
        cin >> grid[i];
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'S') startPos = i * cols + j;
            else if (grid[i][j] == 'T') targetPos = i * cols + j;
        }
    }
    waterPos.push_back(startPos);
    waterPos.push_back(targetPos);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] >= 'A' && grid[i][j] <= 'K') waterPos.push_back(i * cols + j);
        }
    }
    int nodeCount = waterPos.size(), checkCount = nodeCount - 2;
    vector<int> nodeBit(nodeCount, 0);
    vector<vector<int>> edgeDist(nodeCount, vector<int>(nodeCount, -1)), edgeOrder(nodeCount);
    vector<vector<string>> edgePath(nodeCount, vector<string>(nodeCount));
    for (int i = 0; i < nodeCount; ++i) waterAt[waterPos[i]] = i;
    for (int i = 2; i < nodeCount; ++i) nodeBit[i] = 1 << (i - 2);
    for (int src = 0; src < nodeCount; ++src) {
        vector<int> cellDist(cellCount, -1), parent(cellCount, -1), parentDir(cellCount, -1);
        queue<int> bfs;
        int srcPos = waterPos[src];
        cellDist[srcPos] = 0;
        bfs.push(srcPos);
        while (!bfs.empty()) {
            int cur = bfs.front(), curRow = cur / cols, curCol = cur % cols;
            bfs.pop();
            if (cur != srcPos && waterAt[cur] != -1) continue;
            for (int d = 0; d < 4; ++d) {
                int nextRow = curRow + dr[d], nextCol = curCol + dc[d];
                if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols) continue;
                int nextPos = nextRow * cols + nextCol;
                if (grid[nextRow][nextCol] == '~' || cellDist[nextPos] != -1) continue;
                cellDist[nextPos] = cellDist[cur] + 1;
                parent[nextPos] = cur;
                parentDir[nextPos] = d;
                bfs.push(nextPos);
            }
        }
        for (int dst = 0; dst < nodeCount; ++dst) {
            if (dst == src || cellDist[waterPos[dst]] == -1) continue;
            edgeDist[src][dst] = cellDist[waterPos[dst]];
            string path;
            for (int pos = waterPos[dst]; pos != srcPos; pos = parent[pos]) path.push_back(moveDir[parentDir[pos]]);
            reverse(path.begin(), path.end());
            edgePath[src][dst] = path;
        }
    }
    auto canReach = [&](int limit) -> bool {
        vector<int> seen(nodeCount, 0);
        queue<int> bfs;
        int reached = 0;
        seen[0] = 1;
        bfs.push(0);
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();
            if (cur >= 2) ++reached;
            for (int next = 0; next < nodeCount; ++next) {
                if (seen[next] || edgeDist[cur][next] == -1 || edgeDist[cur][next] > limit) continue;
                seen[next] = 1;
                bfs.push(next);
            }
        }
        return seen[1] && reached >= need;
    };
    int low = 0, high = cellCount;
    while (low < high) {
        int mid = (low + high) / 2;
        if (canReach(mid)) high = mid;
        else low = mid + 1;
    }
    int limit = low, maskCount = 1 << checkCount, inf = 1000000000;
    for (int src = 0; src < nodeCount; ++src) {
        for (int dst = 0; dst < nodeCount; ++dst) {
            if (edgeDist[src][dst] != -1 && edgeDist[src][dst] <= limit) edgeOrder[src].push_back(dst);
        }
        sort(edgeOrder[src].begin(), edgeOrder[src].end(), [&](int a, int b) {
            return edgePath[src][a] < edgePath[src][b];
        });
    }
    vector<int> best(maskCount * nodeCount, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int mask = 0; mask < maskCount; ++mask) {
        if (__builtin_popcount(static_cast<unsigned int>(mask)) < need) continue;
        int state = mask * nodeCount + 1;
        best[state] = 0;
        pq.push(make_pair(0, state));
    }
    auto relax = [&](int mask, int node, int newDist) {
        if ((mask & nodeBit[node]) != nodeBit[node]) return;
        int state = mask * nodeCount + node;
        if (newDist >= best[state]) return;
        best[state] = newDist;
        pq.push(make_pair(newDist, state));
    };
    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        int curDist = cur.first, state = cur.second;
        if (curDist != best[state]) continue;
        int mask = state / nodeCount, node = state % nodeCount;
        for (int prev : edgeOrder[node]) {
            int newDist = curDist + edgeDist[node][prev];
            relax(mask, prev, newDist);
            if (nodeBit[node] != 0) relax(mask ^ nodeBit[node], prev, newDist);
        }
    }
    string answer;
    int mask = 0, node = 0;
    while (node != 1 || __builtin_popcount(static_cast<unsigned int>(mask)) < need) {
        for (int next : edgeOrder[node]) {
            int nextMask = mask | nodeBit[next];
            if (best[mask * nodeCount + node] != edgeDist[node][next] + best[nextMask * nodeCount + next]) continue;
            answer += edgePath[node][next];
            mask = nextMask;
            node = next;
            break;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, cols, need;
    while (cin >> rows >> cols >> need) cout << solveCase(rows, cols, need) << '\n';
    return 0;
}
