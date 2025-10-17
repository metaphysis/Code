// Dynamic len(set(a[L:R]))
// UVa ID: 12345
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int M = 50005;
int n, m, sn, a[M], bL[M], t[M*20], l, r, ans[M], AMS, p, q;
char s[5];

// 查询结构体：x-左端点, y-右端点, z-时间戳, id-查询编号
struct node { int x, y, z, id; } A[M], B[M];

// 带修莫队排序函数
bool cmp(node a, node b) {
    if (bL[a.x] == bL[b.x]) {  // 左端点在同一块
        if (bL[a.y] == bL[b.y]) // 右端点在同一块
            return bL[a.y] & 1 ? a.z > b.z : a.z < b.z;  // 奇偶排序优化
        return bL[a.x] & 1 ? a.y < b.y : a.y > b.y;  // 奇偶排序优化
    }
    return a.x < b.x;  // 按左端点所在块排序
}

// 添加元素到当前区间
void add(int x) { if (!t[x]++) ++AMS; }

// 从当前区间删除元素
void del(int x) { if (!--t[x]) --AMS; }

int main() {
    scanf("%d%d", &n, &m);
    sn = pow(n, 2.0 / 3);  // 计算块大小
    // 预处理每个位置所在的块
    for (int i = 1; i <= n; i++) {
        bL[i] = (i - 1) / sn + 1;
        scanf("%d", &a[i]);
    }
    
    // 读入操作
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%s%d%d", s, &x, &y);
        if (s[0] == 'Q') {  // 查询操作
            ++q;
            A[q] = {x + 1, y, p, q};  // 转换为1-indexed，区间[x+1, y]
        } else {  // 修改操作
            ++p;
            B[p] = {x + 1, a[x + 1], y, p};  // 记录修改信息
            a[x + 1] = y;  // 直接应用修改
        }
    }
    
    // 恢复初始数组状态
    for (int i = p; i >= 1; i--) a[B[i].x] = B[i].y;
    
    // 对查询排序
    sort(A + 1, A + q + 1, cmp);
    l = 1; r = 0; p = 0;  // 初始化指针
    
    // 处理每个查询
    for (int i = 1; i <= q; i++) {
        // 调整右指针
        while (r < A[i].y) add(a[++r]);
        while (l > A[i].x) add(a[--l]);
        while (r > A[i].y) del(a[r--]);
        while (l < A[i].x) del(a[l++]);
        
        // 调整时间指针（应用修改）
        while (p < A[i].z) {
            ++p;
            if (l <= B[p].x && B[p].x <= r) {  // 修改位置在当前区间内
                del(a[B[p].x]);  // 删除旧值
                a[B[p].x] = B[p].z;  // 应用修改
                add(a[B[p].x]);  // 添加新值
            } else {
                a[B[p].x] = B[p].z;  // 直接修改，不影响当前统计
            }
        }
        // 调整时间指针（回滚修改）
        while (p > A[i].z) {
            if (l <= B[p].x && B[p].x <= r) {  // 修改位置在当前区间内
                del(a[B[p].x]);  // 删除当前值
                a[B[p].x] = B[p].y;  // 恢复旧值
                add(a[B[p].x]);  // 添加旧值
            } else {
                a[B[p].x] = B[p].y;  // 直接恢复，不影响当前统计
            }
            --p;
        }
        
        // 记录答案
        ans[A[i].id] = AMS;
    }
    
    // 输出所有查询结果
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}
