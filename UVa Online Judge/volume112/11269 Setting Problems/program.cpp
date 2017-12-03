// Setting Problems
// UVa ID: 11269
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
        if (verify != p.verify) return verify > p.verify;
        return create < p.create;
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
            if (createtime + problems[i].verify > finishtime)
                finishtime = createtime + problems[i].verify;
            finishtime += problems[i].verify;
        }
        cout << max(createtime, finishtime) << '\n';
    }

    return 0;
}
