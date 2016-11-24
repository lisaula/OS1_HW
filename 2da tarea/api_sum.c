#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>

int suma(int a, int b){
	int value;
	int status = syscall(545,a, b,&value);
	if(status<0)
		value = status;
	return value;
}