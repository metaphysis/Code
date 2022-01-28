// Economic Phone Calls
// UVa ID: 11052
// Verdict: Accepted
// Submission Date: 2022-01-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct entry
{
    int year, month, day, hour, minute, keep;
} call[1010];

int n;

bool ge(entry a, entry b)
{
    if (a.month != b.month) return a.month > b .month;
    if (a.day != b.day) return a.day > b.day;
    if (a.hour != b.hour) return a.hour > b.hour;
    if (a.minute != b.minute) return a.minute > b.minute;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    char colon, mark;
    string number;
    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> call[i].month >> colon;
            cin >> call[i].day >> colon;
            cin >> call[i].hour >> colon;
            cin >> call[i].minute;
            cin >> number >> mark;
            if (mark == '+') call[i].keep = 1;
            else call[i].keep = 0;
        }
        entry last = entry{0, 24, 0, 0, 0, 0};
        int end = 0;
        while (!call[end].keep && end < n) end++;
        for (int i = n - 1; i >= end; i--)
        {
            if (ge(call[i], last)) call[i].year = last.year + 1;
            else call[i].year = last.year;
            last = call[i];
        }
        last = entry{0, 24, 0, 0, 0, 0};
        int cnt = 0;
        for (int i = n - 1; i >= end; i--)
        {
            if (call[i].keep)
            {
                cnt++;
                last = call[i];
            }
            else
            {
                int y = last.year;
                if (ge(call[i - 1], last)) y += 1;
                if (call[i - 1].year != y)
                {
                    cnt++;
                    last = call[i];
                }
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}
