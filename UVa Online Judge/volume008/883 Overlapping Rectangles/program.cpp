// Overlapping Rectangles
// UVa ID: 883
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseCount;
    cin >> caseCount;
    bool firstCase = true;

    while (caseCount--) {
        int NR;
        cin >> NR;
        struct Rect {
            double xmin, xmax, ymin, ymax;
        };
        vector<Rect> rects(NR);
        for (int i = 0; i < NR; ++i) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            rects[i].xmin = min(x1, x2);
            rects[i].xmax = max(x1, x2);
            rects[i].ymin = min(y1, y2);
            rects[i].ymax = max(y1, y2);
        }

        int NL;
        cin >> NL;
        vector<double> yLines(NL);
        for (int i = 0; i < NL; ++i) cin >> yLines[i];

        if (!firstCase) cout << '\n';
        firstCase = false;

        for (double y : yLines) {
            vector<pair<double, int>> events;
            for (const auto &r : rects) {
                if (y > r.ymin && y < r.ymax) {
                    events.emplace_back(r.xmin, 1);
                    events.emplace_back(r.xmax, -1);
                }
            }

            if (events.empty()) {
                cout << "0\n";
                continue;
            }

            sort(events.begin(), events.end());

            int curOD = 0, maxOD = 0;
            double bestLeft = 0.0, bestRight = 0.0;

            curOD += events[0].second;
            double startX = events[0].first;

            for (size_t i = 1; i < events.size(); ++i) {
                double curX = events[i].first;
                if (curOD > maxOD) {
                    maxOD = curOD;
                    bestLeft = startX;
                    bestRight = curX;
                }
                curOD += events[i].second;
                startX = curX;
            }

            cout << maxOD << ' '
                 << fixed << setprecision(2) << bestLeft << ' '
                 << bestRight << '\n';
        }
    }

    return 0;
}
