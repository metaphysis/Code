// Cellular Structure
// UVa ID: 620
// Verdict: Accepted
// Submission Date: 2016-08-28
// UVa Run Time: 0.000s
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

bool is_fully_grown(string cell);
bool is_mutangenic(string cell);

bool is_simple(string cell)
{
    return cell.length() == 1 && cell.front() == 'A';
}

bool is_fully_grown(string cell)
{
    if (cell.length() <= 2)
        return false;
    
    if (cell.back() == 'B')
    {
        cell.erase(cell.end() - 1);
        if (cell.back() == 'A')
        {
            cell.erase(cell.end() - 1);
            return is_simple(cell) || is_fully_grown(cell) || is_mutangenic(cell);
        }
    }

    return false;
}

bool is_mutangenic(string cell)
{
    if (cell.length() <= 2)
        return false;
    
    if (cell.back() == 'A')
    {
        cell.erase(cell.end() - 1);
        if (cell.front() == 'B')
        {
            cell.erase(cell.begin());
            return is_simple(cell) || is_fully_grown(cell) || is_mutangenic(cell);
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    cin >> n;
    
    string line;
    for (int i = 1; i <= n; i++)
    {
        cin >> line;
        if (is_simple(line))
            cout << "SIMPLE\n";
        else if (is_fully_grown(line))
            cout << "FULLY-GROWN\n";
        else if (is_mutangenic(line))
            cout << "MUTAGENIC\n";
        else
            cout << "MUTANT\n";
    }
    
	return 0;
}
