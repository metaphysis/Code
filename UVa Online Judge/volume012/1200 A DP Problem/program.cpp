// A DP Problem
// UVa ID: 1200
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

pair<int, int> parse(string expression)
{
    string next = "+";
    for (auto c : expression)
    {
        if (c == '+' || c == '-')
            next += ' ';
        next += c;
    }
        
    int x = 0, coefficient = 0;
    istringstream iss(next);
    string block;
    while (iss >> block)
    {
        int sign = 1;
        if (block.front() == '-') sign = -1;
        block.erase(block.begin());
        if (block.back() == 'x')
        {
            block.pop_back();
            int n = 0;
            if (block.length() == 0) n = 1;
            else
            {
                for (auto c : block)
                    n = n * 10 + c - '0';
            }
            
            x += n * sign;
        }
        else
        {
            int n = 0;
            for (auto c : block)
                n = n * 10 + c - '0';
            coefficient += n * sign;
        }
    }
    
    return make_pair(x, coefficient);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;
    
    cin >> cases; cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);
        for (int i = line.length() - 1; i >= 0; i--)
            if (isblank(line[i]))
                line.erase(line.begin() + i);

        int equal = line.find('=');
        pair<int, int> leftPart = parse(line.substr(0, equal));
        pair<int, int> rightPart = parse(line.substr(equal + 1));
        
        int x = leftPart.first - rightPart.first;
        int coefficient = rightPart.second - leftPart.second;
        
        if (x == 0)
        {
            if (coefficient == 0) cout << "IDENTITY\n";
            else cout << "IMPOSSIBLE\n";   
        }
        else
        {
            cout << (int)(floor(1.0 * coefficient / x)) << '\n';
        }
    }

    return 0;
}
