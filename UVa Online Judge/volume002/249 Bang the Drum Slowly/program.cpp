// Bang the Drum Slowly
// UVa IDs: 249
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

const int NO_ADDRESS = -1;

struct address
{
    int address1, address2;
};

vector < address > instructions;
int n, t;

// simulate execution of program
double execute(int current_address, int next_address)
{
    // seek the next address
    double elapsed = 0.0;
    if (current_address < next_address)
        elapsed += (next_address - current_address);
    else
        elapsed += (n - current_address + next_address);

    // execute the instruction and jump to next address
    elapsed += t;
    current_address = next_address;
    current_address += t;
    current_address = (current_address > n) ? (current_address - n) : current_address;

    // continue execution
    if (instructions[next_address].address1 > 0
        && instructions[next_address].address2 == NO_ADDRESS)
        elapsed += execute(current_address, instructions[next_address].address1);
    else if (instructions[next_address].address1 > 0 && instructions[next_address].address2 > 0)
    {
        double time1 = execute(current_address, instructions[next_address].address1);
        double time2 = execute(current_address, instructions[next_address].address2);
        elapsed += (time1 + time2) / 2.0;
    }

    return elapsed;
}

// find directed circle by topological sort
bool findCircle()
{
    vector < int >in(n + 1);

    fill(in.begin(), in.end(), 0);

    for (int i = 1; i <= n; i++)
    {
        if (instructions[i].address1 > 0)
            in[instructions[i].address1]++;
        if (instructions[i].address2 > 0)
            in[instructions[i].address2]++;
    }

    bool looped = false;
    int nodes = n;
    while (nodes > 0)
    {
        int index = 0;
        for (int i = 1; i <= n; i++)
            if (in[i] == 0)
            {
                index = i;
                break;
            }

        if (index == 0)
        {
            looped = true;
            break;
        }

        nodes--;

        in[index]--;
        if (instructions[index].address1 > 0)
            in[instructions[index].address1]--;
        if (instructions[index].address2 > 0)
            in[instructions[index].address2]--;
    }

    return looped;
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n >> t, n && t)
    {
        instructions.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            instructions[i].address1 = NO_ADDRESS;
            instructions[i].address2 = NO_ADDRESS;
        }

        int indexer, addresses;
        while (cin >> indexer, indexer > 0)
        {
            cin >> addresses;

            instructions[indexer].address1 = addresses;
            if (addresses >= 1)
                cin >> instructions[indexer].address1;
            if (addresses >= 2)
                cin >> instructions[indexer].address2;
        }

        ++cases;

        if (findCircle())
        {
            cout << "Case " << cases << " is looped!" << endl;
            assert(false);
        }

        double execution_time = execute(0, 1);
        cout << "Case " << cases << ". Execution time = ";
        cout << fixed << setprecision(4) << execution_time << endl;
    }

    return 0;
}
