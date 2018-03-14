// Machined Surfaces
// UVa ID: 414
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    int N;
    while (cin >> N, N)
    {
        cin.ignore(1024, '\n');
        vector<int> spaces;
        for (int i = 1; i <= N; i++)
        {
            getline(cin, line);
            spaces.push_back(count(line.begin(), line.end(), ' '));
        }
        
        int minimum = *min_element(spaces.begin(), spaces.end()), total = 0;
        total = accumulate(spaces.begin(), spaces.end(), total) - minimum * spaces.size();

        cout << total << endl;
    }
    
	return 0;
}
