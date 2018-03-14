// Key to Success
// UVa ID: 468
// Verdict: Accepted
// Submission Date: 2016-07-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct item
{
    char letter;
    int frequency;
    
    bool operator<(const item& another) const
    {
        if (frequency != another.frequency)
            return frequency > another.frequency;
        else
            return letter < another.letter;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    
    int cases = stoi(line);
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1)
            cout << '\n';

        getline(cin, line);
        
        string plain_line, encoded_line;
        map<char, int> plain, encoded;
        getline(cin, plain_line);
        for (int j = 0; j < plain_line.length(); j++)
            if (isalpha(plain_line[j]))
                plain[plain_line[j]]++;
                
        getline(cin, encoded_line);
        for (int j = 0; j < encoded_line.length(); j++)
            if (isalpha(encoded_line[j]))
                encoded[encoded_line[j]]++;
                
        vector<item> text1, text2;
        for (auto p : plain)
            text1.push_back((item){p.first, p.second});
        for (auto p : encoded)
            text2.push_back((item){p.first, p.second});

        sort(text1.begin(), text1.end());
        sort(text2.begin(), text2.end());
        
        map<char, char> code;
        for (int j = 0; j < text1.size(); j++)
            code[text2[j].letter] = text1[j].letter;
            
        for (auto c : encoded_line)
            if (isalpha(c))
                cout << code[c];
            else
                cout << c;
                    
        cout << '\n';
    }
    
	return 0;
}
