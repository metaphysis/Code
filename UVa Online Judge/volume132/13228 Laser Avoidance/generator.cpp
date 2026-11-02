// 文件名: generator.cpp
// 编译: g++ -O3 generator.cpp -o generator
// 用法: ./gen [T组数] [最大n] [随机种子seed]
// 示例: ./gen 20 50 12345  (一次生成 20 组测试数据，每组 n 在 1~50 之间)
#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);

struct Pt { double x, y; };

// 判定射线 (O, dir) 是否与线段 A-B 相交
bool ray_hits_seg(Pt O, Pt dir, Pt A, Pt B) {
    Pt v1 = {O.x - A.x, O.y - A.y};
    Pt v2 = {B.x - A.x, B.y - A.y};
    Pt v3 = {-dir.y, dir.x};
    double dot = v2.x * v3.x + v2.y * v3.y;
    if (fabs(dot) < 1e-9) return false;
    double t1 = (v2.x * v1.y - v2.y * v1.x) / dot;
    double t2 = (v1.x * v3.x + v1.y * v3.y) / dot;
    return t1 >= -1e-7 && t2 >= -1e-7 && t2 <= 1.0 + 1e-7;
}

// 点 O 到线段 A-B 的距离平方
double pt_seg_dist_sq(Pt O, Pt A, Pt B) {
    double l2 = (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
    double t = max(0.0, min(1.0, ((O.x - A.x) * (B.x - A.x) + (O.y - A.y) * (B.y - A.y)) / (l2 + 1e-9)));
    double dx = O.x - (A.x + t * (B.x - A.x));
    double dy = O.y - (A.y + t * (B.y - A.y));
    return dx * dx + dy * dy;
}

void generate_one_case(mt19937& rng, int max_n) {
    int n = uniform_int_distribution<int>(max(1, max_n / 2), max_n)(rng);
    uniform_real_distribution<double> coord_dist(20.0, 100.0);
    uniform_real_distribution<double> prob(0.0, 1.0);

    double p = round(coord_dist(rng));
    double q = round(coord_dist(rng));

    // 构造一条从 S(0,0) 到 T(p,q) 的折线骨架（Safe Polyline），
    // 所有激光只要不穿过这条骨架折线，就绝对保证 S 到 T 存在合法路径！
    int spine_pts = uniform_int_distribution<int>(3, 8)(rng);
    vector<Pt> spine;
    spine.push_back({0.0, 0.0});

    bool comb_mode = (prob(rng) < 0.4); // 40% 概率生成大幅度上下折返的“梳状”通道
    for (int i = 1; i < spine_pts; ++i) {
        double ratio = (double)i / spine_pts;
        double bx, by;
        if (comb_mode) {
            double side = (i % 2 == 1) ? 40.0 : -40.0;
            bx = ratio * p + uniform_real_distribution<double>(-10.0, 10.0)(rng);
            by = ratio * q + side + uniform_real_distribution<double>(-10.0, 10.0)(rng);
        } else {
            bx = ratio * p + uniform_real_distribution<double>(-35.0, 35.0)(rng);
            by = ratio * q + uniform_real_distribution<double>(-35.0, 35.0)(rng);
        }
        spine.push_back({round(bx), round(by)});
    }
    spine.push_back({p, q});

    cout << n << " " << fixed << setprecision(2) << p << " " << q << "\n";

    vector<Pt> origins;
    for (int i = 0; i < n; ) {
        Pt O;
        // 25% 概率复用已有源点（测试重合源点 Coincident Origins）
        if (!origins.empty() && prob(rng) < 0.25) {
            O = origins[uniform_int_distribution<int>(0, (int)origins.size() - 1)(rng)];
        } else if (prob(rng) < 0.5 && spine.size() > 2) {
            // 50% 概率在骨架折点附近生成源点，强迫最短路径紧贴这些源点转弯
            Pt sp = spine[uniform_int_distribution<int>(1, (int)spine.size() - 2)(rng)];
            O.x = sp.x + round(uniform_real_distribution<double>(-15.0, 15.0)(rng));
            O.y = sp.y + round(uniform_real_distribution<double>(-15.0, 15.0)(rng));
        } else {
            O.x = round(uniform_real_distribution<double>(-30.0, 130.0)(rng));
            O.y = round(uniform_real_distribution<double>(-30.0, 130.0)(rng));
        }

        // 避免源点直接砸在骨架折线上（保持至少 0.5 单位的安全间距）
        bool too_close = false;
        for (size_t j = 0; j + 1 < spine.size(); ++j) {
            if (pt_seg_dist_sq(O, spine[j], spine[j + 1]) < 0.25) {
                too_close = true;
                break;
            }
        }
        if (too_close) continue;

        // 随机选择一个发射角 theta，要求该射线不穿过安全骨架折线 spine
        double theta = uniform_real_distribution<double>(-PI, PI)(rng);
        Pt dir = {cos(theta), sin(theta)};
        bool hits_spine = false;
        for (size_t j = 0; j + 1 < spine.size(); ++j) {
            if (ray_hits_seg(O, dir, spine[j], spine[j + 1])) {
                hits_spine = true;
                break;
            }
        }
        if (hits_spine) continue;

        origins.push_back(O);
        cout << fixed << setprecision(2) << O.x << " " << O.y << " "
             << setprecision(5) << theta << "\n";
        i++;
    }
}

int main(int argc, char* argv[]) {
    int T = (argc > 1) ? atoi(argv[1]) : 10;       // 默认一次生成 10 组测试数据
    int max_n = (argc > 2) ? atoi(argv[2]) : 200;   // 默认每组最多 50 条激光（可设为 1000）
    int seed = (argc > 3) ? atoi(argv[3]) : time(NULL);  // 默认随机种子

    mt19937 rng(seed);
    for (int t = 0; t < T; ++t) {
        generate_one_case(rng, max_n);
    }
    return 0;
}
