// Square Counting
// UVa ID: 11016
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point &p) const {
        return y < p.y;
    }
} pointArray[200];
int totalPoints;

vector<Point> sweepLines[11000];

int floorDiv(int p, int q) {
    if (q < 0) {
        p = -p;
        q = -q;
    }
    return p >= 0 ? (p / q) : -((-p + q - 1) / q);
}

int ceilDiv(int p, int q) {
    if (q < 0) {
        p = -p;
        q = -q;
    }
    return p >= 0 ? ((p + q - 1) / q) : -((-p) / q);
}

int lineCeil(const Point &A, const Point &B, int x) {
    return A.y + ceilDiv((B.y - A.y) * (x - A.x), B.x - A.x);
}

int lineFloor(const Point &A, const Point &B, int x) {
    return A.y + floorDiv((B.y - A.y) * (x - A.x), B.x - A.x);
}

int main() {
    while (scanf("%d", &totalPoints) == 1 && totalPoints > 0) {
        for (int i = 0; i < totalPoints; i++) scanf("%d %d", &pointArray[i].x, &pointArray[i].y);
        pointArray[totalPoints] = pointArray[0];
        for (int i = 0; i < 11000; i++) sweepLines[i].clear();
        for (int i = 0; i < totalPoints; i++) {
            Point A = pointArray[i], B = pointArray[i + 1];
            if (A.x == B.x) continue;
            if (A.x > B.x) swap(A, B);
            for (int x = A.x; x < B.x; x++) {
                Point e;
                e.x = -1;
                e.y = max(lineCeil(A, B, x), lineCeil(A, B, x + 1));
                sweepLines[x].push_back(e);
                e.x = +1;
                e.y = min(lineFloor(A, B, x), lineFloor(A, B, x + 1));
                sweepLines[x].push_back(e);
            }
        }
        int answer[2] = {0, 0};
        for (int x = 0; x < 10100; x++) {
            vector<Point> &cur = sweepLines[x];
            if (cur.size() == 0) continue;
            sort(cur.begin(), cur.end());
            int y0 = 0, lineCount = 0, insideCount = 0, m = cur.size();
            for (int i = 0; i < m;) {
                if (cur[i].y == y0) {
                    lineCount += cur[i].x;
                    if (cur[i].x == -1) insideCount++;
                    i++;
                    continue;
                }
                int y1 = cur[i].y;
                if (lineCount == 0 && insideCount % 2 == 1) {
                    int color = (x + y0) % 2;
                    int n = y1 - y0;
                    if (n % 2 == 1) {
                        answer[color]++;
                        color ^= 1;
                        n--;
                    }
                    answer[0] += n / 2;
                    answer[1] += n / 2;
                }
                y0 = y1;
            }
        }
        if (answer[0] < answer[1]) swap(answer[0], answer[1]);
        printf("%d %d\n", answer[0], answer[1]);
    }
    return 0;
}
