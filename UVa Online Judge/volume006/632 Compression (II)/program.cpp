// Compression (II)
// UVa ID: 632
// Verdict: Accepted
// Submission Date: 2016-08-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct cell
{
    int label;
    string s;
    
    bool operator<(const cell& another) const
    {
        return s < another.s;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int datasets;
    cin >> datasets;
    
    string line;
    for (int d = 1; d <= datasets; d++)
    {
        if (d > 1)
            cout << '\n';

        int length;
        cin >> length;
        
        cin.ignore(1024, '\n');

        string word;
        while (true)
        {
            getline(cin, line);
            word += line;
            if (word.length() >= length)
                break;
        }

        string s0 = word, s1 = word;
        s1.push_back(s1.front());
        s1.erase(s1.begin());
        
        vector<cell> words;
        for (int i = 0; i < length; i++)
        {
            //cout << word << '\n';
            words.push_back((cell){i, word});
            word.push_back(word.front());
            word.erase(word.begin());
        }

        stable_sort(words.begin(), words.end());

        string created;
        int indexer = -1;
        for (int i = 0; i < length; i++)
        {
            created += words[i].s.back();
            if (indexer == -1 && words[i].label == 1)
                indexer = i;
        }

        cout << indexer << '\n';
        
        while (created.length() > 50)
        {
            cout << created.substr(0, 50) << '\n';
            created = created.substr(50);
        }
        
        if (created.length() > 0)
            cout << created << '\n';
    }
    
	return 0;
}
