#include <bits/stdc++.h>
using namespace std;

bool isSide(char ch) {
    return ch == '+' || ch == '-' || ch == '|';
}

bool isOk(char ch) {
    return ch == '#' || ch == '.';
}

int solve(vector<string> &grid, int len, int wid) {
    vector<vector<bool> > use(len, vector<bool>(wid, true));
    int ans = 0;
    for (int col = 0; col < wid; col++) {
        use[0][col] = false;
        use[len - 1][col] = false;
    }
    for (int row = 0; row < len; row++) {
        use[row][0] = false;
        use[row][wid - 1] = false;
    }
    for (int row = 1; row < len - 1; row++) {
        for (int col = 1; col < wid - 1; col++) {
            bool bad = false;
            if (col < wid - 2 && grid[row][col] == '.' && grid[row][col + 1] == '.' && use[row][col] && use[row][col + 1]) {
                if (isSide(grid[row][col - 1])) bad = true;
                if (isSide(grid[row][col + 2])) bad = true;
                if (!bad) {
                    if (isOk(grid[row - 1][col]) && isOk(grid[row - 1][col + 1]) && grid[row + 1][col] == '-' && grid[row + 1][col + 1] == '-') {
                        ans++;
                        use[row][col - 1] = false;
                        use[row][col] = false;
                        use[row][col + 1] = false;
                        use[row][col + 2] = false;
                    } else if (isOk(grid[row + 1][col]) && isOk(grid[row + 1][col + 1]) && grid[row - 1][col] == '-' && grid[row - 1][col + 1] == '-') {
                        ans++;
                        use[row][col - 1] = false;
                        use[row][col] = false;
                        use[row][col + 1] = false;
                        use[row][col + 2] = false;
                    }
                }
            }
            bad = false;
            if (row < len - 2 && grid[row][col] == '.' && grid[row + 1][col] == '.' && use[row][col] && use[row + 1][col]) {
                if (isSide(grid[row - 1][col])) bad = true;
                if (isSide(grid[row + 2][col])) bad = true;
                if (!bad) {
                    if (isOk(grid[row][col - 1]) && isOk(grid[row + 1][col - 1]) && grid[row][col + 1] == '|' && grid[row + 1][col + 1] == '|') {
                        ans++;
                        use[row - 1][col] = false;
                        use[row][col] = false;
                        use[row + 1][col] = false;
                        use[row + 2][col] = false;
                    } else if (isOk(grid[row][col + 1]) && isOk(grid[row + 1][col + 1]) && grid[row][col - 1] == '|' && grid[row + 1][col - 1] == '|') {
                        ans++;
                        use[row - 1][col] = false;
                        use[row][col] = false;
                        use[row + 1][col] = false;
                        use[row + 2][col] = false;
                    }
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test, len, wid, need;
    cin >> test;
    while (test--) {
        cin >> len >> wid >> need;
        vector<string> grid(len);
        for (int row = 0; row < len; row++) cin >> grid[row];
        int cnt = solve(grid, len, wid);
        if (cnt >= need) cout << "LOCATION OKAY\n";
        else cout << "CHOOSE ANOTHER LOCATION\n";
    }
    return 0;
}
