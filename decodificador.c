#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define _GNU_SOURCE // necessário porque getline() é extensão GNU

// Campos do formato de instrução.
// opcode  := ir(31 downto 26)
// rs      := ir(25 downto 21);
// rt      := ir(20 downto 16);
// rd      := ir(15 downto 11);
// shamt   := ir(10 downto  6);
// imm     := ir(15 downto  0);
// address := ir(25 downto  0);

/* Definição das Máscaras. */
int mascaraOpCode     = 0xFC000000;
int mascaraRs         = 0x03E00000;
int mascaraRt         = 0x001F0000;
int mascaraRd         = 0x0000F800;
int mascaraShamt      = 0x000007C0;
int mascaraFunct      = 0x0000003F;
int mascaraImmediate  = 0x0000FFFF;
int mascaraAddress    = 0x03FFFFFF;

char *registerName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2",
                  "$a3",   "$t0", "$t1", "$t2", "$t3", "$t4", "$t5",
                  "$t6",   "$t7", "$s0", "$s1", "$s2", "$s3", "$s4",
                  "$s5",   "$s6", "$s7", "$t8", "$t9", "$k0", "$k1",
                  "$gp",   "$sp", "$fp", "$ra"};

/* Função para imprimir um número 32 bits com binário.
Adaptado de um código encontrado na internet.    */
void bin_prnt_byte(int x) {

  int i, n;

  char buffer [50] = {0};

  for (i = 0; i < 32; i++) {
    if ((x & 0x80000000) != 0) {
      // printf("1");
      n = sprintf (buffer, "%s%s", buffer, "1");
    } else {
      // printf("0");
      n = sprintf (buffer, "%s%s", buffer, "0");
    }
    if ((i % 4 == 3) && i < 31) {
      // printf(" "); /* insert a space between nybbles */
      n = sprintf (buffer, "%s%s", buffer, " ");
    }
      x = x << 1;
  }
}
/* Função que recupera o campo OpCode. */
unsigned int getOpCode(unsigned int ir) {
  unsigned int opcode = ((ir & mascaraOpCode) >> 26);
  return opcode;
}

/* Função que recupera o campo registrador Rs. */
unsigned int getRs(unsigned int ir) {

  unsigned int rs = (ir & mascaraRs) >> 21;
  return rs;
}

/* Função que recupera o campo registrador Rt. */
unsigned int getRt(unsigned int ir) {

  unsigned int rt = (ir & mascaraRt) >> 16;
  return rt;
}

/* Função que recupera o campo registrador Rd. */
unsigned int getRd(unsigned int ir) {

  unsigned int rd = (ir & mascaraRd) >> 11;
  return rd;
}

/* Função que recupera o campo Shamt (deslocamento). */
int getShamt(unsigned int ir) {

  unsigned int shamt = (ir & mascaraShamt) >> 6;
  return shamt;
}

/* Função que recupera o campo Funct. */
unsigned int getFunct(unsigned int ir) {

  unsigned int funct = (ir & mascaraFunct);
  return funct;
}

/* Função que recupera o campo imm. */
int getImmediate(unsigned int ir) {

  unsigned int imm = (ir & mascaraImmediate);
  return imm;
}


/* Função que recupera o campo Address. */
unsigned int getAddress(unsigned int ir) {

  unsigned int address = (ir & mascaraAddress);
  return address * 4; 
}

/* Converte um char * representando um binário, para inteiro. */
int intFromBinary(char *s) {

  int inteiro = (int) strtol(s, 0, 2);
  bin_prnt_byte(inteiro);

  return inteiro;
}

