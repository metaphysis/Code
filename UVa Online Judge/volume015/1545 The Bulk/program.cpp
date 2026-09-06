#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Face {
    vector<Point> point;
};

unsigned char inside[1000][1000];
unsigned char mark[1000][1000];

void addFace(const Face &face, vector<int> &cells) {
    int minY = 1000, maxY = 0;
    for (const Point &point : face.point) {
        minY = min(minY, point.y);
        maxY = max(maxY, point.y);
    }
    for (int y = minY; y < maxY; y++) {
        double scanY = y + 0.5;
        vector<int> crossX;
        int pointCount = face.point.size();
        for (int i = 0; i < pointCount; i++) {
            Point a = face.point[i], b = face.point[(i + 1) % pointCount];
            if (a.x != b.x) continue;
            int lowY = min(a.y, b.y), highY = max(a.y, b.y);
            if (scanY > lowY && scanY < highY) crossX.push_back(a.x);
        }
        sort(crossX.begin(), crossX.end());
        for (int i = 0; i + 1 < (int)crossX.size(); i += 2) {
            int leftX = crossX[i], rightX = crossX[i + 1];
            for (int x = leftX; x < rightX; x++) {
                int id = x * 1000 + y;
                if (mark[x][y] == 0) cells.push_back(id);
                mark[x][y] ^= 1;
            }
        }
    }
}

int solve() {
    int faceCount;
    cin >> faceCount;
    vector<Face> layers[1001];
    for (int i = 0; i < faceCount; i++) {
        int pointCount;
        cin >> pointCount;
        vector<int> x(pointCount), y(pointCount), z(pointCount);
        for (int j = 0; j < pointCount; j++) cin >> x[j] >> y[j] >> z[j];
        bool horizontal = true;
        for (int j = 1; j < pointCount; j++)
            if (z[j] != z[0]) horizontal = false;
        if (!horizontal) continue;
        Face face;
        for (int j = 0; j < pointCount; j++) face.point.push_back({x[j], y[j]});
        layers[z[0]].push_back(face);
    }
    int lastZ = 0, insideCount = 0, volume = 0;
    for (int z = 0; z <= 1000; z++) {
        if (layers[z].empty()) continue;
        volume += insideCount * (z - lastZ);
        vector<int> cells;
        for (const Face &face : layers[z]) addFace(face, cells);
        for (int id : cells) {
            int x = id / 1000, y = id % 1000;
            if (mark[x][y] != 0) {
                if (inside[x][y] != 0) {
                    inside[x][y] = 0;
                    insideCount--;
                } else {
                    inside[x][y] = 1;
                    insideCount++;
                }
            }
            mark[x][y] = 0;
        }
        lastZ = z;
    }
    volume += insideCount * (1000 - lastZ);
    cout << "The bulk is composed of " << volume << " units.\n";
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) solve();
    return 0;
}
