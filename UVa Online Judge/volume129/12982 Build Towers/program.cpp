#include <bits/stdc++.h>
using namespace std;

const int maxSticks = 8, maxBlocks = 42, keySize = 50;
const int cacheLimit = 200000;
int stickCount, depthLimit;
int blockColor[169], blockLow[169], blockHigh[169];
int stickSize[maxSticks];
unsigned char sticks[maxSticks][maxBlocks];

struct StateKey {
    unsigned char data[keySize];
    bool operator==(const StateKey &other) const {
        return memcmp(data, other.data, keySize) == 0;
    }
};

struct KeyHash {
    size_t operator()(const StateKey &key) const {
        unsigned long long hashValue = 14695981039346656037ULL;
        for (int i = 0; i < keySize; ++i) {
            hashValue ^= key.data[i];
            hashValue *= 1099511628211ULL;
        }
        return hashValue;
    }
};

struct Move {
    int from, to, topId, baseId, mergedId, moveType;
};

struct DepGraph {
    unsigned long long edge[maxBlocks], fixedEdge[maxBlocks];
    int nodeCount, visit[maxBlocks], parent[maxBlocks];
    void removeEdge(int from, int to) {
        unsigned long long bit = 1ULL << to;
        if (!(fixedEdge[from] & bit)) edge[from] &= ~bit;
    }
    bool findCycle(int node) {
        visit[node] = 1;
        unsigned long long mask = edge[node];
        while (mask) {
            int next = __builtin_ctzll(mask);
            mask &= mask - 1;
            if (visit[next] == 0) {
                parent[next] = node;
                if (findCycle(next)) return true;
            } else if (visit[next] == 1) {
                removeEdge(node, next);
                int cur = node;
                while (cur != next) {
                    removeEdge(parent[cur], cur);
                    cur = parent[cur];
                }
                return true;
            }
        }
        visit[node] = 2;
        return false;
    }
    bool removeCycle() {
        fill(visit, visit + nodeCount, 0);
        for (int i = 0; i < nodeCount; ++i) {
            if (visit[i] == 0 && findCycle(i)) return true;
        }
        return false;
    }
};

unordered_map<StateKey, int, KeyHash> stateDepth;

int getId(int color, int low, int high) {
    return color * 28 + high * (high + 1) / 2 + low + 1;
}

void initBlocks() {
    for (int color = 0; color < 6; ++color) {
        for (int high = 0; high <= 6; ++high) {
            for (int low = 0; low <= high; ++low) {
                int id = getId(color, low, high);
                blockColor[id] = color;
                blockLow[id] = low;
                blockHigh[id] = high;
            }
        }
    }
}

bool lessStick(int left, int right) {
    int len = min(stickSize[left], stickSize[right]);
    for (int i = 0; i < len; ++i) {
        if (sticks[left][i] != sticks[right][i]) return sticks[left][i] < sticks[right][i];
    }
    return stickSize[left] < stickSize[right];
}

StateKey getState() {
    StateKey key = {};
    int order[maxSticks], pos = 0;
    for (int i = 0; i < stickCount; ++i) order[i] = i;
    sort(order, order + stickCount, lessStick);
    for (int i = 0; i < stickCount; ++i) {
        int col = order[i];
        for (int j = 0; j < stickSize[col]; ++j) key.data[pos++] = sticks[col][j];
        key.data[pos++] = 0;
    }
    return key;
}

int getExtraBound(int allowance) {
    DepGraph graph = {};
    int blockId[maxBlocks], above[maxBlocks], colId[maxBlocks], level[maxBlocks];
    int nodeAt[6][7], extra = 0;
    for (int col = 0; col < stickCount; ++col) {
        for (int pos = 0; pos < stickSize[col]; ++pos) {
            int node = graph.nodeCount++, id = sticks[col][pos];
            blockId[node] = id;
            colId[node] = col;
            level[node] = pos;
            above[node] = pos + 1 < stickSize[col] ? node + 1 : -1;
            nodeAt[blockColor[id]][blockLow[id]] = node;
            if (pos > 0) graph.fixedEdge[node] = 1ULL << (node - 1);
            graph.edge[node] = graph.fixedEdge[node];
        }
    }
    for (int node = 0; node < graph.nodeCount; ++node) {
        int id = blockId[node];
        if (blockHigh[id] == 6) continue;
        int target = nodeAt[blockColor[id]][blockHigh[id] + 1];
        if (above[target] == -1) continue;
        // 位于下一尺寸整体上方时，必然需要先临时搬走
        if (colId[node] == colId[target] && level[node] > level[target]) {
            ++extra;
            if (extra > allowance) return extra;
        } else graph.edge[above[target]] |= 1ULL << node;
    }
    // 每次计数后删除环中全部可取消边，避免重复计数
    while (graph.removeCycle()) {
        ++extra;
        if (extra > allowance) return extra;
    }
    return extra;
}

