// In-circles Again
// UVa ID: 1269
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

// 由半角的正弦值计算其余切值
double cotFromSin(double sinHalf) {
    if (sinHalf > 1.0) sinHalf = 1.0;
    if (sinHalf < -1.0) sinHalf = -1.0;
    double cosHalf = sqrt(max(0.0, 1.0 - sinHalf * sinHalf));
    return cosHalf / sinHalf;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);
    double inRadius, smallRadius1, smallRadius2, smallRadius3;
    int caseNo = 0;
    while (cin >> inRadius >> smallRadius1 >> smallRadius2 >> smallRadius3) {
        if (inRadius < 0) break;
        ++caseNo;
        double sinHalf1 = abs(inRadius - smallRadius1) / (inRadius + smallRadius1);
        double sinHalf2 = abs(inRadius - smallRadius2) / (inRadius + smallRadius2);
        double sinHalf3 = abs(inRadius - smallRadius3) / (inRadius + smallRadius3);
        double cot1 = cotFromSin(sinHalf1);
        double cot2 = cotFromSin(sinHalf2);
        double cot3 = cotFromSin(sinHalf3);
        double area = inRadius * inRadius * (cot1 + cot2 + cot3);
        cout << "Case " << caseNo << ": " << area << '\n';
    }
    return 0;
}
