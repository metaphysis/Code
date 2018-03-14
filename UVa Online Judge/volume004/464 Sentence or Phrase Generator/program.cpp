// Sentence/Phrase Generator
// UVa ID: 464
// Verdict: Accepted
// Submission Date: 2016-08-04
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int k = 1;
bool printSpace = false;

map<string, vector<vector<string>>> phrases = {
    {"#sentence", {{"#trans-sentence"}, {"#intrans-sentence"}}},
    {"#trans-sentence", {{"#subject", "#verb-phrase", "#object", "#prep-phrase"}}},
    {"#intrans-sentence", {{"#subject", "#intrans-verb-phrase", "#prep-phrase"}}},
    {"#subject", {{"#noun-phrase"}}},
    {"#object", {{"#noun-phrase"}}},
    {"#noun-phrase", {{"#article" , "#modified-noun"}}},
    {"#modified-noun", {{"#noun"}, {"#modifier", "#noun"}}},
    {"#modifier", {{"#adjective"}, {"#adverb", "#adjective"}}},
    {"#verb-phrase", {{"#trans-verb"}, {"#adverb", "#trans-verb"}}},
    {"#intrans-verb-phrase", {{"#intrans-verb"}, {"#adverb", "#intrans-verb"}}},
    {"#prep-phrase", {{"#preposition", "#noun-phrase"}, {"#empty"}}},
    {"#noun", {{"man"}, {"dog"}, {"fish"}, {"computer"}, {"waves"}}},
    {"#trans-verb", {{"struck"}, {"saw"}, {"bit"}, {"took"}}},
    {"#intrans-verb", {{"slept"}, {"jumped"}, {"walked"}, {"swam"}}},
    {"#article", {{"the"}, {"a"}}},
    {"#adjective", {{"green"}, {"small"}, {"rabid"}, {"quick"}}},
    {"#adverb", {{"nearly"}, {"suddenly"}, {"restlessly"}}},
    {"#preposition", {{"on"}, {"over"}, {"through"}}},
    {"#empty", {{""}}}
};

void generate(string phrase)
{
    if (phrase.length() > 0 && phrase.front() == '#')
    {
        int choices = phrases[phrase].size();

        int indexChoosed = 0;
        if (choices > 1)
        {
            indexChoosed = k % choices;
            k++;
        }

        for (auto p : phrases[phrase][indexChoosed])
            generate(p);
    }
    else
    {
        if (printSpace == false)
            printSpace = true;
        else if (phrase.length() > 0)
            cout << ' ';

        cout << phrase;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        while (line.length() > 0 && isblank(line.front()))
            line.erase(line.begin());
        while (line.length() > 0 && isblank(line.back()))
            line.erase(line.end() - 1);

        printSpace = false;
        generate('#' + line);
        cout << '\n';
    }
        
	return 0;
}
