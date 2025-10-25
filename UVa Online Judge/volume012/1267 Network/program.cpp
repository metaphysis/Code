// Network
// UVa ID: 1267
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 1005;

vector<int> treeGraph[MAX_NODES];
bool isServerNode[MAX_NODES];
bool hasVodService[MAX_NODES];
bool isClientCovered[MAX_NODES];
int parentNode[MAX_NODES];
int distanceFromSource[MAX_NODES];
int nodeCount, sourceServer, maxDistance;

// 从源服务器出发计算到所有节点的距离
void calculateDistancesFromSource() {
    queue<int> bfsQueue;
    memset(distanceFromSource, -1, sizeof(distanceFromSource));
    distanceFromSource[sourceServer] = 0;
    bfsQueue.push(sourceServer);
    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front();
        bfsQueue.pop();
        for (int neighbor : treeGraph[currentNode]) {
            if (distanceFromSource[neighbor] == -1) {
                distanceFromSource[neighbor] = distanceFromSource[currentNode] + 1;
                bfsQueue.push(neighbor);
            }
        }
    }
}

// 从指定节点向上跳 k 步找到放置副本的服务器位置
int findReplicaPosition(int startNode) {
    int current = startNode;
    for (int step = 0; step < maxDistance; step++) {
        if (parentNode[current] != -1) {
            current = parentNode[current];
        }
    }
    return current;
}

// 从服务器位置出发覆盖距离内的所有客户端
void coverClientsFromServer(int serverPos) {
    queue<pair<int, int>> bfsQueue;
    bool visited[MAX_NODES] = {false};
    bfsQueue.push({serverPos, 0});
    visited[serverPos] = true;
    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front().first;
        int currentDist = bfsQueue.front().second;
        bfsQueue.pop();
        if (!isServerNode[currentNode]) {
            isClientCovered[currentNode] = true;
        }
        if (currentDist < maxDistance) {
            for (int neighbor : treeGraph[currentNode]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    bfsQueue.push({neighbor, currentDist + 1});
                }
            }
        }
    }
}

// DFS 建立父节点关系
void buildParentTree(int currentNode, int parent) {
    parentNode[currentNode] = parent;
    for (int child : treeGraph[currentNode]) {
        if (child != parent) {
            buildParentTree(child, currentNode);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testCases;
    cin >> testCases;
    while (testCases--) {
        cin >> nodeCount;
        for (int i = 1; i <= nodeCount; i++) {
            treeGraph[i].clear();
            isServerNode[i] = false;
        }
        cin >> sourceServer >> maxDistance;

        // 读取树结构
        for (int i = 0; i < nodeCount - 1; i++) {
            int nodeA, nodeB;
            cin >> nodeA >> nodeB;
            treeGraph[nodeA].push_back(nodeB);
            treeGraph[nodeB].push_back(nodeA);
        }

        // 确定服务器节点（内部节点为服务器，叶子节点为客户端）
        for (int i = 1; i <= nodeCount; i++) {
            isServerNode[i] = (treeGraph[i].size() > 1);
        }
        // 确保源服务器被标记为服务器
        isServerNode[sourceServer] = true;

        // 建立父节点关系
        buildParentTree(sourceServer, -1);

        // 计算距离
        calculateDistancesFromSource();

        // 找出所有客户端节点
        vector<int> clientNodes;
        for (int i = 1; i <= nodeCount; i++) {
            if (!isServerNode[i]) {
                clientNodes.push_back(i);
            }
        }

        // 初始化覆盖状态
        memset(isClientCovered, false, sizeof(isClientCovered));
        coverClientsFromServer(sourceServer);

        // 收集未覆盖的客户端
        vector<int> uncoveredClients;
        for (int client : clientNodes) {
            if (!isClientCovered[client]) {
                uncoveredClients.push_back(client);
            }
        }

        // 按距离降序排序，优先处理最远的客户端
        sort(uncoveredClients.begin(), uncoveredClients.end(), [&](int a, int b) {
            return distanceFromSource[a] > distanceFromSource[b];
        });

        // 初始化 VOD 服务状态
        memset(hasVodService, false, sizeof(hasVodService));
        hasVodService[sourceServer] = true;

        int replicaCount = 0;
        for (int client : uncoveredClients) {
            if (!isClientCovered[client]) {
                int serverPos = findReplicaPosition(client);
                if (!hasVodService[serverPos]) {
                    hasVodService[serverPos] = true;
                    replicaCount++;
                    coverClientsFromServer(serverPos);
                }
            }
        }

        cout << replicaCount << "\n";
    }

    return 0;
}
