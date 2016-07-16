// Kibbles "n" Bits "n" Bits "n" Bits
// UVa ID: 446
// Verdict: Accepted
// Submission Date: 2016-07-15
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n;
    cin >> n;

    string hex1, operators, hex2;
    int hex1_value, hex2_value, result;
    
    for (int i = 1; i <= n; i++)
    {
        cin >> hex1 >> operators >> hex2;
        hex1_value = stoi("0x" + hex1, nullptr, 0);
        hex2_value = stoi("0x" + hex2, nullptr, 0);
        result = hex1_value + (operators == "+" ? hex2_value : -hex2_value);
        
        bitset<13> first(hex1_value), second(hex2_value);
        cout << first.to_string() << " " << operators << " " << second.to_string() << " = " << result << '\n';
    }
    
	return 0;
}
