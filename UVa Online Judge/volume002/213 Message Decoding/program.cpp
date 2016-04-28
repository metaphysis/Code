// Message Decoding
// UVa IDs: 213
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <map>
#include <bitset>

using namespace std;

map < string, int > indexer;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);

    for (int i = 2, index = 0, length = 1; length < 8; i *= 2, length++)
        for (int j = 0; j < (i - 1); j++)
        {
            bitset < 8 > number(j);
            indexer.insert(make_pair(number.to_string().substr(8 - length,
                        length), index));
            index++;
        }

    string line, header, buffer;
    bool headerReaded = false;
    bool currentReadEnded = false, keyLengthReaded = false;
    int keyLength;

    while (getline(cin, line))
    {
        if (headerReaded == false)
        {
            header = line;
            headerReaded = true;
        }
        else
        {
            buffer += line;

          next:

            if (keyLengthReaded == false)
            {
                if (buffer.length() >= 3)
                {
                    keyLength = stoi(buffer.substr(0, 3), NULL, 2);
                    if (keyLength == 0)
                    {
                        headerReaded = false;
                        keyLengthReaded = false;
                        buffer.clear();
                        cout << "\n";
                    }
                    else
                    {
                        buffer.erase(0, 3);
                        keyLengthReaded = true;
                        currentReadEnded = false;
                    }
                }
            }

            if (currentReadEnded == false)
            {
                while (buffer.length() >= keyLength)
                {
                    string key = buffer.substr(0, keyLength);
                    if (key == string(keyLength, '1'))
                    {
                        currentReadEnded = true;
                        keyLengthReaded = false;
                        buffer.erase(0, keyLength);
                        goto next;
                    }
                    else
                    {
                        cout << header[indexer[key]];
                        buffer.erase(0, keyLength);
                    }
                }
            }
        }
    }

    return 0;
}
