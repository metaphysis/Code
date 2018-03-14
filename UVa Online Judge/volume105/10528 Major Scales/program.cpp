// Major Scales
// UVa ID: 10528
// Verdict: Accepted
// Submission Date: 2017-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string scales[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int gap[7] = {0, 2, 4, 5, 7, 9, 11};
    int flag[12][12] = {0};

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 7; j++)
            flag[i][(i + gap[j]) % 12] = 1;
    
    string line;
    while (getline(cin, line))
    {
        if (line == "END") break;

        istringstream iss(line);
        string block;
        vector<string> notes;
        while (iss >> block) notes.push_back(block);
        
        bool outputed = false;
        for (int i = 0; i < 12; i++)
        {
            bool in = true;
            for (auto note : notes)
            {
                int k = find(scales, scales + 12, note) - scales;
                if (k == 12 || !flag[i][k])
                {
                    in = false;
                    break;
                }
            }

            if (in)
            {
                if (outputed) cout << ' ';
                cout << scales[i];
                outputed = true;
            }
        }
        cout << '\n';
    }

    return 0;
}
