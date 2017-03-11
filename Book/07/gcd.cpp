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
    while (a % b) t = a, a = b, b = t % b;
    return b;
}

int gcd2(int a, int b)
{
    while (a != b) if (a > b) a -= b; else b -= a;
    return a;
}

int main(int argc, char *argv[])
{
    int a, b;
    
    while (cin >> a >> b) cout << gcd1(a, b) << '\n';
}
