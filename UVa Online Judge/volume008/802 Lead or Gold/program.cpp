// Lead or Gold
// UVa ID: 802
// Verdict: Accepted
// Submission Date: 2026-02-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Vector {
    long long a, b, c;
    Vector(long long a = 0, long long b = 0, long long c = 0) : a(a), b(b), c(c) {}
    Vector operator-(const Vector& other) const { return Vector(a - other.a, b - other.b, c - other.c); }
    bool isZero() const { return a == 0 && b == 0 && c == 0; }
};

// 点积
long long dot(const Vector& u, const Vector& v) {
    return u.a * v.a + u.b * v.b + u.c * v.c;
}

// 叉积
Vector cross(const Vector& u, const Vector& v) {
    return Vector(u.b * v.c - u.c * v.b, u.c * v.a - u.a * v.c, u.a * v.b - u.b * v.a);
}

// 判断目标向量 target 是否可以由向量 x 和 y 的非负线性组合得到（二维情况）
bool checkTwo(const Vector& x, const Vector& y, const Vector& target) {
    // 选取两个不相关的分量进行二维判断
    for (int p = 0; p < 3; p++)
    for (int q = p + 1; q < 3; q++) {
        long long a1 = (p == 0 ? x.a : (p == 1 ? x.b : x.c));
        long long b1 = (q == 0 ? x.a : (q == 1 ? x.b : x.c));
        long long a2 = (p == 0 ? y.a : (p == 1 ? y.b : y.c));
        long long b2 = (q == 0 ? y.a : (q == 1 ? y.b : y.c));
        long long c1 = (p == 0 ? target.a : (p == 1 ? target.b : target.c));
        long long c2 = (q == 0 ? target.a : (q == 1 ? target.b : target.c));
        long long det = a1 * b2 - a2 * b1; // 二维行列式
        if (det == 0) continue; // 两向量在该投影上平行，换一组分量
        long long xNum = c1 * b2 - c2 * b1; // 对应 x 系数的分子
        long long yNum = a1 * c2 - a2 * c1; // 对应 y 系数的分子
        // 根据分母正负判断分子符号是否都非负
        if (det > 0) { if (xNum >= 0 && yNum >= 0) return true; }
        else { if (xNum <= 0 && yNum <= 0) return true; }
    }
    return false;
}

int main() {
    int n, testCase = 0;
    bool firstCase = true;
    while (cin >> n && n != 0) {
        if (firstCase) firstCase = false;
        else cout << endl; // 测试用例之间输出空行
        testCase++;
        vector<Vector> mixtures(n);
        for (int i = 0; i < n; i++) cin >> mixtures[i].a >> mixtures[i].b >> mixtures[i].c;
        Vector target;
        cin >> target.a >> target.b >> target.c;

        bool possible = false;
        // 情况1: 检查单个向量
        for (int i = 0; i < n && !possible; i++) {
            // 平行且同向
            if (cross(mixtures[i], target).isZero() && dot(mixtures[i], target) > 0) possible = true;
        }
        // 情况2: 检查两个向量的组合
        for (int i = 0; i < n && !possible; i++)
        for (int j = i + 1; j < n && !possible; j++) {
            Vector cr = cross(mixtures[i], mixtures[j]);
            if (cr.isZero()) {
                // 平行情况，只要目标与其中之一平行且同向即可
                if (cross(mixtures[i], target).isZero()) {
                    if (dot(mixtures[i], target) >= 0 || dot(mixtures[j], target) >= 0) possible = true;
                }
            } else {
                // 不平行，需要共面且可非负表示
                if (dot(target, cr) == 0 && checkTwo(mixtures[i], mixtures[j], target)) possible = true;
            }
        }
        // 情况3: 检查三个线性无关向量的组合
        for (int i = 0; i < n && !possible; i++)
        for (int j = i + 1; j < n && !possible; j++)
        for (int k = j + 1; k < n && !possible; k++) {
            Vector v1 = mixtures[i], v2 = mixtures[j], v3 = mixtures[k];
            long long denom = dot(v3, cross(v1, v2)); // 混合积，即分母
            if (denom == 0) continue; // 线性相关，跳过（已由两向量覆盖）
            long long xNum = dot(target, cross(v2, v3)); // p 的分子
            long long yNum = dot(target, cross(v3, v1)); // q 的分子
            long long zNum = dot(target, cross(v1, v2)); // r 的分子
            // 根据分母正负判断所有分子是否同号且非负（相对于分母）
            if (denom > 0) { if (xNum >= 0 && yNum >= 0 && zNum >= 0) possible = true; }
            else { if (xNum <= 0 && yNum <= 0 && zNum <= 0) possible = true; }
        }

        cout << "Mixture " << testCase << endl;
        cout << (possible ? "Possible" : "Impossible") << endl;
    }
    return 0;
}
