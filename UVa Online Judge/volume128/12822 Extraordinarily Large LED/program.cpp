// Extraordinarily Large LED
// UVa ID: 12822
// Verdict: Accepted
// Submission Date: 2021-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int getTime(string time)
{
    return stoi(time.substr(0, 2)) * 3600 + stoi(time.substr(3, 2)) * 60 + stoi(time.substr(6));
}

int getPower(int score)
{
    if (score == 0) return 6;
    int power[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int r = 0;
    while (score)
    {
        r += power[score % 10];
        score /= 10;
    }
    return r;
}

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string command, time, team;
    while (cin >> command)
    {
        int score, home_score = 0, guest_score = 0;
        int consumed = 0;
        cin >> time;
        int lastTime = getTime(time), currentTime, elapsed;
        while (cin >> command)
        {
            if (command == "END")
            {
                cin >> time;
                currentTime = getTime(time);
                elapsed = currentTime - lastTime;
                consumed += (getPower(home_score) + getPower(guest_score)) * elapsed;
                break;
            }
            if (command == "SCORE")
            {
                cin >> time >> team >> score;
                currentTime = getTime(time);
                elapsed = currentTime - lastTime;
                consumed += (getPower(home_score) + getPower(guest_score)) * elapsed;
                lastTime = currentTime;
                if (team == "home") home_score += score;
                else guest_score += score;
            }
        }
        cout << "Case " << ++cases << ": " << consumed << '\n';
    }

    return 0;
}
