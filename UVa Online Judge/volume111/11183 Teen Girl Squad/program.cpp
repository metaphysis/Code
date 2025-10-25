// Teen Girl Squad
// UVa ID: 11183
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_NODE = 1005;

struct PhoneCall {
    int caller;  // 呼叫者
    int receiver; // 接收者  
    int cost;    // 呼叫费用
};

int parentNode[MAX_NODE];    // 记录每个节点的前驱节点
int nodeId[MAX_NODE];        // 节点在新图中的编号
int visited[MAX_NODE];       // 访问标记数组
int minIncomingCost[MAX_NODE]; // 每个节点的最小入边费用

/**
 * 朱-刘算法求解有向图最小树形图
 * @param rootNode 根节点编号
 * @param nodeCount 节点总数
 * @param callRecords 电话呼叫记录列表
 * @return 最小总费用，无解返回-1
 */
int findMinCallCost(int rootNode, int nodeCount, vector<PhoneCall>& callRecords) {
    int totalCost = 0;
    int callCount = callRecords.size();
    
    while (true) {
        // 步骤1：为每个节点寻找最小入边
        fill(minIncomingCost, minIncomingCost + nodeCount, INF);
        for (int i = 0; i < callCount; i++) {
            int caller = callRecords[i].caller;
            int receiver = callRecords[i].receiver;
            if (caller != receiver && callRecords[i].cost < minIncomingCost[receiver]) {
                parentNode[receiver] = caller;
                minIncomingCost[receiver] = callRecords[i].cost;
            }
        }
        
        // 检查非根节点是否都有入边
        for (int i = 0; i < nodeCount; i++) {
            if (i != rootNode && minIncomingCost[i] == INF) {
                return -1; // 存在节点不可达，无解
            }
        }
        
        // 步骤2：检测环
        int newIdCount = 0;
        fill(nodeId, nodeId + nodeCount, -1);
        fill(visited, visited + nodeCount, -1);
        minIncomingCost[rootNode] = 0; // 根节点无入边
        
        for (int i = 0; i < nodeCount; i++) {
            totalCost += minIncomingCost[i];
            int currentNode = i;
            // 沿着前驱链寻找环
            while (visited[currentNode] != i && nodeId[currentNode] == -1 && currentNode != rootNode) {
                visited[currentNode] = i;
                currentNode = parentNode[currentNode];
            }
            // 找到新环，进行标记
            if (currentNode != rootNode && nodeId[currentNode] == -1) {
                for (int node = parentNode[currentNode]; node != currentNode; node = parentNode[node]) {
                    nodeId[node] = newIdCount;
                }
                nodeId[currentNode] = newIdCount++;
            }
        }
        
        if (newIdCount == 0) break; // 无环，算法结束
        
        // 为不在环中的节点分配新编号
        for (int i = 0; i < nodeCount; i++) {
            if (nodeId[i] == -1) {
                nodeId[i] = newIdCount++;
            }
        }
        
        // 步骤3：缩环，更新边权
        for (int i = 0; i < callCount; i++) {
            int originalCaller = callRecords[i].caller;
            int originalReceiver = callRecords[i].receiver;
            callRecords[i].caller = nodeId[originalCaller];
            callRecords[i].receiver = nodeId[originalReceiver];
            if (callRecords[i].caller != callRecords[i].receiver) {
                callRecords[i].cost -= minIncomingCost[originalReceiver];
            }
        }
        
        nodeCount = newIdCount;
        rootNode = nodeId[rootNode];
    }
    
    return totalCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int testCaseCount;
    cin >> testCaseCount;
    
    for (int caseIndex = 1; caseIndex <= testCaseCount; caseIndex++) {
        int girlCount, callCount;
        cin >> girlCount >> callCount;
        vector<PhoneCall> callRecords(callCount);
        
        for (int i = 0; i < callCount; i++) {
            cin >> callRecords[i].caller >> callRecords[i].receiver >> callRecords[i].cost;
        }
        
        int minCost = findMinCallCost(0, girlCount, callRecords);
        
        cout << "Case #" << caseIndex << ": ";
        if (minCost == -1) {
            cout << "Possums!\n";
        } else {
            cout << minCost << "\n";
        }
    }
    
    return 0;
}
