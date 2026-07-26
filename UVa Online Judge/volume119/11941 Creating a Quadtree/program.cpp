// Creating a Quadtree
// UVa ID: 11941
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163217348

#include <bits/stdc++.h>
using namespace std;

vector<int> parseLine(const string& line) {
    vector<int> nums;
    int num = 0;
    bool inNum = false;
    for (char c : line) {
        if (c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
            inNum = true;
        } else {
            if (inNum) {
                nums.push_back(num);
                num = 0;
                inNum = false;
            }
        }
    }
    if (inNum) nums.push_back(num);
    return nums;
}

bool isPowerOfTwo(int n) { return n > 1 && (n & (n - 1)) == 0; }

void process(int x, int y, int size, const vector<vector<int>>& sum, string& out) {
    int total = size * size;
    int white = sum[y + size - 1][x + size - 1] - sum[y - 1][x + size - 1] - sum[y + size - 1][x - 1] + sum[y - 1][x - 1];
    if (white == 0) { out.push_back('0'); return; }
    if (white == total) { out.push_back('1'); return; }
    out.push_back('*');
    int half = size / 2;
    process(x, y, half, sum, out);
    process(x + half, y, half, sum, out);
    process(x, y + half, half, sum, out);
    process(x + half, y + half, half, sum, out);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    cin.ignore();
    for (int caseIdx = 0; caseIdx < N; ++caseIdx) {
        string line;
        getline(cin, line);
        vector<int> nums = parseLine(line);
        if (nums.empty()) continue;
        int n = nums[0];
        if (!isPowerOfTwo(n)) {
            cout << "Size is invalid\n";
            continue;
        }
        vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
        for (int idx = 1; idx + 3 < (int)nums.size(); idx += 4) {
            int col1 = nums[idx], row1 = nums[idx + 1];
            int col2 = nums[idx + 2], row2 = nums[idx + 3];
            for (int r = row1; r <= row2; ++r)
                for (int c = col1; c <= col2; ++c)
                    mat[r][c] = 1;
        }
        vector<vector<int>> sum(n + 1, vector<int>(n + 1, 0));
        for (int r = 1; r <= n; ++r)
            for (int c = 1; c <= n; ++c)
                sum[r][c] = mat[r][c] + sum[r - 1][c] + sum[r][c - 1] - sum[r - 1][c - 1];
        string out;
        int totalWhite = sum[n][n];
        if (totalWhite == 0 || totalWhite == n * n) {
            cout << "\n";
            continue;
        }
        int half = n / 2;
        process(1, 1, half, sum, out);
        process(1 + half, 1, half, sum, out);
        process(1, 1 + half, half, sum, out);
        process(1 + half, 1 + half, half, sum, out);
        cout << out << '\n';
    }
    return 0;
}
