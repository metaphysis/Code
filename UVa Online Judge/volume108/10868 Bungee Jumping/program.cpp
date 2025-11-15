// Bungee Jumping
// UVa ID: 10868
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double g = 9.81;

int main() {
    double k, l, s, w;
    
    while (cin >> k >> l >> s >> w) {
        if (k == 0 && l == 0 && s == 0 && w == 0) {
            break;
        }
        
        // 绳子从未拉直的情况（自由落体）
        if (l >= s) {
            double v = sqrt(2 * g * s);
            if (v > 10.0) {
                cout << "Killed by the impact." << endl;
            } else {
                cout << "James Bond survives." << endl;
            }
            continue;
        }
        
        // 绳子拉直后的情况
        // 正确的能量守恒公式：m*g*s = 0.5*k*(s-l)² + 0.5*m*v²
        double v_squared = 2 * g * s - (k / w) * (s - l) * (s - l);
        
        // 如果速度为虚数，说明无法到达地面
        if (v_squared < 0) {
            cout << "Stuck in the air." << endl;
        } else {
            double v = sqrt(v_squared);
            if (v > 10.0) {
                cout << "Killed by the impact." << endl;
            } else {
                cout << "James Bond survives." << endl;
            }
        }
    }
    
    return 0;
}
