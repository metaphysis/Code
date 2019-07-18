#include <bits/stdc++.h>

using namespace std;

struct point3
{
    int x, y, z;
    point3 (int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}
    point3 operator+(const point3 p) { return point3(x + p.x, y + p.y, z + p.z); }
    point3 operator-(const point3 p) { return point3(x - p.x, y - p.y, z - p.z); }
};

point3 cross(point3 a, point3 b)
{
    point3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

int norm(point3 p)
{
    return p.x * p.x + p.y * p.y + p.z * p.z;
}

int dot(point3 a, point3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int signedVolume(point3 p, point3 a, point3 b, point3 c)
{
    return dot(a - p, cross(b - p, c - p));
}

int signedArea(point3 a, point3 b, point3 c)
{
    return norm(cross(b - a, c - a));
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n = rand() % 7 + 4, x, y, z;
        cout << n << '\n';
        vector<point3> ps;
        for (int i = 0; i < n; i++)
        {
            while (true)
            {
                bool flag = true;
                x = rand() % 101, y = rand() % 101, z = rand() % 101;
                if (rand() % 2 == 0) x *= -1;
                if (rand() % 2 == 0) y *= -1;
                if (rand() % 2 == 0) z *= -1;
                for (int j = 0; j < i; j++)
                    if (ps[j].x == x && ps[j].y == y && ps[j].z == z)
                    {
                        flag = false;
                        break;
                    }
                if (i >= 2)
                {
                    for (int j = 0; j < i; j++)
                        for (int k = j + 1; k < i; k++)
                            if (signedArea(ps[j], ps[k], point3(x, y, z)) == 0)
                            {
                                flag = false;
                                j = k = i;
                            }
                }
                if (i >= 3)
                {
                    for (int j = 0; j < i; j++)
                        for (int k = j + 1; k < i; k++)
                            for (int l = k + 1; l < i; l++)
                                if (signedVolume(ps[j], ps[k], ps[l], point3(x, y, z)) == 0)
                                {
                                    flag = false;
                                    j = k = l = i;
                                }
                }
                if (flag)
                {
                    ps.push_back(point3(x, y, z));
                    break;
                }
            }
        }
        for (int i = 0; i < ps.size(); i++)
            cout << ps[i].x << ' ' << ps[i].y << ' ' << ps[i].z << '\n';
    }
    cout << "0\n";
    return 0;
}
