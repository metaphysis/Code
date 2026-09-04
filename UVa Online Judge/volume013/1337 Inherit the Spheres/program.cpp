#include <bits/stdc++.h>
using namespace std;

const int maxSphere = 105;
const int maxEvent = 10210;
const long double eps = 1e-12L;

struct Sphere {
    long double x, y, z, r;
};

struct Dsu {
    int parent[maxSphere], rankValue[maxSphere];

    void init(int n) {
        int i;
        for (i = 0; i < n; i++)
            parent[i] = i, rankValue[i] = 0;
    }

    int findRoot(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = findRoot(parent[x]);
    }

    void unite(int x, int y) {
        int rootX, rootY;
        rootX = findRoot(x);
        rootY = findRoot(y);
        if (rootX == rootY)
            return;
        if (rankValue[rootX] < rankValue[rootY])
            swap(rootX, rootY);
        parent[rootY] = rootX;
        if (rankValue[rootX] == rankValue[rootY])
            rankValue[rootX]++;
    }
};

void addEvent(long double events[], int &eventCount, long double value) {
    events[eventCount++] = value;
}

void addPairEvents(const Sphere &first, const Sphere &second, long double events[], int &eventCount) {
    long double dx, dy, dz, centerDis, minRadius, maxRadius, a, circleRadius2, circleRadius, zScale, zRadius, centerZ;
    dx = second.x - first.x;
    dy = second.y - first.y;
    dz = second.z - first.z;
    centerDis = sqrtl(dx * dx + dy * dy + dz * dz);
    minRadius = fabsl(first.r - second.r);
    maxRadius = first.r + second.r;
    if (centerDis <= minRadius + eps || centerDis >= maxRadius - eps || centerDis <= eps)
        return;
    a = (first.r * first.r - second.r * second.r + centerDis * centerDis) / (2.0L * centerDis);
    circleRadius2 = first.r * first.r - a * a;
    if (circleRadius2 < -eps)
        return;
    if (circleRadius2 < 0)
        circleRadius2 = 0;
    circleRadius = sqrtl(circleRadius2);
    zScale = 1.0L - dz * dz / (centerDis * centerDis);
    if (zScale < 0 && zScale > -eps)
        zScale = 0;
    if (zScale < 0)
        return;
    zScale = sqrtl(zScale);
    zRadius = circleRadius * zScale;
    centerZ = first.z + a * dz / centerDis;
    addEvent(events, eventCount, centerZ - zRadius);
    addEvent(events, eventCount, centerZ + zRadius);
}

int getComponents(const Sphere spheres[], int n, long double z) {
    Dsu dsu;
    long double radius[maxSphere], dx, dy, distance2, radiusSum;
    bool active[maxSphere];
    int i, j, componentCount;
    dsu.init(n);
    for (i = 0; i < n; i++) {
        long double height;
        height = spheres[i].r * spheres[i].r - (z - spheres[i].z) * (z - spheres[i].z);
        if (height > 0) {
            active[i] = true;
            radius[i] = sqrtl(height);
        } else {
            active[i] = false;
            radius[i] = 0;
        }
    }
    for (i = 0; i < n; i++) {
        if (!active[i])
            continue;
        for (j = i + 1; j < n; j++) {
            if (!active[j])
                continue;
            dx = spheres[i].x - spheres[j].x;
            dy = spheres[i].y - spheres[j].y;
            distance2 = dx * dx + dy * dy;
            radiusSum = radius[i] + radius[j];
            if (distance2 <= radiusSum * radiusSum)
                dsu.unite(i, j);
        }
    }
    componentCount = 0;
    for (i = 0; i < n; i++)
        if (active[i] && dsu.findRoot(i) == i)
            componentCount++;
    return componentCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        Sphere spheres[maxSphere];
        long double events[maxEvent], temp;
        int eventCount, i, j, intervalCount, previousCount, currentCount;
        string answer;
        eventCount = 0;
        addEvent(events, eventCount, 0.0L);
        addEvent(events, eventCount, 36000.0L);
        for (i = 0; i < n; i++) {
            cin >> temp >> spheres[i].y >> spheres[i].z >> spheres[i].r;
            spheres[i].x = temp;
            addEvent(events, eventCount, spheres[i].z - spheres[i].r);
            addEvent(events, eventCount, spheres[i].z + spheres[i].r);
        }
        for (i = 0; i < n; i++)
            for (j = i + 1; j < n; j++)
                addPairEvents(spheres[i], spheres[j], events, eventCount);
        sort(events, events + eventCount);
        intervalCount = 1;
        for (i = 1; i < eventCount; i++)
            if (fabsl(events[i] - events[intervalCount - 1]) > 1e-10L)
                events[intervalCount++] = events[i];
        previousCount = getComponents(spheres, n, (events[0] + events[1]) / 2.0L);
        for (i = 1; i + 1 < intervalCount; i++) {
            currentCount = getComponents(spheres, n, (events[i] + events[i + 1]) / 2.0L);
            if (currentCount > previousCount)
                answer += '1';
            else if (currentCount < previousCount)
                answer += '0';
            previousCount = currentCount;
        }
        cout << answer.size() << '\n';
        cout << answer << '\n';
    }
    return 0;
}
