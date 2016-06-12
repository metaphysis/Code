#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "#include <iostream>\n"
         << "#include <iomanip>\n"
         << "#include <limits>\n"
         << "using namespace std;\n"
         << "int main(int argc, char *argv[])\n"
         << "{\n";

    string dataTypes[] = {
        "bool",
        "char", "unsigned char",
        "short int", "unsigned short int",
        "int", "unsigned int",
        "long int", "unsigned long int",
        "long long int", "unsigned long long int",
        "float",
        "double", "long double"
    };

    for (int i = 0; i < 14; i++)
    {
        cout << "    cout << setw(24) << right << \"" << dataTypes[i]
             << ":\" << setw(3) << right << sizeof("
             << dataTypes[i] << ") << \"B, \" << setw(20) << right << "
             << (i <= 2 ? "(int)" : "") << "numeric_limits<" << dataTypes[i]
             << ">::min() << \" ~ \" << left << " << (i <= 2 ? "(int)" : "")
             << "numeric_limits<" << dataTypes[i] << ">::max() << endl;\n";
    }

    cout << "    return 0;\n"
         << "}\n";

    return 0;
}
