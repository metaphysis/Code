// Partitioning for Fun and Profit
// UVa ID: 10581
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long dp[221][11][221];

long long countPartitions(int m, int n, int minVal) {
  if (n == 0) return m == 0 ? 1 : 0;
  if (m < minVal * n) return 0;
  if (dp[m][n][minVal] != -1) return dp[m][n][minVal];
  long long res = 0;
  for (int x = minVal; x * n <= m; x++)
    res += countPartitions(m - x, n - 1, x);
  return dp[m][n][minVal] = res;
}

void findKthPartition(int m, int n, long long k, int minVal, vector<int>& result) {
  if (n == 0) return;
  for (int x = minVal; x <= m; x++) {
    long long cnt = countPartitions(m - x, n - 1, x);
    if (k > cnt) k -= cnt;
    else {
      result.push_back(x);
      findKthPartition(m - x, n - 1, k, x, result);
      return;
    }
  }
}

int main() {
  memset(dp, -1, sizeof(dp));
  int c; cin >> c;
  while (c--) {
    int m, n; long long k;
    cin >> m >> n >> k;
    vector<int> result;
    findKthPartition(m, n, k, 1, result);
    for (int x : result) cout << x << endl;
  }
  return 0;
}
