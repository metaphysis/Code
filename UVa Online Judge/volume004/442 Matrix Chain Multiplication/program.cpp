// Matrix Chain Multiplication
// UVa ID: 442
// Verdict: Accepted
// Submission Date: 2016-07-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    cin >> n;
    
    map<char, pair<long long, long long>> matrix;
    for (int i = 1; i <= n; i++)
    {
        char letter;
        long long row, column;
        cin >> letter >> row >> column;
        matrix[letter] = make_pair(row, column);
    }
    
    string line;
    while (cin >> line)
    {
        if (line.length() == 1)
        {
            cout << "0" << endl;
            continue;
        }
        
        vector<pair<long long, long long>> multiplication;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '(' || line[i] == ')')
                multiplication.push_back(make_pair(0, 0));
            else
                multiplication.push_back(matrix[line[i]]);
        }
        
        bool error = false;
        int counter = 0;
        while (multiplication.size() > 1)
        {
            for (int i = 0; i < multiplication.size() - 1; i++)
            {
                if (multiplication[i].first > 0 && multiplication[i + 1].first > 0)
                {
                    if (multiplication[i].second != multiplication[i + 1].first)
                    {
                        error = true;
                        goto skip;
                    }
                    else
                    {
                        counter += multiplication[i].first * multiplication[i].second * multiplication[i + 1].second;
                        multiplication[i].second = multiplication[i + 1].second;
                        multiplication.erase(multiplication.begin() + i + 1);
                        multiplication.erase(multiplication.begin() + i + 1);
                        multiplication.erase(multiplication.begin() + i - 1);
                        break;
                    }
                }
            }
        }
        
        skip:
        if (error) cout << "error" << endl;
        else cout << counter << endl;
        
    }
    
	return 0;
}
