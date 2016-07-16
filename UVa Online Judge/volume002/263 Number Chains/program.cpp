// Number Chains
// UVa ID: 263
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.380s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

bool cmp1(char x, char y)
{
    return x > y;
}

bool cmp2(char x, char y)
{
    return x < y;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int number;
    while (cin >> number, number)
    {
        cout << "Original number was " << number << endl;

        int length = 1;
        set < int > appeared;
        
        while (true)
        {
            string text = to_string(number);
            sort(text.begin(), text.end(), cmp1);
            int big = stoi(text);
            
            sort(text.begin(), text.end(), cmp2);
            int small = stoi(text);
            
            int difference = big - small;
            cout << big << " - " << small << " = " << difference << endl;
            
            if (appeared.count(difference) > 0)
            {
                cout << "Chain length " << length << endl;
                break;
            }
            else
                appeared.insert(difference);
            
            number = difference;
                
            length++;
        }
        
        cout << endl;
    }
    
	return 0;
}
