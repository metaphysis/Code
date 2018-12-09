// A Careful Approach
// UVa ID: 1079
// Verdict: Accepted
// Submission Date: 2018-12-09
// UVa Run Time: 0.300s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct interval
{
    double a, b;
    interval (double a = 0, double b = 0): a(a), b(b) {}
    bool operator<(const interval &x) const
    {
        if (a != x.a) return a < x.a;
        return b < x.b;
    }
} intervals[10];

int n, seq[10];

bool satisfy(double mid)
{
    double last = intervals[seq[0]].a;
    for (int i = 1; i < n; i++)
    {
        if (last + mid > intervals[seq[i]].b) return false;
        if (last + mid <= intervals[seq[i]].a) last = intervals[seq[i]].a;
        else last += mid;
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n)
    {
        if (n == 0) break;
        for (int i = 0; i < n; i++) cin >> intervals[i].a >> intervals[i].b;
        for (int i = 0; i < n; i++) seq[i] = i;
        double maxr = 0;
        do
        {
            double low = 0, high = 1440, mid;
            while (fabs(high - low) > EPSILON)
            {
                mid = (low + high) / 2;
                if (satisfy(mid)) low = mid;
                else high = mid;
            }
            maxr = max(maxr, mid);
        } while (next_permutation(seq, seq + n));
        cout << "Case " << ++cases << ": ";
        int seconds = maxr * 60 + 0.5;
        cout << (seconds / 60) << ':';
        cout << setfill('0') << setw(2) << right << (seconds % 60) << '\n';
    }

    return 0;
}
