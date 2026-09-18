#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-5;

struct Point {
    double x, y;
};

int getLevel(char note) {
    string notes = "CDEFGAB";
    return notes.find(note);
}

bool checkAngle(const vector<Point> &points, int angle, char firstNote, char lastNote, string &answer) {
    double rad = angle * pi / 180.0, cosValue = cos(rad), sinValue = sin(rad);
    vector<Point> restored;
    for (const Point &point : points) {
        double x = point.x * cosValue + point.y * sinValue;
        double y = -point.x * sinValue + point.y * cosValue;
        restored.push_back({x, y});
    }
    sort(restored.begin(), restored.end(), [](const Point &a, const Point &b) {
        return a.x < b.x;
    });
    int n = restored.size(), firstLevel = getLevel(firstNote), lastLevel = getLevel(lastNote);
    double levelDist = (restored[n - 1].y - restored[0].y) / (lastLevel - firstLevel);
    if (levelDist < 0.5 - eps || levelDist > 2.5 + eps) return false;
    string notes = "CDEFGAB", score;
    for (int i = 0; i < n; i++) {
        double realLevel = firstLevel + (restored[i].y - restored[0].y) / levelDist;
        int level = lround(realLevel);
        if (level < 0 || level > 6 || fabs(realLevel - level) > eps) return false;
        score += notes[level];
    }
    if (score.front() != firstNote || score.back() != lastNote) return false;
    for (int i = 1; i < n; i++) {
        double horizontalDist = restored[i].x - restored[i - 1].x;
        if (horizontalDist < 2.0 * levelDist - eps || horizontalDist > 10.0 * levelDist + eps) return false;
    }
    answer = score;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNumber = 0;
    while (cin >> n && n) {
        char firstNote, lastNote;
        cin >> firstNote >> lastNote;
        vector<Point> points(n);
        for (Point &point : points) cin >> point.x >> point.y;
        string answer;
        for (int angle = -60; angle <= 60; angle++)
            if (checkAngle(points, angle, firstNote, lastNote, answer)) break;
        cout << "Case " << ++caseNumber << ": " << answer << '\n';
    }
    return 0;
}
