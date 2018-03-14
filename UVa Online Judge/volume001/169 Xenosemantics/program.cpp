// Xenosemantics
// UVa ID: 169
// Verdict: Accepted
// Submission Date: 2016-02-19
// UVa Run Time: 0.006s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct letter
{
    char character;
    int index;
};

struct word
{
    string text;
    int start;
};

bool operator<(letter x, letter y)
{
    return x.character < y.character;
}

bool operator<(word x, word y)
{
    if (x.start == y.start)
        return x.text.length() < y.text.length();
    else
        return x.start < y.start;
}

// check two words are overlapped or not
bool isOverlapped(word x, word y)
{
    int xend = x.start + x.text.length() - 1;
    int yend = y.start + y.text.length() - 1;
    
    return x.start >= y.start && x.start <= yend ||
        xend >= y.start && xend <= yend ||
        y.start >= x.start && y.start <= xend ||
        yend >= x.start && yend <= xend;
}

bool cmpWord(word x, word y)
{
    if (isOverlapped(x, y))
    {
        int xend = x.start + x.text.length();
        int yend = y.start + y.text.length();
        if (xend != yend)
            return xend < yend;
        else
            return x.start < y.start;
    }
    else
        return x.start < y.start;
}

string block;
vector<letter> letters;
vector<word> words;
map<string, vector<word>> candidates;
vector<vector<word>> trueWords;

void findTrueWord()
{
    //cout << block << endl;
    
    if (block.length() <= 3)
    {
        cout << "*\n";
        return;
    }
    
    stable_sort(letters.begin(), letters.end());
    
    //for (int i = 0; i < letters.size(); i++)
        //cout << setw(3) << right << letters[i].character;
    //cout << endl;
    //for (int i = 0; i < letters.size(); i++)
        //cout << setw(3) << right << letters[i].index;
    //cout << endl;
    
    words.clear();
    for (int i = 0; i < letters.size() - 1; i++)
        if (letters[i].character == letters[i + 1].character)
        {
            int length = letters[i + 1].index - letters[i].index - 1;
            if (length < 2 || length > 250)
                continue;
            string something = block.substr(letters[i].index + 1, length);
            words.push_back((word){something, letters[i].index + 1});
        }
    
    // add word from start with first character  
    for (int i = 2; i < block.length() && i <= 260; i++)
    {
        string falseWord = block.substr(0, i);
        if (falseWord.find(block[i]) != falseWord.npos)
            continue;
        words.push_back((word){falseWord, 0});
    }
    
    // add word end with last character
    for (int i = 2; i < block.length() && i <= 260; i++)
    {
        int index = block.length() - i;
        string falseWord = block.substr(index, i);
        if (falseWord.find(block[index - 1]) != falseWord.npos)
            continue;
        words.push_back((word){falseWord, index});
    }
    
    sort(words.begin(), words.end());
    
    //for (int i = 0; i < words.size(); i++)
        //cout << words[i].text << endl;
        
    candidates.clear();
    for (int i = 0; i < words.size(); i++)
    {
        string temp = words[i].text;
        sort(temp.begin(), temp.end());
        if (candidates.count(temp) == 0)
        {
            vector < word > list;
            list.push_back(words[i]);
            candidates[temp] = list;
        }
        else
        {
            candidates[temp].push_back(words[i]);
        }
    }
    
    trueWords.clear();
    for (map<string, vector<word>>::iterator it = candidates.begin(); it != candidates.end(); it++)
        if ((*it).second.size() > 1)
            trueWords.push_back((*it).second);
    
    vector < bool > isTrueWord;
    for (int i = 0; i < trueWords.size(); i++)
        isTrueWord.push_back(false);
        
    for (int i = 0; i < trueWords.size(); i++)
    {
        if (isTrueWord[i])
            continue;

        for (int j = 0; j < trueWords[i].size(); j++)
        {
            bool found = false;
            for (int m = 0; m < trueWords.size(); m++)
            {
                if (m == i)
                    continue;
                    
                found = false;
                for (int k = 0; k < trueWords[m].size(); k++)
                {
                    if (isOverlapped(trueWords[i][j], trueWords[m][k]))
                    {
                        isTrueWord[i] = true;
                        isTrueWord[m] = true;
                        found = true;
                        break;
                    }
                }
                
                if (found)
                    break;
            }
            if (found)
                break;
       }
    }
    
    words.clear();
    for (int i = 0; i < trueWords.size(); i++)
        if (isTrueWord[i])
            words.push_back(trueWords[i][0]);
    
    // sort the true words, attention: If the first appearances of two 
    // words overlap, then the word that finishes first precedes the other
    sort(words.begin(), words.end(), cmpWord);
    for (int i = 0; i < words.size(); i++)
        cout << words[i].text << "\n";
    cout << "*\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line;
    bool ended = false;
    while (getline(cin, line), line != "#")
    {
        for (int i = 0; i < line.length(); i++)
            if ('a' <= line[i] && line[i] <= 'z')
            {
                block += line[i];
                letters.push_back((letter){line[i], block.length() - 1});
            }
                
        ended = line[line.length() - 1] != '-';
            
        if (ended)
        {
            findTrueWord();
            letters.clear();
            block.clear();
            ended = false;
        }
    }
    
	return 0;
}
