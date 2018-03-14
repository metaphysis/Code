// What Goes Up
// UVa ID: 481
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.350s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> numbers, m;
vector<vector<int>> sequences;

int lis()
{
    m.push_back(numbers.front());
    vector<int> sequence;
    sequence.push_back(numbers.front());
    sequences.push_back(sequence);
    
    for (int i = 1; i < numbers.size(); i++)
    { 
        if (numbers[i] > m.back())
        {
            m.push_back(numbers[i]);
            vector<int> next(sequences.back());
            next.push_back(numbers[i]);
            sequences.push_back(next);
        }
        else
        {
            int n = lower_bound(m.begin(), m.end(), numbers[i]) - m.begin();
            m[n] = numbers[i];
            if (n == 0)
                sequences[n].back() = numbers[i];
            else
            {
                sequences[n].assign(sequences[n- 1].begin(), sequences[n - 1].end());
                sequences[n].push_back(numbers[i]);
            }
        }
    }
    
    return m.size();
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int number;
    while (cin >> number) numbers.push_back(number);
    
    cout << lis() << '\n';
    cout << '-' << '\n';
    for (auto n : sequences.back())
        cout << n << '\n';
    
	return 0;
}
