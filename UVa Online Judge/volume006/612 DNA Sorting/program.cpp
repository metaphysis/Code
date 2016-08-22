// DNA Sorting
// UVa ID: 612
// Verdict: Accepted
// Submission Date: 2016-08-23
// UVa Run Time: 0.030s
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
    string dna;
    int inversion;
    
    bool operator<(const item& another) const
    {
        return inversion < another.inversion;
    }
};

int getInversion(string &line)
{
    int inversion = 0;
    for (int i = 0; i < line.length(); i++)
        for (int j = i + 1; j < line.length(); j++)
            if (line[j] < line[i])
                inversion++;
    return inversion;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, n, m;
    cin >> cases;
    
    vector<item> dnas;
    for (int c = 1; c <= cases; c++)
    {
        dnas.clear();
        
        if (c > 1)
            cout << '\n';
            
        cin >> n >> m;
        cin.ignore(1024, '\n');
        
        string line;
        for(int i = 0; i < m; i++)
        {
            getline(cin, line);
            dnas.push_back((item){line, getInversion(line)});
        }
        
        stable_sort(dnas.begin(), dnas.end());
        for (auto data : dnas)
            cout << data.dna << '\n';
    }
    
	return 0;
}
