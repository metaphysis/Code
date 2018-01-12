// SQF Problems
// UVa ID: 10686
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct category
{
    string name;
    int W, P;
    set<string> keywords;
}categories[32];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, word;
    int cases, n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> categories[i].name >> categories[i].W >> categories[i].P;
            categories[i].keywords.clear();
            for (int j = 0; j < categories[i].W; j++)
            {
                cin >> word;
                categories[i].keywords.insert(word);
            }
        }

        cin.ignore(1024, '\n');
        set<string> description;
        while (getline(cin, line), line.length() > 0)
        {
            string block;
            for (int i = 0; i < line.length(); i++)
            {
                if (isalpha(line[i]))
                    block += line[i];
                else
                {
                    if (block.length() > 0) description.insert(block);
                    block.clear();
                }
            }
            if (block.length() > 0) description.insert(block);
        }
        
        bool outputed = false;
        for (int i = 0; i < n; i++)
        {
            if (categories[i].keywords.size() < categories[i].P) continue;

            int appeared = 0;
            for (auto w : categories[i].keywords)
                if (description.find(w) != description.end())
                    appeared++;

            if (appeared >= categories[i].P)
            {
                if (outputed) cout << ',';
                cout << categories[i].name;
                outputed = true;
            }
        }
        if (!outputed) cout << "SQF Problem.";
        cout << '\n';
    }

    return 0;
}
