// Loglan-A Logical Language
// UVa IDs: 134
// Verdict: Accepted
// Submission Date: 2016-04-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

const int NONE = -1, A = 0, MOD = 1, BA = 2, DA = 3, LA = 4, NAM = 5,
    PREDA = 6, PREDSTRING = 7, PREDNAME = 8, PREDS = 9, VERBPRED = 10,
    PREDVERB = 11, PREDCLAIM = 12, STATEMENT = 13, SENTENCE = 14;

vector < int > symbols;
vector < string > words;

int groups[14][4] = {
    {PREDA, NONE, PREDA, PREDA}, {PREDA, NONE, NONE, PREDSTRING},
    {NAM, NONE, NONE, PREDNAME}, {LA, NONE, PREDSTRING, PREDNAME},
    {MOD, NONE, PREDSTRING, VERBPRED}, {A, PREDSTRING, PREDSTRING, PREDSTRING},
    {PREDSTRING, NONE, NONE, PREDS}, {DA, NONE, PREDS, PREDCLAIM},
    {BA, PREDNAME, PREDS, PREDCLAIM}, {VERBPRED, PREDNAME, NONE, PREDVERB},
    {PREDVERB, NONE, PREDNAME, STATEMENT}, {PREDVERB, NONE, NONE, STATEMENT},
    {STATEMENT, NONE, NONE, SENTENCE}, {PREDCLAIM, NONE, NONE, SENTENCE}
};

int getSymbol(string word)
{
    string vowel = "aeiou";
    if (word.length() == 1 && vowel.find(word[0]) != word.npos)
        return A;
    if (word.length() == 2 && vowel.find(word[1]) != word.npos)
    {
        switch (word[0])
        {
            case 'g':
                return MOD;
            case 'b':
                return BA;
            case 'd':
                return DA;
            case 'l':
                return LA;
        }
        return NONE;
    }
    if (vowel.find(word.back()) == word.npos)
        return NAM;
    if (word.length() == 5)
    {
        int bitOr = 0;
        for (int i = 0; i < 5; i++)
            bitOr |= ((vowel.find(word[i]) != word.npos ? 1 : 0) << (4 - i));
        if (bitOr == 5 || bitOr == 9)
            return PREDA;
    }
    return NONE;
}

bool translateToSymbol()
{
    symbols.clear();
    for (int i = 0; i < words.size(); i++)
    {
        int temp = getSymbol(words[i]);
        if (temp == NONE)
            return false;
        else
            symbols.push_back(temp);
    }
    return true;
}

bool isSentence()
{
    if (translateToSymbol() == false)
        return false;

    for (int i = 0; i < 14; i++)
    {
        while (true)
        {
            bool found = false;
            for (int j = 0; j < symbols.size(); j++)
            {
                if (symbols[j] == groups[i][0])
                {
                    if (groups[i][1] != NONE && j == 0)
                        continue;

                    if (groups[i][2] != NONE && j == (symbols.size() - 1))
                        continue;

                    if (groups[i][1] == NONE && groups[i][2] == NONE)
                    {
                        found = true;
                        symbols[j] = groups[i][3];
                        break;
                    }

                    if (groups[i][1] != NONE && groups[i][2] != NONE)
                    {
                        if (symbols[j - 1] == groups[i][1] &&
                            symbols[j + 1] == groups[i][2])
                        {
                            found = true;
                            symbols[j - 1] = groups[i][3];
                            symbols.erase(symbols.begin() + j + 1);
                            symbols.erase(symbols.begin() + j);
                            break;
                        }
                    }
                    else if (groups[i][1] != NONE &&
                        symbols[j - 1] == groups[i][1])
                    {
                        found = true;
                        symbols[j - 1] = groups[i][3];
                        symbols.erase(symbols.begin() + j);
                        break;
                    }
                    else if (groups[i][2] != NONE &&
                        symbols[j + 1] == groups[i][2])
                    {
                        found = true;
                        symbols[j] = groups[i][3];
                        symbols.erase(symbols.begin() + j + 1);
                        break;
                    }
                }
            }

            if (found == false)
                break;
        }
    }

    return (symbols.size() == 1 && symbols[0] == SENTENCE);
}

int main(int argc, char *argv[])
{
    string line, word;
    while (getline(cin, line), line != "#")
    {
        string newLine(line);
        if (line.find('.') != string::npos)
            newLine = newLine.substr(0, newLine.find('.'));

        istringstream iss(newLine);
        while (iss >> word)
            words.push_back(word);

        if (line.find('.') != string::npos)
        {
            cout << (isSentence()? "Good" : "Bad!") << endl;
            words.clear();
        }
    }

    return 0;
}
