// DNS Translation
// UVa ID: 385
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<char, char> DNA = {{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};
map<string, string> code = {
    {"UUU", "Phe"}, {"UCU", "Ser"}, {"UAU", "Tyr"}, {"UGU", "Cys"},
    {"UUC", "Phe"}, {"UCC", "Ser"}, {"UAC", "Tyr"}, {"UGC", "Cys"},
    {"UUA", "Leu"}, {"UCA", "Ser"},
    {"UUG", "Leu"}, {"UCG", "Ser"}, {"UGG", "Trp"},
    
    {"CUU", "Leu"}, {"CCU", "Pro"}, {"CAU", "His"}, {"CGU", "Arg"},
    {"CUC", "Leu"}, {"CCC", "Pro"}, {"CAC", "His"}, {"CGC", "Arg"},
    {"CUA", "Leu"}, {"CCA", "Pro"}, {"CAA", "Gln"}, {"CGA", "Arg"},
    {"CUG", "Leu"}, {"CCG", "Pro"}, {"CAG", "Gln"}, {"CGG", "Arg"},
    
    {"AUU", "Ile"}, {"ACU", "Thr"}, {"AAU", "Asn"}, {"AGU", "Ser"},
    {"AUC", "Ile"}, {"ACC", "Thr"}, {"AAC", "Asn"}, {"AGC", "Ser"},
    {"AUA", "Ile"}, {"ACA", "Thr"}, {"AAA", "Lys"}, {"AGA", "Arg"},
    {"AUG", "Met"}, {"ACG", "Thr"}, {"AAG", "Lys"}, {"AGG", "Arg"},
    
    {"GUU", "Val"}, {"GCU", "Ala"}, {"GAU", "Asp"}, {"GGU", "Gly"},
    {"GUC", "Val"}, {"GCC", "Ala"}, {"GAC", "Asp"}, {"GGC", "Gly"},
    {"GUA", "Val"}, {"GCA", "Ala"}, {"GAA", "Glu"}, {"GGA", "Gly"},
    {"GUG", "Val"}, {"GCG", "Ala"}, {"GAG", "Glu"}, {"GGG", "Gly"},
    
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string line;
    while (getline(cin, line), line != "*")
    {
        vector<string> mRNA;
        mRNA.push_back(line);
        reverse(line.begin(), line.end());
        mRNA.push_back(line);

        reverse(line.begin(), line.end());
        string strand;
        for (auto base : line)
            strand += DNA[base];
        mRNA.push_back(strand);
        reverse(strand.begin(), strand.end());
        mRNA.push_back(strand);

        for (int i = 0; i < mRNA.size(); i++)
        {
            for (int j = 0; j < mRNA[i].length(); j++)
                if (mRNA[i][j] == 'T')
                    mRNA[i][j] = 'U';
        }

        bool proteinProduced = false;
        for (int i = 0; i < mRNA.size(); i++)
        {
            string message = mRNA[i];
            int start = message.find("AUG");
            if (start == message.npos) continue;
            start += 3;
            vector<string> proteins;
            bool ended = false;
            while (start < message.length())
            {
                string block = message.substr(start, 3);
                if (block != "UAA" && block != "UAG" && block != "UGA")
                {
                    if (code.find(block) != code.end())
                        proteins.push_back(code[block]);
                }
                else
                {
                    ended = true;
                    break;
                }
                start += 3;
            }

            if (ended && proteins.size())
            {
                proteinProduced = true;
                for (int i = 0; i < proteins.size(); i++)
                {
                    if (i > 0) cout << "-";
                    cout << proteins[i];
                }
                cout << endl;
                break;
            }
        }

        if (!proteinProduced)
            cout << "*** No translatable DNA found ***" << endl;
    }
    
	return 0;
}
