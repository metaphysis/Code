#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

struct FlowEdge {
    int to, rev, cap, cost;
};

void addFlowEdge(vector<vector<FlowEdge>> &graph, int from, int to, int cap, int cost) {
    FlowEdge first = {to, static_cast<int>(graph[to].size()), cap, cost};
    FlowEdge second = {from, static_cast<int>(graph[from].size()), 0, -cost};
    graph[from].push_back(first);
    graph[to].push_back(second);
}

int getMaxWeight(const vector<int> &children, const vector<int> &colors, const vector<vector<int>> &crossWeight, const vector<int> &singleWeight, int excluded) {
    int childCount = static_cast<int>(children.size()), leftReal = 0, rightReal = 0;
    vector<int> leftId(childCount, -1), rightId(childCount, -1);
    for (int i = 0; i < childCount; ++i) {
        if (i == excluded) continue;
        if (colors[children[i]] == 0) leftId[i] = leftReal++;
        else rightId[i] = rightReal++;
    }
    int leftCount = leftReal + rightReal, rightCount = rightReal + leftReal;
    int source = leftCount + rightCount, sink = source + 1, nodeCount = sink + 1;
    vector<vector<FlowEdge>> graph(nodeCount);
    for (int i = 0; i < leftCount; ++i) addFlowEdge(graph, source, i, 1, 0);
    for (int i = 0; i < rightCount; ++i) addFlowEdge(graph, leftCount + i, sink, 1, 0);
    for (int i = 0; i < childCount; ++i) {
        if (i == excluded) continue;
        if (colors[children[i]] == 0 && singleWeight[i] > 0) addFlowEdge(graph, leftId[i], leftCount + rightReal + leftId[i], 1, -singleWeight[i]);
        if (colors[children[i]] == 1 && singleWeight[i] > 0) addFlowEdge(graph, leftReal + rightId[i], leftCount + rightId[i], 1, -singleWeight[i]);
    }
    for (int i = 0; i < childCount; ++i) {
        if (i == excluded || colors[children[i]] != 0) continue;
        for (int j = 0; j < childCount; ++j) {
            if (j == excluded || colors[children[j]] != 1 || crossWeight[i][j] <= 0) continue;
            addFlowEdge(graph, leftId[i], leftCount + rightId[j], 1, -crossWeight[i][j]);
        }
    }
    int answer = 0;
    while (true) {
        vector<int> distance(nodeCount, inf), previousNode(nodeCount, -1), previousEdge(nodeCount, -1);
        vector<bool> inQueue(nodeCount, false);
        queue<int> que;
        distance[source] = 0;
        que.push(source);
        inQueue[source] = true;
        while (!que.empty()) {
            int node = que.front();
            que.pop();
            inQueue[node] = false;
            for (int i = 0; i < static_cast<int>(graph[node].size()); ++i) {
                FlowEdge &edge = graph[node][i];
                if (edge.cap == 0 || distance[edge.to] <= distance[node] + edge.cost) continue;
                distance[edge.to] = distance[node] + edge.cost;
                previousNode[edge.to] = node;
                previousEdge[edge.to] = i;
                if (!inQueue[edge.to]) {
                    inQueue[edge.to] = true;
                    que.push(edge.to);
                }
            }
        }
        if (distance[sink] >= 0 || distance[sink] == inf) break;
        answer -= distance[sink];
        int node = sink;
        while (node != source) {
            int from = previousNode[node], edgeId = previousEdge[node];
            FlowEdge &edge = graph[from][edgeId];
            --edge.cap;
            ++graph[node][edge.rev].cap;
            node = from;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, root;
    while (cin >> n >> k >> root && (n != 0 || k != 0 || root != 0)) {
        --root;
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; ++i) {
            int first, second;
            cin >> first >> second;
            --first;
            --second;
            tree[first].push_back(second);
            tree[second].push_back(first);
        }
        vector<int> parent(n, -1), depth(n, 0), order;
        vector<vector<int>> children(n);
        queue<int> que;
        que.push(root);
        parent[root] = root;
        while (!que.empty()) {
            int node = que.front();
            que.pop();
            order.push_back(node);
            for (int next : tree[node]) {
                if (next == parent[node]) continue;
                parent[next] = node;
                depth[next] = depth[node] + 1;
                children[node].push_back(next);
                que.push(next);
            }
        }
        vector<int> firstEnd(k), secondEnd(k), lca(k), firstChild(k, -1), secondChild(k, -1);
        vector<vector<int>> route(n, vector<int>(k, -2)), completed(n), colorGraph(n);
        int zeroCount = 0;
        for (int id = 0; id < k; ++id) {
            cin >> firstEnd[id] >> secondEnd[id];
            --firstEnd[id];
            --secondEnd[id];
            if (firstEnd[id] == secondEnd[id]) {
                ++zeroCount;
                lca[id] = firstEnd[id];
                continue;
            }
            int first = firstEnd[id], second = secondEnd[id];
            while (depth[first] > depth[second]) first = parent[first];
            while (depth[second] > depth[first]) second = parent[second];
            while (first != second) {
                first = parent[first];
                second = parent[second];
            }
            lca[id] = first;
            int node = firstEnd[id], previous = -1;
            while (node != lca[id]) {
                route[node][id] = previous;
                previous = node;
                node = parent[node];
            }
            firstChild[id] = previous;
            node = secondEnd[id];
            previous = -1;
            while (node != lca[id]) {
                route[node][id] = previous;
                previous = node;
                node = parent[node];
            }
            secondChild[id] = previous;
            completed[lca[id]].push_back(id);
            if (firstChild[id] != -1 && secondChild[id] != -1) {
                colorGraph[firstChild[id]].push_back(secondChild[id]);
                colorGraph[secondChild[id]].push_back(firstChild[id]);
            }
        }
        vector<int> colors(n, -1);
        for (int start = 0; start < n; ++start) {
            if (colors[start] != -1) continue;
            colors[start] = 0;
            que.push(start);
            while (!que.empty()) {
                int node = que.front();
                que.pop();
                for (int next : colorGraph[node]) {
                    if (colors[next] == -1) {
                        colors[next] = colors[node] ^ 1;
                        que.push(next);
                    }
                }
            }
        }
        vector<vector<int>> dp(n, vector<int>(k, -inf));
        vector<int> best(n, 0);
        reverse(order.begin(), order.end());
        for (int node : order) {
            int childCount = static_cast<int>(children[node].size()), base = 0;
            vector<int> childIndex(n, -1), singleWeight(childCount, 0);
            vector<vector<int>> crossWeight(childCount, vector<int>(childCount, 0));
            for (int i = 0; i < childCount; ++i) {
                childIndex[children[node][i]] = i;
                base += best[children[node][i]];
            }
            for (int id : completed[node]) {
                int first = firstChild[id], second = secondChild[id];
                if (first == -1 || second == -1) {
                    int child = first == -1 ? second : first;
                    int index = childIndex[child];
                    int weight = dp[child][id] - best[child] + 1;
                    singleWeight[index] = max(singleWeight[index], weight);
                } else {
                    int firstIndex = childIndex[first], secondIndex = childIndex[second];
                    int weight = dp[first][id] - best[first] + dp[second][id] - best[second] + 1;
                    if (colors[first] == 1) {
                        swap(first, second);
                        swap(firstIndex, secondIndex);
                    }
                    crossWeight[firstIndex][secondIndex] = max(crossWeight[firstIndex][secondIndex], weight);
                }
            }
            vector<int> matchWithout(childCount + 1, 0);
            matchWithout[childCount] = getMaxWeight(children[node], colors, crossWeight, singleWeight, -1);
            for (int i = 0; i < childCount; ++i) matchWithout[i] = getMaxWeight(children[node], colors, crossWeight, singleWeight, i);
            best[node] = base + matchWithout[childCount];
            for (int id = 0; id < k; ++id) {
                if (route[node][id] == -2) continue;
                int child = route[node][id];
                if (child == -1) {
                    dp[node][id] = best[node];
                } else {
                    int index = childIndex[child];
                    dp[node][id] = base + dp[child][id] - best[child] + matchWithout[index];
                }
            }
        }
        cout << best[root] + zeroCount << '\n';
    }
    return 0;
}
