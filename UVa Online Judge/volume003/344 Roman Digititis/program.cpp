// Roman Digititis
// UVa ID: 344
// Verdict: Accepted
// Submission Date: 2016-06-25
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

string digits = "ivxlc";

vector<string> single = {
    "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"
};

vector<string> tens = {
    "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc", "c"
};

string numberToRoman(int i)
{
    string text;
    if (i >= 100)
    {
        text += "c";
        i %= 100;
    }
    
    if (i >= 10)
    {
        text += tens[i / 10 - 1];
        i %= 10;
    }
    
    if (i > 0) text += single[i - 1];
    
    return text;
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        map<char, int> counter;
        for (auto c : digits)
            counter[c] = 0;
            
        for (int i = 1; i <= n; i++)
        {
            string text = numberToRoman(i);

            for (auto c : text)
                counter[c]++;
        }
        
        cout << n << ":";
        for (auto c : digits)
        {
            cout << " " << counter[c] << " " << c;
            if (c != 'c') cout << ",";
        }
        cout << endl;
    }
    
	return 0;
}
