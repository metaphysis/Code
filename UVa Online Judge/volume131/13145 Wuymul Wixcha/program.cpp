// Wuymul Wixcha
// UVa ID: 13145
// Verdict: Accepted
// Submission Date: 2021-12-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    //string plain = "The first obvious problem is to decrypt this message. If you are reading this, surely you have already done it. So the rest of this problem is very easy.";
    //string code =  "Nby zclmn ivpciom jlivfyg cm ni xywlsjn nbcm gymmuay. Cz sio uly lyuxcha nbcm, molyfs sio bupy uflyuxs xihy cn. Mi nby lymn iz nbcm jlivfyg cm pyls yums.";
    //char key[256] = {};
    //for (int i = 0; i < plain.length(); i++) key[code[i]] = plain[i];
    //for (int i = 0; i < 26; i++) cout << (key[97 + i] ? key[97 + i] : '?') << '\n';

    //string line;
    //while (getline(cin, line))
    //{
    //    for (int i = 0; i < line.length(); i++)
    //    {
    //        if (isalpha(line[i]))
    //        {
    //            if (isupper(line[i])) cout << (char)('A' + (line[i] - 'A' + 6) % 26);
    //            if (islower(line[i])) cout << (char)('a' + (line[i] - 'a' + 6) % 26);
    //        }
    //        else cout << line[i];
    //    }
    //    cout << '\n';
    //}
    
    int N;
    string line;
    while (cin >> N, N)
    {
        cin.ignore(256, '\n');
        getline(cin, line);
        for (int i = 0; i < line.length(); i++)
        {
            if (isalpha(line[i]))
            {
                if (isupper(line[i])) cout << (char)('A' + (line[i] - 'A' + N % 26 + 26) % 26);
                if (islower(line[i])) cout << (char)('a' + (line[i] - 'a' + N % 26 + 26) % 26);
            }
            else cout << line[i];
        }
        cout << '\n';
    }

    return 0;
}
