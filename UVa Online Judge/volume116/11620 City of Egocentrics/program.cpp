// City of Egocentrics
// UVa ID: 11620
// Verdict: Accepted
// Submission Date: 2026-06-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<vector<int>> a(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                cin >> a[i][j];

        vector<pair<int,int>> hList, vList, dList, aList;

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                // 计算 H
                int leftSum = 0, rightSum = 0;
                for (int i = 0; i < c; ++i) leftSum += a[r][i];
                for (int i = c + 1; i < N; ++i) rightSum += a[r][i];
                if (leftSum == rightSum) hList.push_back({r, c});

                // 计算 V
                int upSum = 0, downSum = 0;
                for (int i = 0; i < r; ++i) upSum += a[i][c];
                for (int i = r + 1; i < N; ++i) downSum += a[i][c];
                if (upSum == downSum) vList.push_back({r, c});

                // 计算 D（主对角线）
                int dLeftUp = 0, dRightDown = 0;
                for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; --i, --j) dLeftUp += a[i][j];
                for (int i = r + 1, j = c + 1; i < N && j < N; ++i, ++j) dRightDown += a[i][j];
                if (dLeftUp == dRightDown) dList.push_back({r, c});

                // 计算 A（反对角线）
                int aRightUp = 0, aLeftDown = 0;
                for (int i = r - 1, j = c + 1; i >= 0 && j < N; --i, ++j) aRightUp += a[i][j];
                for (int i = r + 1, j = c - 1; i < N && j >= 0; ++i, --j) aLeftDown += a[i][j];
                if (aRightUp == aLeftDown) aList.push_back({r, c});
            }
        }

        // 输出 H
        cout << "H\n";
        for (auto &p : hList) cout << p.first << " " << p.second << "\n";

        // 输出 V
        cout << "V\n";
        for (auto &p : vList) cout << p.first << " " << p.second << "\n";

        // 输出 D
        cout << "D\n";
        for (auto &p : dList) cout << p.first << " " << p.second << "\n";

        // 输出 A
        cout << "A\n";
        for (auto &p : aList) cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
