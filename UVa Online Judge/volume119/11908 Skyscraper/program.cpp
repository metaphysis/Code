// Skyscraper
// UVa ID: 11908
// Verdict: Accepted
// Submission Date: 2022-12-07
// UVa Run Time: 0.050s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int T, N, DP[30010];
struct AD {
    int A, B, C;
    bool operator<(AD e) const {
        if (A != e.A) return A < e.A;
        if (B != e.B) return B < e.B;
        return C < e.C;
    }
} ADS[30010];
int dfs(int idx)
{
    if (idx == N) return 0;
    if (~DP[idx]) return DP[idx];
    int r1 = dfs(idx + 1);
    int low = 0, high = N - 1, nxt = N;
    while (low <= high) {
        int middle = (low + high) / 2;
        if (ADS[middle].A >= ADS[idx].A + ADS[idx].B) {
            nxt = middle; high = middle - 1;
        } else low = middle + 1;
    }
    int r2 = ADS[idx].C;
    if (nxt < N) {
        int F = ADS[nxt].A;
        while (nxt < N && ADS[nxt].A == F) {
            r2 = max(r2, ADS[idx].C + dfs(nxt));
            nxt++;
        }
    }
    return DP[idx] = max(r1, r2);
}
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
	    cin >> N;
	    for (int i = 0; i < N; i++) cin >> ADS[i].A >> ADS[i].B >> ADS[i].C;
	    sort(ADS, ADS + N);
	    memset(DP, -1, sizeof DP);
	    cout << dfs(0) << '\n';
	}
	return 0;
}
