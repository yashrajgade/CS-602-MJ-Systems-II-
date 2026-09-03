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

int main()
{
    vector<OpcodeEnt> opTable;

    
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
            mnemonic == "section" 
            )
        {
            continue;
        }


        if (mnemonic.back() == ':')
        {
            continue;
        }


        if (mnemonic == "db" ||
            mnemonic == "dw" ||
            mnemonic == "dd" ||
            mnemonic == "resb" ||
            mnemonic == "resw" ||
            mnemonic == "resd")
        {
            continue;
        }
 
 
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


        
        cout << "\nMnemonic : "
             << mnemonic << endl;

        if (found)
        {
            cout << "Status   : Found" << endl;
        }
        else
        {
            cout << "Status   : Not Found" << endl;
        }


        if (!operand1.empty())
        {
            cout << "Operand  : "
                 << operand1 << endl;

            cout << "Type     : "
                 << getOperandType(operand1)
                 << endl;
        }
       
        if (!operand2.empty())
        {
            cout << "Operand  : "
                 << operand2 << endl;

            cout << "Type     : "
                 << getOperandType(operand2)
                 << endl;
        }
    }

    asmfile.close();

    return 0;
}
