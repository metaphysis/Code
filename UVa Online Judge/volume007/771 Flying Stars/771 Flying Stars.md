## 题目描述

给定若干机场以及每日循环的航班信息。每个机场有固定的时区偏移和登机 / 转机耗时。从起点机场的某个本地时刻出发，需要经过一系列航班抵达终点机场。要求计算从出发时刻到抵达终点时刻的总旅行时间（以天、小时、分钟表示），并输出抵达终点时的本地时间以及最优路径上各航班的标识符。

## 输入格式

每个测试用例由多行组成。第一行包含起点机场标识符、终点机场标识符和出发本地时间（格式 `hh:mm`）。第二行是一个整数 $N$（$2 \le N \le 100$），表示机场总数。接下来 $N$ 个机场的描述，每个描述以标题行开始：机场标识符、时区（格式 `shh:mm`，`+` 或 `-`）、登机耗时（格式 `hh:mm`）和一个整数 $M$（$M \le 300$），表示该机场的航班数。随后 $M$ 行，每行描述一个航班：航班标识符、目的地机场标识符、起飞本地时间（格式 `hh:mm`）和飞行时长（格式 `hh:mm`）。多个测试用例之间由空行分隔。

## 输出格式

对于每个测试用例，第一行输出总旅行时间，格式 `d:hh:mm`，其中 $d$ 为完整天数（不超过 $9$）。第二行输出抵达终点时的当地时间（格式 `hh:mm`）。随后每行输出最优路径上的一个航班标识符，顺序与乘坐顺序一致。相邻测试用例的输出之间用空行分隔。

## 样例

输入

```
Pulkovo JFK 11:15
3
Pulkovo +03:00 01:30 2
BA347 Heathrow 12:10 04:25
Z8805 Heathrow 18:25 04:30
Heathrow +00:00 00:45 3
BA160 JFK 09:20 08:10
BA346 Pulkovo 14:45 04:20
Z8804 Pulkovo 21:30 04:25
JFK -05:00 00:45 1
BA161 Heathrow 14:25 08:05
```

输出

```
1:09:15
12:30
Z8805
BA160
```

## 题目分析

本题要求从起点机场到终点机场的最快路径，其中速度由航班飞行时长决定，但路径选择受限于每日循环的航班时刻表以及各机场的转机等待时间。同时，机场分布在不同的时区，所有时间均为当地时间，因此需要统一到某个绝对时间轴上进行计算。

若以到达某个机场的绝对时刻作为状态，则在每个机场可以选择后续航班，其中航班能否乘坐取决于当地时间的起飞时刻是否晚于当前时刻加上该机场的登机耗时（即最早可登机时刻）。由于航班每日循环，若当天合适航班已过，则需要等待到次日同一时刻。

问题的难点在于：
- 时间的本地与绝对转换，以及时区差的处理。
- 航班时刻的循环性质使得等待时间需要模 $1440$ 分钟计算。
- 节点数最多 $100$，每个机场最多 $300$ 个航班，总边数 $3 \times 10^4$，可以使用最短路径算法。

## 解题思路

### 时间模型

设起点机场为 $S$，其时区偏移为 $\Delta_S$（分钟）。将起点出发的本地时间 $t_0$（分钟，范围 $0 \sim 1439$）作为绝对时间 $0$ 的基准。对于任意机场 $A$，其在绝对时间 $T$（分钟）对应的当地时间为：

$$
\textit{local}_A(T) = (t_0 + T + (\Delta_A - \Delta_S)) \bmod 1440
$$

其中结果规范到 $[0, 1439]$。反之，若已知某机场的当地时间为 $L$，则对应的绝对时间 $T$ 需满足 $T \equiv L - t_0 - (\Delta_A - \Delta_S) \pmod{1440}$。

### 状态表示与转移

用 `dist[u]` 表示到达机场 $u$ 的最早绝对时间（从起点出发时刻算起）。初始 `dist[S] = 0`。当从机场 $u$ 出发时，必须等待 `boarding[u]` 分钟才能登机，因此可登机的最早绝对时刻为 `ready = dist[u] + boarding[u]`。计算 `ready` 时刻 $u$ 的当地时间为：

$$
L = (t_0 + ready + (\Delta_u - \Delta_S)) \bmod 1440
$$

对于 $u$ 的每个航班 $f$（起飞当地时间 `dep`，飞行时长 `dur`），需找到最早的一次起飞（可能当天或之后数天）满足该次起飞当地时间为 `dep` 且不早于 `L`。等待时间 `wait = (dep - L) mod 1440`（结果非负），则起飞绝对时刻 `depAbs = ready + wait`，到达目的地 $v$ 的绝对时刻为 `depAbs + dur`。如果该值小于 `dist[v]`，则更新。

注意，由于飞行时长正数，且等待时间非负，图中边权非负，可使用 Dijkstra 算法。节点最多 $100$ 个，边数最多约 $3 \times 10^4$，优先队列 $\texttt{Moore-Dijkstra}$ 效率足够。

### 路径回溯

在更新 `dist[v]` 时，同时记录前驱节点 `prevNode[v]` 以及所使用的航班标识符 `prevFlight[v]`。当 $\texttt{Moore-Dijkstra}$ 结束，从终点逆向回溯，即可得到完整航班序列，再反转输出。

