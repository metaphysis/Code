// Index
// UVa ID: 698
// Verdict: Accepted
// Submission Date: 2017-06-22
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<string, int> counter;
    map<string, vector<pair<int, int>>> indexing;
    string line, word;
    int cases = 0;

    while (getline(cin, word))
    {
        counter.clear();
        indexing.clear();
        
        do
        {
            for (int i = 0; i < word.length(); i++)
                word[i] = toupper(word[i]);
            counter[word]++;
            if (counter[word] > 1) continue;
            indexing.insert(make_pair(word, vector<pair<int, int>>()));
        }
        while (getline(cin, word), word.length() > 0);
        
        int lineNumbers = 1;
        while (getline(cin, line), line.length() > 0)
        {
            int idx = 0;
            while (idx < line.length())
            {
                if (isalpha(line[idx]) || isdigit(line[idx]))
                {
                    string block;
                    while (idx < line.length())
                    {
                        if (isalpha(line[idx]) || isdigit(line[idx]))
                            block += toupper(line[idx]);
                        else
                            break;
                        idx += 1;
                    }
                    
                    if (indexing.find(block) != indexing.end())
                    {
                        if (indexing[block].size() == 0)
                        {
                            indexing[block].push_back(make_pair(lineNumbers, lineNumbers));
                        }
                        else
                        {
                            if (lineNumbers != indexing[block].back().second)
                            {
                                if (indexing[block].back().second + 1 == lineNumbers)
                                    indexing[block].back().second += 1;
                                else
                                    indexing[block].push_back(make_pair(lineNumbers, lineNumbers));
                            }
                        }
                    }
                }
                else
                    idx += 1;
            }
            
            lineNumbers += 1;
        }
        
        cout << "Case " << ++cases << '\n';
        for (auto entry : indexing)
        {
            if (entry.second.size() == 0) continue;
            
            for (int i = 0; i < counter[entry.first]; i++)
            {
                cout << entry.first;
                bool first = true;
                for (auto p : entry.second)
                {
                    if (first) first = false;
                    else cout << ',';

                    cout << ' ';

                    if (p.first == p.second) cout << p.first;
                    else cout << p.first << '-' << p.second;
                }
                cout << '\n';
            }
        }
        cout << '\n';
    }

    return 0;
}
