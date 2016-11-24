#include <stdio.h>
#include "api_sum.c"
#include <stdbool.h>


bool getInput(int * ptr);
void freeBuffer();
int main(void){

	int a;
	int b;
	bool finish=false, input=false;
	do{
		printf("Input a: ");
		getInput(&a);
		printf("Input b: ");
		getInput(&b);
		int result = suma(a, b);
		printf("Sum: %d\n", result);
		printf("Again? Yes|No\n");
		char str[10];
		scanf("%s", &str);
		if(str[0] =='Y' || str[0] =='y')
			finish = true;
	}while(finish);
}

bool getInput(int * ptr){
	//freeBuffer();
	int temp;
	if (scanf("%d", &temp) != 1) {
        printf("Error: Not an integer.\n");
        return false;
    }else{
    	*ptr = temp;
    	return true;
    }
}

void freeBuffer(){
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF){
		printf("algo\n");
	}
}