// X-Express
// UVa ID: 980
// Verdict: Accepted
// Submission Date: 2017-03-20
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

void getWagons(int &class1, int &class2, int a, int b, int c, int d, int e, int f)
{
    int class1_a = a / 48 + (a % 48 != 0);
    int class1_b = b / 48 + (b % 48 != 0);
    
    class1 = max(class1, class1_a + class1_b);
        
    int class2_c = c / 64 + (c % 64 != 0);
    int class2_d = d / 64 + (d % 64 != 0);
 
    int ee = e;
    ee -= ((class2_c + class2_d) * 64 - (c + d));
    int class2_e = 0;
    if (ee > 0) class2_e = ee / 64 + (ee % 64 != 0);
    
    int ff = f;
    ff -= ((class2_c + class2_d + class2_e) * 64 - (c + d + e));
    ff -= (class1 * 48 - (a + b));
    int class2_f = 0;
    if (ff > 0) class2_f = ff / 64 + (ff % 64 != 0);
    
    class2 = max(class2, class2_c + class2_d + class2_e + class2_f);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int a1, b1, c1, d1, e1, f1;
    int a2, b2, c2, d2, e2, f2;
    int a3, b3, c3, d3, e3, f3;
    
    int cases = 0;
    
    while (cin >> a1 >> b1 >> c1 >> d1 >> e1 >> f1)
    {
        cin >> a2 >> b2 >> c2 >> d2 >> e2 >> f2;
        cin >> a3 >> b3 >> c3 >> d3 >> e3 >> f3;
        
        int class1 = 0, class2 = 0;
        class1 = (a1 + a2) / 48 + ((a1 + a2) % 48 != 0) + (b1 + b2) / 48 + ((b1 + b2) % 48 != 0);
        class1 = max(class1, (a1 + a3) / 48 + ((a1 + a3) % 48 != 0) + (b1 + b3) / 48 + ((b1 + b3) % 48 != 0));
        
        getWagons(class1, class2, a1 + a2, b1 + b2, c1 + c2, d1 + d2, e1 + e2, f1 + f2);
        getWagons(class1, class2, a1 + a3, b1 + b3, c1 + c3, d1 + d3, e1 + e3, f1 + f3);
            
        if (cases++ > 0) cout << '\n';
        cout << class1 << '\n' << class2 << '\n';
    }
    
    return 0;
}
