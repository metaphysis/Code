// Loglan-A Logical Language
// UVa ID: 134
// Verdict: Accepted
// Submission Date: 2016-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// A => a | e | i | o | u
bool isA(char c)
{
    string vowel = "aeiou";
    return vowel.find(c) != string::npos;
}

// MOD => ga | ge | gi | go | gu
bool isMOD(string word)
{
    return word.length() == 2 && word[0] == 'g' && isA(word[1]);
}

// BA => ba | be | bi | bo | bu
bool isBA(string word)
{
    return word.length() == 2 && word[0] == 'b' && isA(word[1]);
}

// DA => da | de | di | do | du
bool isDA(string word)
{
    return word.length() == 2 && word[0] == 'd' && isA(word[1]);
}

// LA => la | le | li | lo | lu
bool isLA(string word)
{
    return word.length() == 2 && word[0] == 'l' && isA(word[1]);
}

// NAM => { all names }，最后一个字母为辅音字母。
bool isNAM(string word)
{
    return !isA(word.at(word.length() - 1));
}

// PREDA => { all predicates }，满足 CCVCV 或者 CVCCV 的模式，C 为辅音字母，
// V 为元音字母。使用位操作，将字符位置编为一个二进制数进行判断。
bool isPREDA(string word)
{
    if (word.length() != 5)
        return false;

    int bitOr = 0;
    for (int i = 0; i < 5; i++)
        bitOr |= ((isA(word[i]) ? 1 : 0) << (4 - i));
            
    return (bitOr == 5 || bitOr == 9);
}

// <predstring> => PREDA | <predstring> PREDA
bool isPredstring(vector<string> words)
{
    if (words.size() == 0)
        return false;

    for (int i = 0; i < words.size(); i++)
        if (!isPREDA(words[i]))
            return false;
    return true;
}

// <preds> => <predstring> | <preds> A <predstring>
bool isPreds(vector<string> words)
{
    if (words.size() == 0)
        return false;

    // 找到起始的 PREDA 或 A
    for (int i = words.size() - 1; i >= 0; i--)
    {
        if (isPREDA(words[i]))
            continue;
        else if (words[i].length() == 1 && isA(words[i][0]))
        {
            if (i > 0)
            {
                vector<string> preds(words.begin(), words.begin() + i);
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
bool isPredname(vector<string> words)
{
    if (words.size() == 0)
        return false;
        
    if (!isLA(words.front()) && !isNAM(words.front()))
        return false;

    if (words.size() == 1 && isNAM(words.front()))
        return true;

    if (isLA(words.front()))
    {
        vector<string> predstring(words.begin() + 1, words.end());
        return isPredstring(predstring);
    }
    else
        return false;

    return true;
}

// <statement> => <predname> <verbpred> <predname> | <predname> <verbpred>
bool isStatement(vector<string> words)
{
    // 找到 <verbpred>
    int i, j;
    for (i = 0; i <= (words.size() - 2); i++)
        if (isMOD(words.at(i)))
        {
            // 提取 <verbpred> 之前的 <predname>
            vector<string> predname(words.begin(), words.begin() + i);
            
            // 找到构成 <verbpred> 在 MOD 之后的所有 PREDA，若未到 words 的末端，
            // 则句子可能是 statement 的第一种模式，否则可能是第二种模式
            for (j = i + 1; j < words.size(); j++)
                if (!isPREDA(words[j]))
                    break;
            if (j < (words.size() - 1))
            {
                vector<string> nextPredname(words.begin() + j, words.end());
                return isPredname(predname) && isPredname(nextPredname);
            }
            else
                return isPredname(predname);
        }

    return false;
}

// <predclaim> => <predname> BA <preds> | DA <preds>
bool isPredclaim(vector<string> words)
{
    // DA <preds>
    if (isDA(words.front()))
    {
        vector<string> preds(words.begin() + 1, words.end());
        return isPreds(preds);
    }

    // <predname> BA <preds>
    for (int i = 0; i < words.size(); i++)
    {
        if (isBA(words[i]))
        {
            vector<string> predname(words.begin(), words.begin() + i);
            vector<string> preds(words.begin() + i + 1, words.end());
            return isPredname(predname) && isPreds(preds);
        }
    }

    return false;
}

// <sentence> => <statement> | <predclaim>
bool isSentence(vector<string> words)
{
    if (words.size() == 0) return false;
    return isStatement(words) || isPredclaim(words);
}

int main(int argc, char *argv[])
{
    vector<string> words;

    string line, word;
    while (getline(cin, line), line != "#")
    {
        // 读入字符串，将其转换为单词数组以便判定。
        string newLine(line);
        if (line.find('.') != string::npos)
            newLine = newLine.substr(0, newLine.find('.'));

        istringstream iss(newLine);
        while (iss >> word)
            words.push_back(word);

        if (line.find('.') != string::npos)
        {
            cout << (isSentence(words) ? "Good" : "Bad!") << endl;
            words.clear();
        }
    }

    return 0;
}
