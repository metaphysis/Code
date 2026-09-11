// Cube Killer
// UVa ID: 12612
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y, z;
};

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        scanf("%d", &N);
        vector<Point> pts(N);
        long long minX = LLONG_MAX, maxX = LLONG_MIN;
        long long minY = LLONG_MAX, maxY = LLONG_MIN;
        long long minZ = LLONG_MAX, maxZ = LLONG_MIN;
        for (int i = 0; i < N; ++i) {
            scanf("%lld %lld %lld", &pts[i].x, &pts[i].y, &pts[i].z);
            minX = min(minX, pts[i].x); maxX = max(maxX, pts[i].x);
            minY = min(minY, pts[i].y); maxY = max(maxY, pts[i].y);
            minZ = min(minZ, pts[i].z); maxZ = max(maxZ, pts[i].z);
        }
        long long R = max(maxX - minX, max(maxY - minY, maxZ - minZ));
        vector<int> pointMask(N, 0);
        bool ok = true;
        for (int i = 0; i < N; ++i) {
            int m = 0;
            if (pts[i].x == minX) m |= 1;   // X 下界面
            if (pts[i].x == maxX) m |= 2;   // X 上界面
            if (pts[i].y == minY) m |= 4;   // Y 下界面
            if (pts[i].y == maxY) m |= 8;   // Y 上界面
            if (pts[i].z == minZ) m |= 16;  // Z 下界面
            if (pts[i].z == maxZ) m |= 32;  // Z 上界面
            pointMask[i] = m;
            if (m == 0) ok = false;
        }
        if (!ok) {
            printf("Case %d: -1\n", caseNo);
            continue;
        }
        vector<vector<int>> choices(3);
        if (maxX - minX == R) {
            choices[0].push_back(1 | 2);
        } else {
            choices[0].push_back(0);
            choices[0].push_back(1);
            choices[0].push_back(2);
        }
        if (maxY - minY == R) {
            choices[1].push_back(4 | 8);
        } else {
            choices[1].push_back(0);
            choices[1].push_back(4);
            choices[1].push_back(8);
        }
        if (maxZ - minZ == R) {
            choices[2].push_back(16 | 32);
        } else {
            choices[2].push_back(0);
            choices[2].push_back(16);
            choices[2].push_back(32);
        }
        bool found = false;
        for (int c0 : choices[0]) {
            for (int c1 : choices[1]) {
                for (int c2 : choices[2]) {
                    int selected = c0 | c1 | c2;
                    bool coverAll = true;
                    for (int m : pointMask) {
                        if ((m & selected) == 0) {
                            coverAll = false;
                            break;
                        }
                    }
                    if (coverAll) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }
        if (found) printf("Case %d: %lld\n", caseNo, R);
        else printf("Case %d: -1\n", caseNo);
    }
    return 0;
}
