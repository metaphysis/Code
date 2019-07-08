// All Souls Night
// UVa ID: 11769
// Verdict: Accepted
// Submission Date: 2019-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point3
{
    int x, y, z;
    point3 (int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}
    point3 operator+(const point3 p) { return point3(x + p.x, y + p.y, z + p.z); }
    point3 operator-(const point3 p) { return point3(x - p.x, y - p.y, z - p.z); }
};

double norm(point3 p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
}

point3 cross(point3 a, point3 b)
{
    point3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

int dot(point3 a, point3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int signedVolume(point3 a, point3 b, point3 c)
{
    return dot(a, cross(b, c));
}

double signedArea(point3 a, point3 b, point3 c)
{
    return norm(cross(b - a, c - a));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    point3 souls[32];

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> souls[i].x >> souls[i].y >> souls[i].z;
        double area = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                {
                    int left = 0, right = 0;
                    for (int l = 0; l < n; l++)
                    {
                        if (l == i || l == j || l == k) continue;
                        int t = signedVolume(souls[i] - souls[l], souls[j] - souls[l], souls[k] - souls[l]);
                        if (t > 0) left++;
                        if (t < 0) right++;
                        if (left * right > 0) break;
                    }
                    if (left == 0 || right == 0)
                    {
                        area += norm(cross(souls[j] - souls[i], souls[k] - souls[i]));
                        cout << souls[i].x << ' ' << souls[i].y << ' ' << souls[i].z << '\n';
                        cout << souls[j].x << ' ' << souls[j].y << ' ' << souls[j].z << '\n';
                        cout << souls[k].x << ' ' << souls[k].y << ' ' << souls[k].z << '\n';
                        cout << '\n';
                    }
                }
        cout << "Case " << ++cases << ": " << fixed << setprecision(2) << area / 2 << '\n';
    }

    return 0;
}
