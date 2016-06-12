// Presentation Error
// UVa IDs: 
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

int main(int argc, char *argv[])
{
    string line;
    getline(cin, line);
    
    int cases = stoi(line);
    while (cases--)
    {
        getline(cin, line);
        
        istringstream iss(line);
        
        int jury_line, submit_line;
        iss >> jury_line >> submit_line;
        
        vector <string> jury, submit;
        for (int i = 1; i <= jury_line; i++)
        {
            getline(cin, line);
            while (isblank(line.back()))
                line.erase(line.end() - 1);
            if (line.length() > 0)
                jury.push_back(line);
        }
        
        bool is_wa = false;
        for (int i = 1; i <= submit_line; i++)
        {
            getline(cin, line);
            while (isblank(line.back()))
                line.erase(line.end() - 1);
            if (line.length() > 0)
                submit.push_back(line);
            if (line.find('[') != line.npos || line.find(']') != line.npos)
                is_wa = true;
        }
        
        if (is_wa)
        {
            cout << "Wrong Answer" << endl;
            continue;
        }
        
        if (jury.size() == submit.size())
        {
            bool is_same = true;
            for (int i = 0; i < jury.size(); i++)
                if (jury[i] != submit[i])
                {
                    is_same = false;
                    break;
                }
            if (is_same)
            {
                cout << "Accepted" << endl;
                continue;
            }
        }
        
        string juryText, submitText;
        for (int i = 0; i < jury.size(); i++)
            juryText += jury[i];
            
        for (int i = 0; i < submit.size(); i++)
            submitText += submit[i] + ']';
            
        for (int i = 0; i < juryText.length(); i++)
            if (isalpha(juryText[i]))
                juryText[i] = toupper(juryText[i]);
                    
        for (int i = 0; i < submitText.length(); i++)
            if (isalpha(submitText[i]))
                submitText[i] = toupper(submitText[i]);
                
        vector <string> essentials;
        int indexer = 0;
        while (indexer < juryText.length())
        {
            if (juryText[indexer] == '[')
            {
                indexer++;
                string block;
                while (juryText[indexer] != ']')
                {
                    block += juryText[indexer];
                    indexer++;
                }
                essentials.push_back(block);
            }
            
            indexer++;
        }
        
        int start = 0, key = 0;
        while (start < submitText.length() && key < essentials.size())
        { 
            start = submitText.find(essentials[key], start);
            if (start == submitText.npos)
                break;
            start += essentials[key].length();
            key++;
        }
        
        if (key < essentials.size())
            cout << "Wrong Answer" << endl;
        else
            cout << "Presentation Error" << endl;
    }
    
	return 0;
}
