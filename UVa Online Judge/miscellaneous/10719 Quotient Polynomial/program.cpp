// Quotient Polynomial
// UVa ID: 10719
// Verdict: Accepted
// Submission Date: 2017-03-26
// UVa Run Time: 0.040s
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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int k, number, r;
        vector<int> poly, quotient;
        
        k = stoi(line);
        
        getline(cin, line);
        istringstream iss(line);
        while (iss >> number) poly.push_back(number);

        for (int j = 0; j < poly.size() - 1; j++)
        {
            quotient.push_back(poly[j]);
            poly[j + 1] += poly[j] * k;
        }
        
        r = poly.back();
        
        cout << "q(x):";
        for (int i = 0; i < quotient.size(); i++)
            cout << ' ' << quotient[i];
        cout << '\n';
        cout << "r = " << r << '\n';
        cout << '\n';
    }

    return 0;
}
