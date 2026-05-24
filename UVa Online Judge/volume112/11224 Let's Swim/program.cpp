// Let's Swim
// UVa ID: 11224
// Verdict: Accepted
// Submission Date: 2026-05-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Swimmer {
    int rank, time;
};

bool cmpByTime(const Swimmer &a, const Swimmer &b) {
    if (a.time != b.time) return a.time < b.time;
    return a.rank < b.rank;
}

int getLane(int qualPos) {
    int lane[9] = {0, 4, 5, 3, 6, 2, 7, 1, 8};
    return lane[qualPos];
}

int laneGoodness(int lane) {
    int goodness[9] = {0, 7, 5, 3, 1, 2, 4, 6, 8};
    return goodness[lane];
}

int finalPosition(int gRank, int gQualPos, vector<Swimmer> &finalists) {
    int gLane = getLane(gQualPos);
    int beat = 0;
    for (int i = 0; i < 8; i++) {
        if (finalists[i].rank == gRank) continue;
        int oLane = getLane(i + 1);
        if (laneGoodness(gLane) < laneGoodness(oLane)) {
            beat++;
        } else if (laneGoodness(gLane) > laneGoodness(oLane) && gRank < finalists[i].rank) {
            beat++;
        }
    }
    return finalists.size() - beat;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        int N;
        scanf("%d", &N);
        int gRank;
        scanf("%d", &gRank);
        vector<Swimmer> opp;
        for (int i = 0; i < N - 1; i++) {
            int r;
            char t[10];
            scanf("%d %s", &r, t);
            int mm, ss, dd;
            sscanf(t, "%02d:%02d:%02d", &mm, &ss, &dd);
            int time = mm * 6000 + ss * 100 + dd;
            opp.push_back({r, time});
        }
        sort(opp.begin(), opp.end(), cmpByTime);
        vector<Swimmer> top(opp.begin(), opp.begin() + min(N - 1, 8));
        
        // 收集关键时间点
        set<int> keyTimes;
        for (int i = 0; i < top.size(); i++) {
            keyTimes.insert(top[i].time);
            keyTimes.insert(top[i].time + 1);
            if (top[i].time > 0) keyTimes.insert(top[i].time - 1);
        }
        vector<int> times(keyTimes.rbegin(), keyTimes.rend());  // 降序（从慢到快）
        
        int bestQual = -1, bestFinal = -1;
        for (int gTime : times) {
            if (gTime < 0) continue;
            vector<Swimmer> all = top;
            all.push_back({gRank, gTime});
            sort(all.begin(), all.end(), cmpByTime);
            
            int gPos = -1;
            for (int i = 0; i < all.size(); i++) {
                if (all[i].rank == gRank && all[i].time == gTime) {
                    gPos = i + 1;
                    break;
                }
            }
            if (gPos > 8) continue;
            
            vector<Swimmer> finalists;
            for (int i = 0; i < 8; i++) finalists.push_back(all[i]);
            int fPos = finalPosition(gRank, gPos, finalists);
            if (fPos <= 3) {
                bestQual = gPos;
                bestFinal = fPos;
                break;
            }
        }
        printf("Case #%d:\n", cas);
        printf("Gustavo should be #%d during the qualification to achieve position #%d in the final.\n", bestQual, bestFinal);
    }
    return 0;
}
