// Ballot Evaluation
// UVa ID: 11629
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int getType(string &line)
{
    if (line.find('>') != line.npos && line.find('=') != line.npos) return 1;
    if (line.find('<') != line.npos && line.find('=') != line.npos) return 2;
    if (line.find('>') != line.npos) return 3;
    if (line.find('<') != line.npos) return 4;
    return 5;
}

bool judge(int type, int guess, int up)
{
    switch (type)
    {
        case 1: return guess >= up;
        case 2: return guess <= up;
        case 3: return guess > up;
        case 4: return guess < up;
        case 5: return guess == up;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, g;

    while (cin >> p >> g)
    {
        map<string, int> percent;
        string party, digit;
        
        for (int i = 0; i < p; i++)
        {
            cin >> party >> digit;
            int number = 0;
            for (auto d : digit)
                if (isdigit(d))
                    number = number * 10 + d - '0';
            percent[party] = number;
        }

        cin.ignore(1024, '\n');
        string line, block;

        for (int cases = 1; cases <= g; cases++)
        {
            getline(cin, line);

            int type = getType(line);

            string replaced = "><=+";
            for (auto r : replaced)
                replace(line.begin(), line.end(), r, ' ');

            istringstream iss(line);
            vector<string> cache;
            while (iss >> block) cache.push_back(block);
            
            int guess = 0;
            for (int j = 0; j < cache.size() - 1; j++)
                guess += percent[cache[j]];
            int up = stoi(cache.back()) * 10;

            cout << "Guess #" << cases << " was ";
            cout << (judge(type, guess, up) ? "correct." : "incorrect.");
            cout << '\n';
        }
    }

    return 0;
}
