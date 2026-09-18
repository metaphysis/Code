#include <bits/stdc++.h>
using namespace std;

long double getUnderArea(long double a, long double l, long double r) {
    return a * a * (r * r * r - l * l * l) / 6.0L;
}

long double getBandArea(long double a, long double l, long double r, long long k, long double pi) {
    long double p = 2.0L * pi, width = r - l;
    return a * a * (p * (r * r - l * l) / 2.0L + p * p * (static_cast<long double>(k) + 0.5L) * width);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int spiralCount;
    cin >> spiralCount;
    long double pi = acosl(-1.0L), period = 2.0L * pi;
    for (int caseId = 1; caseId <= spiralCount; caseId++) {
        long double a;
        int n;
        cin >> a >> n;
        vector<long double> rays(n);
        for (int i = 0; i < n; i++) cin >> rays[i];
        sort(rays.begin(), rays.end());
        int m;
        cin >> m;
        bool unbounded = false;
        long double totalArea = 0.0L;
        set<pair<int, long long>> used;
        for (int i = 0; i < m; i++) {
            long double radius, theta;
            cin >> radius >> theta;
            if (n == 0) {
                unbounded = true;
            } else {
                int sector = static_cast<int>(upper_bound(rays.begin(), rays.end(), theta) - rays.begin()) - 1;
                if (sector < 0) sector = n - 1;
                bool wrapping = sector == n - 1;
                long double l = rays[sector], r = wrapping ? rays[0] + period : rays[sector + 1], phi = theta;
                if (wrapping && theta < rays[0]) phi += period;
                long double layerValue = (radius / a - phi) / period;
                long long regionId;
                if (!wrapping) {
                    if (layerValue < 0.0L) regionId = 0;
                    else regionId = static_cast<long long>(floorl(layerValue)) + 1;
                } else {
                    if (layerValue >= 0.0L) {
                        regionId = static_cast<long long>(floorl(layerValue)) + 2;
                    } else if (phi >= period && radius / a < phi - period) {
                        regionId = 0;
                    } else {
                        regionId = 1;
                    }
                }
                pair<int, long long> region = {sector, regionId};
                if (used.insert(region).second) {
                    if (!wrapping) {
                        if (regionId == 0) totalArea += getUnderArea(a, l, r);
                        else totalArea += getBandArea(a, l, r, regionId - 1, pi);
                    } else {
                        long double innerArea = getUnderArea(a, 0.0L, rays[0]);
                        if (regionId == 0) {
                            totalArea += innerArea;
                        } else if (regionId == 1) {
                            totalArea += getUnderArea(a, l, r) - innerArea;
                        } else {
                            totalArea += getBandArea(a, l, r, regionId - 2, pi);
                        }
                    }
                }
            }
        }
        cout << "Spiral " << caseId << ": ";
        if (unbounded) cout << "-1\n";
        else cout << fixed << setprecision(4) << totalArea / 10.0L << " liters\n";
    }
    return 0;
}
