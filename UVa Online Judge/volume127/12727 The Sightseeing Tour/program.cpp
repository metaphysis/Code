// The Sightseeing Tour
// UVa ID: 12727
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.050s


#include <bits/stdc++.h>
using namespace std;

struct Bin {
    int A, B, C;
    uint64_t mask;
};
int T, N, M, K;
vector<Bin> bins;
uint64_t fullMask;
bool feasible[301];
vector<uint64_t> suffixOr;

void dfs(int idx, uint64_t mask, uint64_t coverMask, int cost) {
    if (coverMask == fullMask) {
        bool isMinimal = true;
        uint64_t temp = mask;
        while (temp) {
            int i = __builtin_ctzll(temp);
            temp &= temp - 1;
            uint64_t tmpCover = 0;
            uint64_t m = mask;
            while (m) {
                int j = __builtin_ctzll(m);
                m &= m - 1;
                if (j != i) tmpCover |= bins[j].mask;
            }
            if (tmpCover == fullMask) {
                isMinimal = false;
                break;
            }
        }
        if (isMinimal && cost <= 300) feasible[cost] = true;
        return;
    }
    if (idx == M) return;
    if ((coverMask | suffixOr[idx]) != fullMask) return;
    dfs(idx + 1, mask, coverMask, cost);
    uint64_t newCover = coverMask | bins[idx].mask;
    if (newCover != coverMask)
        dfs(idx + 1, mask | (1ULL << idx), newCover, cost + bins[idx].C);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        cin >> N >> M >> K;
        bins.resize(M);
        vector<int> pts;
        pts.push_back(1);
        pts.push_back(N + 1);
        for (int i = 0; i < M; ++i) {
            cin >> bins[i].A >> bins[i].B >> bins[i].C;
            pts.push_back(bins[i].A);
            pts.push_back(bins[i].B + 1);
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        int segCnt = (int)pts.size() - 1;
        fullMask = (segCnt == 64 ? ~0ULL : ((1ULL << segCnt) - 1));
        for (int i = 0; i < M; ++i) {
            int l = lower_bound(pts.begin(), pts.end(), bins[i].A) - pts.begin();
            int r = lower_bound(pts.begin(), pts.end(), bins[i].B + 1) - pts.begin();
            bins[i].mask = ((1ULL << (r - l)) - 1) << l;
        }
        sort(bins.begin(), bins.end(), [](const Bin& x, const Bin& y) {
            if (x.A != y.A) return x.A < y.A;
            return x.B < y.B;
        });
        suffixOr.assign(M + 1, 0);
        for (int i = M - 1; i >= 0; --i)
            suffixOr[i] = suffixOr[i + 1] | bins[i].mask;
        memset(feasible, 0, sizeof(feasible));
        dfs(0, 0, 0, 0);
        vector<int> fea;
        for (int i = 0; i <= 300; ++i)
            if (feasible[i]) fea.push_back(i);
        long long total = 0;
        if (!fea.empty()) {
            vector<long long> segL, segR, segVal;
            long long cur = 1;
            if (cur <= fea[0] - 1) {
                segL.push_back(cur);
                segR.push_back(fea[0] - 1);
                segVal.push_back(0);
                cur = fea[0];
            }
            for (size_t i = 0; i < fea.size(); ++i) {
                long long nxt = (i + 1 < fea.size() ? fea[i + 1] : LLONG_MAX);
                long long end = nxt - 1;
                if (cur <= end) {
                    segL.push_back(cur);
                    segR.push_back(end);
                    segVal.push_back(fea[i]);
                    cur = end + 1;
                }
            }
            for (int i = 0; i < K; ++i) {
                long long X, Y;
                cin >> X >> Y;
                long long ans = 0;
                for (size_t j = 0; j < segL.size(); ++j) {
                    if (Y < segL[j] || X > segR[j]) continue;
                    long long l = max(X, segL[j]);
                    long long r = min(Y, segR[j]);
                    ans += (r - l + 1) * segVal[j];
                }
                total += ans;
            }
        } else {
            for (int i = 0; i < K; ++i) {
                long long X, Y;
                cin >> X >> Y;
            }
        }
        cout << "Case #" << caseNo << ": " << total << "\n";
    }
    return 0;
}
