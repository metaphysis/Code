// Saftbreaker
// UVa IDs: 296
// Verdict: Accepted
// Submission Date: 2016-05-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct guess
{
    string number;
    int right, wrong;
};

int main(int argc, char *argv[])
{
    vector < string > candidates;
    for (int i = 0; i <= 9999; i++)
    {
        candidates.push_back(to_string(i));
        while (candidates.back().length() < 4)
            candidates.back().insert(candidates.back().begin(), '0');
    }
    
    int N, G;
    cin >> N;
    
    while (N--)
    {
        string line;
        
        cin >> G;
        cin.ignore();
        
        vector < guess > guesses;
        while (G--)
        {
            getline(cin, line);
            guesses.push_back(
                (guess){line.substr(0, 4), line[5] - '0', line[7] - '0'});
        }
        
        set < string > good;
        for (int i = 0; i < candidates.size(); i++)
        {
            bool isGood = true;
            for (int j = 0; j < guesses.size(); j++)
            {
                string temp = candidates[i];
                
                int right = 0;
                for (int k = 0; k < 4; k++)
                    if (temp[k] == guesses[j].number[k])
                    {
                        temp[k] = '*';
                        right++;
                    }
                
                if (right != guesses[j].right)
                {
                    isGood = false;
                    break;
                }

                int wrong = 0;
                for (int k = 0; k < 4; k++)
                {
                    if (temp[k] != '*')
                    {
                        int location = temp.find(guesses[j].number[k]);
                        if (location != temp.npos)
                        {
                            temp[location] = '-';
                            wrong++;
                        }
                    }
                }
                        
                if (wrong != guesses[j].wrong)
                {
                    isGood = false;
                    break;
                }
            }
            
            if (isGood)
                good.insert(candidates[i]);
                
            if (good.size() > 1)
                break;
        }
        
        if (good.size() == 1)
        {
            cout << *(good.begin()) << endl;
        }
        else if (good.size() == 0)
        {
            cout << "impossible" << endl;
        }
        else
        {
            cout << "indeterminate" << endl;
        }
    }
    
	return 0;
}
