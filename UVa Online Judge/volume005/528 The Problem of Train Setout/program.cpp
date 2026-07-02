// The Problem of Train Setout
// UVa ID: 528
// Verdict: Accepted
// Submission Date: 2026-06-27
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Arrival {
    int time;
    int type; // 0: 快车, 1: 普通车
};

struct Train {
    int type;
    int id;
    int arrive;
    int wait; // 截断后的等待时间
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Ae, Ao, Le, Lo, T;
    bool firstCase = true;

    while (cin >> Ae >> Ao >> Le >> Lo >> T) {
        if (Ae == 0 && Ao == 0 && Le == 0 && Lo == 0 && T == 0)
            break;

        if (!firstCase) cout << "\n";
        firstCase = false;

        // ---------- 生成到达事件 ----------
        vector<Arrival> arrivals;
        int t = 0;
        while (t <= T) {
            arrivals.push_back({t, 0});
            if (Ae == 0) break;
            t += Ae;
        }
        t = Ao;
        while (t <= T) {
            arrivals.push_back({t, 1});
            if (Ao == 0) break;
            t += Ao;
        }

        sort(arrivals.begin(), arrivals.end(), [](const Arrival& a, const Arrival& b) {
            if (a.time != b.time) return a.time < b.time;
            return a.type < b.type; // 同时间快车优先（编号顺序）
        });

        // ---------- 模拟 ----------
        vector<Train> trains;
        queue<int> eq, oq;
        int waitE = 0, waitO = 0;
        int lastE = -1, lastO = -1;
        vector<tuple<int,int,int>> triplets;

        auto record = [&](int curTime) {
            if (waitE != lastE || waitO != lastO) {
                triplets.push_back({curTime, waitE, waitO});
                lastE = waitE;
                lastO = waitO;
            }
        };

        // 强制记录初始状态 (0,0,0)
        triplets.push_back({0, 0, 0});
        lastE = 0;
        lastO = 0;

        bool busy = false;
        int finishTime = 0;
        int idx = 0;
        int cur = 0;
        int eid = 0, oid = 0;
        vector<int> waitEList, waitOList;

        while (idx < (int)arrivals.size() || busy || !eq.empty() || !oq.empty()) {
            int nextArrival = (idx < (int)arrivals.size()) ? arrivals[idx].time : INT_MAX;
            int nextFinish = busy ? finishTime : INT_MAX;
            int nextTime = min(nextArrival, nextFinish);
            if (nextTime == INT_MAX) break;

            cur = nextTime;

            // 1. 处理完成事件
            if (busy && finishTime == cur) {
                busy = false;
            }

            // 2. 处理所有到达事件
            while (idx < (int)arrivals.size() && arrivals[idx].time == cur) {
                int type = arrivals[idx].type;
                Train tr;
                tr.type = type;
                tr.id = (type == 0) ? ++eid : ++oid;
                tr.arrive = cur;
                tr.wait = -1;
                trains.push_back(tr);
                int tidx = (int)trains.size() - 1;

                if (type == 0) {
                    eq.push(tidx);
                    ++waitE;
                } else {
                    oq.push(tidx);
                    ++waitO;
                }
                ++idx;
            }

            // 3. 尝试开始新服务
            if (!busy) {
                if (!eq.empty()) {
                    int tidx = eq.front(); eq.pop();
                    --waitE;
                    Train& tr = trains[tidx];
                    int actualWait = cur - tr.arrive;
                    tr.wait = min(actualWait, T - tr.arrive); // 截断到T
                    waitEList.push_back(tr.wait);

                    busy = true;
                    finishTime = cur + Le;
                } else if (!oq.empty()) {
                    int tidx = oq.front(); oq.pop();
                    --waitO;
                    Train& tr = trains[tidx];
                    int actualWait = cur - tr.arrive;
                    tr.wait = min(actualWait, T - tr.arrive);
                    waitOList.push_back(tr.wait);

                    busy = true;
                    finishTime = cur + Lo;
                }
            }

            // 4. 记录状态（仅当 cur <= T）
            if (cur <= T) record(cur);
        }

        // ---------- 输出第一部分 ----------
        for (auto& tp : triplets)
            cout << get<0>(tp) << " " << get<1>(tp) << " " << get<2>(tp) << "\n";
        cout << "0\n";

        // ---------- 计算平均值（整数除法） ----------
        int We = 0, Wo = 0, Wt = 0;
        int cntE = (int)waitEList.size();
        int cntO = (int)waitOList.size();

        if (cntE > 0) {
            long long sumE = 0;
            for (int w : waitEList) sumE += w;
            We = (int)(sumE / cntE);
        }
        if (cntO > 0) {
            long long sumO = 0;
            for (int w : waitOList) sumO += w;
            Wo = (int)(sumO / cntO);
        }
        if (cntE + cntO > 0) {
            long long sumAll = 0;
            for (int w : waitEList) sumAll += w;
            for (int w : waitOList) sumAll += w;
            Wt = (int)(sumAll / (cntE + cntO));
        }

        cout << We << " " << Wo << " " << Wt << "\n";
        cout << "0\n";

        // ---------- 输出第三部分 ----------
        for (auto& tr : trains) {
            if (tr.type == 0 && tr.wait >= 0)
                cout << "E" << tr.id << " " << tr.wait << "\n";
        }
        for (auto& tr : trains) {
            if (tr.type == 1 && tr.wait >= 0)
                cout << "O" << tr.id << " " << tr.wait << "\n";
        }
        // 第三部分末尾不输出 0
    }

    return 0;
}
