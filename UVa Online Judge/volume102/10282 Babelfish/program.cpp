// Babelfish
// UVa ID: 10282
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.170s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

    map<string, string> dict;
    string line, word1, word2;
    
    while (getline(cin, line), line.length() > 0)
    {
        istringstream iss(line);
        iss >> word1 >> word2;
        dict[word2] = word1;
    }
    
    while (cin >> word2)
    {
        if (dict.find(word2) != dict.end()) cout << dict[word2] << '\n';
        else cout << "eh\n";
    }

    return 0;
}
