// Standard Deviation
// UVa ID: 10886
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.410s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

unsigned long long seed; // 全局变量，gen() 会修改它

long double gen()
{
    static const long double Z = (long double)1.0 / (1ULL << 32);
    seed >>= 16;
    seed &= (1ULL << 32) - 1;
    seed *= seed;
    return seed * Z;
}

int main()
{
    int caseCount;
    cin >> caseCount;
    cout << fixed << setprecision(5);
    for (int caseId = 1; caseId <= caseCount; ++caseId)
    {
        int n;
        unsigned long long initSeed;
        cin >> n >> initSeed;
        seed = initSeed;
        long double sumX = 0.0, sumX2 = 0.0;
        for (int i = 0; i < n; ++i)
        {
            long double x = gen();
            sumX += x;
            sumX2 += x * x;
        }
        long double mean = sumX / n;
        long double variance = sumX2 / n - mean * mean;
        if (variance < 0) variance = 0; // 处理浮点误差
        long double stdDev = sqrt(variance);
        cout << "Case #" << caseId << ": " << stdDev << endl;
    }
    return 0;
}
