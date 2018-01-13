// Open Source
// UVa ID: 11239
// Verdict: Accepted
// Submission Date: 2018-01-13
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

struct record
{
    string project;
    int number;
    bool operator < (const record &r) const
    {
        if (number != r.number) return number > r.number;
        return project < r.project;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, project;
    
    while (getline(cin, line))
    {
        if (line.front() == '0') break;

        map<string, int> userid;
        map<string, string> signup;
        map<string, int> cnt;

        project = line;
        cnt[project] = 0;

        while (getline(cin, line))
        {
            if (line.front() == '1') break;
            if (isupper(line.front()))
            {
                project = line;
                cnt[project] = 0;
            }
            else
            {
                if (signup.find(line) == signup.end() || project != signup[line])
                    userid[line]++;
                signup[line] = project;
            }
        }

        for (auto user : userid)
            if (user.second == 1)
                cnt[signup[user.first]]++;
        
        vector<record> rs;
        for (auto ct : cnt) rs.push_back(record{ct.first, ct.second});
        sort(rs.begin(), rs.end());
        for (auto r : rs) cout << r.project << ' ' << r.number << '\n';
    }

    return 0;
}
