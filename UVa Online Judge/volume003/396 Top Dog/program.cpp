// Top Dog
// UVa ID: 396
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<string> names;
map<string, vector<vector<string>>> tables;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        cout << n << endl;
        
        names.clear();
        tables.clear();

        while (getline(cin, line), line.length() > 0)
            names.push_back(line);
        
        while (getline(cin, line), line.length() > 0)
        {
            vector<vector<string>> fields;
            string name = line;
            while (getline(cin, line), line != "#")
            {
                istringstream iss(line);
                vector<string> property;
                string block;
                while (iss >> block) property.push_back(block);
                fields.push_back(property);
            }
            tables[name] = fields;
        }
        
        for (auto name : names)
        {
            if (tables.find(name) == tables.end())
                cout << "<TABLE NOT FOUND>" << endl;
            else
            {
                cout << "SELECT ";
                bool first_field = true;
                for (auto field : tables[name])
                {
                    if (first_field) first_field = false;
                    else cout << ", ";
                    
                    if (field[1] == "INT" || field[1] == "LONGINT") cout << "(NUM) ";
                    else cout << "(CHAR) ";
                    
                    cout << field[0];
                }
                cout << " FROM " << name << ";" << endl;
            }
        }
        
        cout << endl;
        
        while (getline(cin, line), line.length() > 0)
        {
            string name = line;
            vector<vector<string>> records;
            vector<string> record;
            
            while (getline(cin, line), line != "#")
            {
                if (line == "<NULL>")
                    record.push_back("");
                else
                    record.push_back(line);
                if (record.size() == tables[name].size())
                {
                    records.push_back(record);
                    record.clear();
                }
            }
            
            cout << name << "(" << tables[name].size() << ")(" << records.size() << ")" << endl;
            for (int i = 0; i < records.size(); i++)
            {
                for (int j = 0; j < records[i].size(); j++)
                {
                    cout << tables[name][j].front();
                    if (tables[name][j][1] == "VARCHAR" && stoi(tables[name][j][2]) > 64)
                        cout << "(" << tables[name][j][2] << ")";
                    cout << " ";
                    cout << "\"" << records[i][j] << "\"";
                    cout << endl;
                }
            }
        }
    }
    
	return 0;
}
