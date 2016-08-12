// Last Name First, Please
// UVa ID: 597
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct file
{
    string firstname, lastname, extension;
};

file files[20];
int file_count = 0;

void parse(string& line)
{
    int space = line.find(' '), period = line.find('.');
    files[file_count].firstname = line.substr(0, space);
    files[file_count].lastname = line.substr(space + 1, period - space - 1);
    files[file_count].extension = line.substr(period);
    file_count++;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);


    while (getline(cin, line))
    {
        file_count = 0;
        parse(line);
        while (getline(cin, line), line.length() > 0)
            parse(line);
        
    }
    
	return 0;
}
