#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

struct Triangle {
    long double sideLen[3], sideSq[3], angleCos[3], twiceArea;
};

long double getMinCost(const Triangle& tri, const array<int, 3>& weight) {
    long double vertexCost[3], bestCost = numeric_limits<long double>::max();
    for (int i = 0; i < 3; ++i) {
        int j = (i + 1) % 3, k = (i + 2) % 3;
        vertexCost[i] = weight[j] * tri.sideLen[k] + weight[k] * tri.sideLen[j];
        bestCost = min(bestCost, vertexCost[i]);
    }
    if (weight[0] == 0 || weight[1] == 0 || weight[2] == 0) return bestCost;
    for (int i = 0; i < 3; ++i) {
        int j = (i + 1) % 3, k = (i + 2) % 3;
        long double forceSq = 1.0L * weight[j] * weight[j] + 1.0L * weight[k] * weight[k] + 2.0L * weight[j] * weight[k] * tri.angleCos[i];
        if (forceSq <= 1.0L * weight[i] * weight[i]) return vertexCost[i];
    }
    long double waSq = 1.0L * weight[0] * weight[0], wbSq = 1.0L * weight[1] * weight[1], wcSq = 1.0L * weight[2] * weight[2];
    long double rad = 2.0L * (waSq * wbSq + wbSq * wcSq + wcSq * waSq) - waSq * waSq - wbSq * wbSq - wcSq * wcSq;
    long double costSq = (tri.sideSq[0] * (wbSq + wcSq - waSq)
                        + tri.sideSq[1] * (waSq + wcSq - wbSq)
                        + tri.sideSq[2] * (waSq + wbSq - wcSq)) / 2.0L
                        + tri.twiceArea * sqrtl(max(0.0L, rad));
    return sqrtl(max(0.0L, costSq));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(4);
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        Point point[3];
        Triangle tri;
        int capacity[3], goods;
        for (int i = 0; i < 3; ++i) cin >> point[i].x >> point[i].y;
        cin >> capacity[0] >> capacity[1] >> capacity[2] >> goods;
        for (int i = 0; i < 3; ++i) {
            int j = (i + 1) % 3, k = (i + 2) % 3;
            long double dx = point[j].x - point[k].x, dy = point[j].y - point[k].y;
            tri.sideSq[i] = dx * dx + dy * dy;
            tri.sideLen[i] = sqrtl(tri.sideSq[i]);
        }
        for (int i = 0; i < 3; ++i) {
            int j = (i + 1) % 3, k = (i + 2) % 3;
            tri.angleCos[i] = (tri.sideSq[j] + tri.sideSq[k] - tri.sideSq[i]) / (2.0L * tri.sideLen[j] * tri.sideLen[k]);
            tri.angleCos[i] = max(-1.0L, min(1.0L, tri.angleCos[i]));
        }
        tri.twiceArea = fabsl((point[1].x - point[0].x) * (point[2].y - point[0].y) - (point[1].y - point[0].y) * (point[2].x - point[0].x));
        array<int, 3> order = {{0, 1, 2}};
        long double answer = numeric_limits<long double>::max();
        do {
            array<int, 3> weight = {{0, 0, 0}};
            int remaining = goods;
            for (int i = 0; i < 3; ++i) {
                int id = order[i];
                weight[id] = min(capacity[id], remaining);
                remaining -= weight[id];
            }
            answer = min(answer, getMinCost(tri, weight));
        } while (next_permutation(order.begin(), order.end()));
        cout << "Case " << caseId << ": " << 2.0L * answer << '\n';
    }
    return 0;
}
