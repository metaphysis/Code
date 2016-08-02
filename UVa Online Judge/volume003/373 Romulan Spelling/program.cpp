// Romulan Spelling
// UVa ID: 373
// Verdict: Accepted
// Submission Date: 2016-07-31
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    string line;
    while (getline(cin, line))
    {
        for (int i = 0, length = line.length(); i < length; i++)
        {
            if (tolower(line[i]) == 'g')
            {
                if (i && tolower(line[i - 1]) == 'p')
                {
                    if (i < length - 1 && tolower(line[i + 1]) == 'u' && tolower(line[i + 2]) == 'k')
                        ;
                    else
                    {
                        int j = i;
                        do
                        {
                            if (j > 1 && tolower(line[j - 2]) == 'e')
                                break;
                            swap(line[j - 1], line[j]);
                            j--;
                        }
                        while (j && tolower(line[j - 1]) == 'p');
                    }
                }
            }

            if (tolower(line[i]) == 'g')
            {
                if (i < length && tolower(line[i + 1]) == 'p')
                {
                    if (i && tolower(line[i - 1]) == 'e')
                        swap(line[i], line[i + 1]);

                    else if (i < length - 2 && tolower(line[i + 2]) == 'u' && tolower(line[i + 3]) == 'k')
                    {
                        swap(line[i], line[i + 1]);
                        if (i > 1 && tolower(line[i - 1]) == 'g' && tolower(line[i - 2]) == 'e')
                            swap(line[i - 1], line[i]);
                    }
                }
            }
        }
        
        cout << line << '\n';
    }
    return 0;
}
