#include <bits/stdc++.h>
using namespace std;

int n, k;
double passProb[55], memo[55][55][2];
bool visited[55][55][2];

double getRightProb(int left, int right, int side) {
    double diff[55], sum = 0.0;
    diff[left] = 1.0;
    for (int i = left; i <= right; i++)
        diff[i + 1] = diff[i] * (1.0 - passProb[i]) / passProb[i];
    for (int i = left; i <= right + 1; i++)
        sum += diff[i];
    if (side == 0)
        return diff[left] / sum;
    return (sum - diff[right + 1]) / sum;
}

double dfs(int left, int right, int side) {
    if (left == 1 && right == n - 1)
        return 1.0;
    if (visited[left][right][side])
        return memo[left][right][side];
    visited[left][right][side] = true;
    double rightProb = getRightProb(left, right, side), result = 0.0;
    if (right < n - 1)
        result += rightProb * dfs(left, right + 1, 1);
    if (left > 1)
        result += (1.0 - rightProb) * dfs(left - 1, right, 0);
    return memo[left][right][side] = result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> k) {
        for (int i = 1; i < n; i++)
            cin >> passProb[i];
        memset(visited, false, sizeof(visited));
        cout << fixed << setprecision(10) << dfs(k, k, 0) << '\n';
    }
    return 0;
}
