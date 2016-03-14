// Pascal Program Lengths
// UVa IDs: 189
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector < string > program;

string operators[13] = {
    "(", "{", "+", "-", "*", "/", "=", "<", ">", "<=", ">=", "<>", "@", "^", ":="
};

string reserves[] = {
    "AND", "ARRAY", "BEGIN", "CASE", "CONST", "DIV", "DO",
    "DIWNTO", "ELSE", "END", "FILE", "FOR", "FUNTION",
    "GOTO", "IF", "LABEL", "MOD", "NIL", "OF", "OR", "PACKED",
    "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "THEN",
    "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH"
};

bool isIdentifier(string token)
{
    if (token.length() == 0)
        return false;
    
    // leading character is a-z, A-Z, _
    if (isalpha(token.front()) == false && token.front() != '_')
        return false;
    
    // following character can be a-z, A-Z, _, 0-9
    for (int i = 1; i < token.length(); i++)
        if (isalpha(token[i]) == false && token[i] != '_' &&
            isdigit(token[i]) == false)
                return false;
                
    return true;
}

void getUnits(string name)
{
    for (int i = 0; i < program.size(); i++)
        cout << program[i] << endl;
        
    int units = 0;
    cout << "Program by " << name << " contains " << units << " units.\n";
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        string firstTwoColumns = line.substr(0, 2);
        if (firstTwoColumns == "~~")
        {
            getUnits(line.substr(2));
            program.clear();
        }
        else
            program.push_back(line);
    }
    
	return 0;
}
