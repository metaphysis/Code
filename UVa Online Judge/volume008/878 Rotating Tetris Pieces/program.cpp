// Rotating Tetris Pieces
// UVa ID: 878
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.090s

#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> rotateShape(const vector<pair<int,int>>& points, int k) {
    vector<pair<int,int>> res;
    for (auto& p : points) {
        int x = p.first, y = p.second;
        int nx, ny;
        if (k == 0) { nx = x; ny = y; }
        else if (k == 1) { nx = y; ny = -x; }
        else if (k == 2) { nx = -x; ny = -y; }
        else { nx = -y; ny = x; }
        res.emplace_back(nx, ny);
    }
    int minX = res[0].first, minY = res[0].second;
    for (auto& p : res) {
        minX = min(minX, p.first);
        minY = min(minY, p.second);
    }
    for (auto& p : res) {
        p.first -= minX;
        p.second -= minY;
    }
    sort(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<int> answers;

    for (int caseIdx = 0; caseIdx < T; ++caseIdx) {
        vector<pair<int,int>> points;
        string token;
        while (cin >> token) {
            size_t comma = token.find(',');
            if (comma == string::npos) continue;
            int x = stoi(token.substr(0, comma));
            int y = stoi(token.substr(comma + 1));
            if (x == -1 && y == -1) break;
            points.emplace_back(x, y);
        }

        set<vector<pair<int,int>>> uniqueShapes;
        for (int k = 0; k < 4; ++k) {
            uniqueShapes.insert(rotateShape(points, k));
        }
        answers.push_back((int)uniqueShapes.size());
    }

    for (int i = 0; i < (int)answers.size(); ++i) {
        if (i > 0) cout << '\n';
        cout << answers[i] << '\n';
    }

    return 0;
}
