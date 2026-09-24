#include <bits/stdc++.h>
using namespace std;

struct BandwidthSolver {
    int n, limit;
    vector<int> graphMask, twinMask, curOrder, foundOrder;
    vector<vector<int>> graphDist, ballMask;
    unordered_set<string> failedStates;

    BandwidthSolver(const vector<int> &graph) : n(graph.size()), limit(0), graphMask(graph) {
        twinMask.assign(n, 0);
        graphDist.assign(n, vector<int>(n, n));
        ballMask.assign(n, vector<int>(n, 0));
        for (int s = 0; s < n; ++s) {
            vector<int> que(1, s);
            graphDist[s][s] = 0;
            for (int head = 0; head < (int)que.size(); ++head) {
                int u = que[head], restMask = graphMask[u];
                while (restMask) {
                    int v = __builtin_ctz(restMask);
                    restMask &= restMask - 1;
                    if (graphDist[s][v] != n) continue;
                    graphDist[s][v] = graphDist[s][u] + 1;
                    que.push_back(v);
                }
            }
        }
        for (int v = 0; v < n; ++v) for (int u = 0; u < n; ++u) for (int r = graphDist[v][u]; r < n; ++r) ballMask[v][r] |= 1 << u;
        for (int v = 0; v < n; ++v) for (int u = 0; u < n; ++u) {
            if (v == u) continue;
            if ((graphMask[v] & ~(1 << u)) == (graphMask[u] & ~(1 << v))) twinMask[v] |= 1 << u;
        }
    }

    int getWidth(const vector<int> &order) {
        vector<int> pos(n);
        int width = 0;
        for (int i = 0; i < n; ++i) pos[order[i]] = i;
        for (int u = 0; u < n; ++u) {
            int restMask = graphMask[u];
            while (restMask) {
                int v = __builtin_ctz(restMask);
                restMask &= restMask - 1;
                width = max(width, abs(pos[u] - pos[v]));
            }
        }
        return width;
    }

    bool dfs(int remainMask, array<int, 25> latest) {
        if (!remainMask) {
            foundOrder = curOrder;
            return true;
        }
        int remainCount = __builtin_popcount(remainMask), pos = n - remainCount, freeMask, triedMask = 0;
        array<int, 25> low = {}, baseLow = {}, baseHigh = {};
        vector<int> candidates;
        // 根据剩余邻域大小计算位置区间
        for (int bits = remainMask; bits; bits &= bits - 1) {
            int v = __builtin_ctz(bits), shift = 0;
            for (int r = 1; r < n && r * limit < remainCount - 1; ++r) {
                int count = __builtin_popcount(ballMask[v][r] & remainMask);
                shift = max(shift, count - 1 - r * limit);
            }
            baseLow[v] = pos + shift;
            baseHigh[v] = min(latest[v], n - 1 - shift);
            if (baseLow[v] > baseHigh[v]) return false;
        }
        // 利用最短路关系进一步收紧位置区间
        for (int bits = remainMask; bits; bits &= bits - 1) {
            int v = __builtin_ctz(bits);
            low[v] = baseLow[v];
            latest[v] = baseHigh[v];
            for (int otherBits = remainMask; otherBits; otherBits &= otherBits - 1) {
                int u = __builtin_ctz(otherBits), gap = limit * graphDist[u][v];
                low[v] = max(low[v], baseLow[u] - gap);
                latest[v] = min(latest[v], baseHigh[u] + gap);
            }
            if (low[v] > latest[v]) return false;
            if (low[v] == pos) candidates.push_back(v);
        }
        // 检查所有位置区间能否进行一一匹配
        freeMask = remainMask;
        for (int slot = pos; slot < n; ++slot) {
            int chosen = -1;
            for (int bits = freeMask; bits; bits &= bits - 1) {
                int v = __builtin_ctz(bits);
                if (low[v] > slot) continue;
                if (chosen == -1 || latest[v] < latest[chosen]) chosen = v;
            }
            if (chosen == -1 || latest[chosen] < slot) return false;
            freeMask ^= 1 << chosen;
        }
        string state(n, '\0');
        for (int bits = remainMask; bits; bits &= bits - 1) {
            int v = __builtin_ctz(bits);
            state[v] = char(latest[v] + 1);
        }
        if (failedStates.count(state)) return false;
        sort(candidates.begin(), candidates.end(), [&](int u, int v) {
            int degreeU = __builtin_popcount(graphMask[u] & remainMask), degreeV = __builtin_popcount(graphMask[v] & remainMask);
            if (latest[u] != latest[v]) return latest[u] < latest[v];
            return degreeU != degreeV ? degreeU > degreeV : u < v;
        });
        for (int v : candidates) {
            if (twinMask[v] & triedMask) continue;
            triedMask |= 1 << v;
            int nextMask = remainMask ^ (1 << v);
            array<int, 25> nextLatest = latest;
            for (int bits = nextMask; bits; bits &= bits - 1) {
                int u = __builtin_ctz(bits);
                nextLatest[u] = min(nextLatest[u], pos + limit * graphDist[v][u]);
            }
            curOrder.push_back(v);
            if (dfs(nextMask, nextLatest)) return true;
            curOrder.pop_back();
        }
        if (failedStates.size() < 100000) failedStates.insert(state);
        return false;
    }

