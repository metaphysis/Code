// Indexing
// UVa ID: 789
// Verdict: Accepted
// Submission Date: 2017-06-11
// UVa Run Time: 0.110s
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

    map<string, set<int>> indexing;
    char key;
    
    cin >> key; cin.ignore(1024, '\n');
    
    string line, word;
    int lineNumbers = 1;
    
    while (getline(cin, line))
    {
        istringstream iss(line);
        while (iss >> word)
        {
            while (word.length() > 0 && !isupper(word.front()))
                word.erase(word.begin());
            while (word.length() > 0 && !isupper(word.back()))
                word.pop_back();
            if (word.length() > 0 && word.front() == key)
                indexing[word].insert(lineNumbers);
        }
        lineNumbers += 1;
    }
    
    for (auto entry : indexing)
    {
        cout << entry.first;
        for (auto number : entry.second)
            cout << ' ' << number;
        cout << '\n';
    }
    
    return 0;
}
