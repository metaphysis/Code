// ID Codes
// UVa IDs: 146
// Verdict: Accepted
// Submission Date: 2016-01-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line), line != "#")
    {
        if (next_permutation(line.begin(), line.end()))
            cout << line << endl;
        else
            cout << "No Successor" << endl;
    }
    
	return 0;
}
