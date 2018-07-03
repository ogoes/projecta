#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *registerName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2",
                       "$a3",   "$t0", "$t1", "$t2", "$t3", "$t4", "$t5",
                       "$t6",   "$t7", "$s0", "$s1", "$s2", "$s3", "$s4",
                       "$s5",   "$s6", "$s7", "$t8", "$t9", "$k0", "$k1",
                       "$gp",   "$sp", "$fp", "$ra"};

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