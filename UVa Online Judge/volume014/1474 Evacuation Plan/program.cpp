// Evacuation Plan
// UVa ID: 1474
// Verdict: Accepted
// Submission Date: 2026-05-22
// UVa Run Time: 4.930s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 4005;
const ll INF = 1e18;

int n, m;
pair<int, int> team[MAXN];          // (位置, 原始下标)
pair<int, int> shelterWithId[MAXN]; // (位置, 原始编号)
int shelterPos[MAXN];               // 排序后的避难所位置
int shelterOriginalId[MAXN];        // 排序后的避难所对应的原始编号
ll dpPrev[MAXN], dpCur[MAXN];
int choice[MAXN][MAXN];
ll pre[MAXN];
int ptr[MAXN][MAXN]; // ptr[j][i] = 对于避难所 j，前 i 个队伍中最后一个 <= shelterPos[j] 的位置

// 计算 cost(l, r, j) = [l, r] 的队伍到 shelterPos[j] 的距离和
inline ll cost(int l, int r, int j) {
    int s = shelterPos[j];
    int p = ptr[j][r];
    if (p < l) {
        return (pre[r] - pre[l-1]) - (ll)s * (r - l + 1);
    }
    if (p >= r) {
        return (ll)s * (r - l + 1) - (pre[r] - pre[l-1]);
    }
    ll left = (ll)s * (p - l + 1) - (pre[p] - pre[l-1]);
    ll right = (pre[r] - pre[p]) - (ll)s * (r - p);
    return left + right;
}

// 分治优化
void divide(int j, int l, int r, int optL, int optR) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    int bestK = -1;
    ll bestVal = INF;
    for (int k = max(optL, j - 1); k <= min(optR, mid - 1); ++k) {
        ll val = dpPrev[k] + cost(k + 1, mid, j);
        if (val < bestVal) {
            bestVal = val;
            bestK = k;
        }
    }
    dpCur[mid] = bestVal;
    choice[j][mid] = bestK;
    divide(j, l, mid - 1, optL, bestK);
    divide(j, mid + 1, r, bestK, optR);
}

void solve() {
    // 读入队伍
    for (int i = 1; i <= n; ++i) {
        cin >> team[i].first;
        team[i].second = i;
    }
    
    // 读入避难所，记录原始编号
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> shelterWithId[i].first;
        shelterWithId[i].second = i; // 原始编号从 1 开始
    }
    
    // 排序
    sort(team + 1, team + n + 1);
    sort(shelterWithId + 1, shelterWithId + m + 1);
    
    // 提取排序后的避难所位置和原始编号
    for (int j = 1; j <= m; ++j) {
        shelterPos[j] = shelterWithId[j].first;
        shelterOriginalId[j] = shelterWithId[j].second;
    }
    
    // 前缀和
    pre[0] = 0;
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + team[i].first;
    
    // 预处理 ptr[j][i]
    for (int j = 1; j <= m; ++j) {
        int p = 0;
        for (int i = 1; i <= n; ++i) {
            if (team[i].first <= shelterPos[j]) p = i;
            ptr[j][i] = p;
        }
    }
    
    // 初始化
    for (int i = 0; i <= n; ++i) dpPrev[i] = INF;
    dpPrev[0] = 0;
    
    // DP 主循环
    for (int j = 1; j <= m; ++j) {
        divide(j, j, n, j - 1, n);
        swap(dpPrev, dpCur);
    }
    
    // 输出总燃料
    cout << dpPrev[n] << "\n";
    
    // 回溯分配：assignByOriginalTeam[原始队伍下标] = 避难所原始编号
    vector<int> assignByOriginalTeam(n + 1);
    int cur = n;
    for (int j = m; j >= 1; --j) {
        int prev = choice[j][cur];
        // 当前避难所（排序后下标 j）分配给队伍区间 [prev+1, cur]
        int originalShelterId = shelterOriginalId[j];
        for (int i = prev + 1; i <= cur; ++i) {
            int originalTeamId = team[i].second;
            assignByOriginalTeam[originalTeamId] = originalShelterId;
        }
        cur = prev;
    }
    
    // 按原始队伍顺序输出
    for (int i = 1; i <= n; ++i) {
        cout << assignByOriginalTeam[i] << (i == n ? "\n" : " ");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n) solve();
    return 0;
}
