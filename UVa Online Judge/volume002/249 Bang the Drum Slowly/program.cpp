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

struct address
{
    int address1, address2;
};

vector<address> instructions;
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
    if (instructions[next_address].address1 > 0 && instructions[next_address].address2 == 0)
        elapsed += execute(current_address, instructions[next_address].address1);
    else if (instructions[next_address].address1 > 0 && instructions[next_address].address2 > 0)
    {
        double time1 = execute(current_address, instructions[next_address].address1);
        double time2 = execute(current_address, instructions[next_address].address2);
        elapsed += (time1 + time2) / 2.0;
    }
    
    return elapsed;
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n >> t, n && t)
    {
        instructions.resize(n + 1);
        int indexer, addresses, address1, address2;
        while (cin >> indexer, indexer > 0)
        {
            address1 = 0, address2 = 0;
            cin >> addresses;
            if (addresses == 1)
                cin >> address1;
            else if (addresses == 2)
                cin >> address1 >> address2;
            instructions[indexer] = (address){address1, address2};
        }
        
        assert(cases <= 1125);
        
        double execution_time = execute(0, 1);
        cout << "Case " << ++cases << ". Execution time = ";
        cout << fixed << setprecision(4) << execution_time << endl;
    }
    
	return 0;
}
