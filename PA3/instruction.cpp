//
// Created by Jonathan Cantlon on 10/25/2023.
//

#include "instruction.h"

Instruction::Instruction(){nczv = 0000;}

Instruction::Instruction(const Instruction& oldInstruct){nczv = this->get_nczv();}

bool Instruction::add_i(int mem1, int mem2, int mem3, bool flag)
{
    bitset<32> operand1 = call_memory(mem1);
    bitset<32> operand2 = call_memory(mem2);
    bitset<32> i = bitset<32>(operand1.to_ulong() + operand2.to_ulong());

    result = bitset<32>(i.to_ulong());
    set_memory(mem3, i);

    if(flag)
    {
        bitset<4> temp;
        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}
        temp[1] = i[32];
        set_nczv(temp);
    }

    return true;
}

bool Instruction::and_i(int mem1, int mem2, int mem3, bool flag)
{
    bitset<32> operand1 = call_memory(mem1);
    bitset<32> operand2 = call_memory(mem2);

    result = (operand1 &= operand2);
    set_memory(mem3, result);

    if(flag)
    {
        bitset<4> temp;
        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}

        set_nczv(temp);
    }
    return true;
}

bool Instruction::asr_i(int mem1, int mem2, int num, bool flag)
{
    bitset<32> operand = call_memory(mem1);

    int hold = operand[32];
    bitset<31> temp(operand.to_ulong());
    temp = (temp >>= num);
    bitset<32> value(temp.to_ulong());
    value[32] = hold;

    bitset<4> newFlags;
    newFlags[4] = hold;

    if(flag)
    {
        bitset<4> temp;

        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}

        if(result[31] == true){temp[3] = true;}
        else{temp[3] = false;}

        set_nczv(temp);
    }

    result = value;
    set_memory(mem2, result);
    return true;
}

bool Instruction::lsr_i(int mem1, int mem2, int num, bool flag)
{
    bitset<32> operand = call_memory(mem1);
    result = (operand >>= num);
    auto temp = result.to_ulong();
    set_memory(mem2, result);
    if(flag)
    {
        bitset<4> temp;

        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}

        set_nczv(temp);
    }
    return true;
}

bool Instruction::lsl_i(int mem1, int mem2, int num, bool flag)
{
    bitset<32> operand = call_memory(mem1);
    result = (operand <<= num);
    set_memory(mem2, result);
    if(flag)
    {
        bitset<4> temp;
        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}

        set_nczv(temp);
    }
    return true;
}

bool Instruction::not_i(int mem1, bool flag)
{
    bitset<32> operand = call_memory(mem1);
    result = ~operand;
    if(flag)
    {
        bitset<4> temp;
        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}

        set_nczv(temp);
    }
    return true;
}

bool Instruction::orr_i(int mem1, int mem2, int mem3, bool flag)
{
    bitset<32> operand1 = call_memory(mem1);
    bitset<32> operand2 = call_memory(mem2);

    result = (operand1 |= operand2);
    set_memory(mem3, result);

    if(flag)
    {
        bitset<4> temp;
        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}

        set_nczv(temp);
    }
    return true;
}

bool Instruction::sub_i(int mem1, int mem2, int mem3, bool flag)
{
    bitset<32> operand1 = call_memory(mem1);
    bitset<32> operand2 = call_memory(mem2);
    bitset<32> i = bitset<32>(operand1.to_ulong() - operand2.to_ulong());
    result = i;
    set_memory(mem3, result);

    if(flag)
    {
        bitset<4> temp;
        if(result[32] == 0){temp[2] = false;}
        else{temp[2] = true;}
        if(result == 0){temp[0] = true;}
        else{temp[0] = false;}

        set_nczv(temp);
    }
    return true;
}

bool Instruction::xor_i(int mem1, int mem2, int mem3, bool flag)
{
    bitset<32> operand1 = call_memory(mem1);
    bitset<32> operand2 = call_memory(mem2);

    result = (operand1 ^= operand2);
    set_memory(mem3, result);

    if(flag)
    {
        bitset<4> temp;
        if(result.to_ulong() == 0){temp[0] = true;}
        else{temp[0] = false;}

        set_nczv(temp);
    }
    return true;
}

bool Instruction::mov_i(int mem1, bitset<32> operandImm, bool flag)
{
    auto temp = operandImm.to_ulong();
    set_memory(mem1, operandImm);
    result = operandImm;
    bitset<4> tempFlag;

    if(call_memory(mem1).to_ulong() == 0){tempFlag[2] = true;}
    else                       {tempFlag[2] = false;}
    if(call_memory(mem1).to_ulong() == 0){tempFlag[0] = true;}
    else                       {tempFlag[0] = false;}

    set_nczv(tempFlag);
    return true;
}

bool Instruction::cmp_i(int mem1, int mem2)
{
    bitset<32> tempOp = (call_memory(mem1) & ~call_memory(mem2));
    bitset<4> tempFlag;
    result = tempOp;

    if(result[32] == 0){tempFlag[2] = false;}
    else{tempFlag[2] = true;}
    if(result == 0){tempFlag[0] = true;}
    else{tempFlag[0] = false;}

    set_nczv(tempFlag);
    return true;
}

bool Instruction::tst_i(int mem1, int mem2)
{

    bitset<32> tempOp = (call_memory(mem1) & ~call_memory(mem2));
    bitset<4> tempFlag;
    result = tempOp;
    if(tempOp.to_ulong() == 0){tempFlag[2] = true;}
    else{tempFlag[2] = false;}
    if(tempOp.to_ulong() == 0){tempFlag[0] = true;}

    else{tempFlag[0] = false;}
    return true;
}

bool Instruction::run_Instruction(string str, int o1, int o2, int o3, bitset<32> o4)
{
    bool flag = false;
    if(str[3] == 'S'){flag = true;}
    str = str.substr(0,3);

    if(str == "ADD"){this->add_i(o2, o3, o1, flag);}
    if(str == "AND"){this->and_i(o2, o3, o1, flag);}
    if(str == "ASR"){this->asr_i(o2, o3,o1, flag);}
    if(str == "LSR"){this->lsr_i(o2, o1, o3, flag);}
    if(str == "LSL"){this->lsl_i(o2, o1, o3, flag);}
    if(str == "NOT"){this->not_i(o1, flag);}
    if(str == "ORR"){this->orr_i(o2, o3, o1, flag);}
    if(str == "SUB"){this->sub_i(o2, o3, o1, flag);}
    if(str == "XOR"){this->xor_i(o2, o3, o1, flag);}
    if(str == "MOV"){this->mov_i(o1, o4, flag);}
    if(str == "CMP"){this->cmp_i(o2, o1);}
    if(str == "TST"){this->tst_i(o2, o1);}
    return true;
}

bitset<4> Instruction::get_nczv(){return nczv;}

bool Instruction::set_nczv(bitset<4> newN){nczv = newN; return true;}

bitset<32> Instruction::get_result(){return result;}

bitset<32> Instruction::call_memory(int num)
{
    return memory[num];
}

void Instruction::set_memory(int num, bitset<32> newMem)
{
    memory[num] = newMem;
}
