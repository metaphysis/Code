#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

long double getWidth(const vector<Point>& polygon, long double y) {
    vector<long double> intersections;
    long double width = 0.0L;
    int vertexCount, intersectionCount, i;
    Point firstPoint, secondPoint;
    vertexCount = static_cast<int>(polygon.size());
    for (i = 0; i < vertexCount; i++) {
        firstPoint = polygon[i];
        secondPoint = polygon[(i + 1) % vertexCount];
        if ((firstPoint.y < y && y < secondPoint.y) || (secondPoint.y < y && y < firstPoint.y)) intersections.push_back(firstPoint.x + (secondPoint.x - firstPoint.x) * (y - firstPoint.y) / (secondPoint.y - firstPoint.y));
    }
    sort(intersections.begin(), intersections.end());
    intersectionCount = static_cast<int>(intersections.size());
    for (i = 0; i + 1 < intersectionCount; i += 2) width += intersections[i + 1] - intersections[i];
    return width;
}

long double calculateDamage(const vector<Point>& monster, const vector<Point>& projectile) {
    vector<long double> levels;
    long double damage = 0.0L, lower, upper, height, firstY, secondY, firstMonsterWidth, secondMonsterWidth, firstProjectileWidth, secondProjectileWidth, monsterLower, monsterUpper, projectileLower, projectileUpper, monsterChange, projectileChange;
    int levelCount, i;
    for (const Point& point : monster) levels.push_back(point.y);
    for (const Point& point : projectile) levels.push_back(point.y);
    sort(levels.begin(), levels.end());
    levels.erase(unique(levels.begin(), levels.end()), levels.end());
    levelCount = static_cast<int>(levels.size());
    for (i = 0; i + 1 < levelCount; i++) {
        lower = levels[i];
        upper = levels[i + 1];
        height = upper - lower;
        firstY = lower + height / 3.0L;
        secondY = lower + 2.0L * height / 3.0L;
        firstMonsterWidth = getWidth(monster, firstY);
        secondMonsterWidth = getWidth(monster, secondY);
        firstProjectileWidth = getWidth(projectile, firstY);
        secondProjectileWidth = getWidth(projectile, secondY);
        monsterLower = 2.0L * firstMonsterWidth - secondMonsterWidth;
        monsterUpper = 2.0L * secondMonsterWidth - firstMonsterWidth;
        projectileLower = 2.0L * firstProjectileWidth - secondProjectileWidth;
        projectileUpper = 2.0L * secondProjectileWidth - firstProjectileWidth;
        monsterChange = monsterUpper - monsterLower;
        projectileChange = projectileUpper - projectileLower;
        damage += height * (monsterLower * projectileLower + (monsterLower * projectileChange + projectileLower * monsterChange) / 2.0L + monsterChange * projectileChange / 3.0L);
    }
    if (damage < 0.0L) damage = 0.0L;
    return damage;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseId, monsterCount, projectileCount, vertexIndex;
    cin >> testCount;
    cout << fixed << setprecision(6);
    for (caseId = 1; caseId <= testCount; caseId++) {
        vector<Point> monster, projectile;
        cin >> monsterCount;
        monster.resize(monsterCount);
        for (vertexIndex = 0; vertexIndex < monsterCount; vertexIndex++) cin >> monster[vertexIndex].x >> monster[vertexIndex].y;
        cin >> projectileCount;
        projectile.resize(projectileCount);
        for (vertexIndex = 0; vertexIndex < projectileCount; vertexIndex++) cin >> projectile[vertexIndex].x >> projectile[vertexIndex].y;
        cout << "Case " << caseId << ": " << calculateDamage(monster, projectile) << '\n';
    }
    return 0;
}
