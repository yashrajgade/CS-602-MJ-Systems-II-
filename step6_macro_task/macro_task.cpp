#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

struct Macro
{
    string name;
    int count;
    vector<string> body;
};

map<string, Macro> macroTable;

string trim(string str)
{
    size_t start = str.find_first_not_of(" \t\r\n");

    if (start == string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t\r\n");

    return str.substr(start, end - start + 1);
}

vector<string> getArguments(string str)
{
    vector<string> args;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, ','))
    {
        args.push_back(trim(temp));
    }

    return args;
}

string replaceParameters(string line, vector<string> args)
{
    string result;

    for (int i = 0; i < line.length();)
    {
        if (line[i] == '%' && i + 1 < line.length() &&
            isdigit((unsigned char)line[i + 1]))
        {
            int num = 0;
            i++;

            while (i < line.length() &&
                   isdigit((unsigned char)line[i]))
            {
                num = num * 10 + line[i] - '0';
                i++;
            }

            if (num >= 1 && num <= args.size())
                result += args[num - 1];
            else
                result += "%" + to_string(num);
        }
        else
        {
            result += line[i];
            i++;
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./macro input.asm output.asm";
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    if (!input)
    {
        cout << "Cannot open input file";
        return 1;
    }

    if (!output)
    {
        cout << "Cannot create output file";
        return 1;
    }

    string line;
    Macro *current = NULL;

    while (getline(input, line))
    {
        string temp = trim(line);

        if (temp.rfind("%macro", 0) == 0)
        {
            stringstream ss(temp);
            string keyword, name;
            int count;

            ss >> keyword >> name >> count;

            Macro m;
            m.name = name;
            m.count = count;

            macroTable[name] = m;
            current = &macroTable[name];

            continue;
        }

        if (current != NULL)
        {
            if (temp == "%endmacro")
            {
                current = NULL;
            }
            else
            {
                current->body.push_back(line);
            }

            continue;
        }

        stringstream ss(temp);
        string name;

        ss >> name;

        if (macroTable.find(name) != macroTable.end())
        {
            string remaining;
            getline(ss, remaining);

            vector<string> args = getArguments(trim(remaining));

            Macro &m = macroTable[name];

            if (args.size() != m.count)
            {
                cout << "Wrong number of arguments";
                return 1;
            }

            for (string bodyLine : m.body)
            {
                output << replaceParameters(bodyLine, args) << endl;
            }
        }
        else
        {
            output << line << endl;
        }
    }

    input.close();
    output.close();

    cout << "Macro expansion completed successfully!" << endl;
    cout << "Output file: " << argv[2] << endl;

    return 0;
}
