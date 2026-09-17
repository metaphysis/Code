#include <bits/stdc++.h>
using namespace std;

struct Road {
    int a, b;
};

Road roads[64];
int roadCount, adj[64][64], degree[64], order[64];
int color[64], colorLimit;

int parseOctal(const string &s) {
    int value = 0;
    for (char c : s) value = value * 8 + c - '0';
    return value;
}

void addRoad(int a, int b) {
    if (a > b) swap(a, b);
    for (int i = 0; i < roadCount; ++i)
        if (roads[i].a == a && roads[i].b == b) return;
    roads[roadCount].a = a;
    roads[roadCount].b = b;
    ++roadCount;
}

int getRoad(int a, int b) {
    if (a > b) swap(a, b);
    for (int i = 0; i < roadCount; ++i)
        if (roads[i].a == a && roads[i].b == b) return i;
    return -1;
}

bool compareDegree(int a, int b) {
    return degree[a] > degree[b];
}

bool canColor(int pos = 0, int maxColor = 0) {
    if (pos == roadCount) return true;
    unsigned long long allMask = ((1ULL << colorLimit) - 1) << 1;
    for (int i = pos; i < roadCount; ++i) {
        int vertex = order[i];
        unsigned long long availableMask = allMask;
        for (int next = 0; next < roadCount; ++next)
            if (adj[vertex][next] && color[next]) availableMask &= ~(1ULL << color[next]);
        if (!availableMask) return false;
    }
    int vertex = order[pos];
    unsigned long long occupiedMask = 0;
    for (int next = 0; next < roadCount; ++next)
        if (adj[vertex][next] && color[next]) occupiedMask |= 1ULL << color[next];
    int maxTry = min(colorLimit, maxColor + 1);
    for (int currentColor = 1; currentColor <= maxTry; ++currentColor) {
        if (occupiedMask & (1ULL << currentColor)) continue;
        color[vertex] = currentColor;
        if (canColor(pos + 1, max(maxColor, currentColor))) return true;
    }
    color[vertex] = 0;
    return false;
}

int solve(int levelCount) {
    for (int i = 0; i < roadCount; ++i) {
        degree[i] = 0;
        for (int j = 0; j < roadCount; ++j) degree[i] += adj[i][j];
        order[i] = i;
    }
    sort(order, order + roadCount, compareDegree);
    int left = 3 + min(2, levelCount - 1), right = roadCount;
    while (left < right) {
        colorLimit = (left + right) / 2;
        memset(color, 0, sizeof(color));
        if (canColor()) right = colorLimit;
        else left = colorLimit + 1;
    }
    return left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string l1Text, l2Text, mText;
    while (cin >> l1Text >> l2Text >> mText) {
        int l1 = parseOctal(l1Text), l2 = parseOctal(l2Text);
        int constraintCount = parseOctal(mText);
        if (l1 > l2) break;
        roadCount = 0;
        for (int level = l1; level <= l2; ++level) {
            for (int house = 0; house < 8; ++house) {
                addRoad(level * 8 + house, level * 8 + (house + 1) % 8);
                if (level < l2) addRoad(level * 8 + house, (level + 1) * 8 + house);
            }
            addRoad(level * 8, level * 8 + 4);
        }
        memset(adj, 0, sizeof(adj));
        for (int i = 0; i < roadCount; ++i) {
            for (int j = i + 1; j < roadCount; ++j) {
                bool shareEndpoint = roads[i].a == roads[j].a || roads[i].a == roads[j].b;
                shareEndpoint = shareEndpoint || roads[i].b == roads[j].a || roads[i].b == roads[j].b;
                if (shareEndpoint) adj[i][j] = adj[j][i] = 1;
            }
        }
        for (int i = 0; i < constraintCount; ++i) {
            string aText, bText, cText, dText;
            cin >> aText >> bText >> cText >> dText;
            int a = parseOctal(aText), b = parseOctal(bText);
            int c = parseOctal(cText), d = parseOctal(dText);
            int firstRoad = getRoad(a, b), secondRoad = getRoad(c, d);
            if (firstRoad < 0 || secondRoad < 0 || firstRoad == secondRoad) continue;
            adj[firstRoad][secondRoad] = adj[secondRoad][firstRoad] = 1;
        }
        cout << oct << solve(l2 - l1 + 1) << '\n' << dec;
    }
    return 0;
}
