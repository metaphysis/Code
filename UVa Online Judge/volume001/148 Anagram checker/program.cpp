// Anagram checker
// UVa ID: 148
// Verdict: Accepted
// Submission Date: 2016-01-22
// UVa Run Time: 0.059s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct item
{
    string word;
    int count[26];
};

item words[2001];
int goalCount[26], currentCount[26];
vector < string > single;
bool used[2001];
int wordGet[2001], indexGet, total;
string targetLine;

void isGood()
{
    bool good = true;
    for (int i = 0; i < 26; i++)
        if (currentCount[i] != goalCount[i])
        {
            good = false;
            break;
        }
    
    if (!good)
        return;
        
    if (indexGet == single.size())
    {
        vector < string > t1(single);
        vector < string > t2;
        
        for (int i = 0; i < indexGet; i++)
            t2.push_back(words[wordGet[i]].word);
            
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        
        bool good = false;
        for (int i = 0; i < t1.size(); i++)
            if (t1[i] != t2[i])
            {
                good = true;
                break;
            }
            
        if (!good)
            return;
    }
    
    cout << targetLine << " =";
    for (int i = 0; i < indexGet; i++)
        cout << " " << words[wordGet[i]].word;
    cout << endl;
}

void backtrack(int start, int length, int target)
{
    if (length == target)
    {
        isGood();
        return;
    }
    
    for (int i = start; i < total; i++)
    {
        if (used[i])
            continue;
            
        if ((length + words[i].word.length()) > target)
            continue;
        
        bool good = true;
        for (int j = 0; j < 26; j++)
            if ((words[i].count[j] + currentCount[j]) > goalCount[j])
            {
                good = false;
                break;
            }
        if (!good)
            continue;
              
        wordGet[indexGet++] = i;
        used[i] = true;
        for (int j = 0; j < 26; j++)
            currentCount[j] += words[i].count[j];
        backtrack(i + 1, length + words[i].word.length(), target);
        for (int j = 0; j < 26; j++)
            currentCount[j] -= words[i].count[j];
        used[i] = false;
        indexGet--;
    }
        
}

int main(int argc, char *argv[])
{
    string line;
    total = 0;
    while (getline(cin, line), line != "#")
    {
        item aItem;
        aItem.word = line;
        memset(aItem.count, 0, sizeof(aItem.count));
        for (int i = 0; i < line.length(); i++)
            aItem.count[line[i] - 'A']++;

        words[total++] = aItem;
    }
    
    while (getline(cin, line), line != "#")
    {
        int alphaCount = 0;
        targetLine.assign(line);
        
        memset(goalCount, 0, sizeof(goalCount));
        for (int i = 0; i < line.length(); i++)
            if (isalpha(line[i]))
            {
                goalCount[line[i] - 'A']++;
                alphaCount++;
            }
                
        single.clear();
        istringstream iss(line);
        string word;
        while (iss >> word)
            single.push_back(word);
            
        memset(currentCount, 0, sizeof(currentCount));
        memset(used, 0 , sizeof(used));
        indexGet = 0;
        backtrack(0, 0, alphaCount);
    }
    
	return 0;
}
