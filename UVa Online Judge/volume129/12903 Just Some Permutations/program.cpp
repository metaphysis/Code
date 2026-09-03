#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxN = 2000;

int fact[maxN + 1], invFact[maxN + 1];
int rook[maxN + 1][maxN + 1];
int trans[4][4][2];
int mat[4][4][maxN + 1], nxt[4][4][maxN + 1];

int modPow(int base, int exp) {
    long long result = 1;
    long long value = base;
    while (exp > 0) {
        if (exp & 1) result = result * value % mod;
        value = value * value % mod;
        exp >>= 1;
    }
    return (int)result;
}

void buildFactorial() {
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++) fact[i] = (long long)fact[i - 1] * i % mod;
    invFact[maxN] = modPow(fact[maxN], mod - 2);
    for (int i = maxN; i >= 1; i--) invFact[i - 1] = (long long)invFact[i] * i % mod;
}

void buildTransition() {
    memset(trans, 0, sizeof(trans));
    for (int from = 0; from < 4; from++) {
        int leftUsed = from & 1;
        int selfUsed = (from >> 1) & 1;
        for (int choice = 0; choice < 4; choice++) {
            int to = 0;
            if (choice == 0) {
                to = selfUsed;
                trans[from][to][0]++;
            } else if (choice == 1) {
                if (leftUsed) continue;
                to = selfUsed;
                trans[from][to][1]++;
            } else if (choice == 2) {
                if (selfUsed) continue;
                to = 1;
                trans[from][to][1]++;
            } else {
                to = selfUsed | 2;
                trans[from][to][1]++;
            }
        }
    }
}

void buildRook() {
    memset(mat, 0, sizeof(mat));
    for (int state = 0; state < 4; state++) mat[state][state][0] = 1;
    for (int length = 1; length <= maxN; length++) {
        memset(nxt, 0, sizeof(nxt));
        for (int from = 0; from < 4; from++) {
            for (int middle = 0; middle < 4; middle++) {
                for (int to = 0; to < 4; to++) {
                    for (int degree = 0; degree < length; degree++) {
                        if (mat[from][middle][degree] == 0) continue;
                        for (int addDegree = 0; addDegree <= 1; addDegree++) {
                            if (trans[middle][to][addDegree] == 0) continue;
                            int newDegree = degree + addDegree;
                            long long value = (long long)mat[from][middle][degree] * trans[middle][to][addDegree] % mod;
                            nxt[from][to][newDegree] += value;
                            if (nxt[from][to][newDegree] >= mod) nxt[from][to][newDegree] -= mod;
                        }
                    }
                }
            }
        }
        memcpy(mat, nxt, sizeof(mat));
        for (int state = 0; state < 4; state++) {
            for (int degree = 0; degree <= length; degree++) {
                rook[length][degree] += mat[state][state][degree];
                if (rook[length][degree] >= mod) rook[length][degree] -= mod;
            }
        }
    }
}

int solveCase(int n, int k) {
    if (k == 0) return fact[n];
    long long answer = 0;
    for (int j = k; j <= n; j++) {
        long long chooseValue = (long long)fact[j - 1] * invFact[k - 1] % mod * invFact[j - k] % mod;
        long long ways = (long long)rook[n][j] * fact[n - j] % mod;
        long long value = chooseValue * ways % mod;
        if ((j - k) & 1) answer -= value;
        else answer += value;
        answer %= mod;
    }
    if (answer < 0) answer += mod;
    return (int)answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildFactorial();
    buildTransition();
    buildRook();
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int n, k;
        cin >> n >> k;
        cout << "Case " << caseId << ": " << solveCase(n, k) << '\n';
    }
    return 0;
}
