// Wind of Change
// UVa ID: 10517
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double earthRadius = 6378.0;
const double pi = 2 * acos(0.0);

double toRadians(double degrees) {
    return degrees * pi / 180.0;
}

double toDegrees(double radians) {
    return radians * 180.0 / pi;
}

int main() {
    int numCases;
    cin >> numCases;
    for (int caseNum = 1; caseNum <= numCases; caseNum++) {
        double n, m;
        cin >> n >> m;
        if (n >= 1001.0 || n >= m) {
            cout << "Case " << caseNum << ": Invalid or impossible." << endl;
            continue;
        }
        double ratio = n / m;
        double low = 0.0, high = toRadians(70.0), mid;
        bool found = false;
        for (int iter = 0; iter < 100; iter++) {
            mid = (low + high) / 2.0;
            double left = cos(mid + n / earthRadius);
            double right = ratio * cos(mid);
            if (left > right) low = mid;
            else high = mid;
        }
        double latitude = toDegrees(mid);
        if (latitude < 0.0 || latitude > 70.0) {
            cout << "Case " << caseNum << ": Invalid or impossible." << endl;
            continue;
        }
        int degrees = static_cast<int>(latitude);
        double minutesFloat = (latitude - degrees) * 60.0;
        int minutes = static_cast<int>(minutesFloat);
        double secondsFloat = (minutesFloat - minutes) * 60.0;
        int seconds = static_cast<int>(secondsFloat + 0.5);
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            degrees++;
        }
        cout << "Case " << caseNum << ": " << degrees << " deg " << minutes << " min " << seconds << " sec" << endl;
    }
    return 0;
}
