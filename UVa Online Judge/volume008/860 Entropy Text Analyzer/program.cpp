// Entropy Text Analyzer
// UVa ID: 860
// Verdict: Accepted
// Submission Date: 2016-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "****END_OF_INPUT****")
    {
        map<string, int> counter;
        int lambda = 0;

        do
        {
            // , . : ; ! ? " ( )
            string buffer, word;
            for (int i = 0; i < line.length(); i++)
                if (line[i] == ',' || line[i] == '.' || line[i] == ':' ||
                    line[i] == ';' || line[i] == '!' || line[i] == '?' ||
                    line[i] == '\"' || line[i] == '(' || line[i] == ')')
                    buffer += ' ';
                else
                    buffer += tolower(line[i]);

            istringstream iss(buffer);
            while (iss >> word)
            {
                lambda++;
                counter[word]++;
            }
            
        } while (getline(cin, line), line != "****END_OF_TEXT****");
        
        double Et = 0.0, Emax, Erel;
        
        for (auto c : counter)
            Et += c.second * (log10(lambda) - log10(c.second));
        
        Et /= lambda;
        Emax = log10(lambda);
        Erel = Et / Emax * 100.0;
        
        cout << lambda << ' ';
        cout << fixed << setprecision(1) << Et << ' ';
        cout << fixed << setprecision(0) << Erel << '\n';
    }
    
	return 0;
}
