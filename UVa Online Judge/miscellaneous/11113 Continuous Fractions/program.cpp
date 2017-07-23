// Continuous Fractions
// UVa ID: 11113
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    unsigned long long p, q;
    while (cin >> p >> q, q > 0)
    {
        cout << "Case " << ++cases << ":\n";
        cout << p << " / " << q << '\n';

        vector<unsigned long long> digits;
        digits.push_back(p / q);
        p %= q;
        
        while (p > 0)
        {
            swap(p, q);
            digits.push_back(p / q);
            p %= q;
        }
        digits.back() -= 1;

        vector<int> widths;
        widths.push_back(1);
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            int nextLength = widths.front() + to_string(digits[i]).length() + 3;
            widths.insert(widths.begin(), nextLength);
        }
        widths.pop_back();
        
        int totalWidth = widths.front();
        for (int i = 0; i < widths.size(); i++)
        {
            int upWidth = widths[i + 1];
            int leftSpaces = totalWidth - upWidth;
            for (int i = 0; i < leftSpaces; i++) cout << '.';

            int leftPart = upWidth / 2 - 1 + (upWidth % 2);
            for (int i = 0; i < leftPart; i++) cout << '.';
            cout << '1';
            int rightPart = upWidth / 2;
            for (int i = 0; i < rightPart; i++) cout << '.';
            cout << '\n';
            
            leftSpaces = totalWidth - widths[i];
            for (int i = 0; i < leftSpaces; i++) cout << '.';
            cout << to_string(digits[i]) << ".+.";
            for (int i = 0; i < upWidth; i++) cout << '-';
            cout << '\n';
        }
        
        for (int i = 0; i < totalWidth - 1; i++) cout << '.';
        cout << "1";

        cout << '\n';
    }

    return 0;
}
