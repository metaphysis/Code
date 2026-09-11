// Tile Cutting
// UVa ID: 1718
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.430s

#include <bits/stdc++.h>
using namespace std;

struct Complex {
    double x, y;
    Complex(double x = 0, double y = 0) : x(x), y(y) {}
    Complex operator-(const Complex &v) const {
        return Complex(x - v.x, y - v.y);
    }
    Complex operator+(const Complex &v) const {
        return Complex(x + v.x, y + v.y);
    }
    Complex operator*(const Complex &v) const {
        return Complex(x * v.x - y * v.y, x * v.y + y * v.x);
    }
    Complex operator/(const int &v) const {
        return Complex(x / v, y / v);
    }
    double real() {
        return x;
    }
};

template <typename T>
class TOOL_FFT {
public:
    typedef unsigned int UINT32;
#define MAXN (1048576 << 1)
    Complex roots[2][MAXN];
    int preN;
    T pi;
    TOOL_FFT() {
        preN = 0;
        pi = acos(-1);
    }
    int numberOfBitsNeeded(int powerOfTwo) {
        for (int i = 0;; ++i) {
            if (powerOfTwo & (1 << i)) return i;
        }
    }
    inline UINT32 fastReverseBits(UINT32 a, int numBits) {
        a = ((a & 0x55555555U) << 1) | ((a & 0xAAAAAAAAU) >> 1);
        a = ((a & 0x33333333U) << 2) | ((a & 0xCCCCCCCCU) >> 2);
        a = ((a & 0x0F0F0F0FU) << 4) | ((a & 0xF0F0F0F0U) >> 4);
        a = ((a & 0x00FF00FFU) << 8) | ((a & 0xFF00FF00U) >> 8);
        a = ((a & 0x0000FFFFU) << 16) | ((a & 0xFFFF0000U) >> 16);
        return a >> (32 - numBits);
    }
    void fft(bool inverseTransform, vector<Complex> &in, vector<Complex> &out) {
        int numSamples = in.size();
        int numBits = numberOfBitsNeeded(numSamples);
        for (int i = 0; i < numSamples; ++i)
            out[fastReverseBits(i, numBits)] = in[i];
        for (int i = 1; i <= numBits; i++) {
            int blockSize = 1 << i, blockEnd = blockSize >> 1, blockCnt = numSamples / blockSize;
            for (int j = 0; j < numSamples; j += blockSize) {
                Complex *t = roots[inverseTransform];
                for (int k = 0; k < blockEnd; k++, t += blockCnt) {
                    Complex a = (*t) * out[k + j + blockEnd];
                    out[k + j + blockEnd] = out[k + j] - a;
                    out[k + j] = out[k + j] + a;
                }
            }
        }
        if (inverseTransform) {
            for (int i = 0; i < numSamples; ++i)
                out[i] = out[i] / numSamples;
        }
    }
    void prework(int n) {
        if (preN == n) return;
        preN = n;
        roots[0][0] = Complex(1, 0);
        roots[1][0] = Complex(1, 0);
        for (int i = 1; i < n; i++) {
            roots[0][i] = Complex(cos(2 * i * pi / n), sin(2 * i * pi / n));
            roots[1][i] = Complex(cos(2 * i * pi / n), -sin(2 * i * pi / n));
        }
    }
    vector<T> convolution(Complex *a, Complex *b, int n) {
        prework(n);
        vector<Complex> s(a, a + n), d1(n), d2(n), y(n);
        vector<T> ret(n);
        fft(false, s, d1);
        s[0] = b[0];
        for (int i = 1, j = n - 1; i < n; ++i, --j)
            s[i] = b[j];
        fft(false, s, d2);
        for (int i = 0; i < n; ++i)
            y[i] = d1[i] * d2[i];
        fft(true, y, s);
        for (int i = 0; i < n; ++i)
            ret[i] = s[i].real();
        return ret;
    }
};

TOOL_FFT<double> fftTool;

Complex coeffA[MAXN], coeffB[MAXN];
vector<double> convResult;
long long answerArr[1048576];
long long divisorCountArr[1048576] = {};

int main() {
    const int MAX_VAL = 500000;
    int pow2Size;
    for (pow2Size = 1; pow2Size < (MAX_VAL << 1); pow2Size <<= 1);
    for (int i = 1; i <= MAX_VAL; i++) {
        for (int j = i; j <= MAX_VAL; j += i)
            divisorCountArr[j]++;
    }
    memset(coeffA, 0, sizeof(coeffA[0]) * pow2Size);
    memset(coeffB, 0, sizeof(coeffB[0]) * pow2Size);
    for (int i = 1; i <= MAX_VAL; i++) {
        coeffA[i] = Complex(divisorCountArr[i], 0);
        coeffB[pow2Size - i] = Complex(divisorCountArr[i], 0);
    }
    convResult = fftTool.convolution(coeffA, coeffB, pow2Size);
    for (int i = 1; i <= MAX_VAL; i++)
        answerArr[i] = (long long)(convResult[i] + 0.5);
    int testcase, left, right;
    while (scanf("%d", &testcase) == 1) {
        while (testcase--) {
            scanf("%d %d", &left, &right);
            assert(left <= right);
            assert(left >= 1 && right <= MAX_VAL);
            int maxIdx = left;
            for (int i = left; i <= right; i++) {
                if (answerArr[i] > answerArr[maxIdx])
                    maxIdx = i;
            }
            printf("%d %lld\n", maxIdx, answerArr[maxIdx]);
        }
    }
    return 0;
}
