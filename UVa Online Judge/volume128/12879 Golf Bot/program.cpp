// Golf Bot
// UVa ID: 12879
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.900s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>

using namespace std;

typedef complex<double> Complex;

const double PI = acos(-1.0);

// 快速傅里叶变换
void fft(vector<Complex>& a, bool invert) {
    int n = a.size();
    // 位逆序置换
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    
    // 迭代FFT
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            Complex w(1);
            for (int j = 0; j < len / 2; j++) {
                Complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    
    // 逆变换需要除以n
    if (invert) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

// 多项式乘法（卷积）
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    // 扩展为2的幂次
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    
    // 正向FFT
    fft(fa, false);
    fft(fb, false);
    
    // 点值相乘
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    
    // 逆向FFT
    fft(fa, true);
    
    // 取实部并四舍五入
    vector<int> res(n);
    for (int i = 0; i < n; i++) res[i] = round(fa[i].real());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N) {
        vector<int> k(N);
        int max_dist = 0;
        
        // 读取可用的击球距离
        for (int i = 0; i < N; i++) {
            cin >> k[i];
            if (k[i] > max_dist) max_dist = k[i];
        }

        // 创建标记数组，has[x] = 1 表示距离x可用
        int size = 1;
        while (size <= 2 * max_dist) size <<= 1;
        vector<int> has(size, 0);
        for (int i = 0; i < N; i++) {
            has[k[i]] = 1;
        }

        // 计算两数之和的计数
        vector<int> sum_count = multiply(has, has);

        // 读取洞的距离并统计可完成的洞数
        cin >> M;
        int ans = 0;
        for (int i = 0; i < M; i++) {
            int d;
            cin >> d;
            // 检查一次击球或两次击球是否可能
            if (d < has.size() && has[d]) {
                ans++;
            } else if (d < sum_count.size() && sum_count[d] > 0) {
                ans++;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
