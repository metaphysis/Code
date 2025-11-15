// Circles in Triangle
// UVa ID: 10386
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double SQRT3 = sqrt(3.0);

int main() {
    int N;
    cin >> N;
    
    // Pre-calculated optimal angles
    const double angle8 = 0.75435478480197;  // Optimal angle for 8 circles
    const double angle11 = 0.43171784545542; // Optimal angle for 11 circles
    
    // Pre-calculated ratios
    const double ratio8 = 2.0 * SQRT3 + 8.0 * cos(angle8);
    const double ratio11 = 2.0 * SQRT3 + 8.0 * cos(angle11);
    
    cout << fixed << setprecision(10);
    
    for (int i = 0; i < N; i++) {
        double r;
        cin >> r;
        
        double s8 = ratio8 * r;
        double s11 = ratio11 * r;
        
        cout << s8 << " " << s11 << endl;
    }
    
    return 0;
}
