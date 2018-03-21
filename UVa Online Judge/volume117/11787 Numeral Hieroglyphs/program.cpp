// Numeral Hieroglyphs
// UVa ID: 11787
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<char, int> letter = {{'B', 1}, {'U', 10}, {'S', 100}, {'P', 1000}, {'F', 10000}, {'T', 100000}, {'M', 1000000}};
    
    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        string number;
        cin >> number;

        bool error = false;
        for (int i = 1; i < number.length(); i++)
            if (letter[number[i - 1]] > letter[number[i]])
            {
                error = true;
                break;
            }

        reverse(number.begin(), number.end());

        if (error)
        {
            error = false;
            for (int i = 1; i < number.length(); i++)
                if (letter[number[i - 1]] > letter[number[i]])
                {
                    error = true;
                    break;
                }
        }

        map<char, int> cnt;
        for (auto d : number)
        {
            cnt[d]++;
            if (cnt[d] > 9) error = true;
        }

        if (error)
        {
            cout << "error\n";
            continue;
        }
        
        int r = 0;
        for (auto d : number)
            r += letter[d];
        cout << r << '\n';    
    }

    return 0;
}
