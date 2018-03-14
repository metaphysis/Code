// Unix ls
// UVa ID: 400
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        
        vector<string> filenames;
        int max_length = 0;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            string filename;
            for (int i = 0; i < line.length() && filename.length() < 60; i++)
            {
                if (isdigit(line[i]) || isalpha(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '_')
                    filename += line[i];
            }
            if (filename.length() == 0) continue;
            max_length = max(max_length, (int)filename.length());
            filenames.push_back(filename);
        }
        
        sort(filenames.begin(), filenames.end());
        
        n = filenames.size();
        int C = 1 + (60 - max_length) / (max_length + 2);
        int R = n / C + (n % C == 0 ? 0 : 1);
        
        cout << string(60, '-') << '\n';
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                int index = j * R + i;
                if (index < n)
                    cout << setw(max_length + ((j + 1) * R + i < n ? 2 : 0)) << left << filenames[index];
            }
            cout << '\n';
        }
    }
    
	return 0;
}
