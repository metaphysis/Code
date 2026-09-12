#include <bits/stdc++.h>
using namespace std;

struct Ball {
    double x, y, r;
    bool dead;
};

bool canHit(const Ball &b, int deg) {
    const double pi = acos(-1.0), eps = 1e-9;
    double rad = deg * pi / 180.0, vx = cos(rad), vy = sin(rad);
    double dot = b.x * vx + b.y * vy, dis;
    if (dot >= 0.0) dis = fabs(b.x * vy - b.y * vx);
    else dis = hypot(b.x, b.y);
    return dis <= b.r + eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, burst = 0;
        cin >> n;
        vector<Ball> balls(n);
        for (int i = 0; i < n; i++) {
            cin >> balls[i].x >> balls[i].y >> balls[i].r;
            balls[i].r /= 2.0;
            balls[i].dead = false;
        }
        for (int deg = 0; deg <= 90; deg += 10) {
            bool fire = false;
            for (int i = 0; i < n; i++)
                if (!balls[i].dead && canHit(balls[i], deg)) fire = true;
            if (fire) {
                cout << "Fire laser at " << deg << " degrees.\n";
                for (int i = 0; i < n; i++) {
                    if (!balls[i].dead && canHit(balls[i], deg)) {
                        balls[i].dead = true;
                        burst++;
                    }
                }
            }
        }
        if (burst == 0) cout << "No balloon burst.\n";
        else if (burst == 1) cout << "1 burst balloon.\n";
        else cout << burst << " burst balloons.\n";
    }
    return 0;
}
