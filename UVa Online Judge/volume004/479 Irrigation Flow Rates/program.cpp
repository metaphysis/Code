// Irrigation Flow Rates
// UVa ID: 479
// Verdict: Accepted
// Submission Date: 2026-06-27
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int type;           // 0: 井, 1: 阀门, 2: 喷头
    string name;
    int flowRate;       // 仅井有效
    int target;         // 仅井有效（固定目标）
    int leftTarget;     // 仅阀门有效
    int rightTarget;    // 仅阀门有效
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int networkNum = 1;
    int W, S, V;
    while (cin >> W >> S >> V) {
        if (W == 9999 && S == 9999 && V == 9999) break;

        vector<int> wellFlows(W);
        for (int i = 0; i < W; ++i) cin >> wellFlows[i];

        unordered_map<string, int> idOf;
        vector<Node> nodes;

        auto getNode = [&](const string& name) -> int {
            auto it = idOf.find(name);
            if (it != idOf.end()) return it->second;
            Node nd;
            nd.type = -1;
            nd.name = name;
            nd.flowRate = 0;
            nd.target = -1;
            nd.leftTarget = -1;
            nd.rightTarget = -1;
            int id = (int)nodes.size();
            nodes.push_back(nd);
            idOf[name] = id;
            return id;
        };

        vector<string> wellNames(W), wellTargets(W);
        for (int i = 0; i < W; ++i) {
            string wName, dest;
            cin >> wName >> dest;
            wellNames[i] = wName;
            wellTargets[i] = dest;
            int id = getNode(wName);
            nodes[id].type = 0;
            nodes[id].flowRate = wellFlows[i];
        }

        vector<string> sprNames(S);
        for (int i = 0; i < S; ++i) {
            string sName;
            cin >> sName;
            sprNames[i] = sName;
            int id = getNode(sName);
            nodes[id].type = 2;
        }

        vector<string> valveNames(V), leftDests(V), rightDests(V);
        for (int i = 0; i < V; ++i) {
            string vName, lDest, rDest;
            cin >> vName >> lDest >> rDest;
            valveNames[i] = vName;
            leftDests[i] = lDest;
            rightDests[i] = rDest;
            int id = getNode(vName);
            nodes[id].type = 1;
        }

        int n = (int)nodes.size();

        // 解析井的目标
        for (int i = 0; i < W; ++i) {
            int id = idOf[wellNames[i]];
            nodes[id].target = idOf[wellTargets[i]];
        }

        // 解析阀门的目标，并记录阀门顺序
        vector<int> valveIds;
        for (int i = 0; i < V; ++i) {
            int id = idOf[valveNames[i]];
            valveIds.push_back(id);
            nodes[id].leftTarget = idOf[leftDests[i]];
            nodes[id].rightTarget = idOf[rightDests[i]];
        }

        // 记录喷头顺序
        vector<int> sprinklerIds;
        for (int i = 0; i < S; ++i)
            sprinklerIds.push_back(idOf[sprNames[i]]);

        // 阀门 id 到其在 valveIds 中下标的映射
        vector<int> valveIdToIdx(n, -1);
        for (int idx = 0; idx < V; ++idx)
            valveIdToIdx[valveIds[idx]] = idx;

        cout << "Irrigation network #" << networkNum++ << '\n';

        int setNum = 1;
        while (true) {
            string setting = "";
            bool ended = false;
            // 读取一个完整的阀门设置（可能由多个 token 组成，也可能是一个连续串）
            while ((int)setting.size() < V) {
                string token;
                if (!(cin >> token)) { ended = true; break; }
                if (token == "*") { ended = true; break; }
                setting += token;
            }
            if (ended) break;

            // 构建当前设置下的有效出边
            vector<int> outEdge(n, -1);
            for (int i = 0; i < n; ++i) {
                if (nodes[i].type == 0) {          // 井
                    outEdge[i] = nodes[i].target;
                } else if (nodes[i].type == 1) {    // 阀门
                    int idx = valveIdToIdx[i];
                    char c = setting[idx];
                    outEdge[i] = (c == 'L') ? nodes[i].leftTarget : nodes[i].rightTarget;
                }
                // 喷头无出边
            }

            // 计算入度
            vector<int> inDeg(n, 0);
            for (int i = 0; i < n; ++i)
                if (outEdge[i] != -1)
                    ++inDeg[outEdge[i]];

            // 流量数组，井赋初值，其余为0
            vector<long long> flow(n, 0);
            for (int i = 0; i < n; ++i)
                if (nodes[i].type == 0)
                    flow[i] = nodes[i].flowRate;

            // 拓扑排序
            queue<int> q;
            for (int i = 0; i < n; ++i)
                if (inDeg[i] == 0) q.push(i);

            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (outEdge[u] != -1) {
                    int v = outEdge[u];
                    flow[v] += flow[u];
                    if (--inDeg[v] == 0) q.push(v);
                }
            }

            // 输出当前设置的结果
            cout << "Valve settings #" << setNum++ << '\n';
            for (int i = 0; i < S; ++i) {
                int id = sprinklerIds[i];
                cout << "Sprinkler #" << (i + 1) << " flow is " << flow[id] << " gallons/min\n";
            }
        }
    }
    return 0;
}
