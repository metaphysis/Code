// Simple division
// UVa ID: 10407
// Verdict: Accepted
// Submission Date: 2017-03-17
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

int gcd1(int a, int b)
{
    int t;
    while (b != 0) t = a, a = b, b = t % b;
    return a;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    vector<int> numbers;
    int number;

    while (cin >> number, number != 0)
    {
        numbers.push_back(number);
        while (cin >> number, number != 0) numbers.push_back(number);

        sort(numbers.begin(), numbers.end());
        numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

        if (numbers.size() == 1) cout << abs(numbers.front()) << '\n';
        else
        {
            int gcd = numbers[1] - numbers[0];
            for (int i = 2; i < numbers.size(); i++)
                gcd = gcd1(gcd, numbers[i] - numbers[i - 1]); 
            cout << gcd << '\n';
        }

        numbers.clear();
    }

    return 0;
}
