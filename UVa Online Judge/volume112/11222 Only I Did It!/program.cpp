// Only I Did It!
// UVa ID: 11222
// Verdict: Accepted
// Submission Date: 2017-12-31
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int a[10010], b[10010], c[10010];
    int s1, s2, s3;
    int cases, p;
    
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));

        cin >> s1;
        for (int i = 0; i < s1; i++) { cin >> p; a[p] = 1; }
        cin >> s2;
        for (int i = 0; i < s2; i++) { cin >> p; b[p] = 1; }
        cin >> s3;
        for (int i = 0; i < s3; i++) { cin >> p; c[p] = 1; }
        
        s1 = s2 = s3 = 0;
        for (int i = 1; i <= 10000; i++)
        {
            if (a[i] && !b[i] && !c[i]) a[s1++] = i;
            if (b[i] && !a[i] && !c[i]) b[s2++] = i;
            if (c[i] && !a[i] && !b[i]) c[s3++] = i;
        }
        
        cout << "Case #" << cs << ":\n";
        if ((s1 > s2 && s1 > s3) || (s1 == s2 && s1 >= s3) || (s1 == s3 && s1 >= s2))
        {
            cout << "1 " << s1;
            for (int i = 0; i < s1; i++) cout << ' ' << a[i];
            cout << '\n';
        }
        if ((s2 > s1 && s2 > s3) || (s2 == s1 && s2 >= s3) || (s2 == s3 && s2 >= s1))
        {
            cout << "2 " << s2;
            for (int i = 0; i < s2; i++) cout << ' ' << b[i];
            cout << '\n';
        }
        if ((s3 > s1 && s3 > s2) || (s3 == s1 && s3 >= s2) || (s3 == s2 && s3 >= s1))
        {
            cout << "3 " << s3;
            for (int i = 0; i < s3; i++) cout << ' ' << c[i];
            cout << '\n';
        }
    }

    return 0;
}
