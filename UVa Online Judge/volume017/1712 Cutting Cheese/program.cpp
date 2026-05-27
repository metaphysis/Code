// Cutting Cheese
// UVa ID: 1712
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.380s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;
const double L = 0.0;
const double R = 100.0;

struct Hole {
    double r, z0, zLow;   // z0 是球心 z 坐标, zLow = z0 - r
    double r2;            // 半径平方，用于快速计算
};

inline double sphereSliceVolume(const Hole& h, double z1, double z2) {
    double R = h.r, z0 = h.z0;
    if (z2 <= z0 - R + EPS || z1 >= z0 + R - EPS) return 0.0;
    double low = max(z1, z0 - R);
    double high = min(z2, z0 + R);
    if (high - low < EPS) return 0.0;
    if (low <= z0 - R + EPS && high >= z0 + R - EPS)
        return 4.0/3.0 * PI * R * R * R;
    auto F = [&](double z) -> double {
        double dz = z - z0;
        return PI * (h.r2 * dz - dz * dz * dz / 3.0);
    };
    return F(high) - F(low);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(9);
    
    int n, s;
    while (cin >> n >> s) {
        vector<Hole> holes(n);
        double totalHoleVol = 0.0;
        for (int i = 0; i < n; ++i) {
            double r, x, y, z;
            cin >> r >> x >> y >> z;
            r /= 1000.0; x /= 1000.0; y /= 1000.0; z /= 1000.0;
            holes[i] = {r, z, z - r, r * r};
            totalHoleVol += 4.0/3.0 * PI * r * r * r;
        }
        // 按 z0 - r 升序排序，便于二分查找有效孔洞
        sort(holes.begin(), holes.end(), [](const Hole& a, const Hole& b) {
            return a.zLow < b.zLow;
        });
        
        double totalCheeseVol = 100.0 * 100.0 * 100.0 - totalHoleVol;
        double targetSliceVol = totalCheeseVol / s;
        
        vector<double> ans(s);
        double prevZ = 0.0;
        
        // 预分配 lambda，避免重复构造
        auto cheeseVolumeUpToZ = [&](double zCut) -> double {
            double vol = 10000.0 * zCut;  // 100*100 = 10000
            // 二分查找第一个 zLow >= zCut 的孔洞
            int idx = upper_bound(holes.begin(), holes.end(), zCut,
                [](double val, const Hole& h) { return val < h.zLow; }) - holes.begin();
            for (int i = 0; i < idx; ++i)
                vol -= sphereSliceVolume(holes[i], 0.0, zCut);
            return vol;
        };
        
        for (int i = 0; i < s; ++i) {
            double needVol = (i + 1) * targetSliceVol;
            double lo = prevZ, hi = R;
            for (int iter = 0; iter < 40; ++iter) {  // 40 次足够
                double mid = (lo + hi) * 0.5;
                if (cheeseVolumeUpToZ(mid) < needVol)
                    lo = mid;
                else
                    hi = mid;
            }
            double curZ = (lo + hi) * 0.5;
            ans[i] = curZ - prevZ;
            prevZ = curZ;
        }
        
        for (int i = 0; i < s; ++i)
            cout << ans[i] << '\n';
    }
    return 0;
}