### 复杂度分析

设机场数为 $N$（$\le 100$），每个机场航班数最多 $M$（$\le 300$），总边数 $E \le 3\times 10^4$。$\texttt{Moore-Dijkstra}$ 使用优先队列，每次松弛操作 $O(\log N)$，总复杂度 $O(E \log N)$，远小于可接受范围。

## 代码实现

```cpp
// Flying Stars
// UVa ID: 771
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 解析 "hh:mm" 为分钟数
int parseTime(const string& s) {
    int h = stoi(s.substr(0, 2));
    int m = stoi(s.substr(3, 2));
    return h * 60 + m;
}

// 解析时区 "+hh:mm" 或 "-hh:mm" 为分钟偏移
int parseTimezone(const string& s) {
    int sign = (s[0] == '+') ? 1 : -1;
    int h = stoi(s.substr(1, 2));
    int m = stoi(s.substr(4, 2));
    return sign * (h * 60 + m);
}

// 将分钟数格式化为 "hh:mm"（0~1439）
string formatTime(int t) {
    t %= 1440;
    if (t < 0) t += 1440;
    char buf[6];
    sprintf(buf, "%02d:%02d", t / 60, t % 60);
    return string(buf);
}

// 将总分钟数格式化为 "d:hh:mm"
string formatDuration(int total) {
    int days = total / 1440;
    int rem = total % 1440;
    char buf[20];
    sprintf(buf, "%d:%02d:%02d", days, rem / 60, rem % 60);
    return string(buf);
}

struct Flight {
    string id;
    string dest;
    int dep;   // 本地起飞时间，分钟 (0~1439)
    int dur;   // 飞行时长，分钟
};

struct Airport {
    string id;
    int offset;    // 时区偏移，分钟
    int boarding;  // 登机/转机耗时，分钟
    vector<Flight> flights;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string srcId, dstId, startStr;
    bool firstCase = true;
    while (cin >> srcId >> dstId >> startStr) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        int N;
        cin >> N;
        unordered_map<string, int> idx;
        vector<Airport> airports(N);
        for (int i = 0; i < N; ++i) {
            string id, tz, boardStr;
            int M;
            cin >> id >> tz >> boardStr >> M;
            idx[id] = i;
            airports[i].id = id;
            airports[i].offset = parseTimezone(tz);
            airports[i].boarding = parseTime(boardStr);
            airports[i].flights.resize(M);
            for (int j = 0; j < M; ++j) {
                string fid, dest, depStr, durStr;
                cin >> fid >> dest >> depStr >> durStr;
                airports[i].flights[j].id = fid;
                airports[i].flights[j].dest = dest;
                airports[i].flights[j].dep = parseTime(depStr);
                airports[i].flights[j].dur = parseTime(durStr);
            }
        }
        int src = idx[srcId];
        int dst = idx[dstId];
        int startLocal = parseTime(startStr);
        int offsetSrc = airports[src].offset;
        const int INF = 1e9;
        vector<int> dist(N, INF);
        vector<int> prevNode(N, -1);
        vector<string> prevFlight(N, "");
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [curDist, u] = pq.top();
            pq.pop();
            if (curDist != dist[u]) continue;
            if (u == dst) break;
            int ready = curDist + airports[u].boarding; // 可登机绝对时间
            // 计算 ready 时刻该机场的本地时间
            int localReady = (startLocal + ready + (airports[u].offset - offsetSrc)) % 1440;
            if (localReady < 0) localReady += 1440;
            for (const Flight& f : airports[u].flights) {
                int wait = (f.dep - localReady) % 1440;
                if (wait < 0) wait += 1440;
                int depAbs = ready + wait;
                int arrAbs = depAbs + f.dur;
                int v = idx[f.dest];
                if (arrAbs < dist[v]) {
                    dist[v] = arrAbs;
                    prevNode[v] = u;
                    prevFlight[v] = f.id;
                    pq.push({arrAbs, v});
                }
            }
        }
        // 输出总旅行时间
        cout << formatDuration(dist[dst]) << '\n';
        // 输出到达目的地当地时间
        int arrivalLocal = (startLocal + dist[dst] + (airports[dst].offset - offsetSrc)) % 1440;
        if (arrivalLocal < 0) arrivalLocal += 1440;
        cout << formatTime(arrivalLocal) << '\n';
        // 回溯路径
        vector<string> route;
        int cur = dst;
        while (cur != src) {
            route.push_back(prevFlight[cur]);
            cur = prevNode[cur];
        }
        reverse(route.begin(), route.end());
        for (const string& fid : route) cout << fid << '\n';
    }
    return 0;
}
```

## 总结

本题将时区、航班周期和转机等待时间整合到一个绝对时间轴上，通过 $\texttt{Moore-Dijkstra}$ 算法求解最短路径。关键点在于将本地时间与绝对时间相互转换，以及正确处理航班时刻的循环等待。该解法能够处理最多 $100$ 个机场、$300$ 个航班的数据规模，时间复杂度 $O(E \log N)$，空间复杂度 $O(N + E)$，满足题目要求。在实际实现中，注意所有时间运算以分钟为单位，避免浮点误差，并严格处理模运算的负数情况。
