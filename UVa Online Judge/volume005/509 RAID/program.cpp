// RAID!
// UVa ID: 509
// Verdict: Accepted
// Submission Date: 2017-04-26
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int disk, size, block;
    char parity, bit;
    char hexadecimal[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    
    while (cin >> disk, disk > 0)
    {
        cin >> size >> block >> parity;
        
        vector<vector<string>> data(block, vector<string>());

        // read input.
        for (int i = 0; i < disk; i++)
            for (int j = 0; j < block; j++)
            {
                string bits;
                for (int k = 0; k < size; k++)
                {
                    cin >> bit;
                    bits += bit;
                }
                data[j].push_back(bits);
            }

        bool valid = true;
        string content, hexText;
        
        // p is the index of parity block.
        for (int i = 0, p = 0; i < block; i++, p++, p %= disk)
        {
            for (int j = 0; j < size; j++)
            {
                string bits;
                for (int k = 0; k < disk; k++)
                    bits += data[i][k][j];

                int unavailableBits = 0, unavailableIdx = -1;
                for (int x = 0; x < bits.size(); x++)
                {
                    if (bits[x] == 'x')
                    {
                        unavailableBits++;
                        if (unavailableIdx == -1) unavailableIdx = x;
                    }
                }

                // too many unavailable bits
                if (unavailableBits >= 2)
                {
                    valid = false;
                    goto print;
                }
                // reconstructe unavailable bit
                else if (unavailableBits == 1)
                {
                    // replace the unavailable bit and check
                    bits[unavailableIdx] = '1';
                    int r = bits.front() - '0';
                    for (int x = 1; x < bits.size(); x++)
                        r ^= (bits[x] - '0');

                    if ((parity == 'E' && r == 1) || (parity == 'O' && r == 0))
                        bits[unavailableIdx] = '0';

                    // set
                    data[i][unavailableIdx][j] = bits[unavailableIdx];
                }
                // check parity error or not
                else
                {
                    int r = bits.front() - '0';
                    for (size_t x = 1; x < bits.size(); x++)
                        r ^= (bits[x] - '0');

                    if ((parity == 'E' && r == 1) || (parity == 'O' && r == 0))
                    {
                        valid = false;
                        goto print;
                    }
                }
            }

            // merge all data block but prity block
            for (int j = 0; j < disk; j++)
                if (j != p)
                    content += data[i][j];
        }

        // translate the binary text to hexadecimal text.
        while (content.size() % 4 != 0) content += '0';
        for (int i = 0; i < content.size(); i += 4)
            hexText += hexadecimal[stoi(content.substr(i, 4), 0, 2)];

        // output.
        print:
        cout << "Disk set " << ++cases;
        if (valid)
            cout << " is valid, contents are: " << hexText << '\n';
        else
            cout << " is invalid.\n";
    }

    return 0;
}
