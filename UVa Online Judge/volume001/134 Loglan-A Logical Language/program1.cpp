// Loglan-A Logical Language
// UVa ID: 134
// Verdict: Accepted
// Submission Date: 2016-04-12
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

vector < int > S;
vector < string > W;

int T[14][4] = {
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
    S.clear();
    for (int i = 0; i < W.size(); i++)
    {
        int symbol = getSymbol(W[i]);
        if (symbol == NONE)
            return false;
        else
            S.push_back(symbol);
    }
    return true;
}

bool isSentence()
{
    if (translateToSymbol() == false)
        return false;

    for (int i = 0; i < 14; i++)
        for (int j = 0; j < S.size();)
        {
            if ((S[j] != T[i][0]) ||
                (T[i][1] != NONE && (j == 0 || S[j - 1] != T[i][1])) ||
                (T[i][2] != NONE && (j == (S.size() - 1) || S[j + 1] != T[i][2])))
            {
                j++;
                continue;
            }
            j = T[i][1] != NONE ? S.erase(S.begin() + j - 1) - S.begin() : j;
            j = T[i][2] != NONE ? S.erase(S.begin() + j + 1) - S.begin() - 1 : j;
            S[j] = T[i][3];
        }

    return (S.size() == 1 && S[0] == SENTENCE);
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
            W.push_back(word);

        if (line.find('.') != string::npos)
        {
            cout << (isSentence()? "Good" : "Bad!") << endl;
            W.clear();
        }
    }

    return 0;
}
