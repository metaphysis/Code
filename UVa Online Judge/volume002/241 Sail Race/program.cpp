// Sail Race
// UVa ID: 241
// Verdict: Accepted
// Submission Date: 2026-05-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 角度转弧度
double toRadians(double deg) { return deg * M_PI / 180.0; }
// 弧度转角度
double toDegrees(double rad) { return rad * 180.0 / M_PI; }

// 将角度归一化到 [0, 360)
double normalizeAngle(double a) {
    a = fmod(a, 360.0);
    if (a < 0) a += 360.0;
    return a;
}

// 计算两个角度之间的最小夹角 (0~180)
double angleDiff(double a, double b) {
    double d = fabs(a - b);
    if (d > 180) d = 360 - d;
    return d;
}

// 根据与风夹角计算船速
double boatSpeed(double ws, double off, double pa, double pr,
                 double ra, double rr, double da, double dr) {
    if (off < pa - 1e-9) return 0;          // 不可航行（理论上不会发生）
    if (off < ra) return pr * ws;
    if (off < da) return rr * ws;
    return dr * ws;
}

int main() {
    int raceNum = 0;
    double windDir, windSpeed, tackPenalty;
    int n;

    while (cin >> windDir >> windSpeed >> tackPenalty >> n) {
        if (windDir == 0 && windSpeed == 0 && tackPenalty == 0 && n == 0) break;
        raceNum++;

        // 读取第二行：6 个航行性能参数
        double pointAngle, pointRatio, reachAngle, reachRatio, downwindAngle, downwindRatio;
        cin >> pointAngle >> pointRatio >> reachAngle >> reachRatio >> downwindAngle >> downwindRatio;

        // 读取 n 个标位信息
        vector<tuple<string, double, double>> marks(n);
        for (int i = 0; i < n; i++) {
            cin >> get<0>(marks[i]) >> get<1>(marks[i]) >> get<2>(marks[i]);
        }

        // 预先计算 layout 总长度（各段直线距离之和）
        double layoutLen = 0;
        for (int i = 0; i < n - 1; i++) {
            auto [name1, x1, y1] = marks[i];
            auto [name2, x2, y2] = marks[i + 1];
            double dx = x2 - x1, dy = y2 - y1;
            layoutLen += sqrt(dx * dx + dy * dy);
        }

        // 输出 race 标题和 layout 长度
        cout << "Race " << raceNum << " has " << n - 1 << " legs\n";
        cout << "The race layout is " << fixed << setprecision(2) << layoutLen << " nm long\n\n";

        double totalDist = 0, totalTime = 0;
        int totalSegments = 0, tackSeq = 0;

        // 处理每个 Leg（两个相邻标位之间）
        for (int i = 0; i < n - 1; i++) {
            auto [name1, x1, y1] = marks[i];
            auto [name2, x2, y2] = marks[i + 1];
            double dx = x2 - x1, dy = y2 - y1;
            double directDist = sqrt(dx * dx + dy * dy);
            double targetDir = normalizeAngle(toDegrees(atan2(dx, dy)));

            cout << "Leg " << i + 1 << " from Mark " << name1 << " to " << name2
                 << ": direction = " << fixed << setprecision(1) << targetDir
                 << ", distance = " << fixed << setprecision(2) << directDist << " nm\n";

            double alpha = angleDiff(targetDir, windDir);

            // 情况1：可以直接航行
            if (alpha >= pointAngle) {
                double speed = boatSpeed(windSpeed, alpha, pointAngle, pointRatio,
                                         reachAngle, reachRatio, downwindAngle, downwindRatio);
                totalDist += directDist;
                totalTime += directDist / speed;
                totalSegments++;
                cout << "Tack " << ++tackSeq << ": speed = " << fixed << setprecision(1) << speed
                     << ", direction = " << fixed << setprecision(1) << targetDir
                     << ", distance = " << fixed << setprecision(2) << directDist << " nm\n";
            }
            // 情况2：必须换舷，两段航行
            else {
                double phi1 = normalizeAngle(windDir + pointAngle);
                double phi2 = normalizeAngle(windDir - pointAngle);

                double rad1 = toRadians(phi1), rad2 = toRadians(phi2);
                double sin1 = sin(rad1), cos1 = cos(rad1);
                double sin2 = sin(rad2), cos2 = cos(rad2);

                // 解线性方程组求两段距离 a, b
                double det = sin1 * cos2 - sin2 * cos1;
                double a = (dx * cos2 - dy * sin2) / det;
                double b = (dy * sin1 - dx * cos1) / det;

                // 两段速度相同（因为与风夹角 = pointAngle）
                double speed = boatSpeed(windSpeed, pointAngle, pointAngle, pointRatio,
                                         reachAngle, reachRatio, downwindAngle, downwindRatio);

                totalDist += a + b;
                totalTime += a / speed + b / speed;
                totalSegments += 2;

                cout << "Tack " << ++tackSeq << ": speed = " << fixed << setprecision(1) << speed
                     << ", direction = " << fixed << setprecision(1) << phi1
                     << ", distance = " << fixed << setprecision(2) << a << " nm\n";
                cout << "Tack " << ++tackSeq << ": speed = " << fixed << setprecision(1) << speed
                     << ", direction = " << fixed << setprecision(1) << phi2
                     << ", distance = " << fixed << setprecision(2) << b << " nm\n";
            }
            cout << '\n';
        }

        // 罚时计算：总航段数 - 1
        int penaltyCount = totalSegments - 1;
        double totalPenalty = penaltyCount * tackPenalty;

        cout << "Race " << raceNum << " was " << fixed << setprecision(2) << totalDist
             << " nm long with " << totalSegments << " tack legs\n";
        cout << "Estimated Race Duration is " << fixed << setprecision(2) << totalTime + totalPenalty
             << " hours with " << fixed << setprecision(2) << totalPenalty << " hours of Tack Penalty\n\n";
    }

    return 0;
}