bool dfs(int used, int baseBound) {
    if (used + baseBound > depthLimit) return false;
    if (baseBound == 0) return true;
    int allowance = depthLimit - used - baseBound;
    if (getExtraBound(allowance) > allowance) return false;
    StateKey key = getState();
    auto it = stateDepth.find(key);
    if (it != stateDepth.end()) {
        if (it->second <= used) return false;
        it->second = used;
    } else if (stateDepth.size() < cacheLimit) stateDepth.emplace(key, used);
    int emptyPos = -1, moveCount = 0;
    Move moves[maxSticks * (maxSticks - 1)];
    for (int i = 0; i < stickCount; ++i) {
        if (stickSize[i] == 0) {
            emptyPos = i;
            break;
        }
    }
    for (int from = 0; from < stickCount; ++from) {
        if (stickSize[from] == 0) continue;
        int topId = sticks[from][stickSize[from] - 1];
        for (int to = 0; to < stickCount; ++to) {
            if (from == to) continue;
            int baseId = 0, mergedId = 0, moveType = 2;
            if (stickSize[to] == 0) {
                if (to != emptyPos || stickSize[from] == 1) continue;
                if (blockHigh[topId] == 6) moveType = 1;
            } else {
                baseId = sticks[to][stickSize[to] - 1];
                if (blockColor[topId] != blockColor[baseId]) continue;
                if (blockHigh[topId] >= blockLow[baseId]) continue;
                if (blockHigh[topId] + 1 == blockLow[baseId]) {
                    mergedId = getId(blockColor[topId], blockLow[topId], blockHigh[baseId]);
                    moveType = 0;
                }
            }
            if (moveType == 2 && allowance == 0) continue;
            moves[moveCount++] = {from, to, topId, baseId, mergedId, moveType};
        }
    }
    for (int moveType = 0; moveType < 3; ++moveType) {
        for (int i = 0; i < moveCount; ++i) {
            const Move &cur = moves[i];
            if (cur.moveType != moveType) continue;
            int from = cur.from, to = cur.to, decrease = moveType < 2 ? 1 : 0;
            --stickSize[from];
            if (cur.mergedId != 0) sticks[to][stickSize[to] - 1] = cur.mergedId;
            else sticks[to][stickSize[to]++] = cur.topId;
            bool found = dfs(used + 1, baseBound - decrease);
            if (cur.mergedId != 0) sticks[to][stickSize[to] - 1] = cur.baseId;
            else --stickSize[to];
            sticks[from][stickSize[from]++] = cur.topId;
            if (found) return true;
        }
    }
    return false;
}

int solve() {
    int blockCount = 0, fixedCount = 0, baseBound, extraBound;
    for (int col = 0; col < stickCount; ++col) {
        blockCount += stickSize[col];
        if (stickSize[col] > 0 && blockHigh[sticks[col][0]] == 6) ++fixedCount;
    }
    baseBound = blockCount - fixedCount;
    extraBound = getExtraBound(maxBlocks);
    for (depthLimit = baseBound + extraBound; ; ++depthLimit) {
        stateDepth.clear();
        if (dfs(0, baseBound)) return depthLimit;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initBlocks();
    stateDepth.max_load_factor(0.8f);
    stateDepth.reserve(cacheLimit);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        cin >> stickCount;
        int colorMap[256], colorCount = 0;
        fill(colorMap, colorMap + 256, -1);
        for (int col = 0; col < stickCount; ++col) {
            int plateCount;
            cin >> plateCount;
            stickSize[col] = 0;
            for (int pos = 0; pos < plateCount; ++pos) {
                string token;
                cin >> token;
                int ch = (unsigned char)token[0], low, high, id;
                size_t dashPos = token.find('-');
                if (colorMap[ch] == -1) colorMap[ch] = colorCount++;
                low = stoi(token.substr(1));
                high = low;
                if (dashPos != string::npos) high = stoi(token.substr(dashPos + 1));
                id = getId(colorMap[ch], low, high);
                if (stickSize[col] > 0) {
                    int baseId = sticks[col][stickSize[col] - 1];
                    if (blockColor[baseId] == colorMap[ch] && high + 1 == blockLow[baseId]) {
                        sticks[col][stickSize[col] - 1] = getId(colorMap[ch], low, blockHigh[baseId]);
                        continue;
                    }
                }
                sticks[col][stickSize[col]++] = id;
            }
        }
        int answer = solve();
        cout << "Case #" << caseId << ": " << answer << '\n';
    }
    return 0;
}
