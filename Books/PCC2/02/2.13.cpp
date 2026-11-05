#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1 << 20), K = 24;

int N, A[MAXN], log2t[MAXN + 1] = {}, st[MAXN][K] = {};

void prepareMin() {
    log2t[1] = 0;
    for (int i = 2; i <= N; i++) log2t[i] = log2t[i / 2] + 1;
    for (int i = 0; i < N; i++) st[i][0] = A[i];
    for (int j = 1; j < K; j++)
        for (int i = 0; i + (1 << j) <= N; i++)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

void prepareSum() {
    log2t[1] = 0;
    for (int i = 2; i <= N; i++) log2t[i] = log2t[i / 2] + 1;
    for (int i = 0; i < N; i++) st[i][0] = A[i];
    for (int j = 1; j < K; j++)
        for (int i = 0; i + (1 << j) <= N; i++)
            st[i][j] = st[i][j - 1] + st[i + (1 << (j - 1))][j - 1];
}

int queryMin(int L, int R) {
    int j = log2t[R - L + 1];
    return min(st[L][j], st[R - (1 << j) + 1][j]);
}

int querySum(int L, int R) {
    int sum = 0;
    for (int j = K - 1; j >= 0; j--)
        if ((1 << j) <= R - L + 1) {
            sum += st[L][j];
            L += 1 << j;
        }
    return sum;
}

// ---------- 暴力 ----------
int bruteMin(int L, int R) {
    int res = A[L];
    for (int i = L + 1; i <= R; i++) res = min(res, A[i]);
    return res;
}

long long bruteSum(int L, int R) {
    long long s = 0;
    for (int i = L; i <= R; i++) s += A[i];
    return s;
}

// ---------- 验证 ----------
void testMin(int T) {
    prepareMin();                       // 关键：先构建 min 表
    bool ok = true;
    for (int t = 0; t < T; t++) {
        int L = rand() % N, R = rand() % N;
        if (L > R) swap(L, R);
        int q = queryMin(L, R);
        int b = bruteMin(L, R);
        if (q != b) {
            cout << "[Min] mismatch [" << L << ", " << R
                 << "] query=" << q << " brute=" << b << '\n';
            ok = false;
            break;
        }
    }
    // 边界：L == R
    for (int i = 0; i < N && ok; i++) {
        if (queryMin(i, i) != A[i]) {
            cout << "[Min] single-element mismatch at " << i << '\n';
            ok = false;
        }
    }
    cout << (ok ? "[Min] all tests passed\n" : "[Min] FAILED\n");
}

void testSum(int T) {
    prepareSum();                       // 关键：重新构建 sum 表
    bool ok = true;
    for (int t = 0; t < T; t++) {
        int L = rand() % N, R = rand() % N;
        if (L > R) swap(L, R);
        int q = querySum(L, R);
        long long b = bruteSum(L, R);
        if (q != b) {
            cout << "[Sum] mismatch [" << L << ", " << R
                 << "] query=" << q << " brute=" << b << '\n';
            ok = false;
            break;
        }
    }
    // 边界：L == R
    for (int i = 0; i < N && ok; i++) {
        if (querySum(i, i) != A[i]) {
            cout << "[Sum] single-element mismatch at " << i << '\n';
            ok = false;
        }
    }
    cout << (ok ? "[Sum] all tests passed\n" : "[Sum] FAILED\n");
}

int main() {
    srand((unsigned)time(NULL));
    N = 2048;
    for (int i = 0; i < N; i++) A[i] = rand() % MAXN;
    testMin(10000);
    testSum(10000);
    return 0;
}