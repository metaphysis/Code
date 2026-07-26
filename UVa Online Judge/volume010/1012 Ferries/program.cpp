// Ferries
// UVa ID: 1012
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163183054

#include <bits/stdc++.h>
using namespace std;

struct Section {
    string type;
    int length;          // for road
    int duration;        // for ferry
    vector<int> deps;    // ferry departure minutes
};

int main() {
    int s;
    int caseNum = 0;
    while (cin >> s && s != 0) {
        ++caseNum;
        vector<Section> sections(s);
        for (int i = 0; i < s; ++i) {
            string from, to, typ;
            cin >> from >> to >> typ;
            sections[i].type = typ;
            if (typ == "road") {
                cin >> sections[i].length;
            } else {
                int f;
                cin >> sections[i].duration >> f;
                sections[i].deps.resize(f);
                for (int j = 0; j < f; ++j)
                    cin >> sections[i].deps[j];
            }
        }

        // 全速模拟，获得最小总时间 T_min 以及每个 ferry 的乘坐班次信息
        double cur = 0.0;
        vector<int> ferryIdx;     // ferry 在 sections 中的下标
        vector<double> ferryT;    // 全速模拟中该 ferry 的发船时刻（绝对分钟）
        vector<int> ferryD;       // 该 ferry 的持续时间
        for (int i = 0; i < s; ++i) {
            if (sections[i].type == "road") {
                cur += sections[i].length * 60.0 / 80.0;
            } else {
                // 计算下一个发船时刻
                double nextDep = 1e100;
                for (int dep : sections[i].deps) {
                    double k = ceil((cur - dep) / 60.0);
                    if (k < 0) k = 0;
                    double cand = dep + 60.0 * k;
                    if (cand < nextDep) nextDep = cand;
                }
                cur = nextDep + sections[i].duration;
                ferryIdx.push_back(i);
                ferryT.push_back(nextDep);
                ferryD.push_back(sections[i].duration);
            }
        }
        double T_min = cur;
        int K = (int)ferryT.size();   // ferry 数量

        // 计算每组 road 的总长度：roadGroupLen[i] 表示第 i 个 ferry 之前（或之后）的 road 长度
        // 索引 0  -> 第一个 ferry 之前的 road
        // 索引 1  -> 第一个 ferry 与第二个 ferry 之间的 road
        // ...
        // 索引 K  -> 最后一个 ferry 之后的 road
        vector<double> roadGroupLen(K + 1, 0.0);
        int fcnt = 0;
        double sumLen = 0.0;
        for (int i = 0; i < s; ++i) {
            if (sections[i].type == "road") {
                sumLen += sections[i].length;
            } else {
                roadGroupLen[fcnt] = sumLen;
                sumLen = 0.0;
                ++fcnt;
            }
        }
        roadGroupLen[K] = sumLen;

        double ansV;
        if (K == 0) {
            // 没有 ferry，全部是 road，必须全速
            ansV = (roadGroupLen[0] > 0 ? 80.0 : 0.0);
        } else if (roadGroupLen[K] > 0) {
            // 最后一个部分是 road，必须全速
            ansV = 80.0;
        } else {
            // 最后一段是 ferry，计算各段所需速度，取最大值
            ansV = 0.0;
            // 第一段
            double t0 = ferryT[0];
            if (t0 > 0 && roadGroupLen[0] > 0)
                ansV = max(ansV, 60.0 * roadGroupLen[0] / t0);
            // 中间段
            for (int i = 1; i < K; ++i) {
                double t = ferryT[i] - (ferryT[i-1] + ferryD[i-1]);
                if (t > 0 && roadGroupLen[i] > 0)
                    ansV = max(ansV, 60.0 * roadGroupLen[i] / t);
            }
            // 注意：最后一个轮渡后无公路（因为 roadGroupLen[K]==0），无需处理
        }

        // 输出
        cout << "Test Case " << caseNum << ": ";
        int totalSec = (int)round(T_min * 60.0);
        int hh = totalSec / 3600;
        int mm = (totalSec % 3600) / 60;
        int ss = totalSec % 60;
        cout << setw(2) << setfill('0') << hh << ":"
             << setw(2) << setfill('0') << mm << ":"
             << setw(2) << setfill('0') << ss << " ";
        cout << fixed << setprecision(2) << ansV << endl;
        cout << endl;   // 空行
    }
    return 0;
}
