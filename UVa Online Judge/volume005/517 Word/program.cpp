// Word
// UVa ID: 517
// Verdict: Accepted
// Submission Date: 2016-12-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 16;

int rules[8], steps[MAXN], indexer[MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int n, s;
    string word, rule;
    
    while (cin >> n)
    {
        cin >> word;

        int w = 0;
        for (int i = 0; i < word.length(); i++)
        {
            w *= 2;
            if (word[i] == 'b') w++;
        }
        
        for (int i = 1; i <= 8; i++)
        {
            cin >> rule;

            int r = 0;
            for (int j = 0; j < rule.length() - 1; j++)
            {
                r *= 2;
                if (rule[j] == 'b') r++;
            }
            rules[r] = rule.back() - 'a';
        }

        cin >> s;

        memset(steps, -1, sizeof(steps));
        
        for (int i = 0; i < s; i++)
        {
            if (steps[w] >= 0)
            {
                int t = (s - i) % (i - steps[w]);
                w = indexer[steps[w] + t];
                break;
            }
            else
            {
                steps[w] = i;
                indexer[i] = w;
                
                int ww = 0;
                for (int j = 0; j < n; j++)
                {
                    int k = 0;
                    if ((1 << (j + 2) % n) & w) k += 4;
                    if ((1 << j) & w) k += 2;
                    if ((1 << ((j - 1 + n) % n)) & w) k += 1;
                    ww |= (rules[k] << j);
                }
                w = ww;
            }
        }
        
        word = bitset<16>(w).to_string().substr(16 - n);

        set<string> words;
        string wordword = word + word;
        for (int i = 0; i < word.length(); i++)
            words.insert(wordword.substr(i, word.length()));

        word = *(words.begin());
        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == '0') cout << 'a';
            else cout << 'b';
        }
        cout << '\n';
    }
    
	return 0;
}
