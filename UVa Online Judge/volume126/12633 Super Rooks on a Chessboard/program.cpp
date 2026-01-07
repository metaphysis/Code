// Super Rooks on a Chessboard
// UVa ID: 12633
// Verdict: Accepted
// Submission Date: 2026-01-02
// UVa Run Time: 0.180s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> Complex;
const double PI = acos(-1.0);

// 快速傅里叶变换
void $\texttt{FFT}$(vector<Complex>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            Complex w(1);
            for (int j = 0; j < len / 2; ++j) {
                Complex u = a[i + j];
                Complex v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) for (Complex& x : a) x /= n;
}

// 多项式乘法（卷积）
vector<long long> multiply(const vector<int>& a, const vector<int>& b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    vector<Complex> fa(n), fb(n);
    for (int i = 0; i < a.size(); ++i) fa[i] = a[i];
    for (int i = 0; i < b.size(); ++i) fb[i] = b[i];
    $\texttt{FFT}$(fa, false);
    $\texttt{FFT}$(fb, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    $\texttt{FFT}$(fa, true);
    vector<long long> result(n);
    for (int i = 0; i < n; ++i) result[i] = llround(fa[i].real());
    return result;
}

const int MAXRC = 50000;
const int SHIFT = MAXRC; // 对角线差值偏移量，使下标非负

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int R, C, N;
        cin >> R >> C >> N;
        
        // 标记数组
        vector<bool> rowUsed(R + 1, false);
        vector<bool> colUsed(C + 1, false);
        vector<bool> diagUsed(2 * MAXRC + 5, false); // 对角线 d = r-c，偏移后索引 d+SHIFT
        
        for (int i = 0; i < N; ++i) {
            int r, c;
            cin >> r >> c;
            rowUsed[r] = true;
            colUsed[c] = true;
            int d = r - c;
            diagUsed[d + SHIFT] = true;
        }
        
        // 构建多项式 P 和 Q
        // P 对应行：P[r] = 1 如果行 r 未被占用
        // Q 对应列：Q[c] = 1 如果列 c 未被占用
        vector<int> P(R + 1, 0), Q(C + 1, 0);
        for (int r = 1; r <= R; ++r) if (!rowUsed[r]) P[r] = 1;
        for (int c = 1; c <= C; ++c) if (!colUsed[c]) Q[c] = 1;
        
        // 反转 Q 以便卷积计算差值
        vector<int> Qrev(C + 1, 0);
        for (int c = 1; c <= C; ++c) Qrev[c] = Q[C - c + 1];
        
        // 卷积 P * Qrev
        vector<long long> conv = multiply(P, Qrev);
        
        // 计算安全格子数
        long long safeCells = 0;
        int offset = C + 1; // 卷积索引偏移量
        for (int d = -(C - 1); d <= R - 1; ++d) {
            int k = d + offset; // 卷积中的索引
            if (k < 0 || k >= conv.size()) continue;
            if (!diagUsed[d + SHIFT]) {
                safeCells += conv[k];
            }
        }
        
        cout << "Case " << caseNo << ": " << safeCells << "\n";
    }
    
    return 0;
}
