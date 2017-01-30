// Message Decoding
// UVa ID: 213
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <map>
#include <bitset>

using namespace std;

map<string, int> indexer;

int main(int argc, char *argv[])
{
    for (int i = 2, idx = 0, length = 1; length < 8; i *= 2, length++)
        for (int j = 0; j < (i - 1); j++)
        {
            bitset<8> n(j);
            indexer.insert(make_pair(n.to_string().substr(8 - length, length), idx));
            idx++;
        }

    string line, header, buffer;
    bool headerReaded = false;
    bool segmentEnded = false, segmentStarterReaded = false;
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

            if (segmentStarterReaded == false)
            {
                if (buffer.length() >= 3)
                {
                    keyLength = stoi(buffer.substr(0, 3), NULL, 2);
                    if (keyLength == 0)
                    {
                        headerReaded = false;
                        segmentStarterReaded = false;
                        buffer.clear();
                        cout << "\n";
                    }
                    else
                    {
                        buffer.erase(0, 3);
                        segmentStarterReaded = true;
                        segmentEnded = false;
                    }
                }
            }

            if (segmentEnded == false)
            {
                while (buffer.length() >= keyLength)
                {
                    string key = buffer.substr(0, keyLength);
                    if (key == string(keyLength, '1'))
                    {
                        segmentEnded = true;
                        segmentStarterReaded = false;
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
