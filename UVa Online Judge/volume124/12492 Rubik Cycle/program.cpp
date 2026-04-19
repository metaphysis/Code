// Rubik Cycle
// UVa ID: 12492
// Verdict: Accepted
// Submission Date: 2026-03-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 1-indexed 编号方案，共54个贴纸
int p[55], t;  // 全局变量用于交换

// 最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 4个贴纸轮换函数
// e=1: 顺时针轮换 a->b->c->d->a
// e=0: 逆时针轮换 a->d->c->b->a
void x(int a, int b, int c, int d, int e) {
    if (e) {  // 顺时针
        t = p[a];
        p[a] = p[b];
        p[b] = p[c];
        p[c] = p[d];
        p[d] = t;
    } else {  // 逆时针
        t = p[d];
        p[d] = p[c];
        p[c] = p[b];
        p[b] = p[a];
        p[a] = t;
    }
}

// F面旋转
void F(int e) {
    x(1, 7, 9, 3, e);   // 角块
    x(4, 8, 6, 2, e);   // 边块
    x(12, 30, 37, 27, e); // 相邻面调整
    x(15, 29, 40, 26, e);
    x(18, 28, 43, 25, e);
}

// B面旋转
void B(int e) {
    x(10, 21, 39, 36, e);
    x(13, 20, 42, 35, e);
    x(16, 19, 45, 34, e);
    x(54, 52, 46, 48, e);
    x(53, 49, 47, 51, e);
}

// U面旋转
void U(int e) {
    x(19, 25, 27, 21, e);
    x(22, 26, 24, 20, e);
    x(10, 1, 43, 52, e);
    x(11, 2, 44, 53, e);
    x(12, 3, 45, 54, e);
}

// D面旋转
void D(int e) {
    x(9, 18, 48, 39, e);
    x(8, 17, 47, 38, e);
    x(7, 16, 46, 37, e);
    x(30, 36, 34, 28, e);
    x(29, 33, 35, 31, e);
}

// L面旋转
void L(int e) {
    x(10, 16, 18, 12, e);
    x(13, 17, 15, 11, e);
    x(1, 19, 48, 30, e);
    x(4, 22, 51, 33, e);
    x(7, 25, 54, 36, e);
}

// R面旋转
void R(int e) {
    x(21, 3, 28, 46, e);
    x(24, 6, 31, 49, e);
    x(27, 9, 34, 52, e);
    x(45, 43, 37, 39, e);
    x(44, 40, 38, 42, e);
}

// 计算排列的阶
ll findOrder() {
    vector<bool> visited(55, false);
    ll lcm = 1;
    
    for (int i = 1; i <= 54; i++) {
        if (!visited[i]) {
            int len = 0;
            int cur = i;
            while (!visited[cur]) {
                visited[cur] = true;
                cur = p[cur];
                len++;
            }
            if (len > 0) {
                lcm = lcm / gcd(lcm, len) * len;
            }
        }
    }
    return lcm;
}

int main() {
    char s[85];
    
    while (~scanf("%s", s)) {
        int len = strlen(s);
        
        // 初始化排列为恒等排列
        for (int i = 1; i <= 54; i++) p[i] = i;
        
        // 应用序列中的每个旋转
        for (int i = 0; i < len; i++) {
            switch (s[i]) {
                case 'f': F(0); break;
                case 'F': F(1); break;
                case 'b': B(0); break;
                case 'B': B(1); break;
                case 'u': U(0); break;
                case 'U': U(1); break;
                case 'd': D(0); break;
                case 'D': D(1); break;
                case 'l': L(0); break;
                case 'L': L(1); break;
                case 'r': R(0); break;
                case 'R': R(1); break;
                default: break;  // 忽略非字母字符（如样例中的'1'）
            }
        }
        
        // 计算并输出结果
        ll result = findOrder();
        printf("%lld\n", result);
    }
    return 0;
}