/* Decodificação das instruções. */
void decodificar(unsigned int ir) {

  switch ( getOpCode(ir) ) {
    case 0:  // 000000, Aritmética.
      if( getFunct(ir) == 0 ) {
        if(getRd(ir) == 0 && getRs(ir) == 0 && getRt(ir) == 0)
          printf("nop\n");
        else { // 000000 -> sll, R-Type
          printf("sll ");
          printf("%s, ", registerName[getRd(ir)]);
          printf("%s, ", registerName[getRt(ir)]);
          printf("%i\n", getShamt(ir));
        }
      } else if(getFunct(ir) == 12) // 001100 -> syscall, R-Type.
          printf("syscall\n");
      else if(getFunct(ir) == 2) {  // 000010 -> srl, R-Type.

        printf("srl ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRt(ir)]);
        printf("%i\n", getShamt(ir));
        

      } else if(getFunct(ir) == 3) {  // 000011 -> sra, R-Type.

        printf("sra ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRt(ir)]);
        printf("%i\n", getShamt(ir));
        

      } else if(getFunct(ir) == 4) {  // 000100 -> sllv, R-Type.

        printf("sllv ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRt(ir)]);
        printf("%s\n", registerName[getRs(ir)]);        

      } else if(getFunct(ir) == 6) {  // 000110 -> srlv, R-Type.

        printf("srlv ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 8) {  // 001000 -> jr, I-Type.

        printf("jr ");
        printf("%s\n", registerName[getRs(ir)]);

      } else if(getFunct(ir) == 16) { // 010000 -> mfhi, R-Type.

        printf("mfhi ");
        printf("%s\n", registerName[getRd(ir)]);

      } else if(getFunct(ir) == 18) { // 010010 -> mflo, R-Type.

        printf("mflo ");
        printf("%s\n", registerName[getRd(ir)]);

      } else if(getFunct(ir) == 24) { // 011000 -> mult, R-Type.

        printf("mult ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 25) { // 011001 -> multu, R-Type.

        printf("multu ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 26) { // 011010 -> div, R-Type.

        printf("div ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 27) { // 011011 -> divu, R-Type.

        printf("divu ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 32) { // 100000 -> add, R-Type.

        printf("add ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 33) { // 100001 -> addu, R-Type.

        printf("addu ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 34) { // 100010 -> sub, R-Type.

        printf("sub ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 35) { // 100011 -> subu, R-Type.

        printf("subu ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 36) { // 100100 -> and, R-Type.

        printf("and ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 37) { // 100101 -> or, R-Type.

        printf("or ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 38) { // 100110 -> xor, R-Type.

        printf("xor ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 42) { // 101010 -> slt, R-Type.

        printf("slt ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else if(getFunct(ir) == 43) { // 101011 -> sltu, R-Type.

        printf("sltu ");
        printf("%s, ", registerName[getRd(ir)]);
        printf("%s, ", registerName[getRs(ir)]);
        printf("%s\n", registerName[getRt(ir)]);

      } else {
        fprintf(stdout, "Instrução não implementada. funct: %d.\n", getFunct(ir));
      }
      break;
    case 1:
      if(getRt(ir) == 0){ // 000001 -> I-Type, bltz
        printf("bltz ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("0x%0.4X\n", getImmediate(ir));
      } else if(getRt(ir) == 1){ // 000001 -> I-Type, bgez
        printf("bgez ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("0x%0.4X\n", getImmediate(ir));
      } else if(getRt(ir) == 16){ // 000001 -> I-Type, bltzal
        printf("bltzal ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("0x%0.4X\n", getImmediate(ir));
      } else if(getRt(ir) == 17){ // 000001 -> I-Type, bgezal
        printf("bgezal ");
        printf("%s, ", registerName[getRs(ir)]);
        printf("0x%0.4X\n", getImmediate(ir));
      } 
      break;            
    case 2: // 000010 -> J-Type, j
      printf("j ");
      printf("0x%0.8X\n", getAddress(ir));
      break;
    case 3: // 000011 -> J-Type, jal
      printf("jal ");
      printf("0x%0.8X\n", getAddress(ir));
      break;
    case 4: // 00100 -> I-Type. beq
      printf("bne ");
      printf("%s, ", registerName[getRs(ir)]);
      printf("%s, ", registerName[getRt(ir)]);
      printf("0x%0.4X\n", getImmediate(ir));
      break;
    case 5: // 00101 -> I-Type. bne
      printf("beq ");
      printf("%s, ", registerName[getRs(ir)]);
      printf("%s, ", registerName[getRt(ir)]);
      printf("0x%0.4X\n", getImmediate(ir));
      break;
    case 6: // 000110 -> I-Type, blez
      printf("blez ");
      printf("%s, ", registerName[getRs(ir)]);
      printf("0x%0.4X\n", getImmediate(ir));
      break;
    case 7: // 000111 -> I-Type, bgtz
      printf("bgtz ");
      printf("%s, ", registerName[getRs(ir)]);
      printf("0x%0.4X\n", getImmediate(ir));
      break;
    case 8: // 001000 -> I-Type. addi 
      printf("addi ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%s, ", registerName[getRs(ir)]);
      printf("%d\n", getImmediate(ir));
      break;
    case 9: // 001001 -> I-Type. addiu
      printf("addiu ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%s, ", registerName[getRs(ir)]);
      printf("%d\n", getImmediate(ir));
      break;
    case 10: // 001010 -> I-Type. slti
      printf("addiu ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%s, ", registerName[getRs(ir)]);
      printf("%d\n", getImmediate(ir));
      break;
    case 11: // 001011 -> I-Type, sltiu
      printf("sltiu ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%s, ", registerName[getRs(ir)]);
      printf("%d\n", getImmediate(ir));
      break;
    case 12: // 001100 -> I-Type. andi
      printf("andi ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%s, ", registerName[getRs(ir)]);
      printf("%d\n", getImmediate(ir));
      break;
    case 13: // 001101 -> I-Type. ori
      printf("ori ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%s, ", registerName[getRs(ir)]);
      printf("%d\n", getImmediate(ir));
      break;
    case 14: // 001110 -> I-Type. xori
      printf("xori ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%s, ", registerName[getRs(ir)]);
      printf("%d\n", getImmediate(ir));
      break;  
    case 15: // 100011 -> I-Type, lui
      printf("lui ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%d\n", getImmediate(ir));
      break;
    case 32: // 100000 -> I-Type, lb
      printf("lb ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%d", getImmediate(ir));
      printf("(%s)\n", registerName[getRs(ir)]);
      break;
    case 35: // 100011 -> I-Type, lw
      printf("lw ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%d", getImmediate(ir));
      printf("(%s)\n", registerName[getRs(ir)]);
      break;
    case 40: // 100011 -> I-Type, sb
      printf("sb ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%d", getImmediate(ir));
      printf("(%s)\n", registerName[getRs(ir)]);
      break;
    case 43: // 100011 -> I-Type, sw
      printf("sw ");
      printf("%s, ", registerName[getRt(ir)]);
      printf("%d", getImmediate(ir));
      printf("(%s)\n", registerName[getRs(ir)]);
      break;
    default: // outros casos.
      fprintf(stdout, "Instrução não implementada. OpCode: %d.\n", getOpCode(ir));
  }
}

int main(int argc, char *argv[]) {

  int i;
  unsigned int ir;
  if (argc < 2) {
    fprintf(stderr, "Uso:\n ./decodificador arquivo.b\n");
    return (0);
  }

  FILE *arquivo = fopen(argv[1], "r");
  size_t len = 32; // tamanho da linha.
  char *linha = malloc(len);

  if (!arquivo) {
    perror(argv[1]);
    exit(1);
  }

  while (getline(&linha, &len, arquivo) > 0) {
    ir = intFromBinary(linha);
    decodificar(ir);
  }

  if (linha) {
    free(linha);
  }

  fclose(arquivo);

  return 0;
}
