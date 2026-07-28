// Friend or Foe
// UVa ID: 11289
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163269377

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, z;
    int label; // +1 帝国, -1 联盟
};

// 使用感知机算法训练线性分类器，要求帝国点 > 0，联盟点 <= 0
void trainPerceptron(const vector<Point>& points, long long& a, long long& b, long long& c, long long& d) {
    a = b = c = d = 0;
    while (true) {
        bool allCorrect = true;
        for (const auto& p : points) {
            long long dot = a * p.x + b * p.y + c * p.z + d;
            if (p.label * dot <= 0) { // 分类错误，更新权重
                a += p.label * p.x;
                b += p.label * p.y;
                c += p.label * p.z;
                d += p.label;
                allCorrect = false;
                break; // 重新开始检查
            }
        }
        if (allCorrect) break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int nA, nE;
    while (cin >> nA) {
        if (nA == -1) {
            cin >> nE; // 吸收另一个 -1
            break;
        }
        vector<Point> points;
        for (int i = 0; i < nA; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            points.push_back({x, y, z, -1}); // 联盟
        }
        cin >> nE;
        for (int i = 0; i < nE; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            points.push_back({x, y, z, 1});  // 帝国
        }
        long long a, b, c, d;
        trainPerceptron(points, a, b, c, d);
        cout << fixed << setprecision(6)
             << (double)a << " " << (double)b << " "
             << (double)c << " " << (double)d << "\n";
    }

    return 0;
}
