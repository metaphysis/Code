// Uncompress
// UVa ID: 245
// Verdict: Accepted
// Submission Date: 2016-05-12
// UVa Run Time: 0.060s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line;
    list < string > words;
    while (getline(cin, line), line != "0")
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                string number;
                number += line[i++];

                while (i < line.length() && isdigit(line[i]))
                    number += line[i++];

                auto it = words.begin();
                
                advance(it, stoi(number) - 1);
                
                string word = *it;
                words.erase(it);
                
                cout << word;
                words.insert(words.begin(), word);
                
                i--;
            }
            else if (isalpha(line[i]))
            {
                string word;
                word += line[i++];
                
                while (i < line.length() && isalpha(line[i]))
                    word += line[i++];
                    
                words.insert(words.begin(), word);
                cout << word;
                
                i--;
            }
            else
                cout << line[i];
        }
        
        cout << "\n";
    }
	return 0;
}
