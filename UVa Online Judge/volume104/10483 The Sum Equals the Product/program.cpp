// The Sum Equals the Product
// UVa ID: 10483
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.050s
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

struct product
{
    int sum, a, b, c;
    bool operator<(const product &x)
    {
        if (sum != x.sum) return sum < x.sum;
        if (a != x.a) return a < x.a;
        if (b != x.b) return b < x.b;
        return c < x.c;
    }
} solutions[400];

int cnt = 0;

void trick()
{
    int cubic = pow(256.0, 1.0 / 3.0) * 100 + 1;

    for (int a = 1; a <= cubic; a++)
    {
        int square = 2560000 / a + 1;
        for (int b = a; b <= square; b++)
        {
            if (a * b <= 10000) continue;
            if (((a + b) * 10000) % (a * b - 10000) != 0) continue;
            int c = ((a + b) * 10000) / (a * b - 10000);
            if (c < b || c > 25600) continue;
            solutions[cnt++] = product{a + b + c, a, b, c};
        }
    }
        
    sort(solutions, solutions + cnt);
}

void print(int f)
{
    cout << (f / 100) << ".";
    f %= 100;
    cout << (f / 10);
    f %= 10;
    cout << f;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    trick();

    int smaller, bigger;
    string number1, number2;
    
    while (cin >> number1 >> number2)
    {
        smaller = 0, bigger = 0;
        
        for (int i = 0; i < number1.length(); i++)
        {
            if (number1[i] == '.') continue;
            smaller = smaller * 10 + number1[i] - '0';
        }
        
        for (int i = 0; i < number2.length(); i++)
        {
            if (number2[i] == '.') continue;
            bigger = bigger * 10 + number2[i] - '0';
        }
        
        if (smaller > bigger) swap(smaller, bigger);
        
        for (int i = 0; i < cnt; i++)
            if (solutions[i].sum >= smaller && solutions[i].sum <= bigger)
            {
                print(solutions[i].sum) << " = ";
                print(solutions[i].a) << " + ";
                print(solutions[i].b) << " + ";
                print(solutions[i].c) << " = ";
                print(solutions[i].a) << " * ";
                print(solutions[i].b) << " * ";
                print(solutions[i].c) << "\n";
            }
    }
    
    return 0;
}
