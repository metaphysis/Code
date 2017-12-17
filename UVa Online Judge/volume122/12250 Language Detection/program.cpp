// Language Detection
// UVa ID: 12250
// Verdict: Accepted
// Submission Date: 2017-12-17
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

    int cases = 0;
    string line;
    while (getline(cin, line), line.front() != '#')
    {
        cout << "Case " << ++cases << ": ";
        if (line == "HELLO") cout << "ENGLISH";
        else if (line == "HOLA") cout << "SPANISH";
        else if (line == "HALLO") cout << "GERMAN";
        else if (line == "BONJOUR") cout << "FRENCH";
        else if (line == "CIAO") cout << "ITALIAN";
        else if (line == "ZDRAVSTVUJTE") cout << "RUSSIAN";
        else cout << "UNKNOWN";
        cout << '\n';
    }

    return 0;
}
