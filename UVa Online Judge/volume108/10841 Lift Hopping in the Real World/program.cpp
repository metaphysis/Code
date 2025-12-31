// Lift Hopping in the Real World
// UVa ID: 10841
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX_F = 100;
const int MAX_N = 50;

int n, k;
int T[MAX_N];
vector<int> stops[MAX_N];
bool reachable[MAX_F][MAX_N];
int firstWait[MAX_N][MAX_F];  // 电梯e第一次在楼层f被呼叫的最坏等待时间

// 预处理：计算每部电梯在每个楼层的首次等待时间
void precomputeFirstWait() {
    for (int e = 0; e < n; e++) {
        for (int f = 0; f < MAX_F; f++) {
            int maxWait = 0;
            for (int s : stops[e]) {
                maxWait = max(maxWait, abs(f - s) * T[e]);
            }
            firstWait[e][f] = maxWait;
        }
    }
}

struct State {
    int floor;
    int elev;       // 当前使用的电梯，-1表示无电梯
    long long mask; // 已使用过的电梯集合
    int time;
    State(int f, int e, long long m, int t) : floor(f), elev(e), mask(m), time(t) {}
    bool operator>(const State& other) const {
        return time > other.time;  // 小顶堆
    }
};

void solve() {
    // 目标楼层就是0层
    if (k == 0) {
        cout << 0 << endl;
        return;
    }
    
    // 检查是否有电梯停靠0层
    bool hasElevatorAt0 = false;
    for (int e = 0; e < n; e++) {
        if (reachable[0][e]) {
            hasElevatorAt0 = true;
            break;
        }
    }
    if (!hasElevatorAt0) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    
    precomputeFirstWait();
    
    // dist[floor][elev+2][mask] 使用unordered_map减少内存
    // elev索引：-1 -> n+1, 其他 -> elev
    vector<vector<unordered_map<long long, int>>> dist(
        MAX_F, vector<unordered_map<long long, int>>(n + 2));
    priority_queue<State, vector<State>, greater<State>> pq;
    
    // 初始状态：在0层，无电梯
    dist[0][n + 1][0] = 0;  // n+1表示无电梯（对应elev=-1）
    pq.push(State(0, -1, 0, 0));
    
    int answer = INF;
    
    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
        int curFloor = cur.floor;
        int curElev = cur.elev;
        long long curMask = cur.mask;
        int curTime = cur.time;
        
        // 剪枝：如果当前时间已经超过已知最优解
        if (curTime >= answer) continue;
        
        // 验证当前状态是否最优
        int elevIdx = (curElev == -1) ? n + 1 : curElev;
        auto& distMap = dist[curFloor][elevIdx];
        auto it = distMap.find(curMask);
        if (it != distMap.end() && curTime > it->second) continue;
        
        // 到达目标楼层，更新答案
        if (curFloor == k) {
            answer = curTime;
            continue;
        }
        
        if (curElev == -1) {
            // 情况1：无电梯，可以呼叫停靠当前楼层的新电梯
            for (int e = 0; e < n; e++) {
                if (reachable[curFloor][e] && !((curMask >> e) & 1)) {
                    long long newMask = curMask | (1LL << e);
                    int waitTime = firstWait[e][curFloor];
                    int newTime = curTime + waitTime;  // 第一次呼叫，没有换乘时间
                    
                    auto& newDistMap = dist[curFloor][e];
                    if (newDistMap.find(newMask) == newDistMap.end() || newTime < newDistMap[newMask]) {
                        newDistMap[newMask] = newTime;
                        pq.push(State(curFloor, e, newMask, newTime));
                    }
                }
            }
        } else {
            // 情况2：有电梯，可以在电梯内移动
            for (int nextFloor : stops[curElev]) {
                if (nextFloor == curFloor) continue;
                
                int moveTime = abs(nextFloor - curFloor) * T[curElev];
                int newTime = curTime + moveTime;
                
                auto& newDistMap = dist[nextFloor][curElev];
                if (newDistMap.find(curMask) == newDistMap.end() || newTime < newDistMap[curMask]) {
                    newDistMap[curMask] = newTime;
                    pq.push(State(nextFloor, curElev, curMask, newTime));
                }
            }
            
            // 情况3：有电梯，可以换乘到新电梯
            for (int e = 0; e < n; e++) {
                if (e != curElev && reachable[curFloor][e] && !((curMask >> e) & 1)) {
                    long long newMask = curMask | (1LL << e);
                    int waitTime = firstWait[e][curFloor];
                    int newTime = curTime + 5 + waitTime;  // 5秒换乘时间
                    
                    auto& newDistMap = dist[curFloor][e];
                    if (newDistMap.find(newMask) == newDistMap.end() || newTime < newDistMap[newMask]) {
                        newDistMap[newMask] = newTime;
                        pq.push(State(curFloor, e, newMask, newTime));
                    }
                }
            }
        }
    }
    
    if (answer == INF) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << answer << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        if (!(ss >> n >> k)) break;
        
        // 读取电梯运行时间
        getline(cin, line);
        stringstream ss2(line);
        for (int i = 0; i < n; i++) ss2 >> T[i];
        
        // 初始化
        memset(reachable, 0, sizeof reachable);
        for (int i = 0; i < n; i++) stops[i].clear();
        
        // 读取电梯停靠楼层
        for (int i = 0; i < n; i++) {
            getline(cin, line);
            stringstream ss3(line);
            int floor;
            while (ss3 >> floor) {
                stops[i].push_back(floor);
                reachable[floor][i] = true;
            }
        }
        
        solve();
    }
    
    return 0;
}
