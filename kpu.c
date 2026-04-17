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

        /* TODO: implement proper signed negative detection with two's complement '*/
        case OP_SUB:{
            uint32_t result = kpu->reg_arr[operand1] - operand2;
            if(result > 0xFFFF){
                kpu->flag_reg |= (1<<2);
            }

            kpu->reg_arr[operand1] = result & 0xFFFF;

            if(kpu->reg_arr[operand1] == 0x0000){
                kpu->flag_reg |= (1<<0);
            }

            break;
            
        }

        case OP_MUL:{
            uint32_t result = kpu->reg_arr[operand1] * operand2;
            if(result > 0xFFFF){
                kpu->flag_reg |= (1<<2);
            }

            kpu->reg_arr[operand1] = result & 0xFFFF;

            if(kpu->reg_arr[operand1] == 0x0000){
                kpu->flag_reg |= (1<<0);
            }
            
            break;
        }

        case OP_DIV:{
            if(operand2 == 0x0000){
                printf("ERROR: DIVISION BY ZERO.");
                return;
            }

            kpu->reg_arr[operand1] /= operand2;
            
            if(kpu->reg_arr[operand1] == 0x0000){
                kpu->flag_reg |= (1<<0);
            }

            break;
        }

        case OP_MOVE:{
            uint8_t reg_src = (operand2 >> 8) & 0xFF;
            if(reg_src >= REG_COUNT){
                printf("ERROR: Invalid register.\n");
                return;
            }
            uint8_t reg_dst = operand1;

            kpu->reg_arr[reg_dst] = kpu->reg_arr[reg_src];
            break;
        }

        case OP_LOADI:{
            kpu->reg_arr[operand1] = operand2;
            break;
        }

        case OP_LOAD:{
           if(operand2 >= MEMORY_SIZE - 1){
                printf("ERROR: Memory access out of bounds.\n");
                return;
           }
            uint16_t value = kpu->memory_arr[operand2] | (kpu->memory_arr[operand2+1]);
            kpu->reg_arr[operand1] =  value;
            break;
        }

        case OP_STORE:{
            if(operand2 >= MEMORY_SIZE - 1){
                printf("ERROR: Memory access out of bounds.\n");
                return;
            }
            uint8_t high_byte = (kpu->reg_arr[operand1] >> 8) & 0xFF;
            uint8_t low_byte = (kpu->reg_arr[operand1] >> 0) & 0x00FF;
            kpu->memory_arr[operand2] = low_byte;
            kpu->memory_arr[operand2+1] = high_byte;
            break;
        }
    }
}



void kpu_run(KPU *kpu){
    
}
