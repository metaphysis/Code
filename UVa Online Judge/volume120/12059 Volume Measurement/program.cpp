#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    const double pi = acos(-1.0), eps = 1e-9;
    cin >> testCount;
    cout << fixed << setprecision(3);
    for (int caseId = 1; caseId <= testCount; caseId++) {
        double baseLen, height, cubeLen, angle;
        cin >> baseLen >> height >> cubeLen >> angle;
        double rad = angle * pi / 180.0, sinVal = sin(rad), cosVal = cos(rad);
        double sumVal = sinVal + cosVal, topLen = baseLen * (1.0 - cubeLen / height);
        cout << "Case " << caseId << ":\n";
        if (cubeLen >= height || topLen * sumVal + eps < cubeLen) {
            cout << "IMPOSSIBLE.\n";
            continue;
        }
        double lowVal = max(0.0, cubeLen * sumVal - baseLen);
        double highVal = max(0.0, cubeLen * sumVal - topLen);
        double extraVol = height * (highVal * highVal * highVal - lowVal * lowVal * lowVal) / (6.0 * baseLen * sinVal * cosVal);
        double volume = baseLen * baseLen * height / 3.0 + extraVol;
        cout << volume << '\n';
    }
    return 0;
}
