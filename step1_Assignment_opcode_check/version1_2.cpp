#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class OpcodeEnt
{
public:
    string opcode;
    string mnemonic;
    int opCount;
    string operand1;
    string operand2;
    string modrm;
    string extension;
};


bool isReg(string operand)
{
    string registers[] =
    {
        "eax", "ebx", "ecx", "edx",
        "esi", "edi", "esp", "ebp"
    };

    for (string reg : registers)
    {
        if (operand == reg)
            return true;
    }

    return false;
}


bool isConstant(string operand)
{
    if (operand.empty())
        return false;

    for (char c : operand)
    {
        if (!isdigit(c))
            return false;
    }

    return true;
}


string getOperandType(string operand)
{
    if (isReg(operand))
        return "Register";

    if (isConstant(operand))
        return "Constant";

    if (!operand.empty() &&
        operand[0] == '[' &&
        operand[operand.length() - 1] == ']')
    {
        return "Memory";
    }

    return "Symbol";
}



void convertToHex(int number)
{
    char hex[] = "0123456789ABCDEF";

    if (number == 0)
    {
        cout << "00";
        return;
    }

    string result = "";

    while (number > 0)
    {
        int remainder = number % 16;

        result = hex[remainder] + result;

        number = number / 16;
    }

    if (result.length() == 1)
    {
        result = "0" + result;
    }

    cout << result;
}


int main()
{
    vector<OpcodeEnt> opTable;


    // Read opcode file

    ifstream file("instructions.txt");

    if (!file)
    {
        cout << "Error: Cannot open instructions.txt"
             << endl;

        return 1;
    }

    OpcodeEnt entry;

    while (file >> entry.opcode
                >> entry.mnemonic
                >> entry.opCount
                >> entry.operand1
                >> entry.operand2
                >> entry.modrm
                >> entry.extension)
    {
        opTable.push_back(entry);
    }

    file.close();


    ifstream asmfile("demo.asm");

    if (!asmfile)
    {
        cout << "Error: Cannot open demo.asm"
             << endl;

        return 1;
    }


    string line;


    while (getline(asmfile, line))
    {
        if (line.empty())
            continue;


        size_t comment = line.find(';');

        if (comment != string::npos)
        {
            line = line.substr(0, comment);
        }


        stringstream ss(line);

        string mnemonic;

        ss >> mnemonic;

        if (mnemonic.empty())
            continue;

        if (mnemonic == "global" ||
            mnemonic == "section")
        {
            continue;
        }


        if (mnemonic.back() == ':')
        {
            continue;
        }


        string directive;

        ss >> directive;


        if (directive == "db")
        {
            string value;

            getline(ss, value);

            cout << "\nVariable: " << mnemonic << endl;

            cout << "DB Value: " << value << endl;

            cout << "Hexadecimal: ";


            string part = "";



            for (int i = 0; i < value.length(); i++)
            {
                if (value[i] == ',')
                {
                    if (!part.empty())
                    {

                        if (part[0] == '"' ||
                            part[0] == '\'')
                        {
                            for (int j = 1;
                                 j < part.length() - 1;
                                 j++)
                            {
                                convertToHex((int)part[j]);

                                cout << " ";
                            }
                        }


                        else
                        {
                            int number = stoi(part);

                            convertToHex(number);

                            cout << " ";
                        }
                    }


                    part = "";
                }

                else
                {
                    if (value[i] != ' ')
                    {
                        part += value[i];
                    }
                }
            }


            if (!part.empty())
            {
                if (part[0] == '"' ||
                    part[0] == '\'')
                {
                    for (int j = 1;
                         j < part.length() - 1;
                         j++)
                    {
                        convertToHex((int)part[j]);

                        cout << " ";
                    }
                }

                else
                {
                    int number = stoi(part);

                    convertToHex(number);
                }
            }


            cout << endl;

            continue;
        }


        if (directive == "dd")
        {
            int number;

            ss >> number;


            cout << "\nVariable: " << mnemonic << endl;

            cout << "DD Value: "
                 << number << endl;

            cout << "Hexadecimal: ";

            convertToHex(number);

            cout << endl;

            continue;
        }


        /*

        string operand1;
        string operand2;

        ss >> operand1;
        ss >> operand2;

        if (!operand1.empty() &&
            operand1.back() == ',')
        {
            operand1.pop_back();
        }


        bool found = false;

        for (const auto &entry : opTable)
        {
            if (entry.mnemonic == mnemonic)
            {
                found = true;
                break;
            }
        }


        cout << "\nMnemonic: "
             << mnemonic << endl;


        if (found)
        {
            cout << "Status: Found" << endl;
        }

        else
        {
            cout << "Status: Not Found" << endl;
        }
        */
    }


    asmfile.close();

    return 0;
}