    bool check(int width) {
        array<int, 25> latest;
        limit = width;
        latest.fill(n - 1);
        curOrder.clear();
        foundOrder.clear();
        failedStates.clear();
        return dfs((1 << n) - 1, latest);
    }

    pair<int, vector<int>> solve() {
        if (n == 1) return make_pair(0, vector<int>(1, 0));
        int upper, lower = 0, endLower = n - 1, remainMask = (1 << n) - 1;
        vector<int> bestOrder(n);
        iota(bestOrder.begin(), bestOrder.end(), 0);
        upper = getWidth(bestOrder);
        // 使用多起点广度优先遍历构造初始上界
        for (int s = 0; s < n; ++s) {
            int seenMask = 1 << s, width;
            vector<int> order(1, s);
            for (int head = 0; head < (int)order.size(); ++head) {
                int restMask = graphMask[order[head]] & ~seenMask;
                vector<int> nextVertices;
                while (restMask) {
                    int v = __builtin_ctz(restMask);
                    restMask &= restMask - 1;
                    nextVertices.push_back(v);
                }
                sort(nextVertices.begin(), nextVertices.end(), [&](int u, int v) {
                    int degreeU = __builtin_popcount(graphMask[u]), degreeV = __builtin_popcount(graphMask[v]);
                    return degreeU != degreeV ? degreeU < degreeV : u < v;
                });
                for (int v : nextVertices) {
                    seenMask |= 1 << v;
                    order.push_back(v);
                }
            }
            width = getWidth(order);
            if (width < upper) {
                upper = width;
                bestOrder = order;
            }
        }
        // 通过交换两个位置进一步降低上界
        bool improved = true;
        while (improved) {
            improved = false;
            for (int i = 0; i < n && !improved; ++i) for (int j = i + 1; j < n; ++j) {
                int width;
                swap(bestOrder[i], bestOrder[j]);
                width = getWidth(bestOrder);
                if (width < upper) {
                    upper = width;
                    improved = true;
                    break;
                }
                swap(bestOrder[i], bestOrder[j]);
            }
        }
        // 邻域必须容纳在中心两侧，首个顶点的邻域只能位于右侧
        for (int v = 0; v < n; ++v) {
            int need = 0;
            for (int r = 1; r < n; ++r) {
                int count = __builtin_popcount(ballMask[v][r]) - 1;
                need = max(need, (count + r - 1) / r);
                lower = max(lower, (count + 2 * r - 1) / (2 * r));
            }
            endLower = min(endLower, need);
        }
        lower = max(lower, endLower);
        // 任意子图的最小度数都是答案的下界
        while (remainMask) {
            int chosen = -1, minDegree = n;
            for (int bits = remainMask; bits; bits &= bits - 1) {
                int v = __builtin_ctz(bits), degree = __builtin_popcount(graphMask[v] & remainMask);
                if (degree < minDegree) {
                    minDegree = degree;
                    chosen = v;
                }
            }
            lower = max(lower, minDegree);
            remainMask ^= 1 << chosen;
        }
        while (lower < upper) {
            int mid = (lower + upper) / 2;
            if (check(mid)) {
                upper = mid;
                bestOrder = foundOrder;
            } else lower = mid + 1;
        }
        return make_pair(upper, bestOrder);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    string line;
    cin >> testCount;
    for (int caseId = 0; caseId < testCount; ++caseId) {
        int n, unusedMask, resultWidth = 0;
        cin >> n;
        getline(cin, line);
        vector<int> imageId(n), graphMask(n, 0), resultOrder;
        vector<vector<int>> neighborId(n);
        map<int, int> idIndex;
        for (int i = 0; i < n; ++i) {
            int nextId;
            getline(cin, line);
            istringstream input(line);
            input >> imageId[i];
            idIndex[imageId[i]] = i;
            while (input >> nextId) neighborId[i].push_back(nextId);
        }
        for (int i = 0; i < n; ++i) for (int nextId : neighborId[i]) {
            int j = idIndex[nextId];
            if (i != j) {
                graphMask[i] |= 1 << j;
                graphMask[j] |= 1 << i;
            }
        }
        unusedMask = (1 << n) - 1;
        while (unusedMask) {
            int start = __builtin_ctz(unusedMask), componentSize;
            vector<int> component(1, start), localGraph;
            unusedMask ^= 1 << start;
            for (int head = 0; head < (int)component.size(); ++head) {
                int restMask = graphMask[component[head]] & unusedMask;
                while (restMask) {
                    int v = __builtin_ctz(restMask);
                    restMask &= restMask - 1;
                    unusedMask ^= 1 << v;
                    component.push_back(v);
                }
            }
            componentSize = component.size();
            localGraph.assign(componentSize, 0);
            for (int i = 0; i < componentSize; ++i) for (int j = 0; j < componentSize; ++j) if (graphMask[component[i]] & (1 << component[j])) localGraph[i] |= 1 << j;
            BandwidthSolver solver(localGraph);
            pair<int, vector<int>> result = solver.solve();
            resultWidth = max(resultWidth, result.first);
            for (int v : result.second) resultOrder.push_back(imageId[component[v]]);
        }
        if (caseId) cout << '\n';
        cout << resultWidth << '\n';
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << resultOrder[i];
        }
        cout << '\n';
    }
    return 0;
}
