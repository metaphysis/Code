// Sum of Powers
// UVa ID: 766
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXK = 21;

long long comb[MAXK + 2][MAXK + 2];

void initComb() {
    for (int i = 0; i <= MAXK + 1; ++i) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; ++j)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
}

// 使用递推计算伯努利数 B_j^+
vector<pair<long long, long long>> bernoulliPlus(int k) {
    vector<pair<long long, long long>> B(k + 1); // 存储分数 num/den
    
    B[0] = {1, 1}; // B0 = 1/1
    
    for (int m = 1; m <= k; ++m) {
        // 计算 sum_{j=0}^{m-1} C(m+1, j) * B_j
        pair<long long, long long> sum = {0, 1};
        for (int j = 0; j < m; ++j) {
            // 分数加法：a/b + c/d = (ad + bc)/(bd)
            long long a = comb[m + 1][j] * B[j].first;
            long long b = B[j].second;
            
            long long newDen = sum.second / __gcd(sum.second, b) * b;
            long long newNum = sum.first * (newDen / sum.second) + a * (newDen / b);
            
            long long g = __gcd(abs(newNum), newDen);
            sum = {newNum / g, newDen / g};
        }
        
        // B_m = -sum / (m+1)
        long long num = -sum.first;
        long long den = sum.second * (m + 1);
        long long g = __gcd(abs(num), den);
        B[m] = {num / g, den / g};
    }
    
    // 修正 B1^+ = +1/2（而不是 -1/2）
    B[1] = {1, 2};
    
    return B;
}

void solve(int k, vector<long long>& coeff, long long& M) {
    vector<pair<long long, long long>> B = bernoulliPlus(k);
    
    // 计算系数
    vector<pair<long long, long long>> polyCoeff(k + 2, {0, 1});
    
    for (int j = 0; j <= k; ++j) {
        long long binomial = comb[k + 1][j];
        
        // 分数乘法：(a/b) * c = (a*c)/b
        long long num = binomial * B[j].first;
        long long den = B[j].second;
        long long g = __gcd(abs(num), den);
        num /= g;
        den /= g;
        
        // 存储到对应位置
        polyCoeff[k + 1 - j] = {num, den};
    }
    
    // 所有系数乘以 (k+1) 得到 a_j/(k+1) 形式
    for (int j = 0; j <= k + 1; ++j) {
        polyCoeff[j].second *= (k + 1);
        long long g = __gcd(abs(polyCoeff[j].first), polyCoeff[j].second);
        if (g != 0) {
            polyCoeff[j].first /= g;
            polyCoeff[j].second /= g;
        }
    }
    
    // 找到所有分母的最小公倍数
    M = 1;
    for (int j = 0; j <= k + 1; ++j) {
        if (polyCoeff[j].first != 0) {
            M = M / __gcd(M, polyCoeff[j].second) * polyCoeff[j].second;
        }
    }
    
    // 转换为整数系数
    coeff.resize(k + 2);
    for (int j = 0; j <= k + 1; ++j) {
        coeff[j] = polyCoeff[j].first * (M / polyCoeff[j].second);
    }
    
    // 约分
    long long g = 0;
    for (int j = 0; j <= k + 1; ++j) {
        g = __gcd(g, abs(coeff[j]));
    }
    g = __gcd(g, M);
    
    if (g > 1) {
        M /= g;
        for (int j = 0; j <= k + 1; ++j) {
            coeff[j] /= g;
        }
    }
    
    // 确保最高次系数为正
    if (coeff[k + 1] < 0) {
        M = -M;
        for (int j = 0; j <= k + 1; ++j) {
            coeff[j] = -coeff[j];
        }
    }
    
    // 确保 M 为正
    if (M < 0) {
        M = -M;
        for (int j = 0; j <= k + 1; ++j) {
            coeff[j] = -coeff[j];
        }
    }
}

int main() {
    initComb();
    int t;
    cin >> t;
    
    for (int tc = 0; tc < t; ++tc) {
        if (tc > 0) cout << endl;
        
        int k;
        cin >> k;
        
        if (k == 0) {
            cout << "1 1 0\n";
            continue;
        }
        
        vector<long long> coeff;
        long long M;
        solve(k, coeff, M);
        
        cout << M;
        for (int j = k + 1; j >= 0; --j) {
            cout << " " << coeff[j];
        }
        cout << endl;
    }
    
    return 0;
}
