// Word Amalgamation
// UVa ID: 642
// Verdict: Accepted
// Submission Date: 2016-08-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

struct item
{
    string word, sorted;
    bool operator<(const item &another) const
    {
        return word < another.word;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    vector<item> items;
    string line;
    while (getline(cin, line), line.front() != 'X')
    {
        string backup = line;
        sort(line.begin(), line.end());
        items.push_back((item){backup, line});
    }
    sort(items.begin(), items.end());
    
    while (getline(cin, line), line.front() != 'X')
    {
        sort(line.begin(), line.end());
        bool outputed = false;
        for (auto data : items)
            if (data.sorted == line)
            {
                outputed = true;
                cout << data.word << '\n';
            }
        if (!outputed)
            cout << "NOT A VALID WORD\n";
        cout << "******\n";
    }
    
	return 0;
}
