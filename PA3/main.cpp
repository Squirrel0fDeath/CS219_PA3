#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "instruction.h"

string binToHex(string s) {
    string value;
    int val1;
    int val2;
    string temp = (s.substr(s.length()-4, s.length()));

    for(int i = 0; i*4 < s.length(); ++i) {
        val1 = s.length() - ((i * 4)) - 4;
        val2 = s.length() - (i * 4) ;

        if(s.length() > 4  && i != 0)
        {
            temp.clear();
            temp = s.substr(val1, val2);
            if(temp.length() != 4){temp = temp.substr(0,4);}
        }

        if(temp == "0000") { value.insert(0, "0");}
        else if(temp == "0001") { value.insert(0, "1");}
        else if(temp == "0010") { value.insert(0, "2");}
        else if(temp == "0011") { value.insert(0, "3");}
        else if(temp == "0100") { value.insert(0, "4");}
        else if(temp == "0101") { value.insert(0, "5");}
        else if(temp == "0110") { value.insert(0, "6");}
        else if(temp == "0111") { value.insert(0, "7");}
        else if(temp == "1000") { value.insert(0, "8");}
        else if(temp == "1001") { value.insert(0, "9");}
        else if(temp == "1010") { value.insert(0, "A");}
        else if(temp == "1011") { value.insert(0, "B");}
        else if(temp == "1100") { value.insert(0, "C");}
        else if(temp == "1101") { value.insert(0, "D");}
        else if(temp == "1110") { value.insert(0, "E");}
        else if(temp == "1111") { value.insert(0, "F");}
}

    return value;
}

int main() {
    fstream ofs;
    fstream ifs(".\\Programming-Project-3.txt");
    string s, input;
    string operand1;
    string operand2;
    string operand3;

    stringstream s1;
    stringstream s2;
    bitset<32> b1;
    Instruction i1;
    unsigned int x;
    unsigned int y;
    unsigned int z;
    unsigned int z1;
    int lengthCheck;

    ofs.open(".\\Programming-Project-3-output.txt", fstream::out | fstream::trunc);

    while (getline(ifs, s))
    {
        b1.reset();
        s1.clear();
        s2.clear();
        z = 0;

        input = s;
        operand1 = s.substr(s.find_first_of(" \t"), s.length());
        operand1 = operand1.substr(operand1.find('R') + 1, operand1.length());
        if(s.find("NOT") == string::npos
            && s.find("MOV") == string::npos
            && s.find("CMP") == string::npos
            && s.find("TST") == string::npos) {
            operand2 = operand1.substr(operand1.find_first_of(" \t"), operand1.find_last_of(" \t"));
            operand3 = operand1.substr(operand1.find_last_of(" \t"), operand1.length());
            operand1 = operand1.substr(0, operand1.find_first_of(" \t"));
        }
        else
        {
            operand2 = operand1.substr(operand1.find_first_of(" \t"));
            operand1 = operand1.substr(0, operand1.find_first_of(" \t"));
        }
        s = s.substr(0,4);

        s1 << std::hex << operand1;
        s1 >> x;
        b1 = x;
        if(s.find("NOT") == string::npos
           && s.find("MOV") == string::npos
           && s.find("CMP") == string::npos
           && s.find("TST") == string::npos)
        {
            if (operand2.find("0x") != string::npos)
            {
                operand2 = operand2.substr(operand2.find('x') + 1, operand2.length());
                s2 << std::hex << operand2;
                s2 >> z;
                b1 = z;
            }
            else {
                operand1.erase(std::remove_if(operand1.begin(), operand1.end(), ::isspace), operand1.end());
                operand2.erase(std::remove_if(operand2.begin(), operand2.end(), ::isspace), operand2.end());
                operand3.erase(std::remove_if(operand3.begin(), operand3.end(), ::isspace), operand3.end());

                x = stoi(operand1);
                y = stoi(operand2.substr(1,2));
                z = stoi(operand3.substr(1,2));
            }
        }
        else if(s.find("CMP") != string::npos || s.find("TST") != string::npos)
        {
            operand2 = operand2.substr(1,1);
        }
        else{
            operand2.erase(std::remove_if(operand2.begin(), operand2.end(), ::isspace), operand2.end());
            operand2 = operand2.substr(operand2.find('x') + 1, operand2.length());
            s2 << std::hex << stoul(operand2, nullptr, 16);
            s2 >> z;
            b1 = z;
        }

        i1.run_Instruction(s,x,y, z, b1);
        ofs << input << endl << "Result: 0x" << binToHex(i1.get_result().to_string()) << endl;
        ofs << "N: " << i1.get_nczv()[3]
            << " C: " << i1.get_nczv()[2]
            << " V: " << i1.get_nczv()[1]
            << " Z: " << i1.get_nczv()[0]
            << endl;

        ofs << "Register Values: ";
        for(int i = 0; i <=
        7; ++i)
        {
            ofs << "R" << i << ": " << binToHex(i1.call_memory(i).to_string()) << " ";
        }
       // if (s.substr(0, 3) == "ADD") {add(s, hexToBin(operand1), hexToBin(operand2)); }
        ofs << endl;
        ofs << endl;
    }
    return 0;
}