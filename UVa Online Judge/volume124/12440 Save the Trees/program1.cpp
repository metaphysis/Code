// Save the Trees
// UVa ID: 12440
// Verdict: Accepted
// Submission Date: 2026-05-19
// UVa Run Time: 0.470s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 100010;
const LL INF = 1e18;

// 线段树节点维护：
// dpVal: 每个位置作为左端点时的 dp[j-1] 值
// maxH:  每个位置当前所在段的最大高度
// minVal: dpVal + maxH 的最小值
struct SegTree {
    vector<LL> dpVal;   // 存储 dp[j-1]
    vector<LL> maxH;    // 存储当前段的最大高度
    vector<LL> minVal;  // 存储 min(dpVal + maxH)
    vector<LL> lazy;    // 懒标记（用于 maxH 的区间赋值）
    int n;
    
    SegTree(int n) : n(n) {
        dpVal.assign(4 * n, INF);
        maxH.assign(4 * n, 0);
        minVal.assign(4 * n, INF);
        lazy.assign(4 * n, -1);  // -1 表示无懒标记
    }
    
    void pushDown(int o, int l, int r) {
        if (lazy[o] != -1) {
            int mid = (l + r) / 2;
            // 更新左孩子
            maxH[o * 2] = lazy[o];
            minVal[o * 2] = dpVal[o * 2] + lazy[o];
            lazy[o * 2] = lazy[o];
            // 更新右孩子
            maxH[o * 2 + 1] = lazy[o];
            minVal[o * 2 + 1] = dpVal[o * 2 + 1] + lazy[o];
            lazy[o * 2 + 1] = lazy[o];
            // 清除当前懒标记
            lazy[o] = -1;
        }
    }
    
    void maintain(int o) {
        minVal[o] = min(minVal[o * 2], minVal[o * 2 + 1]);
        dpVal[o] = min(dpVal[o * 2], dpVal[o * 2 + 1]);
    }
    
    // 单点设置 dpVal[pos] = val
    void setDp(int o, int l, int r, int pos, LL val) {
        if (l == r) {
            dpVal[o] = val;
            minVal[o] = val + maxH[o];
            return;
        }
        pushDown(o, l, r);
        int mid = (l + r) / 2;
        if (pos <= mid) setDp(o * 2, l, mid, pos, val);
        else setDp(o * 2 + 1, mid + 1, r, pos, val);
        maintain(o);
    }
    
    // 区间设置 maxH[ql..qr] = val
    void setMax(int o, int l, int r, int ql, int qr, LL val) {
        if (ql <= l && r <= qr) {
            maxH[o] = val;
            minVal[o] = dpVal[o] + val;
            lazy[o] = val;
            return;
        }
        pushDown(o, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid) setMax(o * 2, l, mid, ql, qr, val);
        if (qr > mid) setMax(o * 2 + 1, mid + 1, r, ql, qr, val);
        maintain(o);
    }
    
    // 区间查询最小值
    LL query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return minVal[o];
        pushDown(o, l, r);
        int mid = (l + r) / 2;
        LL res = INF;
        if (ql <= mid) res = min(res, query(o * 2, l, mid, ql, qr));
        if (qr > mid) res = min(res, query(o * 2 + 1, mid + 1, r, ql, qr));
        return res;
    }
};

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        int n;
        scanf("%d", &n);
        
        vector<int> height(n + 1);
        vector<int> lastPos(100005, 0);
        
        SegTree seg(n);
        
        // 初始化：左端点 1 的 dp[0] = 0
        seg.setDp(1, 1, n, 1, 0);
        
        vector<int> stk;  // 单调栈，存储下标
        stk.push_back(0);
        height[0] = 1e9;
        
        LL dpVal = 0;
        int L = 0;
        
        for (int i = 1; i <= n; ++i) {
            int type, h;
            scanf("%d%d", &type, &h);
            height[i] = h;
            
            // 更新左边界 L = max(L, lastPos[type] + 1)
            L = max(L, lastPos[type] + 1);
            lastPos[type] = i;
            
            // 维护单调递减栈
            while (height[i] >= height[stk.back()]) {
                stk.pop_back();
            }
            // 新区间 [stk.back() + 1, i] 的最大高度设为 height[i]
            seg.setMax(1, 1, n, stk.back() + 1, i, height[i]);
            stk.push_back(i);
            
            // 查询区间 [L, i] 的最小值，作为当前 dp[i]
            dpVal = seg.query(1, 1, n, L, i);
            
            // 为下一个位置设置 dp[i]
            if (i < n) {
                seg.setDp(1, 1, n, i + 1, dpVal);
            }
        }
        
        printf("Case %d: %lld\n", cas, dpVal);
    }
    return 0;
}
