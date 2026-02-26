// Prime Game
// UVa ID: 11863
// Verdict: Accepted
// Submission Date: 2026-02-26
// UVa Run Time: 0.250s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXSUM = 200005;

int arr[MAXN];
int prefixSum[MAXN];
bool isValidMove[MAXN][MAXN];
bool isPrime[MAXSUM];
int N, K;

void initPrime() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAXSUM; i++) {
        if (isPrime[i]) {
            for (long long j = (long long)i * i; j < MAXSUM; j += i)
                isPrime[j] = false;
        }
    }
}

int getSum(int l, int r) {
    return prefixSum[r] - prefixSum[l - 1];
}

void preprocess() {
    for (int l = 1; l <= N; l++) {
        for (int r = l; r <= N; r++) {
            isValidMove[l][r] = false;
            
            bool hasFortyTwo = false;
            for (int i = l; i <= r; i++) {
                if (arr[i] == 42) {
                    hasFortyTwo = true;
                    break;
                }
            }
            
            if (hasFortyTwo) {
                isValidMove[l][r] = true;
            } else {
                int sum = getSum(l, r);
                if (sum >= 2 && sum < MAXSUM && isPrime[sum])
                    isValidMove[l][r] = true;
            }
        }
    }
}

// win[l][r][p] 表示区间[l,r]，当前玩家还有p次pass可用时的胜负
bool win[MAXN + 2][MAXN + 2][MAXN * 2 + 5];  // 增加边界

void solve() {
    int maxPass = min(2 * K, 2 * N);
    
    // 初始化：长度为0的区间，没有数字可拿，必败
    for (int p = 0; p <= maxPass; p++) {
        for (int i = 1; i <= N + 1; i++) {
            win[i][i - 1][p] = false;  // 空区间，必败
        }
    }
    
    // 按区间长度从小到大DP
    for (int len = 1; len <= N; len++) {
        for (int l = 1; l + len - 1 <= N; l++) {
            int r = l + len - 1;
            
            for (int p = 0; p <= maxPass; p++) {
                bool canWin = false;
                
                // 尝试pass
                if (p > 0 && !win[l][r][p - 1]) {
                    canWin = true;
                } else {
                    // 尝试从左边取
                    for (int i = l; i <= r && !canWin; i++) {
                        if (isValidMove[l][i] && !win[i + 1][r][p])
                            canWin = true;
                    }
                    
                    // 尝试从右边取
                    for (int i = r; i >= l && !canWin; i--) {
                        if (isValidMove[i][r] && !win[l][i - 1][p])
                            canWin = true;
                    }
                }
                
                win[l][r][p] = canWin;
            }
        }
    }
}

int main() {
    initPrime();
    
    int T;
    scanf("%d", &T);
    
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        scanf("%d %d", &N, &K);
        
        for (int i = 1; i <= N; i++) {
            scanf("%d", &arr[i]);
            prefixSum[i] = prefixSum[i - 1] + arr[i];
        }
        
        preprocess();
        solve();
        
        int maxPass = min(2 * K, 2 * N);
        bool sohaWins = win[1][N][maxPass];
        
        printf("Case %d: %s\n", caseNum, sohaWins ? "Soha" : "Tara");
    }
    
    return 0;
}
