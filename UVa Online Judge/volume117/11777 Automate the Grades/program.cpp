// Automate the Grades
// UVa ID: 11777
// Verdict: Accepted
// Submission Date: 2018-01-12
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, term1, term2, finaltest, attendence, test1, test2, test3;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        cin >> term1 >> term2 >> finaltest >> attendence >> test1 >> test2 >> test3;
        if (test1 < test2) swap(test1, test2);
        if (test1 < test3) swap(test1, test3);
        if (test2 < test3) swap(test2, test3);
        int total = 2 * (term1 + term2 + finaltest + attendence) + test1 + test2;
        if (total < 120) cout << "F\n";
        else if (total < 140) cout << "D\n";
        else if (total < 160) cout << "C\n";
        else if (total < 180) cout << "B\n";
        else cout << "A\n";
        
    }
    return 0;
}
