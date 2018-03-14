// Haiku Review
// UVa ID: 576
// Verdict: Accepted
// Submission Date: 2016-08-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    vector<int> syllables = {0, 5, 7, 5};
    string vowels = "aeiouy";
    
    string line, block;
    while (getline(cin, line), line != "e/o/i")
    {
        istringstream iss(line);
        
        bool correct = true;
        int indexer = 1;

        while (getline(iss, block, '/'))
        {
            int count = 0;

            int i = 0;
            while (i < block.length())
            {
                if (vowels.find(block[i]) != block.npos)
                {
                    count++;
                    while (i < block.length() && vowels.find(block[i]) != block.npos)
                        i++;
                }
                else
                    i++;
            }

            if (count != syllables[indexer])
            {
                correct = false;
                break;
            }
            indexer++;
        }
        
        if (correct)
            cout << "Y\n";
        else
            cout << indexer << '\n';
    }
    
	return 0;
}
