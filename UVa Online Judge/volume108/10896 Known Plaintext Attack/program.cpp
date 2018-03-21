// Known Plaintext Attack
// UVa ID: 10896
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

    int cases;
    string sentence, decrypted, word;

    cin >> cases;
    cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        getline(cin, sentence);
        getline(cin, decrypted);

        istringstream iss(sentence);
        vector<char> keys;
        while (iss >> word)
        {
            if (word.length() == decrypted.length())
            {
                bool same = true;
                int shift = (word[0] - decrypted[0] + 26) % 26;
                for (int i = 1; i < word.length(); i++)
                    if (((word[i] - decrypted[i] + 26) % 26) != shift)
                    {
                        same = false;
                        break;
                    }
                if (same) keys.push_back('a' + (word[0] - decrypted[0] + 26) % 26);
            }
        }
        sort(keys.begin(), keys.end());
        for (auto k : keys) cout << k;
        cout << '\n';
    }

    return 0;
}
