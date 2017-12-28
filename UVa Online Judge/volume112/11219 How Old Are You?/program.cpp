// How Old Are You?
// UVa ID: 11219
// Verdict: Accepted
// Submission Date: 2017-12-28
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

    int cases;
    cin >> cases;
    
    string date1, date2;
    for (int c = 1; c <= cases; c++)
    {
        cin >> date1 >> date2;

        string cd, cm, cy, bd, bm, by;

        istringstream iss(date1);
        getline(iss, cd, '/');
        getline(iss, cm, '/');
        getline(iss, cy, '/');
        
        iss.clear(); iss.str(date2);
        getline(iss, bd, '/');
        getline(iss, bm, '/');
        getline(iss, by, '/');
        
        int cdi, cmi, cyi, bdi, bmi, byi;
        
        cdi = stoi(cd), cmi = stoi(cm), cyi = stoi(cy);
        bdi = stoi(bd), bmi = stoi(bm), byi = stoi(by);
        
        cout << "Case #" << c << ": ";
        if (cyi < byi || (cyi == byi && cmi < bmi) || (cyi == byi && cmi == bmi && cdi < bdi))
        {
            cout << "Invalid birth date\n";
            continue;
        }
        
        int year = cyi - byi;
        if (cmi < bmi || (cmi == bmi && cdi < bdi)) year--;
        if (year > 130)
        {
            cout << "Check birth date\n";
            continue;
        }
        
        cout << year << '\n';
    }

    return 0;
}
