// Typesetting
// UVa IDs: 235
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int fontSize[110][10];
map<char, int> indexer;
int paragraph = 0, cases = 0;
int L, W;

void process(string lines)
{
    cout << "Paragraph " << ++paragraph << endl;
    
    int sizes = 1, points = 10;
    int lastSizes = 1, lastPoints = 10;
    int currentWidth = 0;
    int printedLines = 0;
    bool firstWordSetted = false;
    
    string firstWord, lastWord, word;
    istringstream iss(lines);
    
    while (iss >> word)
    {
        if (word == "*f1" || word == "*f2" || word == "*f3" || word == "*f4" || word == "*f5" || word == "*f6")
        {
            sizes = stoi(word.substr(2));
            continue;
        }

        if ((word.length() == 3 && word[0] == '*' && word[1] == 's' & word[2] >= '1' && word[2] <= '9') ||
            (word.length() == 4 && word[0] == '*' && word[1] == 's' & word[2] >= '1' && word[2] <= '9' && word[3] >= '0' && word[3] <= '9'))
        {
            points = stoi(word.substr(2));
            continue;
        }

        double tempWidth = (int)round(lastPoints / 10.0 * fontSize[indexer[' ']][lastSizes]);
        int singleBlankWidth = (int)round(tempWidth);
        
        int singleWordWidth = 0;
        for (int i = 0; i < word.length(); i++)
        {
            tempWidth = points / 10.0 * fontSize[indexer[word[i]]][sizes];
            singleWordWidth += (int)round(tempWidth);
        }
        
        lastSizes = sizes;
        lastPoints = points;
                
        if (singleWordWidth <= W)
        {
            if (firstWordSetted == false)
            {
                firstWord = word;
                lastWord = word;
                firstWordSetted = true;
                currentWidth = singleWordWidth;
                continue;
            }
            
            if (currentWidth + singleBlankWidth + singleWordWidth <= W)
            {
                lastWord = word;
                currentWidth += singleBlankWidth + singleWordWidth;
                continue;
            }
            else
            {
                cout << "Line " << ++printedLines << ": ";
                cout << firstWord << " ... " << lastWord;
                cout << " (" << (W - currentWidth) << " whitespace)" << endl;
                
                firstWord = word;
                lastWord = word;
                firstWordSetted = true;
                currentWidth = singleWordWidth;
            }
        }
        else
        {
            if (currentWidth > 0)
            {
                cout << "Line " << ++printedLines << ": ";
                cout << firstWord << " ... " << lastWord;
                cout << " (" << (W - currentWidth) << " whitespace)" << endl;
            }

            cout << "Line " << ++printedLines << ": ";
            cout << word << " (" << (W - singleWordWidth) << " whitespace)" << endl;
            
            firstWordSetted = false;
            currentWidth = 0;
        }
    }
    
    if (currentWidth > 0)
    {
        cout << "Line " << ++printedLines << ": ";
        cout << firstWord << " ... " << lastWord;
        cout << " (" << (W - currentWidth) << " whitespace)" << endl;
    }
}

int main(int argc, char *argv[])
{
    string line;
    getline(cin, line);
    int n = stoi(line);
    
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        
        istringstream iss(line);
        if (line.front() == ' ')
            indexer.insert(make_pair(' ', i));
        else
        {
            char character;
            iss >> character;
            indexer.insert(make_pair(character, i));
        }
        
        for (int j = 1; j <= 6; j++)
            iss >> fontSize[i][j];
    }
    
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> L >> W;
        
        if (L == 0)
            break;
        
        string allLines;    
        for (int i = 1; i <= L; i++)
        {
            getline(cin, line);
            allLines += line + ' ';
        }
        
        process(allLines);
    }

	return 0;
}
