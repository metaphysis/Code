// Lots of Sunlight
// UVa ID: 1042
// Verdict: Accepted
// Submission Date: 2026-07-21
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const int TOTAL_SEC = 45600;
const int SUNRISE_SEC = 5 * 3600 + 37 * 60;
const int SUNSET_SEC = 18 * 3600 + 17 * 60;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int complexId = 0;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        ++complexId;
        int w, h;
        cin >> w >> h;
        vector<int> m(n + 1), d(n + 1);
        for (int i = 1; i <= n; ++i) {
            if (i < n) cin >> m[i] >> d[i];
            else cin >> m[i];
        }
        vector<double> east(n + 1), west(n + 1);
        east[1] = 0.0;
        west[1] = w;
        for (int i = 2; i <= n; ++i) {
            east[i] = west[i - 1] + d[i - 1];
            west[i] = east[i] + w;
        }
        cout << "Apartment Complex: " << complexId << "\n";
        while (true) {
            int query;
            cin >> query;
            if (query == 0) break;
            int building = query % 100, floors = query / 100;
            if (building < 1 || building > n || floors < 1 || floors > m[building]) {
                cout << "Apartment " << query << ": Does not exist\n";
                continue;
            }
            double maxRatioE = 0.0;
            double maxRatioW = 0.0;
            for (int j = 1; j < building; ++j) {
                double dist = east[building] - west[j];
                int heightDiff = m[j] * h - (floors - 1) * h;
                if (heightDiff <= 0) continue;
                double ratio = heightDiff / dist;
                if (ratio > maxRatioE) maxRatioE = ratio;
            }
            for (int j = building + 1; j <= n; ++j) {
                double dist = east[j] - west[building];
                int heightDiff = m[j] * h - (floors - 1) * h;
                if (heightDiff <= 0) continue;
                double ratio = heightDiff / dist;
                if (ratio > maxRatioW) maxRatioW = ratio;
            }
            double tStart = (maxRatioE == 0.0) ? 0.0 : (TOTAL_SEC / PI) * atan(maxRatioE);
            double tEnd = (maxRatioW == 0.0) ? (double)TOTAL_SEC : TOTAL_SEC - (TOTAL_SEC / PI) * atan(maxRatioW);
            if (tStart < 0) tStart = 0;
            if (tStart > TOTAL_SEC / 2.0) tStart = TOTAL_SEC / 2.0;
            if (tEnd < TOTAL_SEC / 2.0) tEnd = TOTAL_SEC / 2.0;
            if (tEnd > TOTAL_SEC) tEnd = TOTAL_SEC;
            auto formatTime = [](double t) {
                int total = (int)floor(t + 1e-7) + SUNRISE_SEC;
                int hh = total / 3600, mm = (total % 3600) / 60, ss = total % 60;
                cout << setw(2) << setfill('0') << hh << ':'
                     << setw(2) << setfill('0') << mm << ':'
                     << setw(2) << setfill('0') << ss;
            };
            cout << "Apartment " << query << ": ";
            formatTime(tStart);
            cout << " - ";
            formatTime(tEnd);
            cout << "\n";
        }
    }
    return 0;
}
