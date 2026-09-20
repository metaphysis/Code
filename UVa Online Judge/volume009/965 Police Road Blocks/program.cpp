#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class FastInput {
private:
    static const int bufferSize = 1 << 20;
    char buffer[bufferSize];
    int index, size;
public:
    FastInput() : index(0), size(0) {}
    char readChar() {
        if (index >= size) {
            size = fread(buffer, 1, bufferSize, stdin);
            index = 0;
            if (size == 0) return 0;
        }
        return buffer[index++];
    }
    template <typename T>
    bool readInt(T &value) {
        char ch;
        T sign = 1;
        value = 0;
        do {
            ch = readChar();
            if (!ch) return false;
        } while (ch <= ' ');
        if (ch == '-') {
            sign = -1;
            ch = readChar();
        }
        while (ch >= '0' && ch <= '9') {
            value = value * 10 + ch - '0';
            ch = readChar();
        }
        value *= sign;
        return true;
    }
};

class Dinic {
private:
    struct Edge {
        ll cap;
        int to, next;
    };
    int nodeCount;
    vector<int> head, level, current;
    vector<Edge> edges;
    bool buildLevelGraph(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> nodeQueue;
        level[source] = 0;
        nodeQueue.push(source);
        while (!nodeQueue.empty()) {
            int node = nodeQueue.front();
            nodeQueue.pop();
            for (int edgeId = head[node]; edgeId != -1; edgeId = edges[edgeId].next) {
                int nextNode = edges[edgeId].to;
                if (edges[edgeId].cap > 0 && level[nextNode] == -1) {
                    level[nextNode] = level[node] + 1;
                    nodeQueue.push(nextNode);
                }
            }
        }
        return level[sink] != -1;
    }
    ll findBlockingFlow(int source, int sink) {
        ll totalFlow = 0;
        vector<int> nodePath, edgePath;
        nodePath.reserve(nodeCount);
        edgePath.reserve(nodeCount);
        nodePath.push_back(source);
        while (!nodePath.empty()) {
            int node = nodePath.back();
            if (node == sink) {
                ll addFlow = numeric_limits<ll>::max();
                int cutPosition = -1;
                for (int edgeId : edgePath) addFlow = min(addFlow, edges[edgeId].cap);
                for (int edgeId : edgePath) {
                    edges[edgeId].cap -= addFlow;
                    edges[edgeId ^ 1].cap += addFlow;
                }
                totalFlow += addFlow;
                for (int i = 0; i < static_cast<int>(edgePath.size()); ++i) {
                    if (edges[edgePath[i]].cap == 0) {
                        cutPosition = i;
                        break;
                    }
                }
                nodePath.resize(cutPosition + 1);
                edgePath.resize(cutPosition);
                continue;
            }
            int &edgeId = current[node];
            while (edgeId != -1 && (edges[edgeId].cap == 0 || level[edges[edgeId].to] != level[node] + 1)) edgeId = edges[edgeId].next;
            if (edgeId == -1) {
                level[node] = -1;
                nodePath.pop_back();
                if (!edgePath.empty()) {
                    int parent = nodePath.back();
                    current[parent] = edges[current[parent]].next;
                    edgePath.pop_back();
                }
            } else {
                edgePath.push_back(edgeId);
                nodePath.push_back(edges[edgeId].to);
            }
        }
        return totalFlow;
    }
public:
    Dinic(int count, size_t edgeCapacity) : nodeCount(count), head(count, -1), level(count), current(count) {
        edges.reserve(edgeCapacity);
    }
    void addDirectedEdge(int from, int to, ll cap) {
        edges.push_back({cap, to, head[from]});
        head[from] = static_cast<int>(edges.size()) - 1;
        edges.push_back({0, from, head[to]});
        head[to] = static_cast<int>(edges.size()) - 1;
    }
    void addUndirectedEdge(int from, int to, ll cap) {
        edges.push_back({cap, to, head[from]});
        head[from] = static_cast<int>(edges.size()) - 1;
        edges.push_back({cap, from, head[to]});
        head[to] = static_cast<int>(edges.size()) - 1;
    }
    ll maxFlow(int source, int sink) {
        ll result = 0;
        while (buildLevelGraph(source, sink)) {
            current = head;
            ll blockingFlow = findBlockingFlow(source, sink);
            if (blockingFlow == 0) break;
            result += blockingFlow;
        }
        return result;
    }
};

int main() {
    FastInput input;
    int locationCount, roadCount;
    input.readInt(locationCount);
    input.readInt(roadCount);
    int source = locationCount + 1, sink = locationCount + 2;
    size_t edgeCapacity = static_cast<size_t>(roadCount) * 2 + static_cast<size_t>(locationCount) * 2;
    Dinic dinic(locationCount + 3, edgeCapacity);
    ll totalCost = 0;
    for (int i = 0; i < roadCount; ++i) {
        int from, to;
        ll cost;
        input.readInt(from);
        input.readInt(to);
        input.readInt(cost);
        dinic.addUndirectedEdge(from, to, cost);
        totalCost += cost;
    }
    int suspectCount;
    input.readInt(suspectCount);
    vector<int> suspects(suspectCount);
    for (int i = 0; i < suspectCount; ++i) input.readInt(suspects[i]);
    int borderCount;
    input.readInt(borderCount);
    vector<int> borders(borderCount);
    for (int i = 0; i < borderCount; ++i) input.readInt(borders[i]);
    ll infiniteCap = totalCost + 1;
    for (int location : suspects) dinic.addDirectedEdge(source, location, infiniteCap);
    for (int location : borders) dinic.addDirectedEdge(location, sink, infiniteCap);
    printf("%lld\n", dinic.maxFlow(source, sink));
    return 0;
}
