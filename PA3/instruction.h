//
// Created by Jonathan Cantlon on 10/25/2023.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <bitset>
using namespace std;

class Instruction {
private:
    bitset<32> memory[8];
    bitset<4> nczv;
    bitset<32> result;

    bool add_i(int, int, int, bool);
    bool and_i(int, int, int, bool);
    bool asr_i(int, int, int, bool);
    bool lsr_i(int, int, int, bool);
    bool lsl_i(int, int, int, bool);
    bool not_i(int, bool);
    bool orr_i(int, int, int, bool);
    bool sub_i(int, int, int, bool);
    bool xor_i(int, int, int, bool);
    bool mov_i(int, bitset<32>, bool);
    bool cmp_i(int, int);
    bool tst_i(int, int);

public:
    Instruction();
    Instruction(const Instruction&);

    bool run_Instruction(string, int, int, int, bitset<32>);
    bitset<4> get_nczv();
    bool set_nczv(bitset<4>);
    bitset<32> get_result();
    bitset<32> call_memory(int);
    void set_memory(int, bitset<32>);
};
#include "instruction.cpp"
#endif //INSTRUCTION_H
