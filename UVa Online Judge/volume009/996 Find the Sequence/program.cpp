// Find the Sequence
// UVa ID: 996
// Verdict: Accepted
// Submission Date: 2017-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// The judge data is not strong.
//

#include <bits/stdc++.h>

using namespace std;

bool finished = false;

bool isSame(vector<int> &number)
{
    if (number.size() == 0) return false;
    for (int i = 1; i < number.size(); i++)
        if (number[i] != number[i - 1])
            return false;
    return true;
}

bool divided(vector<int> &number)
{
    for (int i = 1; i < number.size(); i++)
        if (number[i - 1] == 0 || ((number[i] % number[i - 1]) != 0))
            return false;
    return true;
}

void print(vector<string> &sequence)
{
    string formula;
    for (int i = sequence.size() - 1; i >= 0; i--)
        formula = "[" + sequence[i] + formula + "]";
    cout << formula << '\n';
}

void dfs(vector<int> number, vector<string> sequence, int depth, int maxDepth)
{
    if (depth > maxDepth || number.size() == 0) return;
    
    if (isSame(number))
    {
        sequence.push_back(to_string(number[0]));
        print(sequence);
        finished = true;
        return;
    }

    if (divided(number))
    {
        vector<int> next_number(number.size(), 0);

        for (int i = 1; i < number.size(); i++)
            next_number[i] = number[i] / number[i - 1];

        for (int i = 1; i <= number[0]; i++)
        {
            if (number[0] % i == 0)
            {
                next_number[0] = number[0] / i;
                vector<string> next_sequence(sequence);
                next_sequence.push_back(to_string(i) + "*");
                
                //cout << i << "*\n";
                //for (int j = 0; j < next_number.size(); j++)
                //    cout << next_number[j] << ' ';
                //cout << '\n';
                
                dfs(next_number, next_sequence, depth + 1, maxDepth);
                
                if (finished) return;
            }
        }        
    }

    vector<int> next_number;
    for (int i = 1; i < number.size(); i++)
        next_number.push_back(number[i] - number[i - 1]);
    
    //cout << number[0] << "+\n";
    //for (int j = 0; j < next_number.size(); j++)
    //    cout << next_number[j] << ' ';
    //cout << '\n';

    vector<string> next_sequence(sequence);
    next_sequence.push_back(to_string(number[0]) + "+");
    dfs(next_number, next_sequence, depth + 1, maxDepth);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    
    while (getline(cin, line))
    {
        int m, n;
        vector<int> number;
        
        istringstream iss(line);
        iss >> m;
        
        while (iss >> n)
            number.push_back(n);
        
        finished = false;
        vector<string> formula;
        
        dfs(number, formula, 1, m);
        
        if (!finished) cout << "[0]\n";
    }
    
    return 0;
}
