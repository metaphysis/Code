// What Base Is This?
// UVa ID: 343
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string X, Y;
    string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    map<char, int> key;
    
    for (int i = 0; i < digits.length(); i++)
        key.insert(make_pair(digits[i], i));
        
    while (cin >> X >> Y)
    {
        set<long long int> Xs, Ys;
        map<int, long long int> valueXs, valueYs;
        
        int baseX = 0;
        for (int i = 0; i < X.length(); i++)
            baseX = max(baseX, key[X[i]] + 1);
        baseX = max(baseX, 2);
        
        for (int bx = baseX; bx <= 36; bx++)
        {
            long long int value = 0;
            for (int i = 0; i < X.length(); i++)
                value = value * bx + key[X[i]];
            valueXs[bx] = value;
            Xs.insert(value);
        }
        
        int baseY = 0;
        for (int i = 0; i < Y.length(); i++)
            baseY = max(baseY, key[Y[i]] + 1);
        baseY = max(baseY, 2);
            
        for (int by = baseY; by <= 36; by++)
        {
            long long int value = 0;
            for (int i = 0; i < Y.length(); i++)
                value = value * by + key[Y[i]];
            valueYs[by] = value;
            Ys.insert(value);
        }
        
        bool flag = false;
        for (int bx = baseX; bx <= 36; bx++)
        {
            if (Ys.find(valueXs[bx]) != Ys.end())
            {
                for (int by = baseY; by <= 36; by++)
                    if (valueYs[by] == valueXs[bx])
                    {
                        cout << X << " (base " << bx << ") = ";
                        cout << Y << " (base " << by << ")" << endl;
                        break;
                    }
                
                flag = true;
                break;
            }
        }
        
        if (flag == false)
        {
            cout << X << " is not equal to " << Y << " in any base 2..36" << endl;
        }
    }
    
	return 0;
}
