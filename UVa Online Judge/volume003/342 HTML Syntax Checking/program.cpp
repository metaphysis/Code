// HTML Syntax Checking
// UVa ID: 342
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.070s
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
    ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n)
    {
        cin.ignore(1024, '\n');
        cin.unsetf(ios::skipws);
        
        cout << "Test Case " << ++cases << endl;
        
        int lines = 1;
        char letter;
        bool error = false;
        stack<string> tags;
        
        while (cin >> letter)
        {
            if (letter == '\n')
            {
                lines++;
                if (lines > n) break;
            }
            
            if (error) continue;
            
            if (letter == '<')
            {
                string tag;
                bool closing = false;
                while (cin >> letter)
                {
                    if (letter == '\n')
                    {
                        cout << "line " << lines << ": bad character in tag name." << endl;
                        error = true;
                        lines++;
                        break;
                    }
                    else if (letter == '/')
                    {
                        if (closing == false)
                        {
                            closing = true;
                            continue;
                        }
                        else
                        {
                            cout << "line " << lines << ": bad character in tag name." << endl;
                            error = true;
                            break;
                        }
                    }
                    else if (letter == '>')
                    {
                        break;
                    }
                    else if (letter < 'A' || letter > 'Z')
                    {
                        cout << "line " << lines << ": bad character in tag name." << endl;
                        error = true;
                        break;
                    }
                    
                    tag += letter;
                    
                    if (tag.length() > 10)
                    {
                        cout << "line " << lines << ": too many/few characters in tag name." << endl;
                        error = true;
                        break;
                    }
                }
                
                if (error == false)
                {
                    if (tag.length() == 0)
                    {
                        cout << "line " << lines << ": too many/few characters in tag name." << endl;
                        error = true;
                    }
                    else if (closing)
                    {
                        if (tags.empty())
                        {
                            cout << "line " << lines << ": no matching begin tag." << endl;
                            error = true;
                        }
                        else if (tags.top() != tag)
                        {
                            cout << "line " << lines << ": expected </" << tags.top() << ">" << endl;
                            error = true;
                        }
                        else tags.pop();
                    }
                    else tags.push(tag);
                }
                
                if (lines > n) break;
            }
        }
        
        if (error == false && tags.empty() == false)
        {
            cout << "line " << (lines - 1) << ": expected </" << tags.top() << ">" << endl;
            error = true;
        }
        
        if (!error) cout << "OK" << endl;
        
        cin.setf(ios::skipws);
    }
    
	return 0;
}
