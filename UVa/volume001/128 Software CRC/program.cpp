// Software CRC
// UVa IDs: 128
// Verdict: Accepted
// Submission Date: 2015-12-01
// UVa Run Time: 0.352s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

const int MOD_BASE = 34943;

int modular[1030];

void generateModular()
{
    modular[0] = 65536 % MOD_BASE;
    
    for (int i = 1; i <= 1024; i++)
        modular[i] = (modular[i - 1] * 256) % MOD_BASE;
}

void intToHex(int residue)
{
    string hex = "0123456789ABCDEF";

    cout << hex[residue / 256 / 16];
    cout << hex[residue / 256 % 16];
    cout << " ";
    cout << hex[(residue % 256) / 16];
    cout << hex[residue % 256 % 16];
    cout << endl;
}

void softwareCRC(string line)
{
    int residue = 0;
    for (int i = line.length() - 1, j = 0; i >= 0; i--, j++)
        residue += (line[i] * modular[j] % MOD_BASE);
    residue = (MOD_BASE - residue % MOD_BASE) % MOD_BASE;
    intToHex(residue);
}

int main(int ac, char *av[])
{
    generateModular();
    
    string line;
    while(getline(cin, line))
    {
        if (line.length() == 0)
        {
            cout << "00 00" << endl;
            continue;
        }
        
        if (line[0] == '#')
            break;
            
        softwareCRC(line);
    }
	return 0;
}
