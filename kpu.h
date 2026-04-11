#ifndef KPU_H
#define KPU_H

#include <stdint.h>
#define MEMORY_SIZE 65536
#define REG_COUNT 8

typedef struct{
    uint16_t reg_arr[REG_COUNT];
    uint16_t prog_counter;
    uint16_t stack;
    uint8_t  memory_arr[MEMORY_SIZE];
    uint32_t instruction_reg;
    uint16_t flag_reg;
} KPU;

typedef enum{
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOVE,
    OP_LOAD, 
    OP_STORE,
    OP_JMP,
    OP_CJMP,
    OP_FUNCALL,
    OP_RET,
    OP_CMP, 
    OP_IN,
    OP_OUT,
    OP_HALT, 
} opcode;


/* Initialises a kpu struct and sets all the values to 0 initially. Takes a KPU pointer and returns nothing.*/
void kpu_unit(KPU *kpu); 

/**/
void kpu_run(KPU *kpu);

/* returns a 32 bit integer which is the instruction address. Takes a KPU pointer and returns a 32 bit integer. */
uint32_t fetch(KPU *kpu);

/* Takes a 32 bit instruction and 2 uint8_t pointer and one uint16_t pointer and returns nothing */
void decode(uint32_t instruction, uint8_t *opcode, uint8_t *operand1, uint16_t *operand2);


/* Takes a KPU pointer, a uint8_t opcode, uint8_t operand1 and a a uint16_t operand2 and returns nothing. it is a void function. */
void execute(KPU *kpu, uint8_t opcode, uint8_t operand1, uint16_t operand2);



#endif
