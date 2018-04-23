#include <stdio.h>
#include <stdlib.h>
#include <string.h>    


char *registerName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2",
                       "$a3",   "$t0", "$t1", "$t2", "$t3", "$t4", "$t5",
                       "$t6",   "$t7", "$s0", "$s1", "$s2", "$s3", "$s4",
                       "$s5",   "$s6", "$s7", "$t8", "$t9", "$k0", "$k1",
                       "$gp",   "$sp", "$fp", "$ra"};
char *registerName2[32] = {"$0", "$1", "$2", "$3", "$4", "$5", "$6",
                       "$7",   "$8", "$9", "$10", "$11", "$12", "$13",
                       "$14",   "$15", "$16", "$17", "$18", "$19", "$20",
                       "$21",   "$22", "$23", "$24", "$25", "$26", "$27",
                       "$28",   "$29", "$30", "$31"};


void intPrintBinary(int I, int bits){
    if ( bits == 4) I = (I & 0x0000000F);
    else if(bits == 5) I = (I & 0x0000001F);
    else if(bits == 16) I = (I & 0x0000FFFF);
    else if(bits == 26) I = (I & 0x03FFFFFF);

    for(int i = bits-1; i >= 0; --i){
        int aux = I >> i;
        if(aux & 1) printf("1");
        else printf("0");

    }
}
int getRegister(char* string){
    char Register[6];
    while(string[0] != '$') string += 1;
    int i = 0;
    while(string[i] != ' ' && string[i] != ',' && string[i] != '\0' && i < 6){
        Register[i] = string[i];
        ++i;
    }
    string += i;
    Register[i] = '\0';

    for(i = 0; i < 32; ++i)
        if(strcmp(Register, registerName[i]) == 0)
            return i;
    for(i = 0; i < 32; ++i)
        if(strcmp(Register, registerName2[i]) == 0)
            return i;
}
int getShamt(char* string){
    while(string[0] < 48 || string[0] >= 58) string += 1;
    char shamt[10];
    while(string[0] >= 48 && string[0] < 58){
        strncat(shamt, string, 1);
        string += 1;
    }
    return atoi(shamt);
}
int j_type(char* string){


    if(strncmp(string, "j", 1) == 0) {
        return 1;
    } else if (strncmp(string, "jr", 2) == 0) {
        return 1;
    } else if (strncmp(string, "jal", 3) == 0) {
        return 1;
    }
    return 0;
}
int r_type(char opcode[], char* string){
    int Rd, Rs, Rt;
    if (strcmp(opcode, "sltu") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("101011\n");
    } else if (strcmp(opcode, "slt") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("101010\n");
    } else if (strcmp(opcode, "xor") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("100110\n");
    } else if (strcmp(opcode, "or") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("100101\n");
    } else if (strcmp(opcode, "and") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("100100\n");
    } else if (strcmp(opcode, "subu") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("100011\n");
    } else if (strcmp(opcode, "sub") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("100010\n");
    } else if (strcmp(opcode, "addu") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);       
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("100001\n");
    } else if (strcmp(opcode, "add") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[6]);    
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("100000\n");
    } else if (strcmp(opcode, "divu") == 0) {
        printf("000000");
        Rs = getRegister(string);
        Rt = getRegister(&string[3]);
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), printf("00000");        
        printf("00000"), printf("011011\n");
    } else if (strcmp(opcode, "div") == 0) {
        printf("000000");
        Rs = getRegister(string);
        Rt = getRegister(&string[3]);
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), printf("00000");        
        printf("00000"), printf("011010\n");
    } else if (strcmp(opcode, "multu") == 0) {
        printf("000000");
        Rs = getRegister(string);
        Rt = getRegister(&string[3]);
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), printf("00000");        
        printf("00000"), printf("011001\n");
    } else if (strcmp(opcode, "mult") == 0) {
        printf("000000");
        Rs = getRegister(string);
        Rt = getRegister(&string[3]);
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), printf("00000");        
        printf("00000"), printf("011000\n");
    } else if (strcmp(opcode, "mflo") == 0) {
        printf("000000");
        Rd = getRegister(string);
        printf("00000"), printf("00000"), intPrintBinary(Rd, 5);        
        printf("00000"), printf("010010\n");
    } else if (strcmp(opcode, "mfhi") == 0) {
        printf("000000");
        Rd = getRegister(string);
        printf("00000"), printf("00000"), intPrintBinary(Rd, 5);        
        printf("00000"), printf("010000\n");
    } else if (strcmp(opcode, "srlv") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);      
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("000110\n");
    } else if (strcmp(opcode, "sllv") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rs = getRegister(&string[3]);
        Rt = getRegister(&string[7]);      
        intPrintBinary(Rs, 5), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        printf("00000"), printf("000100\n");
    } else if (strcmp(opcode, "sra") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rt = getRegister(&string[3]);
        int shamt = getShamt(&string[7]);
        printf("00000"), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        intPrintBinary(shamt, 4), printf("000011\n");
    } else if (strcmp(opcode, "srl") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rt = getRegister(&string[3]);
        int shamt = getShamt(&string[7]);
        printf("00000"), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        intPrintBinary(shamt, 4), printf("000010\n");
    } else if (strcmp(opcode, "syscall") == 0) {
        printf("000000"), printf("00000");
        printf("00000"), printf("00000");
        printf("0000"), printf("001100\n");
    } else if (strcmp(opcode, "sll") == 0) {
        printf("000000");
        Rd = getRegister(string);
        Rt = getRegister(&string[3]);
        int shamt = getShamt(&string[8]);
        printf("00000"), intPrintBinary(Rt, 5), intPrintBinary(Rd, 5);        
        intPrintBinary(shamt, 5), printf("000000\n");
    } else if (strcmp(opcode, "nop") == 0) {
        printf("000000"), printf("00000");
        printf("00000"), printf("00000");
        printf("0000"), printf("000000\n");
        string += 6;
    }








    // implementar j's
}
int i_type(char* string){
    char Rs[4];
    char Rt[4];
    char Rd[4]; 
    char opcode[6];

    int i = 0;
    while(string[0] != ' ') {
        opcode[i] = string[0];
        ++i, ++string;
    }
    opcode[i] = '\0';

}
void codificar(FILE* file){
    char string[100];
    char opcode[6];
    fscanf(file," %s", opcode);
    // fscanf(file," %[^\n]s", string);    
    do {
        fscanf(file," %[^\n]s", string);
        r_type(opcode, string);    
        fscanf(file," %s", opcode);
    } while(!feof(file));
}
int main(int argc, char *argv[]){

    if (argc < 2) {
        fprintf(stderr, "Uso:\n ./codificador arquivo.asm\n");
        return (0);
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Erro em abrir arquivo\n");
        return 0;
    } 
    codificar(file);


    fclose(file);
    return 0;
}