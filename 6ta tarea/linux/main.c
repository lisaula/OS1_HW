#include <stdio.h>
#include "libDLL.h"

int main(void){

  int a =10;
  int b =7;
  int return_value = Suma(a,b);
  printf("a: %d, b: %d\n", a,b);
  printf("return value: %d\n",return_value );
  return 0;
}
