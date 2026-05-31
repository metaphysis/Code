// Normal Distribution
// UVa ID: 10431
// Verdict: Accepted
// Submission Date: 2026-05-31
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double P = 0.2316419;
const double B1 = 0.319381530, B2 = -0.356563782, B3 = 1.781477937;
const double B4 = -1.821255978, B5 = 1.330274429;

// 计算标准正态分布的右尾概率 Q(z)（从 z 到 +∞）
double calculateQ(double z) {
    double t = 1.0 / (1.0 + P * fabs(z));
    double fz = exp(-z * z / 2.0) / sqrt(2.0 * PI);
    double poly = t * (B1 + t * (B2 + t * (B3 + t * (B4 + t * B5))));
    double q = fz * poly;
    return q;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int dataSetNum = 0;
    int N;
    while (cin >> N) {
        if (N == 0) break;
        if (dataSetNum) cout << '\n';
        dataSetNum++;
        vector<double> data(N);
        double sum = 0.0, sumSq = 0.0;
        for (int i = 0; i < N; i++) {
            cin >> data[i];
            sum += data[i];
        }
        double mean = sum / N;
        for (int i = 0; i < N; i++) {
            double diff = data[i] - mean;
            sumSq += diff * diff;
        }
        double stdDev = sqrt(sumSq / (N - 1));
        int Q;
        cin >> Q;
        vector<double> queries(Q);
        for (int i = 0; i < Q; i++) cin >> queries[i];
        cout << fixed << setprecision(4);
        cout << "Data Set #" << dataSetNum << "\nMean = " << mean << "\nStandard Deviation = " << stdDev << '\n';
        for (int i = 0; i < Q; i++) {
            double z = (queries[i] - mean) / stdDev;
            double qVal = calculateQ(z);
            double pVal = 1.0 - qVal;
            double tVal = qVal * N;
            cout << "P(z) = " << pVal << ", Q(z) = " << qVal << ", T = " << tVal << '\n';
        }
    }
    return 0;
}
