// Kingdom
// UVa ID: 1455
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.270s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXY = 2000010; // 2 * 1,000,000 + 10

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

Point cities[MAXN];
int parent[MAXN];
int stateSize[MAXN];
int minY[MAXN];
int maxY[MAXN];

// 差分数组，用于快速区间更新和单点查询
long long diffState[MAXY];  // 州数量的差分
long long diffCity[MAXY];   // 城市总数的差分

// 并查集查找（路径压缩）
int findSet(int x) {
    if (parent[x] != x) parent[x] = findSet(parent[x]);
    return parent[x];
}

// 更新差分数组：在区间[l, r]内的所有奇数位置加上delta
// l和r是转换后的坐标（乘以2后的值）
void updateRange(int l, int r, int size, int delta) {
    if (l > r) return;
    
    // 确保l和r是奇数（因为C对应的都是奇数）
    if (l % 2 == 0) l++;
    if (r % 2 == 0) r--;
    if (l > r) return;
    
    // 差分更新
    diffState[l] += delta;
    if (r + 2 < MAXY) diffState[r + 2] -= delta;
    
    diffCity[l] += delta * size;
    if (r + 2 < MAXY) diffCity[r + 2] -= delta * size;
}

// 合并两个连通分量
void unionSet(int a, int b) {
    int ra = findSet(a);
    int rb = findSet(b);
    if (ra == rb) return;
    
    // 先移除两个旧分量的贡献
    updateRange(minY[ra] * 2 + 1, maxY[ra] * 2 - 1, stateSize[ra], -1);
    updateRange(minY[rb] * 2 + 1, maxY[rb] * 2 - 1, stateSize[rb], -1);
    
    // 按大小合并，小树合并到大树
    if (stateSize[ra] < stateSize[rb]) swap(ra, rb);
    
    // 执行合并
    parent[rb] = ra;
    stateSize[ra] += stateSize[rb];
    minY[ra] = min(minY[ra], minY[rb]);
    maxY[ra] = max(maxY[ra], maxY[rb]);
    
    // 添加新分量的贡献
    updateRange(minY[ra] * 2 + 1, maxY[ra] * 2 - 1, stateSize[ra], 1);
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n;
        scanf("%d", &n);
        
        // 初始化差分数组
        memset(diffState, 0, sizeof(diffState));
        memset(diffCity, 0, sizeof(diffCity));
        
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &cities[i].x, &cities[i].y);
            parent[i] = i;
            stateSize[i] = 1;
            minY[i] = cities[i].y;
            maxY[i] = cities[i].y;
            
            // 单点城市（只有一个城市的分量）不会产生穿透
            // 所以不需要更新差分数组
        }
        
        int m;
        scanf("%d", &m);
        
        while (m--) {
            char cmd[10];
            scanf("%s", cmd);
            
            if (cmd[0] == 'r') {
                // road 命令：修建道路
                int a, b;
                scanf("%d %d", &a, &b);
                unionSet(a, b);
            } 
            else {
                // line 命令：查询
                char cStr[20];
                scanf("%s", cStr);
                
                // 解析 C = X.5 为整数形式 2X+1
                int integerPart = 0;
                for (int i = 0; cStr[i] && cStr[i] != '.'; i++) {
                    integerPart = integerPart * 10 + (cStr[i] - '0');
                }
                int C = integerPart * 2 + 1;  // 2*X + 1
                
                // 计算前缀和得到当前C的答案
                // 注意：我们只需要累加到C位置（包括C）
                long long stateCount = 0;
                long long cityCount = 0;
                
                // 累加所有奇数位置的前缀和
                for (int i = 1; i <= C; i += 2) {
                    stateCount += diffState[i];
                    cityCount += diffCity[i];
                }
                
                printf("%lld %lld\n", stateCount, cityCount);
            }
        }
    }
    
    return 0;
}
