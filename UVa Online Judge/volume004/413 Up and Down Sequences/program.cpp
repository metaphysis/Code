// Up and Down Sequences
// UVa ID: 413
// Verdict: Accepted
// Submission Date: 2016-07-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    cout.precision(6);
    
    while (true)
    {
        vector<int> up, down;
        int number, numberCounter = 0;
        int up_length = 0, down_length = 0, up_sequence = 0, down_sequence = 0;
        
        while (cin >> number, number)
        {
            numberCounter++;
            
            if (up.size() == 0 || number >= up.back()) up.push_back(number);
            else if (up.size() > 1 && up.back() > up.front())
            {
                up_sequence += 1;
                up_length += up.size() - 1;
                
                down.clear();
                down.push_back(up.back());
                down.push_back(number);
                up.clear();
                continue;
            }
            
            if (down.size() == 0 || number <= down.back()) down.push_back(number);
            else if (down.size() > 1 && down.back() < down.front())
            {
                down_sequence += 1;
                down_length += down.size() - 1;
                
                up.clear();
                up.push_back(down.back());
                up.push_back(number);
                down.clear();
            }
        }

        if (up.size() > 1 && up.back() > up.front())
        {
            up_sequence += 1;
            up_length += up.size() - 1;
        }
        
        if (down.size() > 1 && down.back() < down.front())
        {
            down_sequence += 1;
            down_length += down.size() - 1;
        }
        
        if (numberCounter == 0)
            break;
        
        cout << "Nr values = " << numberCounter << ":  ";
        cout << fixed << (up_sequence > 0 ? ((double)up_length / (double)up_sequence) : 0.0);
        cout << ' ';
        cout << fixed << (down_sequence > 0 ? ((double)down_length / (double)down_sequence) : 0.0);
        cout << '\n';
    }
    
	return 0;
}
