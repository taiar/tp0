#include <stdio.h>
#include <stdlib.h>

#include "io.h"

int main(int argc, char *argv[])
{
  FILE *ent;
  int flag = 0;
  char buff[30];
  char buff2[1024];
  ent = fopen("../src/e1", "r");

  get_token(ent, buff, &flag);
  printf("%s\n", buff);

  while(flag != 2)
  {
   get_token(ent, buff, &flag);
   printf("%s\n", buff);
  }

  fclose(ent);
  printf("==========================================\n");
  printf("==========================================\n");
  printf("==========================================\n");
  printf("==========================================\n");

  ent = fopen("../src/e2", "r");
  while(fgets(buff2, 1024, ent))
  {
    printf("%s", buff2);
  }

  fclose(ent);

  return 0;
}
