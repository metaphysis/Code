// Pizza Anyone?
// UVa ID: 565
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.220s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int like[12], unlike[12], counter = 0;
    
void setConstraint(string data)
{
    data.erase(data.end() - 1);

    bitset<16> like_pizza(0), unlike_pizza(0);
    for (int i = 0; i < data.length(); i += 2)
    {  
        if (data[i] == '+')
            like_pizza.set(data[i + 1] - 'A');
        else
            unlike_pizza.set(data[i + 1] - 'A');
    }

    like[counter] = like_pizza.to_ulong();
    unlike[counter] = unlike_pizza.to_ulong();
    counter++;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        setConstraint(line);
        while (getline(cin, line), line != ".")
            setConstraint(line);
        
        bool success = false;
        for (int i = 0; i <= 65536; i++)
        {
            bool good = true;
            for (int j = 0; j < counter; j++)
                if ((i & like[j]) || (~i & unlike[j]))
                    continue;
                else
                {
                    good = false;
                    break;
                }
            
            if (good)
            {
                cout << "Toppings: ";
                bitset<16> pizza(i);
                for (int i = 0; i < 16; i++)
                    if (pizza.test(i))
                        cout << (char)('A' + i);
                cout << '\n';
                success = true;
                break;
            }
        }
        
        if (!success)
            cout << "No pizza can satisfy these requests.\n";
            
        counter = 0;
    }
    
	return 0;
}
