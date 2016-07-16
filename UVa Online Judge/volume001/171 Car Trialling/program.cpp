// Car Trialling
// UVa ID: 171
// Verdict: Accepted
// Submission Date: 2016-03-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const int GO = 0, KEEP = 1, RIGHT = 2, LEFT = 3, FIRST = 4, SECOND = 5,
    THIRD = 6, AT = 7, RECORD = 8, TIME = 9, TO = 10, KMH = 11,
    CHANGE = 12, AVERAGE = 13, SPEED = 14, CAS = 15, NNN = 16, SIGNWORDS = 17,
    AND = 18, THEN = 19, QUOTE = 20, NONE = 21, TO_NNN_KMH = 22,
    TIME_KEEPING = 23, WHEN = 24, DIRECTION = 25, DIRECTIONAL = 26,
    INSTRUCTION = 27, AND_THEN = 28, NAVIGATIONAL = 29, WHERE = 30, HOW = 31;

string debug[] = {
    "GO", "KEEP", "RIGHT", "LEFT", "FIRST", "SECOND",
    "THIRD", "AT", "RECORD", "TIME", "TO", "KMH",
    "CHANGE", "AVERAGE", "SPEED", "CAS", "NNN", "SIGNWORDS",
    "AND", "THEN", "QUOTE", "NONE", "TO_NNN_KMH",
    "TIME_KEEPING", "WHEN", "DIRECTION", "DIRECTIONAL",
    "INSTRUCTION", "AND_THEN", "NAVIGATIONAL", "WHERE", "HOW"
};

string texts[] = { "GO", "KEEP", "RIGHT", "LEFT", "FIRST", "SECOND",
    "THIRD", "AT", "RECORD", "TIME", "TO", "KMH",
    "CHANGE", "AVERAGE", "SPEED", "CAS", "NNN", "#SIGNWORDS",
    "AND", "THEN", "#QUOTE", "#NONE"
};

const int groupCount = 22;

int groups[22][4] = {
    {AVERAGE, CHANGE, SPEED, CAS},
    {THEN, AND, NONE, AND_THEN},
    {NNN, TO, KMH, TO_NNN_KMH},
    {TO_NNN_KMH, CAS, NONE, TIME_KEEPING},
    {TIME, RECORD, NONE, TIME_KEEPING},
    {AT, NONE, SIGNWORDS, WHERE},
    {FIRST, NONE, NONE, WHEN},
    {SECOND, NONE, NONE, WHEN},
    {THIRD, NONE, NONE, WHEN},
    {RIGHT, NONE, NONE, DIRECTION},
    {LEFT, NONE, NONE, DIRECTION},
    {KEEP, NONE, NONE, HOW},
    {WHEN, GO, NONE, HOW},
    {GO, NONE, NONE, HOW},
    {DIRECTION, HOW, WHERE, DIRECTIONAL},
    {DIRECTION, HOW, NONE, DIRECTIONAL},
    {AND_THEN, DIRECTIONAL, DIRECTIONAL, NAVIGATIONAL},
    {AND_THEN, NAVIGATIONAL, DIRECTIONAL, NAVIGATIONAL},
    {DIRECTIONAL, NONE, NONE, NAVIGATIONAL},
    {AND, NAVIGATIONAL, TIME_KEEPING, INSTRUCTION},
    {TIME_KEEPING, NONE, NONE, INSTRUCTION},
    {NAVIGATIONAL, NONE, NONE, INSTRUCTION}
};

vector < int > symbols;

string spaceReduced(string line)
{
    istringstream iss(line);
    string word;
    vector < string > words;
    while (iss >> word)
        words.push_back(word);
    
    bool inQuote = false;
    string newLine;
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i].find('\"') != string::npos)
        {
            if (inQuote == false)
            {
                newLine += words[i];
                inQuote = true;
                
                if (words[i].length() > 1)
                    newLine += " ";
            }
            else
            {
                inQuote = false;
                if (words[i].length() > 1)
                {
                    newLine += words[i];
                    newLine += " ";
                }
                else
                {
                    newLine.erase(newLine.end() - 1);
                    newLine += words[i];
                }
            }
        }
        else
        {
            newLine += words[i];
            newLine += " ";
        }
    }
    
    if (newLine[newLine.length() - 1] == ' ')
        newLine.erase(newLine.end() - 1);
    if (line.length() > 0 && isblank(line.front()))
        newLine = ' ' + newLine;
    if (line.length() > 0 && isblank(line.back()))
        newLine = newLine + ' ';
        
    return newLine;
}

