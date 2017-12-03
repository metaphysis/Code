// Setting Problems
// UVa ID: 11269
// Verdict: Accepted
// Submission Date: 2017-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

struct problem
{
    int create, verify;
    bool operator<(const problem &p) const
    {
        int t1 = 0;
        if (p.create > verify) t1 = create + p.create + p.verify;
        else t1 = create + verify + p.verify;

        int t2 = 0;
        if (create > p.verify) t2 = p.create + create + verify;
        else t2 = p.create + p.verify + verify;

        return t1 < t2;
    }
} problems[25];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++) cin >> problems[i].create;
        for (int i = 0; i < n; i++) cin >> problems[i].verify;
        
        sort(problems, problems + n);
        
        int createtime = 0, finishtime = 0;
        for (int i = 0; i < n; i++)
        {
            createtime += problems[i].create;
            if (createtime > finishtime) finishtime = createtime;
            finishtime += problems[i].verify;
        }
        cout << max(createtime, finishtime) << '\n';
    }

    return 0;
}
