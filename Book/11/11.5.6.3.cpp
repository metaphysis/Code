#include <bits/stdc++.h>

using namespace std;

void manacher(string &line)
{
    string word;
    word.push_back('$');
    for (int i = 0; i < line.length(); i++)
    {
        word.push_back(line[i]);
        word.push_back('#');
    }
    word.back() = '|';
    
    vector<int> P(word.size());
    
    int rightmost = 0, center = 0;
    for (int i = 1; i < word.size(); i++)
    {
        P[i] = (rightmost > i) ? P[2 * center - i] : 1;
        
        while (word[i - P[i]] == word[i + P[i]])
            P[i]++;
        
        if (i + P[i] > rightmost)
        {
            rightmost = i + P[i] - 1;
            center = i;
        }
    }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        if (line.length() == 0)
            continue;

        string word;
        istringstream iss(line);
        while (iss >> word)
            if (manacher(word))
                cout << word << endl;
    }

    return 0;
}
