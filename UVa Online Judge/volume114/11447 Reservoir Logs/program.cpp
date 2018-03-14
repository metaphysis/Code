// Reservoir Logs
// UVa ID: 11447
// Verdict: Accepted
// Submission Date: 2017-12-22
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

typedef vector<point> polygon;

double area(polygon &pg)
{
    double apg = 0.0;
    int n = pg.size();
    if (n < 3) return apg;
    for (int i = 0, j = 1; i < n; i++, j = (i + 1) % n)
        apg += (pg[i].x * pg[j].y - pg[j].x * pg[i].y);
    return fabs(apg / 2.0);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        polygon pg;

        int n;
        cin >> n;
        
        double xi, yi, W, percent, consumed, falling;
        for (int i = 0; i < n; i++)
        {
            cin >> xi >> yi;
            pg.push_back(point(xi, yi));
        }

        cin >> W >> percent >> consumed >> falling;

        double V = area(pg) * W;
        double finalV = 0;

        if (V * percent / 100.0 < consumed) 
        {
            cout << "Lack of water. ";
            finalV = falling;
        }
        else
        {
            finalV = V * percent / 100.0 - consumed + falling;
            
        }

        if (finalV > V) cout << "Excess of water. Final percentage: 100%\n";
        else
        {
            int finvalP = finalV / V * 100.0;
            cout << "Final percentage: " << finvalP << "%\n";
        }
    }

    return 0;
}
