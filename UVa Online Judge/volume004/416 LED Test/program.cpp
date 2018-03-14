// LED Test
// UVa ID: 416
// Verdict: Accepted
// Submission Date: 2016-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<int, string> led = {
    {0, "YYYYYYN"}, {1, "NYYNNNN"}, {2, "YYNYYNY"}, {3, "YYYYNNY"}, {4, "NYYNNYY"},
    {5, "YNYYNYY"}, {6, "YNYYYYY"}, {7, "YYYNNNN"}, {8, "YYYYYYY"}, {9, "YYYYNYY"}
};

vector<string> segments;
int n;

bool match(int depth, int digit, vector<bool> broken)
{
    if (depth == n)
        return true;

    string pattern = segments[depth], displayed = led[digit];
    
    for (int i = 0; i < 7; i++)
        if (broken[i])
            displayed[i] = 'N';

    //cout << "depth = " << depth << " digit = " << digit << " displayed = " << displayed << " pattern = " << pattern << '\n';
    
    for (int i = 0; i < 7; i++)
    {
        if (pattern[i] == displayed[i]) continue;
        else if (pattern[i] == 'N' && displayed[i] == 'Y') broken[i] = true;
        else if (pattern[i] == 'Y' && displayed[i] == 'N') return false;
    }
    
    return match(depth + 1, digit - 1, broken);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        segments.clear();
        
        string segment;
        for (int i = 1; i <= n; i++)
        {
            cin >> segment;
            segments.push_back(segment);
        }

        bool allMatched = false;

        for (int digit = n - 1; digit <= 9; digit++)
        {
            vector<bool> broken(7, false);
            string pattern = segments.front(), displayed = led[digit];

            bool matched = true;
            for (int i = 0; i < 7; i++)
            {
                if (displayed[i] == pattern[i]) continue;
                else if (displayed[i] == 'Y' && pattern[i] == 'N') broken[i] = true;
                else if (displayed[i] == 'N' && pattern[i] == 'Y')
                {
                    matched = false;
                    break;
                }
            }
            
            if (matched && match(0, digit, broken))
            {
                allMatched = true;
                break;
            }
        }
        
        cout << (allMatched ? "MATCH" : "MISMATCH") << '\n';
    }
    
	return 0;
}
