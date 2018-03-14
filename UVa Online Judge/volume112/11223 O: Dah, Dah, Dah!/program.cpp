// O: Dah, Dah, Dah!
// UVa ID: 11223
// Verdict: Accepted
// Submission Date: 2017-12-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<string, char> morse = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
        {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
        {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
        {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
        {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
        {"--..", 'Z'}, {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, 
        {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'},
        {"----.", '9'}, {".-.-.-", '.'}, {"--..--", ','}, {"..--..", '?'}, {".----.", '\''},
        {"-.-.--", '!'}, {"-..-.", '/'}, {"-.--.", '('}, {"-.--.-", ')'}, {".-...", '&'},
        {"---...", ':'}, {"-.-.-.", ';'}, {"-...-", '='}, {".-.-.", '+'}, {"-....-", '-'},
        {"..--.-", '_'}, {".-..-.", '\"'}, {".--.-.", '@'}
    };

    int cases;
    cin >> cases; cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {        
        char dida;
        int space = 0;
        string line, word, code;
        
        while (cin.get(dida))
        {
            if (dida == ' ') space++;
            else
            {
                if (space || dida == '\n')
                {
                    word += morse[code];
                    code.clear();
                    if (space == 2 || dida == '\n')
                    {
                        if (line.length()) line += ' ';
                        line += word;
                        word.clear();
                    }
                    space = 0;
                }
                code += dida;
            }
            if (dida == '\n') break;
        }

        if (c > 1) cout << '\n';
        cout << "Message #" << c << '\n';
        cout << line << '\n';
    }

    return 0;
}
