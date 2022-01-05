// Extraordinarily Tired Students
// UVa ID: 12108
// Verdict: Accepted
// Submission Date: 2022-01-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct student 
{
    int a, b, c;
    queue<int> schedule;
} s[12];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1, n;
    while (cin >> n)
    {
        if (n == 0) break;
        cout << "Case " << cases++ << ": ";
        student s[12];
        for (int i = 0; i < n; i++)
        {
            cin >> s[i].a >> s[i].b >> s[i].c;
            if (s[i].c <= s[i].a)
            {
                for (int j = s[i].c; j <= s[i].a; j++)
                    s[i].schedule.push(j - 1);
            }
            else
            {
                for (int j = s[i].c; j <= (s[i].a + s[i].b); j++)
                    s[i].schedule.push(j - 1);
                for (int j = 1; j <= s[i].a; j++)
                    s[i].schedule.push(j - 1);
            }
        }
        int minutes = 1;
        set<int> exist;
        while (true)
        {
            int mark = 0, sleeping = 0;
            for (int i = 0; i < n; i++)
            {
                if (s[i].schedule.front() >= s[i].a) sleeping++;
                mark = mark * 10 + s[i].schedule.front();
            }
            if (sleeping == 0) { cout << minutes << '\n'; break; }
            if (exist.count(mark)) { cout << "-1\n"; break; }
            exist.insert(mark);
            for (int i = 0; i < n; i++)
            {
                if (s[i].schedule.size() == 1)
                {
                    if (2 * sleeping > n)
                    {
                        for (int j = s[i].a + 1; j <= (s[i].a + s[i].b); j++)
                            s[i].schedule.push(j - 1);
                    }
                    for (int j = 1; j <= s[i].a; j++)
                        s[i].schedule.push(j - 1);
                }
                s[i].schedule.pop();
            }
            minutes++;
        }
    }
    return 0;
}
