// Equidistance
// UVa ID: 10184
// Verdict: Accepted
// Submission Date: 2019-02-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0), R = 6378.0;

const double EPSILON = 1e-7;

struct point3
{
    double x, y, z;
    point3 (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    point3 operator+(const point3 p) { return point3(x + p.x, y + p.y, z + p.z); }
    point3 operator-(const point3 p) { return point3(x - p.x, y - p.y, z - p.z); }
    point3 operator*(double k) { return point3(x * k, y * k, z * k); }
    point3 operator/(double k) { return point3(x / k, y / k, z / k); }
};

bool zero(double x) { return fabs(x) < EPSILON; }

double norm(point3 p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
}

double dot(point3 a, point3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string city, A, B, M;
    map<string, point3> L;
    double latitude, longtitude;

    while (cin >> city, city != "#")
    {
        cin >> latitude >> longtitude;
        latitude = latitude * PI / 180.0;
        longtitude = longtitude * PI / 180.0;
        point3 p;
        p.x = R * cos(latitude) * cos(longtitude);
        p.y = R * cos(latitude) * sin(longtitude);
        p.z = R * sin(latitude);
        L[city] = p;
    }

    while (cin >> A, A != "#")
    {
        cin >> B >> M;
        cout << M << " is ";
        if (L.find(A) == L.end() || L.find(B) == L.end() || L.find(M) == L.end())
            cout << '?';
        else
        {
            point3 a = L[A], b = L[B], m = L[M];
            point3 ba = a - b, om = m;
            double D = 0;
            if (zero(ba.x) && zero(ba.y) && zero(ba.z)) D = 0;
            else
            {
                double dp = dot(ba, om);
                double alpha = acos(fabs(dp) / norm(ba) / norm(om));
                D = R * (PI / 2.0 - alpha);
            }
            cout << fixed << setprecision(0) << D;
        }
        
        cout << " km off " << A << '/' << B << " equidistance.\n";
    }
    
	return 0;
}
