// Rectangle
// UVa ID: 12462
// Verdict: Accepted
// Submission Date: 2026-01-17
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, c;
int h[MAXN], col[MAXN];
long long ans;

struct Bar {
    int height, pos, color;
    bool operator<(const Bar& other) const {
        return height > other.height; // 降序排序
    }
};

Bar bars[MAXN];
int parent[MAXN], setSize[MAXN], mask[MAXN];
bool activated[MAXN];

int findSet(int x) {
    if (parent[x] != x) parent[x] = findSet(parent[x]);
    return parent[x];
}

// 合并两个集合，返回合并后的根
int unionSet(int a, int b) {
    a = findSet(a); b = findSet(b);
    if (a == b) return a;
    if (setSize[a] < setSize[b]) swap(a, b);
    parent[b] = a;
    setSize[a] += setSize[b];
    mask[a] |= mask[b];
    return a;
}

void solve() {
    // 构建Bar数组
    for (int i = 0; i < n; i++) {
        bars[i].height = h[i];
        bars[i].pos = i;
        bars[i].color = col[i];
    }
    sort(bars, bars + n);
    
    // 初始化并查集
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        setSize[i] = 1;
        mask[i] = (1 << col[i]);
        activated[i] = false;
    }
    
    ans = 0;
    int fullMask = (1 << c) - 1;
    
    for (int idx = 0; idx < n; ) {
        int currentHeight = bars[idx].height;
        vector<int> rootsToCheck;
        
        // 处理所有高度相同的条
        while (idx < n && bars[idx].height == currentHeight) {
            int pos = bars[idx].pos;
            activated[pos] = true;
            rootsToCheck.push_back(pos);
            
            // 如果左边已激活，合并
            if (pos > 0 && activated[pos - 1]) {
                int newRoot = unionSet(pos, pos - 1);
                rootsToCheck.push_back(newRoot);
            }
            // 如果右边已激活，合并
            if (pos + 1 < n && activated[pos + 1]) {
                int newRoot = unionSet(pos, pos + 1);
                rootsToCheck.push_back(newRoot);
            }
            idx++;
        }
        
        // 去重检查可能的新连通块
        sort(rootsToCheck.begin(), rootsToCheck.end());
        rootsToCheck.erase(unique(rootsToCheck.begin(), rootsToCheck.end()), rootsToCheck.end());
        
        for (int root : rootsToCheck) {
            root = findSet(root);
            if (mask[root] == fullMask) {
                long long area = (long long)currentHeight * setSize[root];
                if (area > ans) ans = area;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> n >> c, n || c) {
        for (int i = 0; i < n; i++) cin >> h[i];
        for (int i = 0; i < n; i++) cin >> col[i];
        solve();
        cout << ans << "\n";
    }
    
    return 0;
}
