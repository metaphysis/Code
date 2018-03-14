// Permutation Arrays
// UVa ID: 482
// Verdict: Accepted
// Submission Date: 2016-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    
    getline(cin, line);
    int cases = stoi(line);
    
    
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        vector<int> order;
        vector<string> number;
        
        getline(cin, line);
        getline(cin, line);
        istringstream iss(line);
        
        int index;
        while (iss >> index)
            order.push_back(index);
            
        getline(cin, line);
        iss.clear();
        iss.str(line);
        string block;
        while (iss >> block)
            number.push_back(block);
            
        vector<int> output(order.size());
        for (int j = 0; j < order.size(); j++)
            output[order[j] - 1] = j;
            
        for (int j = 0; j < output.size(); j++)
            cout << number[output[j]] << '\n';
    }
    
	return 0;
}
