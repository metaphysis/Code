// Great Circle
// UVa ID: 10809
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-12;

// 解析 "度,分方向" 返回带符号十进制度数
double parseCoord(const string& s) {
    size_t comma = s.find(',');
    int deg = stoi(s.substr(0, comma));
    int minute = stoi(s.substr(comma + 1, s.length() - comma - 2));
    char dir = s.back();
    double val = deg + minute / 60.0;
    if (dir == 'S' || dir == 'W') val = -val;
    return val;
}

// 格式化纬度（弧度）为 "度,分N/S"
string formatLatitude(double latRad) {
    double latDeg = latRad * 180.0 / PI;
    if (latDeg < 0 && latDeg > -1e-9) latDeg = 0;
    if (latDeg > 90) latDeg = 90;
    if (latDeg < -90) latDeg = -90;
    char dir = (latDeg >= 0) ? 'N' : 'S';
    double absDeg = fabs(latDeg);
    int totalMinutes = (int)round(absDeg * 60.0);
    if (totalMinutes == 60) { totalMinutes = 0; absDeg += 1; }
    int degOut = totalMinutes / 60;
    int minuteOut = totalMinutes % 60;
    return to_string(degOut) + "," + to_string(minuteOut) + dir;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    while (N--) {
        string lat1Str, lon1Str, lat2Str, lon2Str;
        cin >> lat1Str >> lon1Str >> lat2Str >> lon2Str;

        double lat1 = parseCoord(lat1Str) * PI / 180.0;
        double lon1 = parseCoord(lon1Str) * PI / 180.0;
        double lat2 = parseCoord(lat2Str) * PI / 180.0;
        double lon2 = parseCoord(lon2Str) * PI / 180.0;

        // 直角坐标
        double x1 = cos(lat1)*cos(lon1), y1 = cos(lat1)*sin(lon1), z1 = sin(lat1);
        double x2 = cos(lat2)*cos(lon2), y2 = cos(lat2)*sin(lon2), z2 = sin(lat2);

        double dot = x1*x2 + y1*y2 + z1*z2;

        // 重合点
        if (fabs(dot - 1.0) < EPS) {
            cout << formatLatitude(lat1) << "\n";
            continue;
        }

        // 对跖点（dot ≈ -1）
        if (fabs(dot + 1.0) < EPS) {
            // 检查是否为北极和南极
            bool northPole = (fabs(lat1 - PI/2) < EPS || fabs(lat2 - PI/2) < EPS);
            bool southPole = (fabs(lat1 + PI/2) < EPS || fabs(lat2 + PI/2) < EPS);
            if (northPole && southPole) {
                cout << "90,0N\n";  // 唯一答案
            } else {
                cout << "undefined\n";
            }
            continue;
        }

        // 一般情况：计算最短弧上的最大纬度
        double nx = y1*z2 - z1*y2;
        double ny = z1*x2 - x1*z2;
        double nz = x1*y2 - y1*x2;

        // 基向量 u = A, v = (n × A) / |n × A|
        double vx = ny*z1 - nz*y1;
        double vy = nz*x1 - nx*z1;
        double vz = nx*y1 - ny*x1;
        double normV = sqrt(vx*vx + vy*vy + vz*vz);
        if (normV < EPS) { cout << "undefined\n"; continue; }
        vx /= normV; vy /= normV; vz /= normV;

        double uz = z1, v_z = vz;
        double d = acos(dot);  // 最短弧角度

        // 端点
        double sinPhi0 = uz;
        double sinPhiD = uz*cos(d) + v_z*sin(d);
        double maxSin = max(sinPhi0, sinPhiD);

        // 内部极值
        double R = sqrt(uz*uz + v_z*v_z);
        double alpha = atan2(v_z, uz);
        for (int k = -1; k <= 1; ++k) {
            double theta = alpha + 2.0*PI*k;
            if (theta >= 0 && theta <= d) {
                maxSin = max(maxSin, R);
                break;
            }
        }

        maxSin = min(maxSin, 1.0);
        maxSin = max(maxSin, -1.0);
        double maxLatRad = asin(maxSin);
        cout << formatLatitude(maxLatRad) << "\n";
    }
    return 0;
}
