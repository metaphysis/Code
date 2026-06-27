// Image Recognizer
// UVa ID: 546
// Verdict: Accepted
// Submission Date: 2026-06-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    vector<vector<int>> data;
    int rows() const { return (int)data.size(); }
    int cols() const { return data.empty() ? 0 : (int)data[0].size(); }
};

vector<int> parseLine(string &s) {
    vector<int> r;
    istringstream iss(s);
    int v;
    while (iss >> v) r.push_back(v);
    return r;
}

void work(Matrix& I, Matrix& T) {
    int hI = I.rows(), wI = I.cols();
    int hT = T.rows(), wT = T.cols();
    int bestVal = INT_MIN;
    int bestY = -1, bestX = -1;
    for (int y = 0; y <= hI - hT; y++) {
        for (int x = 0; x <= wI - wT; x++) {
            int sum = 0;
            for (int i = 0; i < hT; i++)
                for (int j = 0; j < wT; j++)
                    sum += I.data[y + i][x + j] * T.data[i][j];
            if (sum > bestVal || (sum == bestVal && (y < bestY || (y == bestY && x < bestX)))) bestVal = sum, bestY = y, bestX = x;
        }
    }
    cout << '(' << bestX << ',' << bestY << ")\n";
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    Matrix m[2];
    int hasI = 0, hasT = 0, idx;
    string line;
    while (getline(cin, line)) {
        char c = line.front();
        if (c == 'I' || c == 'F') {
            if (hasI && hasT) {
                work(m[0], m[1]);
                for (int i = 0; i < 2; i++) m[i].data.clear();
                hasI = hasT = 0;
            }
            if (c == 'F') break;
            idx = 0;
            hasI = 1;
        } else if (c == 'T') {
            idx = 1;
            hasT = 1;
        } else m[idx].data.push_back(parseLine(line));
    }
    return 0;
}
