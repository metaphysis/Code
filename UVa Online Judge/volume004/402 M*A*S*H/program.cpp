// M*A*S*H
// UVa ID: 402
// Verdict: Accepted
// Submission Date: 2016-07-18
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, n, x;
    
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> n >> x;
        
        queue<int> cards;
        int number;
        while (iss >> number)
            cards.push(number);
            
        vector<int> person(n);
        iota(person.begin(), person.end(), 1);
        
        int remaining = n;
        
        while (remaining > x && cards.empty() == false)
        {
            int token = cards.front();
            cards.pop();
            
            int current = 0, counter = 0;
            while (current < n)
            {
                if (person[current] > 0)
                    counter++;

                if (counter == token)
                {
                    person[current] = 0;
                    remaining--;
                    
                    if (remaining == x)
                        goto skip;
                        
                    counter = 0;
                }

                current++;
            }
        }
        
        skip:
        cout << "Selection #" << ++cases << '\n';
        
        bool first = true;
        for (int i = 0; i < person.size(); i++)
        {
            if (person[i] == 0)
                continue;
            
            if (first)
                first = false;
            else
                cout << ' ';

            cout << person[i];
        }

        cout << "\n\n";
    }
    
	return 0;
}
