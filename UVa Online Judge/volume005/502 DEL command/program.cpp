// DEL command
// UVa ID: 502
// Verdict: Accepted
// Submission Date: 2017-04-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// Easy but error-prone, WA 9 times.

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct file
{
    string name, extension;
};

vector<file> deleted, reserved;
string mask_name, mask_extension;

bool matched(string mask, string text)
{
    if (mask.back() == '*')
    {
        if ((mask.length() - 1) > text.length())
            return false;
            
        for (int i = 0; i < mask.length() - 1; i++)
            if (mask[i] != '?' && mask[i] != text[i])
                return false;
    }
    else
    {
        if (mask.length() != text.length())
            return false;

        for (int i = 0; i < mask.length(); i++)
            if (mask[i] != '?' && mask[i] != text[i])
                return false;
    }
    
    return matched;
}

bool validate()
{
    for (auto f : reserved)
        if (matched(mask_name, f.name) && matched(mask_extension, f.extension))
            return false;
    return true;
}

bool findWildcard()
{
    mask_name.clear(), mask_extension.clear();

    int max_name_length = 0, min_name_length = 8;
    int max_extension_length = 0, min_extension_length = 3;
    
    for (auto f : deleted)
    {
        if (max_name_length < f.name.length())
        {
            mask_name = f.name;
            max_name_length = f.name.length();
        }
        
        if (min_name_length > f.name.length())
            min_name_length = f.name.length();
            
        if (max_extension_length < f.extension.length())
        {
            mask_extension = f.extension;
            max_extension_length = f.extension.length();
        }
        
        if (min_extension_length > f.extension.length())
            min_extension_length = f.extension.length();
    }

    for (auto f : deleted)
    {
        for (int i = 0; i < f.name.length(); i++)
            if (mask_name[i] != '?' && f.name[i] != mask_name[i])
                mask_name[i] = '?';
        for (int i = 0; i < f.extension.length(); i++)
            if (mask_extension[i] != '?' && f.extension[i] != mask_extension[i])
                mask_extension[i] = '?';
    }
    
    if (min_name_length < max_name_length)
        mask_name = mask_name.substr(0, min_name_length) + "*";
        
    if (min_extension_length < max_extension_length)
        mask_extension = mask_extension.substr(0, min_extension_length) + "*";
        
    return validate();
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);

    int cases = stoi(line);
    
    getline(cin, line);
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        deleted.clear(), reserved.clear();

        while (getline(cin, line), line.length() > 0)
        {
            string name = line.substr(1), extension;
            
            int point = name.find('.');
            if (point != name.npos)
            {
                extension = name.substr(point + 1);
                name = name.substr(0, point);
            }
            
            if (line.front() == '-')
                deleted.push_back(file{name, extension});
            else
                reserved.push_back(file{name, extension});
        }

        if (findWildcard())
            cout << "DEL " << mask_name << '.' << mask_extension << '\n';
        else
            cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
