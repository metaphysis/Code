// Do the Untwist
// UVa ID: 641
// Verdict: Accepted
// Submission Date: 2016-08-29
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

    int k;
    string ciphertext;
    string letters = "_abcdefghijklmnopqrstuvwxyz.";
    map<char, int> code;
    
    for (int i = 0; i < letters.length(); i++)
        code[letters[i]] = i;
        
    while (cin >> k, k)
    {
        cin >> ciphertext;
        
        int n = ciphertext.length();
        string plaintext(n, '0');
        
        for (int i = 0; i < ciphertext.length(); i++)
        {
            plaintext[(k * i) % n] = letters[(code[ciphertext[i]] + i) % 28];
            //int m = code[ciphertext[i]];
            //for (int j = 0; j <= 27; j++)
            //    if ((j - i + 28) % 28 == m)
            //    {
            //        plaintext[(k * i) % n] = letters[j];
            //        break;
            //    }
        }
        
        cout << plaintext << '\n';
    }
    
	return 0;
}
