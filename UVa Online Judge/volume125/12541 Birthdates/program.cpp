// Birthdates
// UVa ID: 12541
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct student
{
    string name;
    int dd, mm, yyyy;
    bool operator < (const student &s) const
    {
        if (yyyy != s.yyyy) return yyyy > s.yyyy;
        if (mm != s.mm) return mm > s.mm;
        return dd > s.dd;
    }
}students[110];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> students[i].name;
            cin >> students[i].dd >> students[i].mm >> students[i].yyyy;
        }
        sort(students, students + n);
        cout << students[0].name << '\n' << students[n - 1].name << '\n';
    }

    return 0;
}
