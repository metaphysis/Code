// Cubes EXTREME
// UVa ID: 11436
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.230s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;

void findSolution(ll n) {
    ll bestX = -1, bestY = -1;
    
    // 枚举差值 d = x - y，从小到大枚举
    // d 的范围：1 <= d <= ∛(2N) 左右
    ll maxD = pow(2.0 * n, 1.0/3.0) + 1000;
    
    for (ll d = 1; d <= maxD; d++) {
        // 检查 d 是否是 N 的因子
        if (n % d != 0) continue;
        
        ll m = n / d;
        
        // 解方程：3y² + 3dy + (d² - m) = 0
        ll discriminant = 12LL * m - 3LL * d * d;
        if (discriminant < 0) continue;
        
        ll sqrtDisc = sqrt(discriminant);
        if (sqrtDisc * sqrtDisc != discriminant) continue;
        
        // y = (-3d + sqrtDisc) / 6 必须为正整数
        ll numerator = -3LL * d + sqrtDisc;
        if (numerator > 0 && numerator % 6 == 0) {
            ll y = numerator / 6;
            ll x = y + d;
            
            // 验证解
            if (x * x * x - y * y * y == n) {
                // 更新最优解（y 最小的）
                if (bestY == -1 || y < bestY) {
                    bestY = y;
                    bestX = x;
                }
            }
        }
    }
    
    if (bestY == -1) {
        cout << "No solution" << endl;
    } else {
        cout << bestX << " " << bestY << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    while (cin >> n && n != 0) {
        findSolution(n);
    }
    
    return 0;
}
