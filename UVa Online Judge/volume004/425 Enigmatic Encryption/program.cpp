// Enigmatic Encryption
// UVa ID: 425
// Verdict: Accepted
// Submission Date: 
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <set>
#include <vector>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    
    string password = line;
    string salt = line.substr(0, 2);
    
    set<string> words;
    while (getline(cin, line))
    {
        int i = 0;
        while (i < line.length())
        {
            if (isalpha(line[i]))
            {
                string block;
                while (i < line.length() && isalpha(line[i]))
                {
                    block += tolower(line[i]);
                    i++;
                }
                if (block.length() > 1)
                    words.insert(block);
            }
            else
                i++;
        }
    }
    
    vector<string> allWords;
    for (auto word : words)
        allWords.push_back(word);
    
    char digits[4] = {'0', '2', '4', '8'};
    for (int i = 0; i < allWords.size(); i++)
        for (int j = i + 1; j < allWords.size(); j++)
        {
            if (i == j) continue;
            int length = allWords[i].length() + allWords[j].length();
            if (length >= 4 && length <= 7)
            {
                for (int k = 0; k < 4; k++)
                {
                    string plain1 = allWords[i] + digits[k] + allWords[j];
                    char *encrypted = crypt(plain1.data(), salt.data());
                    if (strcmp(encrypted, password.data()) == 0)
                    {
                        cout << plain1 << '\n';
                        return 0;
                    }
                    
                    string plain2 = allWords[j] + digits[k] + allWords[i];
                    encrypted = crypt(plain2.data(), salt.data());
                    if (strcmp(encrypted, password.data()) == 0)
                    {
                        cout << plain2 << '\n';
                        return 0;
                    }
                }
            }
        }
        
	return 0;
}
