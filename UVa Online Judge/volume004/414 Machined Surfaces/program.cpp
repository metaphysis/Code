// Machined Surfaces
// UVa IDs: 414
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    int N;
    while (cin >> N, N)
    {
        cin.ignore(1024, '\n');
        vector<int> spaces;
        for (int i = 1; i <= N; i++)
        {
            getline(cin, line);
            int spaceCount = 0;
            for (int i = 0; i < line.length(); i++)
                if (isblank(line[i]))
                    spaceCount++;
            spaces.push_back(spaceCount);
        }
        
        int minSpace = *min_element(spaces.begin(), spaces.end());
        int sum = 0;
        for (auto s : spaces)
            sum += s - minSpace;
            
        cout << sum << endl;
    }
    
	return 0;
}
