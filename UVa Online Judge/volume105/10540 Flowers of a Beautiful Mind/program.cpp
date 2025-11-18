// Flowers of a Beautiful Mind
// UVa ID: 10540
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = 2 * acos(0.0);

int main() {
    int R, N;
    int setNum = 1;
    double totalArea[64], overlapArea[64], visibleArea[64];
    while (cin >> R >> N && (R != 0 || N != 0)) {
        int layers = (N + 1) / 2;
        for (int i = 0; i < layers; i++) {
            int k = layers - 1 - i;
            if (k == 0) totalArea[i] = N * PI * R * R;
            else {
                double angleBetween = 2 * PI * k / N;
                double d = 2 * R * sin(angleBetween / 2);
                double theta = 2 * acos(d / (2 * R));
                double segmentArea = 0.5 * R * R * (theta - sin(theta));
                double petalArea = 2 * segmentArea;
                totalArea[i] = N * petalArea;
            }
        }
        cout << "Set " << setNum++ << ":\n";
        cout << layers << "\n";
        cout << fixed << setprecision(4);
        visibleArea[0] = overlapArea[0] = totalArea[0];
        cout << totalArea[0] << " " << visibleArea[0] << "\n";
        for (int i = 1; i < layers; i++) {
            overlapArea[i] = totalArea[i] - totalArea[i - 1];
            visibleArea[i] = overlapArea[i] - overlapArea[i - 1];
            cout << totalArea[i] << " " << visibleArea[i] << "\n";
        }
    }
    return 0;
}
