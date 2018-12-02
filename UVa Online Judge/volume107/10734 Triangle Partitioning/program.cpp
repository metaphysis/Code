// Triangle Partitioning
// UVa ID: 10734
// Verdict: Accepted
// Submission Date: 2018-12-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct triangle
{
    double a, b, c, A, B, C;
    triangle (double a = 0, double b = 0, double c = 0, double A = 0, double B = 0, double C = 0): a(a), b(b), c(c), A(A), B(B), C(C) {}
    bool operator==(const triangle &t) const
    {
        double a1[3] = {A, B, C}, a2[3] = {t.A, t.B, t.C};
        sort(a1, a1 + 3);
        sort(a2, a2 + 3);
        return fabs(A - t.A) < EPSILON && fabs(B - t.B) < EPSILON && fabs(C - t.C) < EPSILON;
    }
};

triangle getTriangle(double a, double b, double c)
{
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    double A = acos((b * b + c * c - a * a) / (2 * b * c));
    double B = acos((a * a + c * c - b * b) / (2 * a * c));
    double C = acos((a * a + b * b - c * c) / (2 * a * b));
    return triangle(a, b, c, A, B, C);
}

pair<triangle, triangle> partition(triangle t)
{
    double M = sqrt(t.a * t.a + t.c * t.c / 4 - t.a * t.c * cos(t.B));
    return pair<triangle, triangle>(getTriangle(t.a, M, t.c / 2), getTriangle(t.b, M, t.c / 2));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    double a, b, c;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        vector<triangle> triangles;
        cin >> a >> b >> c;
        queue<triangle> q;
        q.push(getTriangle(a, b, c));
        while (!q.empty())
        {
            triangle t1 = q.front(); q.pop();
            bool same = false;
            for (auto t2 : triangles)
                if (t1 == t2)
                {
                    same = true;
                    break;
                }
            if (same) continue;
            triangles.push_back(t1);
            pair<triangle, triangle> p2 = partition(t1);
            q.push(p2.first);
            q.push(p2.second);
        }
        cout << "Triangle " << cs << ": " << triangles.size() << '\n';
    }

    return 0;
}
