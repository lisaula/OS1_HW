#include  <stdio.h>
#include <stdlib.h>
#include  <sys/types.h>


int max(int *numbers,int size);

int main(int argc, char* argv[])
{
	printf("Child created with: ");
	int i =0;
	int numbers[argc];
	for(i=0;i <argc;i++){
		printf("%s,", argv[i]);
		numbers[i]=atoi(argv[i]);
	}
	printf("\n");
	return max(numbers,argc);
}
int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

int max(int *numbers, int size){
	qsort(numbers, size, sizeof(int), compare);
	return numbers[size -1];
}