int getSymbol(string word)
{
    int symbol = find(texts, texts + 22, word) - texts;
    if (symbol >= GO && symbol <= THEN)
        return symbol;

    // is nnn
    if ('0' <= word[0] && word[0] <= '9')
    {
        for (int i = 0; i < word.length(); i++)
            if (word[i] < '0' || word[i] > '9')
                return NONE;
        return NNN;
    }

    // is signwords
    if (word[0] == '\"' &&
        word.length() >= 3 && word[word.length() - 1] == '\"')
    {
        if (word[1] == '_' || word[word.length() - 2] == '_')
            return NONE;
            
        for (int i = 1; i < word.length() - 1; i++)
        {
            if (word[i] == '.')
            {
                if (word[i - 1] == '_')
                    return NONE;
                else
                    continue;
            }
            
            if (word[i] == '_')
                continue;
                    
            if ((word[i] < 'A' || word[i] > 'Z'))
                return NONE;
        }
        
        return SIGNWORDS;
    }

    return NONE;
}

bool translateToSymbol(string line)
{
    // check whether special character exists or not
    if (line.find('_') != line.npos || line.find('#') != line.npos)
        return false;
    
    // change space to _ between a pairs of quote
    bool quoteStart = false;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '\"')
            quoteStart = !quoteStart;
        else if ((line[i] == ' ' || line[i] == '\t') && quoteStart)
            line[i] = '_';
    }

    // translate word to symbol
    symbols.clear();
    istringstream iss(line);
    string word;
    while (iss >> word)
    {
        int symbol = getSymbol(word);
        if (symbol == NONE)
            return false;
        symbols.push_back(symbol);
    }

    return true;
}

bool isInstruction(string line)
{
    if (translateToSymbol(line) == false)
        return false;

    for (int i = 0; i < groupCount; i++)
    {
        while (true)
        {
            bool found = false;
            for (int j = 0; j < symbols.size(); j++)
            {
                //cout << "current: " << debug[symbols[j]] << endl;
                if (symbols[j] == groups[i][0])
                {
                    ///cout << "find: " << debug[symbols[j]] << endl;
                    if (groups[i][1] != NONE && j == 0)
                        continue;
                        
                    if (groups[i][2] != NONE && j == (symbols.size() - 1))
                        continue;
                        
                    if (groups[i][1] == NONE && groups[i][2] == NONE)
                    {
                        //cout << "REDUCED: " << debug[symbols[j]];
                        //cout << " TO " << debug[groups[i][3]] << endl;
                        
                        found = true;
                        symbols[j] = groups[i][3];
                        break;
                    }
                    
                    if (groups[i][1] != NONE && groups[i][2] != NONE)
                    {
                        if (symbols[j - 1] == groups[i][1] && symbols[j + 1] == groups[i][2])
                        {
                            //cout << "REDUCED: " << debug[symbols[j - 1]] << " " << debug[symbols[j]] << " " << debug[symbols[j + 1]];
                            //cout << " TO " << debug[groups[i][3]] << endl;
                            
                            found = true;
                            symbols[j - 1] = groups[i][3];
                            symbols.erase(symbols.begin() + j + 1);
                            symbols.erase(symbols.begin() + j);
                            break;
                        }
                    }
                    else if (groups[i][1] != NONE && symbols[j - 1] == groups[i][1])
                    {
                        //cout << "REDUCED: " << debug[symbols[j - 1]] << " " << debug[symbols[j]];
                        //cout << " TO " << debug[groups[i][3]] << endl;
                        
                        found = true;
                        symbols[j - 1] = groups[i][3];
                        symbols.erase(symbols.begin() + j);
                        break;
                    }
                    else if (groups[i][2] != NONE && symbols[j + 1] == groups[i][2])
                    {
                        //cout << "REDUCED: " << debug[symbols[j]] << " " << debug[symbols[j + 1]];
                        //cout << " TO " << debug[groups[i][3]] << endl;
                        
                        found = true;
                        symbols[j] = groups[i][3];
                        symbols.erase(symbols.begin() + j + 1);
                        break;
                    }
                }
            }
                          
            if (found == false)
                break;
                
            //for (int k = 0; k < symbols.size(); k++)
                //cout << debug[symbols[k]] << " ";
            //cout << endl;
        }
    }
    
    return (symbols.size() == 1 && symbols[0] == INSTRUCTION);
}

int main(int argc, char *argv[])
{
    string line, result;
    int lineNumber = 1;
    while (getline(cin, line), line != "#")
    {
        result = "Trap!";
        if (isInstruction(line))
            result = spaceReduced(line);
        cout << setw(3) << right << (lineNumber++) << ". " << result << "\n";
    }

    return 0;
}
