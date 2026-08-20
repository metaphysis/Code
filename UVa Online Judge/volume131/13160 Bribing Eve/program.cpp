// Bribing Eve
// UVa ID: 13160
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.190s

#include <bits/stdc++.h>
using namespace std;

struct Point { int dx, dy; };
struct Event { double angle; int leftPos, leftNeg; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        int a, b;
        cin >> a >> b;
        vector<Point> pts;
        int zeroCnt = 0;
        for (int i = 1; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            int dx = x - a, dy = y - b;
            if (dx == 0 && dy == 0) ++zeroCnt;
            else pts.push_back({dx, dy});
        }
        int M = pts.size();
        vector<int> initSign(M);
        int initPos = 0;
        int pos0 = 0, zero0 = 0;
        int posPi2 = 0, zeroPi2 = 0;
        for (int i = 0; i < M; ++i) {
            int dx = pts[i].dx, dy = pts[i].dy;
            if (dx > 0) ++pos0;
            else if (dx == 0 && dy != 0) ++zero0;
            if (dy > 0) ++posPi2;
            else if (dy == 0 && dx != 0) ++zeroPi2;
            bool positive;
            if (dx > 0) positive = true;
            else if (dx == 0 && dy > 0) positive = true;
            else positive = false;
            initSign[i] = positive ? 1 : -1;
            if (positive) ++initPos;
        }
        vector<Event> events;
        const double eps = 1e-12;
        for (int i = 0; i < M; ++i) {
            int dx = pts[i].dx, dy = pts[i].dy;
            if (dx == 0 || dy == 0 || dx * dy >= 0) continue;
            double angle;
            double vx1 = -dy, vy1 = dx;
            if (vx1 >= 0 && vy1 >= 0) angle = atan2(vy1, vx1);
            else {
                double vx2 = dy, vy2 = -dx;
                angle = atan2(vy2, vx2);
            }
            if (angle <= 0 || angle >= M_PI / 2) continue;
            int leftSign = initSign[i];
            if (leftSign == 1) events.push_back({angle, 1, 0});
            else events.push_back({angle, 0, 1});
        }
        sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
            return e1.angle < e2.angle;
        });
        vector<Event> merged;
        for (auto &ev : events) {
            if (merged.empty() || fabs(ev.angle - merged.back().angle) > eps)
                merged.push_back(ev);
            else {
                merged.back().leftPos += ev.leftPos;
                merged.back().leftNeg += ev.leftNeg;
            }
        }
        int best = pos0;
        int worst = pos0 + zero0 + zeroCnt;
        int curPos = initPos;
        for (auto &ev : merged) {
            best = min(best, curPos);
            worst = max(worst, curPos + zeroCnt);
            int leftPos = ev.leftPos;
            int leftNeg = ev.leftNeg;
            int posTheta = curPos - leftPos;
            int zeroTheta = leftPos + leftNeg;
            best = min(best, posTheta);
            worst = max(worst, posTheta + zeroTheta + zeroCnt);
            curPos = curPos - leftPos + leftNeg;
        }
        best = min(best, curPos);
        worst = max(worst, curPos + zeroCnt);
        best = min(best, posPi2);
        worst = max(worst, posPi2 + zeroPi2 + zeroCnt);
        cout << (best + 1) << " " << (worst + 1) << "\n";
    }
    return 0;
}
