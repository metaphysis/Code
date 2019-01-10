#include <bits/stdc++.h>

using namespace std;

void parse1(string line)
{
    int start = 0, next = line.find(',', start);
    while (next != line.npos)
    {
        string block = line.substr(start, next - start);
        cout << block << endl;
        start = next + 1;
        next = line.find(',', start);
    }
    
    if (start < line.length())
        cout << line.substr(start) << endl;
}

void parse2(string line)
{
    istringstream iss(line);
    
    string block;
    while (getline(iss, block, ','))
        cout << block << endl;
}

int main(int argc, char *argv[])
{
    string line;
    getline(cin, line);
    parse1(line);
    parse2(line);
        
    return 0;
}
