#include <bits/stdc++.h>
using namespace std;

const int maxN = 100, maxM = 100;
double dp[maxN + 1][maxM + 1][maxN + 1];

void initialize() {
    for (int l = 0; l <= maxM; l++) dp[1][l][0] = 1.0;
    for (int r = 2; r <= maxN; r++) {
        for (int l = 0; l <= maxM; l++) {
            double total = r - 1 + l;
            for (int j = 0; j < r; j++) {
                double answer = 0.0;
                if (j > 0) answer += (r - 1.0) / total * dp[r - 1][l][j - 1];
                if (l > 0) {
                    int nextJ = j == 0 ? r - 1 : j - 1;
                    answer += l / total * dp[r][l - 1][nextJ];
                }
                dp[r][l][j] = answer;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initialize();
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << fixed << setprecision(3) << dp[n][m][k] * 100.0 << '\n';
    }
    return 0;
}
