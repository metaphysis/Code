// Printer Queue
// UVa ID: 12100
// Verdict: Accepted
// Submission Date: 2018-01-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct job
{
    int id, priority;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m, pty;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        queue<job> jobs;
        priority_queue<int, vector<int>, less<int>> priorities;

        cin >> n >> m;
        for (int i = 0; i < n; i++)
        {
            cin >> pty;
            jobs.push(job{i, pty});
            priorities.push(pty);
        }
       
        int minutes = 0;
        while (true)
        {
            job jb = jobs.front(); jobs.pop();
            if (jb.priority == priorities.top())
            {
                minutes++;
                priorities.pop();
                if (jb.id == m) break;
            }
            else jobs.push(jb);
        }
        cout << minutes << '\n';
    }

    return 0;
}
