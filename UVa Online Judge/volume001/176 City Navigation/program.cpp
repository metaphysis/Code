// City Navigation
// UVa ID: 176
// Verdict: Accepted
// Submission Date: 2016-02-26
// UVa Run Time: 0.338s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct house
{
    char code;
    int index, number, step;
};

set < int > missing, discovered;
house from, to;

int getHouseId(house h)
{
    return (h.code - 'A') * 1000000 + h.index * 10000 + h.number;
}

bool isMissing(house h)
{
    return missing.count(getHouseId(h)) > 0;
}

bool isVisited(house h)
{
    return discovered.count(getHouseId(h)) > 0;
}

house makeHouse(char code, int index, int number, int step)
{
    return (house){code, index, number, step};
}

void bfs()
{
    queue<house> next;
    next.push(from);

    discovered.clear();
    discovered.insert(getHouseId(from));

    while (next.empty() == false)
    {
        house v = next.front();
        next.pop();

        if (v.number == to.number && v.index == to.index && v.code == to.code)
        {
            cout << (v.step - 2) << "\n";
            break;
        }

        if (v.code == 'A')
        {
            int sNumber = v.number / 100;
            int houseNumber = v.number % 100;

            // north
            if (houseNumber % 2 == 0)
            {
                if (houseNumber == 0)
                {
                    bool nextFound = false;
                    vector < house > temp;
                    
                    // turn right
                    if (v.index > 0)
                        temp.push_back(makeHouse('S', sNumber, (v.index - 1) * 100 + 98, v.step + 1));

                    // go forward
                    if (sNumber > 0)
                        temp.push_back(makeHouse('A', v.index, (sNumber - 1) * 100 + 98, v.step + 1));

                    // turn left
                    if (v.index < 49)
                        temp.push_back(makeHouse('S', sNumber, v.index * 100 + 1, v.step + 1));
                    
                    for (int i = 0; i < temp.size(); i++)
                        if (isMissing(temp[i]) == false)
                        {
                            if (isVisited(temp[i]) == false)
                            {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                        
                    // U-turns
                    if (nextFound == false)
                    {
                        house tempHouse = makeHouse('A', v.index, v.number + 1, v.step + 1);
                        if (isVisited(tempHouse) == false)
                        {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                }
                else
                {
                    house temp = makeHouse('A', v.index, v.number - 2, v.step + 1);
                    if (isMissing(temp))
                        temp = makeHouse('A', v.index, v.number + 1, v.step + 1);
                        
                    if (isVisited(temp) == false)
                    {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }
                }
            }

            // south
            if (houseNumber % 2 == 1)
            {
                if (houseNumber == 99)
                {
                    bool nextFound = false;
                    vector < house > temp;

                    // turn right
                    if (v.index < 49)
                        temp.push_back(makeHouse('S', sNumber + 1, v.index * 100 + 1, v.step + 1));

                    // go forward
                    if (sNumber < 48)
                        temp.push_back(makeHouse('A', v.index, (sNumber + 1) * 100 + 1, v.step + 1));

                    // turn left
                    if (v.index > 0)
                        temp.push_back(makeHouse('S', sNumber + 1, (v.index - 1) * 100 + 98, v.step + 1));

                    for (int i = 0; i < temp.size(); i++)
                        if (isMissing(temp[i]) == false)
                        {
                            if (isVisited(temp[i]) == false)
                            {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                        
                    // U-turns
                    if (nextFound == false)
                    {
                        house tempHouse = makeHouse('A', v.index, v.number - 1, v.step + 1);
                        if (isVisited(tempHouse) == false)
                        {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                }
                else
                {
                    house temp = makeHouse('A', v.index, v.number + 2, v.step + 1);
                    if (isMissing(temp))
                        temp = makeHouse('A', v.index, v.number - 1, v.step + 1);

                    if (isVisited(temp) == false)
                    {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }

                }
            }
        }

        if (v.code == 'S')
        {
            int aNumber = v.number / 100;
            int houseNumber = v.number % 100;

            // east
            if (houseNumber % 2 == 0)
            {
                if (houseNumber == 0)
                {
                    bool nextFound = false;
                    vector < house > temp;
                    
                    // turn right
                    if (v.index < 49)
                        temp.push_back(makeHouse('A', aNumber, v.index * 100 + 1, v.step + 1));

                    // go forward
                    if (aNumber > 0)
                        temp.push_back(makeHouse('S', v.index, (aNumber - 1) * 100 + 98, v.step + 1));

                    // turn left
                    if (v.index > 0)
                        temp.push_back(makeHouse('A', aNumber, (v.index - 1) * 100 + 98, v.step + 1));
                        
                    for (int i = 0; i < temp.size(); i++)
                        if (isMissing(temp[i]) == false)
                        {
                            if (isVisited(temp[i]) == false)
                            {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                        
                    // U-turns
                    if (nextFound == false)
                    {
                        house tempHouse = makeHouse('S', v.index, v.number + 1, v.step + 1);
                        if (isVisited(tempHouse) == false)
                        {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                }
                else
                {
                    house temp = makeHouse('S', v.index, v.number - 2, v.step + 1);
                    if (isMissing(temp))
                        temp = makeHouse('S', v.index, v.number + 1, v.step + 1);
                    
                    if (isVisited(temp) == false)
                    {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }
                }
            }

            // west
            if (houseNumber % 2 == 1)
            {
                if (houseNumber == 99)
                {
                    bool nextFound = false;
                    vector < house > temp;
                    
                    // turn right
                    if (v.index > 0)
                        temp.push_back(makeHouse('A', aNumber + 1, (v.index - 1) * 100 + 98, v.step + 1));

                    // go forward
                    if (aNumber < 48)
                        temp.push_back(makeHouse('S', v.index, (aNumber + 1) * 100 + 1, v.step + 1));

                    // turn left
                    if (v.index < 49)
                        temp.push_back(makeHouse('A', aNumber + 1, v.index * 100 + 1, v.step + 1));

                    for (int i = 0; i < temp.size(); i++)
                        if (isMissing(temp[i]) == false)
                        {
                            if (isVisited(temp[i]) == false)
                            {
                                discovered.insert(getHouseId(temp[i]));
                                next.push(temp[i]);
                            }
                            nextFound = true;
                        }
                        
                    // U-turns
                    if (nextFound == false)
                    {
                        house tempHouse = makeHouse('S', v.index, v.number - 1, v.step + 1);
                        if (isVisited(tempHouse) == false)
                        {
                            discovered.insert(getHouseId(tempHouse));
                            next.push(tempHouse);
                        }
                    }
                }
                else
                {
                    house temp = makeHouse('S', v.index, v.number + 2, v.step + 1);
                    if (isMissing(temp))
                        temp = makeHouse('S', v.index, v.number - 1, v.step + 1);
                        
                    if (isVisited(temp) == false)
                    {
                        discovered.insert(getHouseId(temp));
                        next.push(temp);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line;
    int start, end;

    while(cin >> line, line != "#")
    {
        cin >> start >> end;

        for (int i = start; i <= end + 1; i++)
        {
            house temp = (house){line.front(), stoi(line.substr(1)), i, 0};
            missing.insert(getHouseId(temp));
        }
    }

    while (cin >> line, line != "#")
    {
        cin >> start;
        from = (house){line.front(), stoi(line.substr(1)), start, 1};

        cin >> line >> end;
        to = (house){line.front(), stoi(line.substr(1)), end, 0};

        bfs();
    }

    return 0;
}
