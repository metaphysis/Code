// Pascal Program Lengths
// UVa IDs: 189
// Verdict: Wrong Answer
// Submission Date: 2016-04-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

string program;
string operators[13] = {
    "<=", ">=", "<>", ":=", "@", "^", "+", "-", "*", "/", "=", "<", ">", 
};

int count()
{
    for (int i = 0; i < program.length(); i++)
        if (isalpha(program[i]))
            program[i] = tolower(program[i]);
            
    int counter = 0;
    
    // comment
    int index = 0;
    while (index < program.length())
    {
        if (program[index] == '{')
        {
            program[index++] = ' ';
            while (index < program.length())
            {
                char current = program[index];
                program[index] = ' ';
                if (current == '}')
                    break;
                index++;    
            }
        }
        
        index++;
    }
    
    //cout << program << endl;
    
    // string constant
    index = 0;
    string quotes;
    while (index < program.length())
    {
        if (program[index] == '\'')
        {
            counter++;
            program[index++] = ' ';
            while (index < program.length())
            {
                char current = program[index];
                if (current == '\'' && (index + 1) < program.length())
                {
                    if (program[index + 1] == '\'')
                    {
                        program[index] = ' ';
                        program[index + 1] = ' ';
                        index++;
                    }
                    else
                    {
                        program[index] = ' ';
                        break;
                    }
                }
                else
                    program[index] = ' ';
                index++;
            }
                
        }
        index++;
    }
    
    //cout << program << endl;
    
    // braces
    index = 0;
    while (index < program.length())
    {
        if (program[index] == '(' || program[index] == '[')
        {
            counter++;
            program[index] = ' ';
        }
        else if (program[index] == ')' || program[index] == ']')
        {
            program[index] = ' ';
        }
        index++;
    }
    
    //cout << program << endl;
    
    // identifiers
    index = 0;
    int last = program.find("begin");
    if (last == program.npos)
        last = program.length();
    vector <string> variables;
    while (index < last)
    {
        if (isalpha(program[index]) || program[index] == '_')
        {
            string block;
            block += program[index];
            counter++;
            program[index++] = ' ';
            while (index < last)
                if (isalpha(program[index]) || isdigit(program[index]) ||
                    program[index] == '_')
                {
                    block += program[index];
                    program[index++] = ' ';
                }
                else
                    break;
            variables.push_back(block);
        }
        index++;
    }        

    //for (int i = 0; i < variables.size(); i++)
        //cout << variables[i] << endl;
        
    index = 0;
    while (index < variables.size())
    {
        int next = program.find(variables[index]);
        while (next != program.npos)
        {
            if (isalpha(program[next - 1]) == false &&
                isdigit(program[next - 1]) == false &&
                program[next - 1] != '_' &&
                isalpha(program[next + variables[index].length()]) == false &&
                isdigit(program[next + variables[index].length()]) == false &&
                program[next + variables[index].length()] != '_')
            {
                counter++;
                for (int i = 0; i < variables[index].length(); i++)
                    program[next + i] = ' ';            
            }
            next += variables[index].length();
            next = program.find(variables[index], next);
        }
        index++;
    }
    
    //cout << program << endl;
    
    // number
    index = 0;
    while (index < program.length())
    {
        if (program[index] == '$')
        {
            counter++;
            program[index++] = ' ';
            while (index < program.length())
            {
                char current = program[index];
                if (isdigit(current) || (current >= 'a' && current <= 'f'))
                    program[index] = ' ';
                else
                    break;
                index++;
            }
        }
        else if (isdigit(program[index]))
        {
            counter++;
            program[index++] = ' ';
            while (index < program.length())
                if (isdigit(program[index]))
                    program[index++] = ' ';
                else
                    break;
                
            if (index < program.length() && program[index] == '.')
            {
                program[index++] = ' ';
                while (index < program.length())
                    if (isdigit(program[index]))
                        program[index++] = ' ';
                    else
                        break;
            }
            
            if (index < program.length() && program[index] == 'e')
            {
                program[index++] = ' ';
                if (program[index] == '+' || program[index] == '-')
                    program[index++] = ' ';
                while (index < program.length() && isdigit(program[index]))
                    program[index++] = ' ';
            }
        }
        
        index++;
    }
    
    //cout << program << endl;
    
    // operators
    for (int i = 0; i < 13; i++)
    {
        int start = 0;
        int next = program.find(operators[i], start);
        while (next != program.npos)
        {
            counter++;
            for (int j = 0; j < operators[i].length(); j++)
                program[next + j] = ' ';
            start = next + operators[i].length();
            next = program.find(operators[i], start);
        }
    }
    
    //cout << program << endl;
    
    // others
    index = 0;
    while (index < program.length())
    {
        if (isalpha(program[index]))
        {
            counter++;
            program[index++] = ' ';
            while (index < program.length())
                if (isalpha(program[index]))
                    program[index++] = ' ';
                else
                    break;
        }
        index++;
    }
    
    //cout << program << endl;
    
    return counter;
}

void output(string name)
{
    int units = count();
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
            output(line.substr(2));
            program.clear();
        }
        else
        {
            program += line;
            program += ' ';
        }
    }
    
	return 0;
}
