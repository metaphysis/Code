// Finding Black Circles
// UVa ID: 12559
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

struct Point {
    int x, y;
};

struct Circle {
    Point center;
    int radius;
    bool operator<(const Circle &other) const {
        return make_pair(make_pair(radius, center.x), center.y) < make_pair(make_pair(other.radius, other.center.x), other.center.y);
    }
    bool operator==(const Circle &other) const {
        return radius == other.radius && center.x == other.center.x && center.y == other.center.y;
    }
};

int height, width;
char grid[100][101];

bool checkCircle(const Circle &c) {
    int cnt = 0;
    for (int t = 0; t < 1000; t++) {
        double theta = 2 * PI * t / 1000;
        int x = (int)(c.center.x + c.radius * cos(theta) + 0.5);
        int y = (int)(c.center.y + c.radius * sin(theta) + 0.5);
        if (0 <= y && y < height && 0 <= x && x < width && grid[y][x] == '1') cnt++;
    }
    return cnt > 900;
}

void solveCase() {
    scanf("%d%d", &width, &height);
    for (int i = 0; i < height; i++) scanf("%s", grid[i]);
    vector<Point> horizSegments, vertSegments;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == '1') {
                int x = j;
                while (j < width && grid[i][j] == '1' || j + 1 < width && grid[i][j + 1] == '1') j++;
                if (j - x >= 5) horizSegments.push_back({x, i});
            }
        }
    }
    for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
            if (grid[i][j] == '1') {
                int y = i;
                while (i < height && grid[i][j] == '1' || i + 1 < height && grid[i + 1][j] == '1') i++;
                if (i - y >= 5) vertSegments.push_back({j, y});
            }
        }
    }
    vector<Circle> circles;
    for (int j = 0; j < (int)horizSegments.size(); j++) {
        for (int i = 0; i < j; i++) {
            int d1 = abs(horizSegments[j].y - horizSegments[i].y);
            if (d1 % 2 != 0 || d1 < 10) continue;
            int r1 = d1 / 2;
            for (int l = 0; l < (int)vertSegments.size(); l++) {
                for (int k = 0; k < l; k++) {
                    int d2 = abs(vertSegments[l].x - vertSegments[k].x);
                    if (d2 % 2 != 0 || d2 < 10) continue;
                    int r2 = d2 / 2;
                    if (r1 == r2) {
                        int y = min(horizSegments[i].y, horizSegments[j].y) + r1;
                        int x = min(vertSegments[k].x, vertSegments[l].x) + r2;
                        circles.push_back({ {x, y}, r1 });
                    }
                }
            }
        }
    }
    sort(circles.begin(), circles.end());
    circles.erase(unique(circles.begin(), circles.end()), circles.end());
    for (int i = 0; i < (int)circles.size(); i++) {
        if (!checkCircle(circles[i])) {
            circles.erase(circles.begin() + i);
            i--;
        }
    }
    printf("%d", (int)circles.size());
    for (int i = 0; i < (int)circles.size(); i++) {
        printf(" (%d,%d,%d)", circles[i].radius, circles[i].center.x, circles[i].center.y);
    }
    puts("");
}

int main() {
    int T;
    scanf("%d ", &T);
    for (int cas = 1; cas <= T; cas++) {
        printf("Case %d: ", cas);
        solveCase();
    }
    return 0;
}
