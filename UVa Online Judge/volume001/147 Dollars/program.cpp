// Dollars
// UVa ID: 147
// Verdict: Accepted
// Submission Date: 2016-01-22
// UVa Run Time: 0.012s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// PDF 格式的试题描述和 UVa 网页上的试题描述有出入，主
// 要是上限提高到 300 美元。输出格式亦有改变。

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

long long int cache[6001] = { 0 };

void initialize()
{
    int coins[11] = { 1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000 };
    cache[0] = 1;
    for (int i = 0; i < 11; i++)
        for (int j = 1; j < 6001; j++)
            if (j - coins[i] >= 0)
                cache[j] += cache[j - coins[i]];
}

int main(int argc, char *argv[])
{
    initialize();
    
    string line;
    while (cin >> line)
    {
        string backup = line;
        line.erase(line.find('.'), 1);
        istringstream iss(line);
        
        int money;
        iss >> money;
        
        if (money == 0)
            break;
            
        cout << fixed << setprecision(2) << setw(6) << right << backup;
        cout << setw(17) << right << cache[money / 5] << endl;
    }
    
	return 0;
}
