#include <string.h>
#include <stdio.h>
#include "kpu.h"

void kpu_init(KPU *kpu){
    memset(kpu->reg_arr, 0, sizeof(kpu->reg_arr));
    kpu->prog_counter = 0x0000;
    kpu->stack = 0xFFFF;
    memset(kpu->memory_arr, 0, sizeof(kpu->memory_arr));
    kpu->flag_reg = 0xFFFF;
}

uint32_t fetch(KPU *kpu){
    uint32_t instruction =
        (kpu->memory_arr[kpu->prog_counter] << 24) |
        (kpu->memory_arr[kpu->prog_counter+1] << 16) |
        (kpu->memory_arr[kpu->prog_counter+2] << 8) |
        (kpu->memory_arr[kpu->prog_counter+3]);

    kpu->prog_counter += 4;
    return instruction;
}

void decode(uint32_t instruction, uint8_t *opcode, uint8_t *operand1, uint16_t *operand2){
    *opcode = (instruction >> 24) & 0xFF;
    *operand1 = (instruction >> 16) & 0xFF;
    *operand2 = (instruction) & 0xFFFF;

}


void execute(KPU *kpu, uint8_t opcode, uint8_t operand1, uint16_t operand2){
    if(operand1 >= REG_COUNT){
        printf("ERROR: INVALID REGISTER");
        return;
    }
    switch(opcode){
        case OP_ADD:{
            uint32_t result = kpu->reg_arr[operand1] + operand2;
            if(result > 0xFFFF){
                kpu->flag_reg  |= (1<<2);
            }

            kpu->reg_arr[operand1] = result & 0xFFFF;

            if(kpu->reg_arr[operand1] == 0x0000){
                kpu->flag_reg |= (1<<0);
            }

            break;
        }
        case OP_SUB:{
            uint32_t result = kpu
        }
    }
}



void kpu_run(KPU *kpu){
    
}
