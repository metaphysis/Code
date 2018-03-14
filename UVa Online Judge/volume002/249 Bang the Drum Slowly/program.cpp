// Bang the Drum Slowly
// UVa ID: 249
// Verdict: Accepted
// Submission Date: 2016-06-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NO_ADDRESS = -1;

struct address
{
    int address1, address2;
};

vector<address> instructions;
double memoization[50][50];
int n, t;

double execute(int, int);

double getTime(int current_address, int next_address)
{
    if (memoization[current_address][next_address] <= 0.0)
        memoization[current_address][next_address] = execute(current_address, next_address);
    return memoization[current_address][next_address];
}

// simulate execution of program, use memoization to store results, nor you will get TLE
double execute(int current_address, int next_address)
{
    if (memoization[current_address][next_address] > 0.0)
        return memoization[current_address][next_address];
        
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
    if (instructions[next_address].address1 > 0 && instructions[next_address].address2 == NO_ADDRESS)
        elapsed += getTime(current_address, instructions[next_address].address1);
    else if (instructions[next_address].address1 > 0 && instructions[next_address].address2 > 0)
    {
        double time1 = getTime(current_address, instructions[next_address].address1);
        double time2 = getTime(current_address, instructions[next_address].address2);
        elapsed += (time1 + time2) / 2.0;
    }

    return elapsed;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
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

        for (int i = 0; i < 50; i++)
            for (int j = 0; j < 50; j++)
                memoization[i][j] = 0.0;
                
        double execution_time = execute(0, 1);
        cout << "Case " << ++cases << ". Execution time = ";
        cout << fixed << setprecision(4) << execution_time << endl;
    }

    return 0;
}
