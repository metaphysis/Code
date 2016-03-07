// Loglan - A Logical Language
// UVa IDs: 134
// Verdict: Wrong Answer
// Submission Date: 2016-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum symbol { ERROR, A, MOD, BA, DA, LA, NAM, PREDA };

symbol wordToToken(string word)
{
    string vowels = "aeiou";
        
    if (word.length() == 1)
        return vowels.find(word) == vowels.npos ? ERROR : A;
    
    if (word.length() == 2)
    {
        if (vowels.find(word[1]) == vowels.npos)
            return ERROR;
            
        if (word[0] == 'g')
            return MOD;
        if (word[0] == 'b')
            return BA;
        if (word[0] == 'd')
            return DA;
        if (word[0] == 'l')
            return LA;
    }

    if (vowels.find(word[word.length() - 1]) == vowels.npos)
        return NAM;
        
    if (word.length() == 5)
    {
        int bitOr = 0;
        for (int i = 0; i < 5; i++)
            bitOr |= ((vowels.find(word[i]) != vowels.npos ? 1 : 0) << (4 - i));
            
        if (bitOr == 5 || bitOr == 9)
            return PREDA;
    }
    
    return ERROR;
}

// <predstring> => PREDA | <predstring> PREDA
bool isPredstring(vector<symbol> words)
{
    if (words.size() == 0)
        return false;

    for (int i = 0; i < words.size(); i++)
        if (words[i] != PREDA)
            return false;
    return true;
}

// <preds> => <predstring> | <preds> A <predstring>
bool isPreds(vector<symbol> words)
{
    if (words.size() == 0)
        return false;

    // 找到起始的 PREDA 或 A
    for (int i = words.size() - 1; i >= 0; i--)
    {
        if (words[i] == PREDA)
            continue;
        else if (words[i] == A)
        {
            if (i > 0)
            {
                vector<symbol> preds(words.begin(), words.begin() + i);
                return isPreds(preds);
            }
            else
                return false;
        }
        else
            return false;
    }

    return true;
}

// <predname> => LA <predstring> | NAM
bool isPredname(vector<symbol> words)
{
    if (words.size() == 0)
        return false;
        
    if (words.front() != LA && words.front() != NAM)
        return false;

    if (words.size() == 1 && words.front() == NAM)
        return true;

    if (words.front() == LA)
    {
        vector<symbol> predstring(words.begin() + 1, words.end());
        return isPredstring(predstring);
    }
    else
        return false;

    return true;
}

// <statement> => <predname> <verbpred> <predname> | <predname> <verbpred>
bool isStatement(vector<symbol> words)
{
    // 找到 <verbpred>
    int i, j;
    for (i = 0; i <= (words.size() - 2); i++)
        if (words[i] == MOD)
        {
            // 提取 <verbpred> 之前的 <predname>
            vector<symbol> predname(words.begin(), words.begin() + i);
            
            // 找到构成 <verbpred> 在 MOD 之后的所有 PREDA，若未到 words 的末端，
            // 则句子可能是 statement 的第一种模式，否则可能是第二种模式
            for (j = i + 1; j < words.size(); j++)
                if (words[j] != PREDA)
                    break;
            if (j < (words.size() - 1))
            {
                vector<symbol> nextPredname(words.begin() + j, words.end());
                return isPredname(predname) && isPredname(nextPredname);
            }
            else
                return isPredname(predname);
        }

    return false;
}

// <predclaim> => <predname> BA <preds> | DA <preds>
bool isPredclaim(vector<symbol> words)
{
    // DA <preds>
    if (words.front() == DA)
    {
        vector<symbol> preds(words.begin() + 1, words.end());
        return isPreds(preds);
    }

    // <predname> BA <preds>
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == BA)
        {
            vector<symbol> predname(words.begin(), words.begin() + i);
            vector<symbol> preds(words.begin() + i + 1, words.end());
            return isPredname(predname) && isPreds(preds);
        }
    }

    return false;
}

// <sentence> => <statement> | <predclaim>
bool isSentence(vector<symbol> words)
{
    if (words.size() == 0)
        return false;
    for (int i = 0; i < words.size(); i++)
        if (words[i] == ERROR)
            return false;
    return isStatement(words) || isPredclaim(words);
}

int main(int argc, char *argv[])
{
    vector<symbol> words;

    string line, word;
    while (getline(cin, line), line != "#")
    {
        // 读入字符串，将其转换为单词数组以便判定。
        string newLine(line);
        if (line.find('.') != string::npos)
            newLine = newLine.substr(0, newLine.find('.'));

        istringstream iss(newLine);
        while (iss >> word)
            words.push_back(wordToToken(word));

        if (line.find('.') != string::npos)
        {
            cout << (isSentence(words) ? "Good" : "Bad!") << endl;
            words.clear();
        }
    }

    return 0;
}
