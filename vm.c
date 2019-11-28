#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_R 2
#define MAX_LEN 1000

typedef uint8_t reg;

void jump(char p[], int *pc){
  int tmp = 0;
  char c;
  printf("Jump to label:%c from %d\n", p[*pc + 1], *pc + 1);
  c = p[tmp];
  while(c != p[*pc + 1] && p[tmp + 1] != ':'){
    c = p[tmp];
    tmp++;
  }
  printf("Found label: %c @ %d\n", c, tmp);
  *pc = tmp;
}

int main(int argc, char **argv)
{

  int program_len;
  char program[MAX_LEN];
  int curr = 0;
  int pc;
  int label[10];
  reg r[NUM_R];
  r[0] = 0;
  r[1] = 0;

  if(argc > 2){
    printf("only one file plz\n");
  } else if (argc < 2) {
    printf("I need a filename\n");
  } else {
    FILE *input;
    if(!(input= fopen(argv[1], "r"))){
      fprintf(stderr,"Can't open the file %s.\n", argv[1]),exit(1);
    }
    program_len = fread(program, 1, MAX_LEN, input);
    fclose(input);
    //Start interpreter
    for(pc=0; pc<program_len; pc++){
      switch(program[pc]){
        case '%': curr = curr ^ 1; break;
        case '-': r[curr]--; break;
        case '+': r[curr]++; break;
        case '=': if(r[curr] == r[curr^1] && program[pc+1] != ':') jump(program, &pc); break;
        case '|': printf("r1: %d, r2: %d\n", r[0], r[1]); break;
      }

    }
    return 0;
  }
}
