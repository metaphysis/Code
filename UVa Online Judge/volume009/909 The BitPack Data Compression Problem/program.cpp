// The BitPack Data Compression Problem
// UVa ID: 909
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

deque<char> data;
bool same = true;

void print(int letter)
{
    //cout << (unsigned char)(letter);
    cout << '[' << letter << ']';
}

void process()
{
    if (same)
    {
        int total = data.size();
        while (total >= 128)
        {
            print(255);
            cout << data.front();
            for (int i = 1; i <= 128; i++)
                data.pop_front();
            total -= 128;
        }
        if (total >= 2)
        {
            print(129 + (total - 2));
            cout << data.front();
            for (int i = 1; i <= total; i++)
                data.pop_front();
        }
        else if (total == 1)
        {
            print(0);
            cout << data.front();
            data.pop_front();
        }
    }
    else
    {
        int total = data.size();
        while (total >= 128)
        {
            print(127);
            for (int i = 1; i <= 128; i++)
            {
                cout << data.front();
                data.pop_front();
            }
            total -= 128;
        }
        
        if (total > 0)
        {
            print(total - 1);
            for (int i = 1; i <= total; i++)
            {
                cout << data.front();
                data.pop_front();
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    
    while (getline(cin, line))
    {
        same = true;
        for (int i = 0; i < line.length(); i++)
        {
            if (data.empty())
            {
                same = true;
                data.push_back(line[i]);
            }
            else
            {
                if (data.back() == line[i])
                {
                    if (same)
                    {
                        data.push_back(line[i]);
                    }
                    else
                    {
                        data.pop_back();
                        process();
                        
                        same = true;
                        data.push_back(line[i]);
                        data.push_back(line[i]);
                    }
                }
                else
                {
                    if (same && data.size() > 1)
                    {
                        process();
                        data.push_back(line[i]);
                    }
                    else
                    {
                        same = false;
                        data.push_back(line[i]);
                    }
                }
            }
        }
        
        process();
        
        cout << '\n';
    }
    
    return 0;
}
