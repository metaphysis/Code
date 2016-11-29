// 487–3279
// UVa ID: 755
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.220s
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

    map<char, char> keypad = {
        {'A', 2}, {'B', 2}, {'C', 2}, 
        {'D', 3}, {'E', 3}, {'F', 3}, 
        {'G', 4}, {'H', 4}, {'I', 4}, 
        {'J', 5}, {'K', 5}, {'L', 5}, 
        {'M', 6}, {'N', 6}, {'O', 6}, 
        {'P', 7}, {'R', 7}, {'S', 7}, 
        {'T', 8}, {'U', 8}, {'V', 8}, 
        {'W', 9}, {'X', 9}, {'Y', 9}
    };
    
    int cases = 0;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        int N;
        cin >> N;
        
        map<int, int> times;
        
        string telephone;
        for (int i = 1; i <= N; i++)
        {
            cin >> telephone;
            
            int number = 0;
            for (int j = 0; j < telephone.length(); j++)
            {
                if (isdigit(telephone[j]))
                    number = number * 10 + (telephone[j] - '0');
                else
                {
                    if (isalpha(telephone[j]))
                        number = number * 10 + keypad[telephone[j]];
                }
            }
            times[number]++;
        }
        
        bool outputed = false;
        for (auto record : times)
        {
            if (record.second > 1)
            {
                outputed = true;
                string text = to_string(record.first);
                while (text.length() < 7) text.insert(text.begin(), '0');
                cout << text.substr(0, 3) << '-' << text.substr(3) << ' ' << record.second << '\n';
            }
        }
        
        if (!outputed) cout << "No duplicates.\n";
    }
    
	return 0;
}
