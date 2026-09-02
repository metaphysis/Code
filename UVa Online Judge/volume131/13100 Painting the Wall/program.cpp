#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int fixed, begin, end;
};

int leftCount, rightCount;
vector<vector<int> > graph;
vector<int> matchLeft, matchRight, dist;

bool bfs() {
    queue<int> que;
    bool found = false;
    for (int i = 0; i < leftCount; i++) {
        if (matchLeft[i] == -1) {
            dist[i] = 0;
            que.push(i);
        } else
            dist[i] = -1;
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : graph[u]) {
            int next = matchRight[v];
            if (next == -1)
                found = true;
            else if (dist[next] == -1) {
                dist[next] = dist[u] + 1;
                que.push(next);
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int v : graph[u]) {
        int next = matchRight[v];
        if (next == -1 || (dist[next] == dist[u] + 1 && dfs(next))) {
            matchLeft[u] = v;
            matchRight[v] = u;
            return true;
        }
    }
    dist[u] = -1;
    return false;
}

int maxMatching() {
    int result = 0;
    while (bfs())
        for (int i = 0; i < leftCount; i++)
            if (matchLeft[i] == -1 && dfs(i))
                result++;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount, columnCount;
    while (cin >> rowCount >> columnCount) {
        vector<string> wall(rowCount);
        for (string &row : wall)
            cin >> row;
        vector<vector<int> > horizontalId(rowCount, vector<int>(columnCount, -1));
        vector<vector<int> > verticalId(rowCount, vector<int>(columnCount, -1));
        vector<Segment> horizontal, vertical;
        for (int i = 0; i < rowCount; i++) {
            int j = 0;
            while (j < columnCount) {
                if (wall[i][j] == '.') {
                    j++;
                    continue;
                }
                int begin = j;
                while (j < columnCount && wall[i][j] == '*')
                    j++;
                int id = (int)horizontal.size();
                horizontal.push_back({i, begin, j - 1});
                for (int k = begin; k < j; k++)
                    horizontalId[i][k] = id;
            }
        }
        for (int j = 0; j < columnCount; j++) {
            int i = 0;
            while (i < rowCount) {
                if (wall[i][j] == '.') {
                    i++;
                    continue;
                }
                int begin = i;
                while (i < rowCount && wall[i][j] == '*')
                    i++;
                int id = (int)vertical.size();
                vertical.push_back({j, begin, i - 1});
                for (int k = begin; k < i; k++)
                    verticalId[k][j] = id;
            }
        }
        leftCount = (int)horizontal.size();
        rightCount = (int)vertical.size();
        graph.assign(leftCount, vector<int>());
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < columnCount; j++)
                if (wall[i][j] == '*')
                    graph[horizontalId[i][j]].push_back(verticalId[i][j]);
        matchLeft.assign(leftCount, -1);
        matchRight.assign(rightCount, -1);
        dist.resize(leftCount);
        maxMatching();
        vector<char> visitLeft(leftCount, false), visitRight(rightCount, false);
        queue<int> que;
        for (int i = 0; i < leftCount; i++)
            if (matchLeft[i] == -1) {
                visitLeft[i] = true;
                que.push(i);
            }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v : graph[u])
                if (matchLeft[u] != v && !visitRight[v]) {
                    visitRight[v] = true;
                    int next = matchRight[v];
                    if (next != -1 && !visitLeft[next]) {
                        visitLeft[next] = true;
                        que.push(next);
                    }
                }
        }
        vector<int> answer;
        for (int i = 0; i < leftCount; i++)
            if (!visitLeft[i])
                answer.push_back(i);
        for (int j = 0; j < rightCount; j++)
            if (visitRight[j])
                answer.push_back(leftCount + j);
        cout << answer.size() << '\n';
        for (int id : answer) {
            if (id < leftCount) {
                Segment line = horizontal[id];
                cout << "hline " << line.fixed + 1 << ' ' << line.begin + 1 << ' ' << line.end + 1 << '\n';
            } else {
                Segment line = vertical[id - leftCount];
                cout << "vline " << line.fixed + 1 << ' ' << line.begin + 1 << ' ' << line.end + 1 << '\n';
            }
        }
    }
    return 0;
}
