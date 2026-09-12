#include <bits/stdc++.h>
using namespace std;

const long double pi = acosl(-1.0L);
const long double eps = 1e-12L;

struct Point {
    long double x, y, z;
};

struct Object {
    long double height, lat, lon;
    string name;
};

long double toRad(long double degree) {
    return degree * pi / 180.0L;
}

Point getPoint(long double lat, long double lon) {
    long double a = toRad(lat), b = toRad(lon);
    long double c = cosl(a);
    return {c * cosl(b), c * sinl(b), sinl(a)};
}

bool visible(long double radius, long double throneHeight, long double throneLat, long double throneLon, const Object &obj) {
    long double r1 = radius + throneHeight, r2 = radius + obj.height;
    Point p1 = getPoint(throneLat, throneLon), p2 = getPoint(obj.lat, obj.lon);
    long double dot = p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
    dot = max(-1.0L, min(1.0L, dot));
    long double angle = acosl(dot);
    long double view = acosl(radius / r1) + acosl(radius / r2);
    return angle < view - eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long double diameter;
    while (cin >> diameter) {
        long double throneHeight, throneLat, throneLon;
        cin >> throneHeight >> throneLat >> throneLon;
        int n;
        cin >> n;
        vector<string> ans;
        long double radius = diameter / 2.0L;
        for (int i = 0; i < n; i++) {
            Object obj;
            cin >> obj.height >> obj.lat >> obj.lon;
            getline(cin, obj.name);
            if (!obj.name.empty() && obj.name[0] == ' ')
                obj.name.erase(obj.name.begin());
            if (visible(radius, throneHeight, throneLat, throneLon, obj))
                ans.push_back(obj.name);
        }
        sort(ans.begin(), ans.end());
        for (const string &name : ans)
            cout << name << '\n';
        cout << '\n';
    }
    return 0;
}
