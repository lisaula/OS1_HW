#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argsc, int * argsv[])
{         int num1 = 20;
          int num2 = 10;
          int *result = malloc(sizeof(int));
          int call =syscall(545, num1, num2, result);
          printf("result: %d, call: %d\n", *(result), call);

          return 0;
}
