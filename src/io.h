#include <stdlib.h>
#include <stdio.h>

#ifndef __io__
  #define __io__

  int is_char(char);
  int is_space(char);
  int is_line_break(char);
  void get_token(FILE*, char*, int*);

#endif
