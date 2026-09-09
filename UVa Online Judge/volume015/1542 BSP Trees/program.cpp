#include <bits/stdc++.h>
using namespace std;

struct ObjectInfo {
    int x, z;
    char name;
};

struct PlaneInfo {
    int x1, z1, x2, z2;
};

int getSide(const PlaneInfo &plane, int x, int z) {
    long long dx = plane.x2 - plane.x1, dz = plane.z2 - plane.z1;
    long long cross = dx * (z - plane.z1) - dz * (x - plane.x1);
    return cross > 0 ? 1 : -1;
}

int solve() {
    int n;
    while (cin >> n) {
        vector<ObjectInfo> objects;
        for (int i = 0; i < n; i++) {
            int m;
            cin >> m;
            int x, z;
            cin >> x >> z;
            objects.push_back({x, z, static_cast<char>('A' + i)});
            for (int j = 1; j < m; j++)
                cin >> x >> z;
        }
        int p;
        cin >> p;
        vector<PlaneInfo> planes(p);
        for (int i = 0; i < p; i++)
            cin >> planes[i].x1 >> planes[i].z1 >> planes[i].x2 >> planes[i].z2;
        vector<pair<int, char>> order;
        for (const ObjectInfo &object : objects) {
            int path = 0;
            for (const PlaneInfo &plane : planes) {
                int objectSide = getSide(plane, object.x, object.z);
                int viewerSide = plane.x2 > plane.x1 ? -1 : 1;
                int nearSide = objectSide == viewerSide ? 1 : 0;
                path = path * 2 + nearSide;
            }
            order.push_back({path, object.name});
        }
        sort(order.begin(), order.end());
        for (const pair<int, char> &item : order)
            cout << item.second;
        cout << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
