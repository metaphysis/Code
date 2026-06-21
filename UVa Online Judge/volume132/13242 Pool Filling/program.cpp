// Pool Filling
// UVa ID: 13242
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solveProblem() {
    int cap, target;
    cin >> cap >> target;
    int n;
    cin >> n;
    vector<ll> vol(n), temp(n);
    for (int i = 0; i < n; ++i) cin >> vol[i] >> temp[i];

    vector<ll> prefVol(n + 1, 0), prefTempSum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefVol[i + 1] = prefVol[i] + vol[i];
        prefTempSum[i + 1] = prefTempSum[i] + vol[i] * temp[i];
    }

    ll bestDiffNum = -1, bestDiffDen = 1; // 最优差值 diff/V 的分子和分母
    int bestL = -1, bestR = -1;

    for (int l = 0; l < n; ++l)
        for (int r = l; r < n; ++r) {
            ll V = prefVol[r + 1] - prefVol[l];
            ll S = prefTempSum[r + 1] - prefTempSum[l];

            // 容量限制：至少一半且不超过总容量
            if (V * 2 < cap || V > cap) continue;

            // 温度限制：|S - target*V| <= 5*V
            ll diff = llabs(S - target * V);
            if (diff > 5 * V) continue;

            // 与当前最优比较 (diff / V)
            bool better = false;
            if (bestL == -1) better = true;
            else {
                // diff1 / V1 < diff2 / V2  ⇔  diff1 * V2 < diff2 * V1
                ll lhs = diff * bestDiffDen;
                ll rhs = bestDiffNum * V;
                if (lhs < rhs) better = true;
                else if (lhs == rhs) {
                    // 差值相等，选编号最小（起始小，若同起始则结束小）
                    if (l < bestL) better = true;
                    else if (l == bestL && r < bestR) better = true;
                }
            }
            if (better) {
                bestDiffNum = diff;
                bestDiffDen = V;
                bestL = l;
                bestR = r;
            }
        }

    if (bestL == -1) cout << "Not possible\n";
    else cout << bestL << " " << bestR << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solveProblem();
    return 0;
}
