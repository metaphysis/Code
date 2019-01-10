// A Duckpin Tournament
// UVa ID: 600
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int PLAYERS = 110;

vector<int> numbers[3];
int pins[16][3], frames[16], scores[PLAYERS];

void parse()
{
    int f2 = 0, f3 = 0;
    memset(pins, 0, sizeof(pins));
    for (int f1 = 0; f1 < numbers[0].size(); f1++)
    {
        pins[f1][0] = numbers[0][f1];
        if (numbers[0][f1] == 10 || numbers[0][f1] < 0) continue;
        if (numbers[0][f1] + abs(numbers[1][f2]) > 10) continue;
        pins[f1][1] = numbers[1][f2]; f2++;
        if (numbers[0][f1] + abs(numbers[1][f2 - 1]) == 10 || numbers[1][f2 - 1] < 0) continue;
        if (numbers[0][f1] + numbers[1][f2 - 1] + abs(numbers[2][f3]) > 10) continue;
        pins[f1][2] = numbers[2][f3]; f3++;
    }
    cout << '\n';
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < numbers[0].size(); j++)
            cout << right << setw(4) << pins[j][i];
        cout << endl;
    }
}

void getScores()
{
    memset(frames, 0, sizeof(frames));
    for (int i = 0; i < 10; i++)
    {
        if (pins[i][0] == 10)
        {
            frames[i] += 10;
            if (pins[i + 1][0] >= 0) 
            {
                frames[i] += pins[i + 1][0];
                if (pins[i + 1][0] == 10)
                {
                    if (pins[i + 2][0] > 0)
                        frames[i] += pins[i + 2][0];
                }
                else
                {
                    if (pins[i + 1][1] > 0)
                        frames[i] += pins[i + 1][1];
                }
            }
        }
        else if (pins[i][0] + pins[i][1] == 10)
        {
            frames[i] += 10;
            if (pins[i + 1][0] > 0)
                frames[i] += pins[i + 1][0];
        }
        else
        {
            for (int j = 0; j < 3 && pins[i][j] >= 0; j++)
                frames[i] += pins[i][j];
        }
    }
    
    for (int i = 1; i < 10; i++)
        frames[i] += frames[i - 1];
}

void printScores()
{
    for (int i = 0; i < 10; i++)
        cout << right << setw(4) << frames[i];
    cout << '\n';
}

int main(int argc, char *argv[])
{
    //cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string names[PLAYERS], line;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> names[i];
        int highGameScore = 0, highGameScorePlayer = -1;
        memset(scores, 0, sizeof(scores));

        cin.ignore(256, '\n');
        for (int match = 1; match <= 3; match++)
        {
            for (int i = 0; i < n; i++)
            {
                cout << left << setw(10) << names[i];
                for (int j = 0; j < 3; j++)
                {
                    getline(cin, line);
                    numbers[j].clear();
                    int n;
                    istringstream iss(line);
                    while (iss >> n) numbers[j].push_back(n);
                }
                parse();
                getScores();
                printScores();
                scores[i] += frames[9];
                if (frames[9] > highGameScore)
                {
                    highGameScore = frames[9];
                    highGameScorePlayer = i;
                }
            }
        }

        getline(cin, line);

        int maxScore = 0, maxScorePlayer = -1;
        for (int i = 0; i < n; i++)
            if (scores[i] > maxScore)
            {
                maxScore = scores[i];
                maxScorePlayer = i;
            }
        cout << names[maxScorePlayer] << " has the high series score of " << maxScore << ".\n";
        cout << names[highGameScorePlayer] << " has the high game score of " << highGameScore << ".\n";
        cout << '\n';
    }

    return 0;
}
