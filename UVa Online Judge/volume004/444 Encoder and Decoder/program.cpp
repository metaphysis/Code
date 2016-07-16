// Encoder and Decoder
// UVa ID: 444
// Verdict: Accepted
// Submission Date: 2016-07-15
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

    map<char, string> encoder = {{' ', "32"}, {'!', "33"}, {',', "44"}, {'.', "46"}, {':', "58"}, {';', "59"}, {'?', "63"}};
    map<string, char> decoder = {{"32", ' '}, {"33", '!'}, {"44", ','}, {"46", '.'}, {"58", ':'}, {"59", ';'}, {"63", '?'}};
    
    for (int i = 65; i <= 90; i++)
    {
        string temp = to_string(i);
        encoder[i] = temp;
        decoder[temp] = i;
        
        temp = to_string(i + 32);
        encoder[i + 32] = temp;
        decoder[temp] = i + 32;
    }
    
    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0)
        {
            cout << endl;
            continue;
        }
        
        string text;
        if (isdigit(line.front()))
        {
            reverse(line.begin(), line.end());
            
            int index = 0;
            string normal;
            while (index < line.length())
            {
                if (decoder.find(line.substr(index, 2)) != decoder.end())
                {
                    cout << decoder[line.substr(index, 2)];
                    index += 2;
                    continue;
                }
                
                cout << decoder[line.substr(index, 3)];
                index += 3;
            }
        }
        else
        {
            for (int i = 0; i < line.length(); i++)
                text += encoder[line[i]];
        }
        
        reverse(text.begin(), text.end());
        cout << text << endl;
    }
    
	return 0;
}
