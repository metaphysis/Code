// Palindromes
// UVa ID: 401
// Verdict: Accepted
// Submission Date: 2016-07-13
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

map<char, char> mirror = {
    {'A', 'A'}, {'E', '3'}, {'3', 'E'}, {'H', 'H'}, {'I', 'I'}, {'J', 'L'},
    {'L', 'J'}, {'M', 'M'}, {'O', 'O'}, {'S', '2'}, {'2', 'S'}, {'T', 'T'},
    {'U', 'U'}, {'V', 'V'}, {'W', 'W'}, {'X', 'X'}, {'Y', 'Y'}, {'Z', '5'},
    {'5', 'Z'}, {'1', '1'}, {'8', '8'}
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int left = 0, right = line.length() - 1;
        while (isblank(line[left])) left++;
        while (isblank(line[right])) right--;
        line = line.substr(left, right - left + 1);
        
        string original = line;
        
        reverse(line.begin(), line.end());
        bool is_palindrome = (line == original);
        
        bool is_mirror_string = true;
        for (int i = 0; i < line.length(); i++)
            if (mirror.find(line[i]) == mirror.end() || mirror[line[i]] != original[i])
            {
                is_mirror_string = false;
                break;
            }
            
        cout << original;
        if (is_palindrome && is_mirror_string) cout <<  " -- is a mirrored palindrome.";
        else if (is_palindrome && !is_mirror_string) cout << " -- is a regular palindrome.";
        else if (!is_palindrome && is_mirror_string) cout << " -- is a mirrored string.";
        else cout << " -- is not a palindrome.";
        cout << endl << endl;
    }
    
	return 0;
}
