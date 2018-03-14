// Clock Solitaire
// UVa ID: 635
// Verdict: Accepted
// Submission Date: 2016-08-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string letters = "J23456789TAQK";
    map<char, int> piles;
    for (int i = 0; i < letters.length(); i++)
        piles[letters[i]] = i;

    char card, cards[13][4];
    while (cin >> card, card != '0')
    {
        cin.putback(card);
        string sequence(52, '0');
        for (int i = 0; i < 52; i++)
            cin >> sequence[i];
            
        int success = 0;
        for (int k = 1; k <= 52; k++)
        {
            for (int i = 0; i < 13; i++)
                for (int j = 0; j < 4; j++)
                    cards[i][j] = sequence[i * 4 + j];
            
            int shifts = 0, uncovered[13];
            memset(uncovered, 0, sizeof(uncovered));
            
            int pointer = 12;
            while (true)
            {
                if (uncovered[pointer] > 3)
                    break;
                uncovered[pointer]++;
                pointer = piles[cards[pointer][uncovered[pointer] - 1]];
                shifts++;
            }
            
            if (shifts == 52)
                success++;
                
            sequence.push_back(sequence.front());
            sequence.erase(sequence.begin());
        }
        cout << success << '\n';
    }
    
	return 0;
}
