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

string s;
long long factorial[24] = {1}, n;

void reverseCantorExpansion()
{
    n %= factorial[s.length()];
    
    for (int i = s.length() - 1; i >= 0; i--)
    {
        long long index = n / factorial[i], count = 0;
        for (int j = 0; j < s.length(); j++)
        {
            if (s[j] > 0)
            {
                if (count == index)
                {
                    cout << s[j];
                    s[j] = 0;
                    break;
                }

                count++;
            }
        }
        n %= factorial[i];
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < 24; i++)
        factorial[i] = factorial[i - 1] * i;

    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> s >> n;
        sort(s.begin(), s.end());
        reverseCantorExpansion();
    }

    return 0;
}
