// Dick and Jane
// UVa ID: 10257
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int s, p, y, j;
    while (cin >> s >> p >> y >> j)
    {
        int turtle = (j + 12 - y - p) / 3;
        int cat = (j + 12 - s - turtle) / 2;
        int dog = (j + 12 - cat - turtle);
        cout << dog << ' ' << cat << ' ' << turtle << '\n';
    }

    return 0;
}
