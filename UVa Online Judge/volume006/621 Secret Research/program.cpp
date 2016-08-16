// Secret Research
// UVa ID: 621
// Verdict: Accepted
// Submission Date: 2016-08-17
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    cin >> n;
    cin.ignore(1024, '\n');
    
    string line;
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        if (line == "1" || line == "4" || line == "78")
            cout << "+\n";
        else if (line[line.length() - 2] == '3' && line[line.length() - 1] == '5')
            cout << "-\n";
        else if (line.front() == '9' && line.back() == '4')
            cout << "*\n";
        else
            cout << "?\n";
    }
    
	return 0;
}
