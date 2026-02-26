// Supercomputer Selection The Sequel
// UVa ID: 420
// Verdict: Accepted
// Submission Date: 2026-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

/**
 * 计算四面体 A, B, C, D 的体积
 * 使用行列式公式 V = |det(AB, AC, AD)| / 6
 */
double tetrahedronVolume(double Ax, double Ay, double Az,
                         double Bx, double By, double Bz,
                         double Cx, double Cy, double Cz,
                         double Dx, double Dy, double Dz) {
    double ABx = Bx - Ax, ABy = By - Ay, ABz = Bz - Az;
    double ACx = Cx - Ax, ACy = Cy - Ay, ACz = Cz - Az;
    double ADx = Dx - Ax, ADy = Dy - Ay, ADz = Dz - Az;

    double det = ABx * (ACy * ADz - ACz * ADy)
               - ABy * (ACx * ADz - ACz * ADx)
               + ABz * (ACx * ADy - ACy * ADx);

    return fabs(det) / 6.0;
}

int main() {
    int n, y;
    cin >> n >> y;

    // 存储所有计算机的数据
    // computers[compIdx][year][criterion]
    vector<vector<vector<double>>> computers;
    vector<double> line(n);

    while (true) {
        bool allZero = true;
        for (int i = 0; i < n; i++) {
            cin >> line[i];
            if (line[i] != 0.0) allZero = false;
        }
        if (allZero) break;  // 全 0 行表示输入结束

        // 新的一台计算机开始
        vector<vector<double>> computer;
        computer.push_back(line);
        for (int t = 1; t < y; t++) {
            vector<double> year(n);
            for (int i = 0; i < n; i++) cin >> year[i];
            computer.push_back(year);
        }
        computers.push_back(computer);
    }

    int bestIdx = -1;
    double bestVol = -1.0;

    // 遍历每台计算机
    for (size_t idx = 0; idx < computers.size(); idx++) {
        const auto& comp = computers[idx];
        double totalVol = 0.0;

        // 遍历相邻年份
        for (int t = 0; t < y - 1; t++) {
            // 遍历相邻射线对
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                double theta_i = 2 * PI * i / n;
                double theta_j = 2 * PI * j / n;

                // 年份 t 的三个点
                double Ax = 0.0, Ay = 0.0, Az = t;                 // O_t
                double Bx = comp[t][i] * cos(theta_i);
                double By = comp[t][i] * sin(theta_i);
                double Bz = t;                                     // P_{t,i}
                double Cx = comp[t][j] * cos(theta_j);
                double Cy = comp[t][j] * sin(theta_j);
                double Cz = t;                                     // P_{t,j}

                // 年份 t+1 的三个点
                double A2x = 0.0, A2y = 0.0, A2z = t + 1;         // O_{t+1}
                double B2x = comp[t+1][i] * cos(theta_i);
                double B2y = comp[t+1][i] * sin(theta_i);
                double B2z = t + 1;                               // P_{t+1,i}
                double C2x = comp[t+1][j] * cos(theta_j);
                double C2y = comp[t+1][j] * sin(theta_j);
                double C2z = t + 1;                               // P_{t+1,j}

                // 将三棱柱分解为三个四面体
                double vol1 = tetrahedronVolume(Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, B2x, B2y, B2z);
                double vol2 = tetrahedronVolume(Ax, Ay, Az, Cx, Cy, Cz, B2x, B2y, B2z, C2x, C2y, C2z);
                double vol3 = tetrahedronVolume(Ax, Ay, Az, B2x, B2y, B2z, A2x, A2y, A2z, C2x, C2y, C2z);

                totalVol += vol1 + vol2 + vol3;
            }
        }

        // 更新最优解
        if (totalVol > bestVol + 1e-9) {
            bestVol = totalVol;
            bestIdx = idx;
        }
    }

    // 输出结果，编号从 1 开始
    cout << bestIdx + 1 << " " << fixed << setprecision(2) << bestVol << endl;

    return 0;
}
