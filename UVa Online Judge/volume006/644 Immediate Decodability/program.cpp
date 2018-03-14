// Immediate Decodability
// UVa ID: 644
// Verdict: Accepted
// Submission Date: 2016-08-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    
    string line;
    while (true)
    {
        vector<string> decoded;
        
        bool decodable = true;
        while (getline(cin, line), line.length() > 0 && line.front() != '9')
        {
            if (!decodable)
                continue;

            for (int i = 0; i < decoded.size(); i++)
                if (line.find(decoded[i]) == 0 || decoded[i].find(line) == 0)
                {
                    decodable = false;
                    break;
                }
            
            decoded.push_back(line);
        }
        
        if (line.length() == 0)
            break;
            
        cout << "Set " << ++cases;
        if (decodable)
            cout << " is immediately decodable\n";
        else
            cout << " is not immediately decodable\n";
    }
    
	return 0;
}
