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

bool cmp(const char &a, const char &b)
{
    return toupper(a) < toupper(b);
}

int main(int argc, char *argv[])
{
    string s1 = "aBcD", s2 = "BcDe";
    
    if (lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp))
        cout << "s1 is less than s2.\n";
    else
        cout << "s1 is greater than s2.\n";

    return 0;
}
