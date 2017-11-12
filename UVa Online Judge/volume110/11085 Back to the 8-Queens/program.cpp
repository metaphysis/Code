// Back to the 8-Queens
// UVa ID: 11085
// Verdict: Accepted
// Submission Date: 2017-11-12
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

const int MAXV = 8;

int column[MAXV] = {0}, used[MAXV] = {0}, solutions = 0;
vector<vector<int>> rows;

bool safe()
{
    for (int i = 0; i < MAXV; i++)
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(column[i] - column[j]))
                return false;
    return true;
}

void backtrack(int depth)
{
    if (depth == MAXV && safe()) {
        vector<int> r(MAXV);
        for (int i = 0; i < MAXV; i++)
            r[column[i]] = i + 1;
        rows.push_back(r);
        return;
    }

    for (int i = 0; i < MAXV; i++) if (!used[i]) {
        used[i] = 1, column[depth] = i;
        backtrack(depth + 1);
        used[i] = 0;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    backtrack(0);
    
    int cases = 0;
    
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        
        int number;
        vector<int> r;
        while (iss >> number) r.push_back(number);
        
        int least = 0x3fffffff;
        for (int i = 0; i < rows.size(); i++)
        {
            int sum = 0;
            for (int j = 0; j < r.size(); j++)
                if (rows[i][j] != r[j])
                    sum++;
            least = min(least, sum);
        }
        
        cout << "Case " << ++cases << ": " << least << '\n';
    }
    return 0;
}
