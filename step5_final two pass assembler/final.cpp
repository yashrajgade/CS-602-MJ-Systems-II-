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


string getHex(int number)
{
    char hex[] = "0123456789ABCDEF";

    if (number == 0)
    {
        return "00";
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

    return result;
}


void convertToHex(int number)
{
    cout << getHex(number);
}


string convertDDToLittleEndian(int number)
{
    string hexValue = getHex(number);

    while (hexValue.length() < 8)
    {
        hexValue = "0" + hexValue;
    }

    string result = "";

    for (int i = 6; i >= 0; i -= 2)
    {
        result += hexValue.substr(i, 2);
    }

    return result;
}


string formatOffset(int number)
{
    string hexValue = getHex(number);

    while (hexValue.length() < 8)
    {
        hexValue = "0" + hexValue;
    }

    return hexValue;
}


void printData(string hexOutput,
               int &dataOffset,
               string source)
{
    int position = 0;
    bool firstLine = true;

    while (position < hexOutput.length())
    {
        int remaining = hexOutput.length() - position;

        int lineLength = 16;

        if (remaining < lineLength)
        {
            lineLength = remaining;
        }

        string lineHex =
            hexOutput.substr(position, lineLength);


        cout << formatOffset(dataOffset)
             << " "
             << lineHex;


        if (firstLine)
        {
            cout << " "
                 << source;

            firstLine = false;
        }


        cout << endl;


        dataOffset += lineHex.length() / 2;

        position += lineHex.length();
    }
}

class Symbol
{
public:
    string name;
    int offset;
    int size;
    char type;
};




 int getRegCode(string reg)
 {
    if (reg == "eax") return 0;
    if (reg == "ecx") return 1;
    if (reg == "edx") return 2;
    if (reg == "ebx") return 3;
    if (reg == "esp") return 4;
    if (reg == "ebp") return 5;
    if (reg == "esi") return 6;
    if (reg == "edi") return 7;

    return -1;
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

    int dataOffset = 0;
    int textOffset = 0;
    string currentSection = "";
    vector<Symbol> symbolTable;


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

        // Remove UTF-8 BOM if it appears before the first word.
        if (mnemonic.length() >= 3 &&
            (unsigned char)mnemonic[0] == 0xEF &&
            (unsigned char)mnemonic[1] == 0xBB &&
            (unsigned char)mnemonic[2] == 0xBF)
        {
            mnemonic.erase(0, 3);
        }


        if (mnemonic == "global")
        {
            continue;
        }

        if (mnemonic == "section")
        {
            ss >> currentSection;
            continue;
        }

        if (mnemonic.back() == ':')
        {
            string labelName = mnemonic.substr(0, mnemonic.length() - 1);

            if (currentSection == ".text")
            {
                Symbol s;
                s.name = labelName;
                s.offset = textOffset;
                s.size = 0;
                s.type = (labelName == "main") ? 'T' : 't';
                symbolTable.push_back(s);
            }

            continue;
        }


        string directive;

        ss >> directive;


        if (currentSection == ".data" && directive == "db")
        {
            string value;

            getline(ss, value);

            string hexOutput = "";
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
                                hexOutput +=
                                    getHex((int)part[j]);
                            }
                        }

                        else
                        {
                            int number = stoi(part);

                            hexOutput += getHex(number);
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
                        hexOutput +=
                            getHex((int)part[j]);
                    }
                }

                else
                {
                    int number = stoi(part);

                    hexOutput += getHex(number);
                }
            }


            Symbol s;
            s.name = mnemonic;
            s.offset = dataOffset;
            s.size = hexOutput.length() / 2;
            s.type = 'd';
            symbolTable.push_back(s);

            string source =
                mnemonic + " db" + value;


            printData(hexOutput,
                      dataOffset,
                      source);


            continue;
        }


        if (currentSection == ".data" && directive == "dd")
        {
            string value;

            getline(ss, value);

            string hexOutput = "";
            string part = "";


            for (int i = 0;
                 i <= value.length();
                 i++)
            {
                if (i == value.length() ||
                    value[i] == ',')
                {
                    if (!part.empty())
                    {
                        int number = stoi(part);

                        hexOutput +=
                            convertDDToLittleEndian(number);

                        part = "";
                    }
                }

                else
                {
                    if (value[i] != ' ')
                    {
                        part += value[i];
                    }
                }
            }


            Symbol s;
            s.name = mnemonic;
            s.offset = dataOffset;
            s.size = hexOutput.length() / 2;
            s.type = 'd';
            symbolTable.push_back(s);

            string source =
                mnemonic + " dd" + value;


            printData(hexOutput,
                      dataOffset,
                      source);

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

    }


    asmfile.close();

     ofstream symbolFile("symbol_table.txt");

  if (!symbolFile)
  { 
      cout << "Error: Cannot create symbol_table.txt" << endl;
      return 1;
  }

  cout << "\nSymbol Table\n";
  cout << "Address  Type  Symbol\n";

  symbolFile << "Address  Type  Symbol\n";

  for (const auto &s : symbolTable)
  {
     cout << formatOffset(s.offset) << "  "
          << s.type << "     "
          << s.name << endl;

      symbolFile << formatOffset(s.offset) << "  "
                << s.type << "     "
                << s.name << endl;
  }

  symbolFile.close();

  cout << "\nSymbol table saved to symbol_table.txt" << endl;
  
  
  
  ofstream listing("p.lst");

 if (!listing)
 {
     cout << "Error: Cannot create p.lst" << endl;
    return 1;
 }

 listing << "Address    Machine Code       Assembly Instruction\n";
 

 ifstream input("demo.asm");

 string section = "";


 while (getline(input, line))
 {
    string originalLine = line;

    size_t comment = line.find(';');
    if (comment != string::npos)
        line = line.substr(0, comment);

    stringstream ss(line);

    string mnemonic;
    ss >> mnemonic;

    if (mnemonic.empty())
        continue;

    if (mnemonic == "global")
        continue;

    if (mnemonic == "section")
    {
        ss >> section;
        continue;
    }

    if (mnemonic.back() == ':')
        continue;

    if (section != ".text")
        continue;

    string op1, op2;
    ss >> op1 >> op2;

    if (!op1.empty() && op1.back() == ',')
        op1.pop_back();

    string machineCode = "";
    int size = 0;

    int r1 = getRegCode(op1);
    int r2 = getRegCode(op2);

    if (mnemonic == "mov" && r1 >= 0 && r2 >= 0)
    {
        int modrm = 0xC0 | (r2 << 3) | r1;

        machineCode = "89 " + getHex(modrm);
        size = 2;
    }
    else if (mnemonic == "add" && r1 >= 0 && r2 >= 0)
    {
        int modrm = 0xC0 | (r2 << 3) | r1;

        machineCode = "01 " + getHex(modrm);
        size = 2;
    }
    else if (mnemonic == "sub" && r1 >= 0 && r2 >= 0)
    {
        int modrm = 0xC0 | (r2 << 3) | r1;

        machineCode = "29 " + getHex(modrm);
        size = 2;
    }
    else if (mnemonic == "mov" && r1 >= 0 && isConstant(op2))
    {
        int value = stoi(op2);

        machineCode = getHex(0xB8 + r1) + " ";

        string imm = convertDDToLittleEndian(value);

        for (int i = 0; i < imm.length(); i += 2)
        {
            if (i > 0)
                machineCode += " ";

            machineCode += imm.substr(i, 2);
        }

        size = 5;
    }

    if (!machineCode.empty())
    {
        listing << formatOffset(textOffset)
                << "  " << machineCode
                << "       " << originalLine << endl;

        textOffset += size;
    } 
 }

  input.close();
  listing.close();
  
  
 

 ifstream listFile("p.lst");

 string outputLine;

 while (getline(listFile, outputLine))
 {
    cout << outputLine << endl;
 }

 listFile.close();

   cout << "Listing saved to p.lst" << endl;
  
  
  
      return 0;
   }

