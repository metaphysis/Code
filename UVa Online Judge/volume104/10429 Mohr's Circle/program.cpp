#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double sigmaX, sigmaY, tauXy;
    string direction;
    int elementIndex = 0;
    const double pi = acos(-1.0);
    while (cin >> sigmaX >> sigmaY >> tauXy) {
        if (fabs(tauXy) > 1e-12) cin >> direction;
        double center = (sigmaX + sigmaY) / 2.0;
        double radius = sqrt((sigmaX - sigmaY) * (sigmaX - sigmaY) / 4.0 + tauXy * tauXy);
        double diameterAngle = atan2(2.0 * fabs(tauXy), fabs(sigmaX - sigmaY)) * 180.0 / pi;
        double normalAngle = diameterAngle / 2.0;
        double shearAngle = normalAngle + 45.0;
        double maximumNormalStress = center + radius;
        double minimumNormalStress = center - radius;
        double maximumShearStress = radius;
        if (fabs(maximumNormalStress) < 0.0005) maximumNormalStress = 0.0;
        if (fabs(minimumNormalStress) < 0.0005) minimumNormalStress = 0.0;
        if (fabs(center) < 0.0005) center = 0.0;
        ++elementIndex;
        if (elementIndex > 1) cout << '\n';
        cout << fixed << setprecision(2);
        cout << "Element : " << elementIndex << '\n';
        cout << "Position of maximum normal stresses : " << normalAngle << " deg\n";
        cout << "Maximum normal stresses : " << maximumNormalStress << " MPa and " << minimumNormalStress << " MPa\n\n";
        cout << "Position of maximum shear stresses : " << shearAngle << " deg\n";
        cout << "Maximum shear stress (xy plane) : " << maximumShearStress << " MPa\n";
        cout << "Normal stress at this condition : " << center << " MPa\n";
    }
    return 0;
}
