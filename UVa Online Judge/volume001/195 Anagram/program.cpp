// Anagram
// UVa IDs: 195
// Verdict: Accepted
// Submission Date: 2016-03-15
// UVa Run Time: 0.202s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

set < string > existed;

bool cmp(char x, char y)
{
    if (isupper(x) && isupper(y) || islower(x) && islower(y))
        return x < y;

    if (isupper(x))
    {
        x = tolower(x);
        if (x == y)
            return true;
        else    
            return x < y;
    }
    else
    {
        y = tolower(y);
        if (x == y)
            return false;
        else
            return x < y;
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int n;
    
    cin >> n;
    while (n--)
    {
        string line;
        cin >> line;

        sort(line.begin(), line.end(), cmp);
        
        do
        {
            if (existed.count(line) == 0)
            {
                cout << line << endl;
                existed.insert(line);
            }
        } while (next_permutation(line.begin(), line.end(), cmp));
    }
    
	return 0;
}
