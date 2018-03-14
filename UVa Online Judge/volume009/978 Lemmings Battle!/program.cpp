// Lemmings Battle!
// UVa ID: 978
// Verdict: Accepted
// Submission Date: 2017-02-17
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, battlefields, number_green, number_blue, soldier_power;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> battlefields >> number_green >> number_blue;
        
        priority_queue<int> power_green, power_blue;
        
        for (int i = 1; i <= number_green; i++)
        {
            cin >> soldier_power;
            power_green.push(soldier_power);
        }
        
        for (int i = 1; i <= number_blue; i++)
        {
            cin >> soldier_power;
            power_blue.push(soldier_power);
        }
        
        while (!power_green.empty() && !power_blue.empty())
        {
            int soldier_green, soldier_blue;
            vector<int> survivor_green, survivor_blue;

            for (int j = 1; j <= battlefields; j++)
            {
                soldier_green = soldier_blue = 0;

                if (!power_green.empty())
                {
                    soldier_green = power_green.top();
                    power_green.pop();
                }
                
                if (!power_blue.empty())
                {
                    soldier_blue = power_blue.top();
                    power_blue.pop();
                }
                
                if (soldier_green != soldier_blue)
                {
                    if (soldier_green > soldier_blue)
                    {
                        survivor_green.push_back(soldier_green - soldier_blue);
                    }
                    else
                    {
                        survivor_blue.push_back(soldier_blue - soldier_green);
                    }
                }
            }
            
            for (auto soldier : survivor_green) power_green.push(soldier);
            for (auto soldier : survivor_blue) power_blue.push(soldier);
        }
        
        if (c > 1) cout << '\n';

        if (power_green.empty() && power_blue.empty())
        {
            cout << "green and blue died\n";
        }
        else if (!power_green.empty())
        {
            cout << "green wins\n";
            while (!power_green.empty())
            {
                cout << power_green.top() << '\n';
                power_green.pop();
            }   
        }
        else
        {
            cout << "blue wins\n";
            while (!power_blue.empty())
            {
                cout << power_blue.top() << '\n';
                power_blue.pop();
            }
        }
    }
    
    return 0;
}
