#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
=======
#include <ctype.h>

>>>>>>> b521b64ea15f643fe10fe1e5f4fc0fbe51969717

char *registerName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2",
                       "$a3",   "$t0", "$t1", "$t2", "$t3", "$t4", "$t5",
                       "$t6",   "$t7", "$s0", "$s1", "$s2", "$s3", "$s4",
                       "$s5",   "$s6", "$s7", "$t8", "$t9", "$k0", "$k1",
                       "$gp",   "$sp", "$fp", "$ra"};
<<<<<<< HEAD

int j_type(char string[]){
    
}
int r_type(char string[]){

}
int i_type(char string[]){

}


void codificar(FILE* file){
    FILE* aux = file;
    char string[100];
    fscanf(file," %[^\n]s", string);
    while(!feof(aux)){
        printf("%s\n", string);
        fscanf(file," %[^\n]s", string);
    }
    int a = 12;
    a = (a & 0x0000FFFF);
    printf("%i\n", a);
    
    for(int i = 15; i >= 0; --i){
        int aux = a >> i;
        if(aux & 1) printf("1");
        else printf("0");

    }
    printf("\n");
 
  
    // printf("%0.8b", 12);
}


=======
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
    if(bits == 16 || bits == 26) printf ("\n");
}
int getRegister(char* string){
    char Register[6];
    while(string[0] != '$') string += 1;
    int i = 0;
    while(string[i] != ' ' && string[i] != ',' && string[i] != '\0' && string[i] != ')' && i < 6){
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
int getAddress(char* string){
    while(string[0] != '0') string += 1;
    string += 2;
    int OP, ADR = 0;
    char C[2];
    C[1] = '\0';
    while(string[0] != ' ' && string[0] != '\n' && string[0] != '\0'){
        C[0] = toupper(string[0]);
        if(strcmp(C, "A") == 0)
            OP = 10;
        else if(strcmp(C, "B") == 0)
            OP = 11;
        else if(strcmp(C, "C") == 0)
            OP = 12;
        else if(strcmp(C, "D") == 0)
            OP = 13;
        else if(strcmp(C, "E") == 0)
            OP = 14;
        else if(strcmp(C, "F") == 0)
            OP = 15;
        else 
            OP = atoi(C);
        ADR <<= 4;
        ADR += OP;
        string += 1;
    }
    return ADR;
}
int j_type(char opcode[], char* string){
    int ADR = getAddress(string);
    
    if(strcmp(opcode, "j") == 0) {
        printf("000010");
        intPrintBinary(ADR, 26);        
    } else if (strcmp(opcode, "jal") == 0) {
        printf("000011");
        intPrintBinary(ADR, 26);
    }
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
        printf("00000"), printf("001100\n");
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
        printf("00000"), printf("000000\n");
        string += 6;
    } else if(strcmp(opcode, "jr") == 0){
        printf("000000");
        Rs = getRegister(string);
        intPrintBinary(Rs, 5);
        printf("000000000000000001000\n");
    } 
}
int i_type(char opcode[], char* string){
    int Rd, Rt, Rs;
    int offset, address;
    if(strcmp(opcode, "bltz") == 0){

        printf("000001");
        Rs = getRegister(string);
        offset = getAddress(&string[4]);
        intPrintBinary(Rs, 5);
        printf("00000");
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "bgez") == 0){

        printf("000001");
        Rs = getRegister(string);
        offset = getAddress(&string[4]);
        intPrintBinary(Rs, 5);
        printf("00001");
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "bltzal") == 0){

        printf("000001");
        Rs = getRegister(string);
        offset = getAddress(&string[4]);
        intPrintBinary(Rs, 5);
        printf("10000");
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "bgezal") == 0){

        printf("000001");
        Rs = getRegister(string);
        offset = getAddress(&string[4]);
        intPrintBinary(Rs, 5);
        printf("10001");
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "beq") == 0){
        
        printf("000100");
        Rs = getRegister(string);
        Rt = getRegister(&string[3]);        
        offset = getAddress(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "bne") == 0){

        printf("000101");
        Rs = getRegister(string);
        Rt = getRegister(&string[3]);        
        offset = getAddress(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "blez") == 0){

        printf("000110");
        Rs = getRegister(string);       
        offset = getAddress(&string[4]);
        intPrintBinary(Rs, 5);
        printf("00000");     
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "bgtz") == 0){

        printf("000111");
        Rs = getRegister(string);       
        offset = getAddress(&string[4]);
        intPrintBinary(Rs, 5);
        printf("00000");     
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "addi") == 0){
        
        printf("001000");
        Rt = getRegister(string);
        Rs = getRegister(&string[3]);        
        offset = getShamt(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);

    } else if(strcmp(opcode, "addiu") == 0){
        printf("001001");
        Rt = getRegister(string);
        Rs = getRegister(&string[3]);        
        offset = getShamt(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "slti") == 0){
        printf("001010");
        Rt = getRegister(string);
        Rs = getRegister(&string[3]);        
        offset = getShamt(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "sltiu") == 0){
        printf("001011");
        Rt = getRegister(string);
        Rs = getRegister(&string[3]);        
        offset = getShamt(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "andi") == 0){
        printf("001100");
        Rt = getRegister(string);
        Rs = getRegister(&string[3]);        
        offset = getShamt(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "ori") == 0){
        printf("001101");
        Rt = getRegister(string);
        Rs = getRegister(&string[3]);        
        offset = getShamt(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "xori") == 0){
        printf("001110");
        Rt = getRegister(string);
        Rs = getRegister(&string[3]);        
        offset = getShamt(&string[7]);
        intPrintBinary(Rs, 5);
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "lui") == 0){
        printf("001111");
        Rt = getRegister(string);      
        offset = getShamt(&string[4]);
        printf("00000");
        intPrintBinary(Rt, 5);        
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "lb") == 0){
        printf("100000");
        Rt = getRegister(string);   
        offset = getShamt(&string[4]);
        string += 4;
        while(string[0] != '(') string += 1;
        Rs = getRegister(string);
        intPrintBinary(Rs, 5);             
        intPrintBinary(Rt, 5);     
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "lw") == 0){
        printf("100011");
        Rt = getRegister(string);   
        offset = getShamt(&string[4]);
        string += 4;
        while(string[0] != '(') string += 1;
        Rs = getRegister(string);
        intPrintBinary(Rs, 5);             
        intPrintBinary(Rt, 5);     
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "sb") == 0){
        printf("101000");
        Rt = getRegister(string);   
        offset = getShamt(&string[4]);
        string += 4;
        while(string[0] != '(') string += 1;
        Rs = getRegister(string);
        intPrintBinary(Rs, 5);             
        intPrintBinary(Rt, 5);     
        intPrintBinary(offset, 16);
    } else if(strcmp(opcode, "sw") == 0){
        printf("101011");
        Rt = getRegister(string);   
        offset = getShamt(&string[4]);
        string += 4;
        while(string[0] != '(') string += 1;
        Rs = getRegister(string);
        intPrintBinary(Rs, 5);             
        intPrintBinary(Rt, 5);     
        intPrintBinary(offset, 16);
    }

}
void codificar(FILE* file){
    int i = 0;
    char string[1000];
    char opcode[6];
    fscanf(file," %s", opcode);
    do {
        while(opcode[0] == '#'){
            fscanf(file," %[^\n]s", string);
            fscanf(file," %s", opcode);
        }
        if(strcmp(opcode, "nop") != 0)
            fscanf(file," %[^\n]s", string);
        while(i < strlen(string)){
            if(string[i] == '#'){
                string[i] = '\0';
            }
            ++i;
        }
        r_type(opcode, string);
        i_type(opcode, string);
        j_type(opcode, string);
        fscanf(file," %s", opcode);
    } while(!feof(file));
}
>>>>>>> b521b64ea15f643fe10fe1e5f4fc0fbe51969717
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