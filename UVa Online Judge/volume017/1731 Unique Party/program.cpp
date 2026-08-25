#include <bits/stdc++.h>
using namespace std;

int maxLine(const vector<int> &sum, int cols) {
    vector<int> pref(cols + 1, 0), stk;
    for (int i = 1; i <= cols; i++)
        pref[i] = pref[i - 1] + sum[i - 1];
    for (int i = 0; i <= cols; i++) {
        if (stk.empty() || pref[i] < pref[stk.back()])
            stk.push_back(i);
    }
    int best = 0;
    for (int i = cols; i >= 0; i--) {
        while (!stk.empty() && pref[i] >= pref[stk.back()]) {
            best = max(best, i - stk.back());
            stk.pop_back();
        }
    }
    return best;
}

int maxRect(const vector<vector<int>> &grid, int rows, int cols, int h) {
    int best = 0;
    for (int top = 0; top < rows; top++) {
        vector<int> sum(cols, 0);
        for (int bot = top; bot < rows; bot++) {
            for (int col = 0; col < cols; col++)
                if (grid[bot][col] >= h) sum[col]++;
                else sum[col]--;
            int width = maxLine(sum, cols);
            best = max(best, width * (bot - top + 1));
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    cin >> test;
    for (int tc = 1; tc <= test; tc++) {
        int rows, cols;
        cin >> rows >> cols;
        vector<vector<int>> src(rows, vector<int>(cols));
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                cin >> src[i][j];
        vector<vector<int>> grid;
        if (rows <= cols) {
            grid = src;
        } else {
            grid.assign(cols, vector<int>(rows));
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    grid[j][i] = src[i][j];
            swap(rows, cols);
        }
        int query;
        cin >> query;
        cout << "Case " << tc << ":\n";
        for (int i = 0; i < query; i++) {
            int h;
            cin >> h;
            cout << maxRect(grid, rows, cols, h) << '\n';
        }
    }
    return 0;
}
