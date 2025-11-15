// Bookcase
// UVa ID: 12099
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.300s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

struct Book {
    int height;
    int thickness;
};

bool compareByHeight(const Book& a, const Book& b) {
    return a.height > b.height;
}

int main() {
    int numTestCases;
    cin >> numTestCases;

    while (numTestCases--) {
        int numBooks;
        cin >> numBooks;

        vector<Book> books(numBooks);
        int totalThickness = 0;

        for (int i = 0; i < numBooks; i++) {
            cin >> books[i].height >> books[i].thickness;
            totalThickness += books[i].thickness;
        }

        sort(books.begin(), books.end(), compareByHeight);

        const int INF = INT_MAX / 2;
        vector<vector<int>> dp(totalThickness + 1, vector<int>(totalThickness + 1, INF));
        dp[0][0] = 0;

        int prefixThickness = books[0].thickness;

        for (int idx = 1; idx < numBooks; idx++) {
            int h = books[idx].height;
            int t = books[idx].thickness;

            for (int j = totalThickness; j >= 0; j--) {
                for (int k = totalThickness; k >= 0; k--) {
                    if (dp[j][k] >= INF) continue;

                    // 放入第二层
                    int newJ = j + t;
                    int newHeightSum = dp[j][k] + (j == 0 ? h : 0);
                    if (newJ <= totalThickness) {
                        dp[newJ][k] = min(dp[newJ][k], newHeightSum);
                    }

                    // 放入第三层
                    int newK = k + t;
                    newHeightSum = dp[j][k] + (k == 0 ? h : 0);
                    if (newK <= totalThickness) {
                        dp[j][newK] = min(dp[j][newK], newHeightSum);
                    }
                }
            }
            prefixThickness += t;
        }

        int minArea = INT_MAX;
        for (int j = 1; j <= totalThickness; j++) {
            for (int k = 1; k <= totalThickness; k++) {
                if (dp[j][k] >= INF) continue;
                int thickness1 = totalThickness - j - k;
                if (thickness1 <= 0) continue;
                int totalHeight = books[0].height + dp[j][k];
                int maxWidth = max(thickness1, max(j, k));
                minArea = min(minArea, totalHeight * maxWidth);
            }
        }

        cout << minArea << endl;
    }

    return 0;
}
