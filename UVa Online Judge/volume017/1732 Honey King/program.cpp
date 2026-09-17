#include <bits/stdc++.h>
using namespace std;

bool canBuild(long long r, long long minX, long long maxX, long long minY, long long maxY, long long minZ, long long maxZ) {
    long long leftX = maxX - r, rightX = minX + r;
    long long leftY = maxY - r, rightY = minY + r;
    long long leftZ = maxZ - r, rightZ = minZ + r;
    if (leftX > rightX || leftY > rightY || leftZ > rightZ) return false;
    long long leftSum = leftX + leftY, rightSum = rightX + rightY;
    return max(leftSum, leftZ) <= min(rightSum, rightZ);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n;
        cin >> n;
        long long minX = LLONG_MAX, maxX = LLONG_MIN, minY = LLONG_MAX, maxY = LLONG_MIN;
        long long minZ = LLONG_MAX, maxZ = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            long long x, y, z;
            cin >> x >> y;
            z = x + y;
            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y);
            minZ = min(minZ, z);
            maxZ = max(maxZ, z);
        }
        long long left = -1, right = 40000;
        while (right - left > 1) {
            long long mid = (left + right) / 2;
            if (canBuild(mid, minX, maxX, minY, maxY, minZ, maxZ)) right = mid;
            else left = mid;
        }
        long long ans = 3 * right * (right + 1) + 1;
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
