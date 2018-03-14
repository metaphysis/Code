// Conformity
// UVa ID: 11286
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        long long number;
        map<long long, int> cnt;
        vector<long long> course;
        for (int i = 1; i <= n; i++)
        {
            course.clear();
            for (int j = 1; j <= 5; j++)
            {
                cin >> number;
                course.push_back(number);
            }
            sort(course.begin(), course.end());
            long long id = 0;
            for (auto cs : course) id = id * 1000 + cs;
            cnt[id]++;
        }
        course.clear();
        for (auto ct : cnt) course.push_back(ct.second);
        sort(course.begin(), course.end(), greater<long long>());
        int total = course.front();
        for (int i = 1; i < course.size(); i++)
        {
            if (course[i] != course.front()) break;
            total += course[i];
        }
        cout << total << '\n';
    }

    return 0;
}
