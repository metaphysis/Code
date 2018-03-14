// Raucous Rockers
// UVa ID: 473
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << '\n';
        
        int n, t, m;
        cin >> n >> t >> m;
        cin.ignore(1024, '\n');
        
        string line;
        getline(cin, line);
        
        istringstream iss(line);
        vector<int> songs;
        string minutes;
        while (getline(iss, minutes, ','))
            songs.push_back(stoi(minutes));
            
        
        
    }
    
	return 0;
}
