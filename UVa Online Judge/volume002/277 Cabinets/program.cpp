// Cabinets
// UVa IDs: 277
// Verdict: Accepted
// Submission Date: 2016-05-26
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    getline(cin, line);
    int cases = stoi(line);

    getline(cin, line);
    while (cases--)
    {
        cout << "Item Id,Item Desc,Item Price" << endl;

        map<string, string> codeAndName;

        while (getline(cin, line), line.length() > 0)
        {
            int comma = count(line.begin(), line.end(), ',');
            while (comma < 5)
            {
                line.push_back(',');
                comma++;
            }

            vector<string> item;
            istringstream iss(line);
            for (string block; getline(iss, block, ','); )
                item.push_back(block);

            string code = item[0], name = item[1], description = item[2];
            string extension = item[3], price = item[4];

            if (codeAndName.count(code) == 0)
                codeAndName.insert(make_pair(code, name));

            if (description.length() > 10)
                continue;

            string itemId = code;
            while (itemId.length() < 3)
                itemId.insert(itemId.begin(), '0');
            itemId += description;

            string itemDesc = name;
            if (itemDesc.length() == 0)
            {
                if (codeAndName[code].length() == 0)
                    continue;
                else
                    itemDesc = codeAndName[code];
            }

            if (extension.length())
            {
                itemDesc += '-' + extension;
                if (itemDesc.length() > 30)
                    itemDesc.erase(itemDesc.begin() + 30, itemDesc.end());
            }

            string itemPrice = "0.00";
            if (price.length())
            {
                int cent = stoi(price);
                itemPrice = to_string(cent / 100);
                cent %= 100;
                itemPrice += '.';
                if (cent < 10)
                    itemPrice += '0';
                itemPrice += to_string(cent);
            }

            cout << itemId << "," << itemDesc << "," << itemPrice << endl;
        }

        if (cases)
            cout << endl;
    }

    return 0;
}
