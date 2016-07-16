// Getting Chorded
// UVa ID: 346
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    vector<set<string>> chordes = {
        {"A"}, {"A#", "Bb"}, {"B", "Cb"}, {"C", "B#"},
        {"C#", "Db"}, {"D"}, {"D#", "Eb"}, {"E", "Fb"},
        {"F", "E#"}, {"F#", "Gb"}, {"G"}, {"G#", "Ab"}
    };

    map<string, string> alternatives = {
        {"Ab", "G#"}, {"Bb", "A#"}, {"Cb", "B"}, {"Db", "C#"},
        {"Eb", "D#"}, {"Fb", "E"}, {"Gb", "F#"}, {"B#", "C"},
        {"E#", "F"}
    };

    vector<string> notes(3);
    while (cin >> notes[0] >> notes[1] >> notes[2])
    {
        cout << notes[0] << " " << notes[1] << " " << notes[2] << " is ";
        
        notes[0].front() = toupper(notes[0].front());
        notes[1].front() = toupper(notes[1].front());
        notes[2].front() = toupper(notes[2].front());
        
        if (notes[0].front() > notes[1].front()) swap(notes[0], notes[1]);
        if (notes[0].front() > notes[2].front()) swap(notes[0], notes[2]);
        if (notes[1].front() > notes[2].front()) swap(notes[1], notes[2]);
        
        bool recognized = false;
        for (int i = 0; i < notes.size(); i++)
            for (int j = 0; j < chordes.size(); j++)
                if (chordes[j].count(notes[i]) && chordes[(j + 4) % 12].count(notes[(i + 1) % 3]) && chordes[(j + 7) % 12].count(notes[(i + 2) % 3]))
                {
                    recognized = true;
                    cout << "a " << (notes[i].back() == 'b' || notes[i] == "B#" || notes[i] == "E#" ? alternatives[notes[i]] : notes[i]) << " Major chord.\n";
                    goto get_out;
                }
                else if (chordes[j].count(notes[i]) && chordes[(j + 3) % 12].count(notes[(i + 1) % 3]) && chordes[(j + 7) % 12].count(notes[(i + 2) % 3]))
                {
                    recognized = true;
                    cout << "a " << (notes[i].back() == 'b' || notes[i] == "B#" || notes[i] == "E#" ? alternatives[notes[i]] : notes[i]) << " Minor chord.\n";
                    goto get_out;
                }
   
        get_out:
        if (!recognized) cout << "unrecognized.\n";
    }

	return 0;
}
