// Testing the CATCHER
// UVa ID: 231
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector < int > heights;

int lis()
{
    reverse(heights.begin(), heights.end());
    
    vector < int > m;
    m.push_back(heights.front());
    
    for (int i = 1; i < heights.size(); i++)
        if (heights[i] >= m.back())
            m.push_back(heights[i]);
        else
        {
            int n = upper_bound(m.begin(), m.end(), heights[i]) - m.begin();
            m[n] = heights[i];
        }
    
    return m.size();
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    bool first = true;
    int height, cases = 0;
    while (cin >> height, height != -1)
    {
        heights.clear();
        heights.push_back(height);
        
        while (cin >> height, height != -1)
            heights.push_back(height);
        
        if (first)
            first = false;
        else
            cout << endl;
        
        cases++;
        cout << "Test #" << cases << ":" << endl;
        cout << "  maximum possible interceptions: " << lis() << endl;   
    }
    
	return 0;
}
