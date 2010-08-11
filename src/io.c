#include <stdio.h>
#include <stdlib.h>

  int is_char(char c)
  {
    if  (
        (c >= 65 && c <= 90)  || 
        (c >= 97 && c <= 122) ||
        (c == 45) ||
        (c == 95) ||
          (c >= 48 && c <= 57)
      ) /* [0-9a-zA-Z-] */
      return 1;
    return 0;
  }
  
  int is_space(char c)
  { /* [ ] */
    if (c == 32)
      return 1;
    return 0;
  }  

  int is_line_break(char c)
  { /* CR */
    if (c == 10)
      return 1;
    return 0;
  }

  /**
  * next: flag do tipo do proximo caracter
  *   considerando que o proximo caracter sera sempre um separador ou uma quebra
  *   de linha (caso contrario, ele faria parte da string), temos os seguintes 
  *   valores para a variavel next:
  *    - 0: caso seja um separador (o que determina o fim deste termo)
  *    - 1: caso seja uma quebra de linha (o que determina o fim desta consulta)
  *    - 2: caso seja o fim do arquivo (o que termina o fluxo de leitura da entrada)
  */
  void get_token(FILE *handle, char string[], int *next)
  {
    int count = 0;
    char buff;
    string[0] = '\0';
    buff = getc(handle);
    while(buff != EOF)
    {
      if(is_char(buff))
      {
        string[count] = buff;
        count++;
      }
      else if(is_line_break(buff))
      {
        *next = 1;
        count = 0;
        break;
      }
      else if(is_space(buff))
      {
        *next = 0;
        count = 0;
        break;
      }
      string[count + 1] = '\0';
      buff = getc(handle);
      if(buff == EOF) 
      {
        *next = 2;
        break;
      }
    }
    if(buff == EOF) *next = 2;
  }

