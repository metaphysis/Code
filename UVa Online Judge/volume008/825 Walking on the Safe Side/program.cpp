// Walking on the Safe Side
// UVa ID: 825
// Verdict: Accepted
// Submission Date: 2016-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, W, N, blocked[110][110], number;
    long long int ways[110][110];

    string line;
    
    getline(cin, line);
    cases = stoi(line);
    
    getline(cin, line);
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        getline(cin, line);
        istringstream iss(line);
        iss >> W >> N;

        memset(blocked, 0, sizeof(blocked));
        while (getline(cin, line), line.length() > 0)
        {
            iss.clear(); iss.str(line);
            vector<int> numbers;
            while (iss >> number) numbers.push_back(number);
            for (int i = 1; i < numbers.size(); i++) blocked[numbers.front()][numbers[i]] = 1;
        }

        memset(ways, 0, sizeof(ways));
        ways[0][1] = 1;

        for (int i = 1; i <= W; i++)
            for (int j = 1; j <= N; j++)
                if (blocked[i][j])
                    ways[i][j] = 0;
                else
                    ways[i][j] = ways[i - 1][j] + ways[i][j - 1];
            
        cout << ways[W][N] << '\n';
    }
    
	return 0;
}
