#include <bits/stdc++.h>

using namespace std;

int dp[11][10][100][100];
int A, B, K, E[16] = {0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int dfs(int idx, int digit, int div, int sum) {
    if (idx == 1) return digit % K == div && digit % K == sum;
    if (~dp[idx][digit][div][sum]) return dp[idx][digit][div][sum];
    int cnt = 0;
    for (int i = 0; i <= 9; i++)
        cnt += dfs(idx - 1, i, (K + (div - digit * E[idx] % K) % K) % K, (K + (sum - digit % K) % K) % K);
    return dp[idx][digit][div][sum] = cnt;
}

int get(int n) {
    string s = to_string(n);
    int div = 0, sum = 0, cnt = 0, L = (int)(s.length());
    for (int i = 0; i < L; i++) {
        int digit = s[i] - '0';
        for (int j = 0; j < digit; j++)
            cnt += dfs(L - i, j, div, sum);
        div = (div - digit * E[L - i] % K) % K;
        sum = (sum - digit % K) % K;
        if (div < 0) div += K;
        if (sum < 0) sum += K;
    }
    return cnt + (!div && !sum);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cin >> A >> B >> K;
        if (K >= 90) { cout << 0 << '\n'; continue; }
        memset(dp, -1, sizeof dp);
        cout << get(B) - get(A - 1) << '\n';
    }
    return 0;
}
