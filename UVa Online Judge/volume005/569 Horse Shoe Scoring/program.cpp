// Horse Shoe Scoring
// UVa ID: 569
// Verdict: Wrong Answer
// Submission Date: 2018-05-10
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double ROOT2 = sqrt(2);

struct point
{
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y) {}
    point operator+(point i) { return point(x + i.x, y + i.y); };
    point operator-(point i) { return point(x - i.x, y - i.y); };
    point operator*(double k) { return point(x * k, y * k); };
    point operator/(double k) { return point(x / k, y / k); };
    double distTo(point p) { return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2)); }
};

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
double cp(point a, point b, point c) { return cross(b - a, c - a); }

point rotatePI(point p)
{
    return point(-p.y, p.x);
}

bool isRinger(double d)
{
    return d < 9.0;
}

bool isToucher(double d)
{
    return d <= 11.0;
}

bool isSwinger(double d)
{
    return d <= 10.0 * ROOT2 + 1.0;
}

int getScore(point A, point B)
{
    point C = A + rotatePI(B - A), P = point(0, 0);

    if (cp(A, C, P) < 0)
    {
        // Is Ringer?
        if (isRinger(P.distTo(A))) return 5;
        // Is Toucher?
        if (isToucher(P.distTo(A))) return 2;
        // Is Swinger?
        if (isSwinger(P.distTo(B))) return 1;
    }
    else
    {
        // Is Swinger?
        if (isSwinger(P.distTo(B))) return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cout << "Turn Score" << '\n';

    int cases = 0;
    double x1, y1, x2, y2;
    point A, B;
    while (cin >> x1 >> y1 >> x2 >> y2)
    {
        A = point(x1, y1), B = point(x2, y2);
        int scores = getScore(A, B);
        for (int i = 2; i <= 4; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            A = point(x1, y1), B = point(x2, y2);
            scores += getScore(A, B);
        }
        cout << setw(4) << right << ++cases;
        cout << ' ';
        cout << setw(5) << right << scores << '\n';
    }

    return 0;
}
