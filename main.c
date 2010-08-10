#include <stdio.h>
#include <stdlib.h>

#include "io.h"

int main(int argc, void *argv[])
{
  FILE *ent;
  int flag = 0;
  char buff[30];
  ent = fopen("e1", "r");

  get_token(ent, buff, &flag);
  printf("%s\n", buff);

  while(flag != 2)
  {
   get_token(ent, buff, &flag);
   printf("%s\n", buff);
  }

  fclose(ent);

  return 0;
}
