// Stamps
// UVa IDs: 165
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <map>

using namespace std;

map<int, string> maxSequence;

int main(int argc, char* argv[])
{
    int h, k;
    
    maxSequence[11] = "  1 ->  1";
    maxSequence[12] = "  1  2 ->  2";
    maxSequence[13] = "  1  2  3 ->  3";
    maxSequence[14] = "  1  2  3  4 ->  4";
    maxSequence[15] = "  1  2  3  4  5 ->  5";
    maxSequence[16] = "  1  2  3  4  5  6 ->  6";
    maxSequence[17] = "  1  2  3  4  5  6  7 ->  7";
    maxSequence[18] = "  1  2  3  4  5  6  7  8 ->  8";
    maxSequence[21] = "  1 ->  2";
    maxSequence[22] = "  1  2 ->  4";
    maxSequence[23] = "  1  3  4 ->  8";
    maxSequence[24] = "  1  3  5  6 -> 12";
    maxSequence[25] = "  1  3  5  7  8 -> 16";
    maxSequence[26] = "  1  2  5  8  9 10 -> 20";
    maxSequence[27] = "  1  2  5  8 11 12 13 -> 26";
    maxSequence[31] = "  1 ->  3";
    maxSequence[32] = "  1  3 ->  7";
    maxSequence[33] = "  1  4  5 -> 15";
    maxSequence[34] = "  1  4  7  8 -> 24";
    maxSequence[35] = "  1  4  6 14 15 -> 36";
    maxSequence[36] = "  1  3  7  9 19 24 -> 52";
    maxSequence[41] = "  1 ->  4";
    maxSequence[42] = "  1  3 -> 10";
    maxSequence[43] = "  1  5  8 -> 26";
    maxSequence[44] = "  1  3 11 18 -> 44";
    maxSequence[45] = "  1  3 11 15 32 -> 70";
    maxSequence[51] = "  1 ->  5";
    maxSequence[52] = "  1  4 -> 14";
    maxSequence[53] = "  1  6  7 -> 35";
    maxSequence[54] = "  1  4 12 21 -> 71";
    maxSequence[61] = "  1 ->  6";
    maxSequence[62] = "  1  4 -> 18";
    maxSequence[63] = "  1  7 12 -> 52";
    maxSequence[71] = "  1 ->  7";
    maxSequence[72] = "  1  5 -> 23";
    maxSequence[81] = "  1 ->  8";

    while (cin >> h >> k, h || k)
    {
        if (h * k == 0)
        {
            cout << "  0 ->   0" << endl;
            continue;
        }
            
        cout << maxSequence[h * 10 + k] << endl;
    }
    
	return 0;
}
