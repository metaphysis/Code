// Fractal
// UVa ID: 11253
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Vec {
    ll x, y;
};

Vec addVec(const Vec& a, const Vec& b) { return {a.x + b.x, a.y + b.y}; }
Vec subVec(const Vec& a, const Vec& b) { return {a.x - b.x, a.y - b.y}; }
Vec mulVec(const Vec& a, const Vec& b) { return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }

Vec fullPos[31], fullDir[31]; // fullPos[k] = 完整 s_k 的位移，fullDir[k] = 最终方向

struct Result {
    Vec pos; // 位移
    Vec dir; // 最终方向
};

// 前向声明
Result getPrefix(int k, ll n, const Vec& dir);
Result getRevPrefix(int k, ll n, const Vec& dir);

// 计算 s_k 的前 n 步（移动段）
Result getPrefix(int k, ll n, const Vec& dir) {
    if (n == 0) return {{0, 0}, dir};
    if (k == 0) {
        Vec step1 = dir;
        Vec turn1 = mulVec(dir, {0, 1}); // 左转
        if (n == 1) return {step1, turn1};
        Vec step2 = turn1;
        Vec pos = addVec(step1, step2);
        return {pos, turn1};
    }
    ll half = 1LL << k; // s_{k-1} 的移动步数
    if (n <= half) return getPrefix(k - 1, n, dir);
    // 走完前半部分 s_{k-1}
    Vec pos1 = mulVec(dir, fullPos[k - 1]);
    Vec dir1 = mulVec(dir, fullDir[k - 1]);
    // 中间左转
    Vec dir2 = mulVec(dir1, {0, 1});
    ll r = n - half;
    Result part3 = getRevPrefix(k - 1, r, dir2); // 第三部分 r(s_{k-1})
    Vec totalPos = addVec(pos1, part3.pos);
    return {totalPos, part3.dir};
}

// 计算 r(s_k) 的前 n 步（移动段）
Result getRevPrefix(int k, ll n, const Vec& dir) {
    if (n == 0) return {{0, 0}, dir};
    if (k == 0) {
        Vec step1 = dir;
        Vec turn1 = mulVec(dir, {0, -1}); // 右转
        if (n == 1) return {step1, turn1};
        Vec step2 = turn1;
        Vec pos = addVec(step1, step2);
        return {pos, turn1};
    }
    ll half = 1LL << k;
    if (n <= half) return getPrefix(k - 1, n, dir); // 前半部分也是 s_{k-1}
    Vec pos1 = mulVec(dir, fullPos[k - 1]);
    Vec dir1 = mulVec(dir, fullDir[k - 1]);
    // 中间右转
    Vec dir2 = mulVec(dir1, {0, -1});
    ll r = n - half;
    Result part3 = getRevPrefix(k - 1, r, dir2); // 第三部分 r(s_{k-1})
    Vec totalPos = addVec(pos1, part3.pos);
    return {totalPos, part3.dir};
}

int main() {
    // 预计算完整 s_k 的位移和最终方向
    fullPos[0] = {1, 1};
    fullDir[0] = {0, 1};
    for (int k = 1; k <= 30; ++k) {
        Vec p = fullPos[k - 1], d = fullDir[k - 1];
        // r(s_{k-1}) 的完整位移 Q = 1 - d*p + d^2
        Vec q = subVec({1, 0}, mulVec(d, p));
        q = addVec(q, mulVec(d, d));
        // r(s_{k-1}) 的最终方向 R = -d
        Vec rDir = {-d.x, -d.y};
        // 左转
        Vec left = mulVec(d, {0, 1});
        fullPos[k] = addVec(p, mulVec(left, q));
        fullDir[k] = mulVec(left, rDir);
    }

    ll n;
    while (cin >> n && n >= 0) {
        Result ans = getPrefix(30, n, {1, 0});
        cout << "(" << ans.pos.x << "," << ans.pos.y << ")\n";
    }
    return 0;
}
