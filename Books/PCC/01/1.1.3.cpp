#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "#include <bits/stdc++.h>\n"
         << "using namespace std;\n"
         << "int main(int argc, char *argv[])\n"
         << "{\n";

    vector<string> dataTypes = {
        "bool", "char", "unsigned char", "short int", "unsigned short int",
        "int", "unsigned int", "long int", "unsigned long int",
        "long long int", "unsigned long long int",
        "float", "double", "long double"
    };

    string literal =
        "    cout << [$: ] << sizeof($) << [B, ] << #numeric_limits<$>::min()"
        " << [ ~ ] << #numeric_limits<$>::max() << endl;";

    for (auto t : dataTypes)
    {
        for (auto c : literal)
        {
            if (c == '[' || c == ']') cout << '\"';
            else if (c == '$') cout << t;
            else if (c == '#')
            {
                if (t.front() == 'b' || t.back() == 'r') cout << "(int)";
            }
            else cout << c;
        }

        cout << endl;
    }

    cout << "    return 0;\n"
         << "}\n";

    return 0;
}
