// Letter Sequence Analysis
// UVa ID: 390
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct record
{
    int frequency; string letters;
    bool operator<(const record &another) const
    {
        if (frequency != another.frequency)
            return frequency > another.frequency;
        else
            return letters < another.letters;
    }
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    char element;
    
    cin.unsetf(ios::skipws);
    while (cin >> element)
        line += toupper(element);
    
    map<int, map<string, int>> frequencies;
    
    for (int i = 0; i < line.length(); i++)
        if (isalpha(line[i]))
        {
            int length = 1;
            while (length <= 5 && (i + length - 1) < line.length() && isalpha(line[i + length - 1]))
            {
                string block = line.substr(i, length);
                frequencies[length][block]++;
                length++;
            }
        }

    for (int i = 1; i <= 5; i++)
    {
        if (i > 1) cout << endl;
        cout << "Analysis for Letter Sequences of Length " << i << endl;
        cout << "-----------------------------------------" << endl;
        
        vector<record> records;
        for (auto item : frequencies[i])
            records.push_back((record){item.second, item.first});
        sort(records.begin(), records.end());
        
        int lastFrequency = -1, outputed = 0;
        for (int j = 0; j < records.size(); j++)
        {
            if (records[j].frequency == lastFrequency)
                cout << "," << records[j].letters;
            else
            {
                if (outputed >= 1) cout << ")" << endl;
                if (++outputed > 5) break;
                lastFrequency = records[j].frequency;
                cout << "Frequency = " << records[j].frequency;
                cout << ", Sequence(s) = (" << records[j].letters;
            }
        }
        if (outputed <= 5) cout << ")" << endl;
    }
    
	return 0;
}
