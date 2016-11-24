#include  <stdio.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

char ** sliceArray(char **numbers, int size, char** nuevo, int amount_processes);
int max(int *numbers,int size);

int parse(char *line, char **argU)
{
     int cant= 0;
    while (*line != '\0') 
    {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
          {
                    //printf("entro0\n");
                    *line++ = '\0';     /* replace white spaces with 0    */
                    cant++;
          }
          
          *argU = line;
          *argU++;          /* save the argvent position     */
          
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
          {
               line++;//printf("entro1\n");/* skip the argvent until ...    */
          }
    }
    *argU = 0;                 /* mark the end of argvent list  */
     cant++;
     return cant;
}
void initializeZeros(char ** numbers, int size){
     int i =0;
     for(;i<size;i++){
          numbers[i]=0;
     } 
}

int main(int arg, char* args[])
{
     int arraySize = 20;
     char * temp []= {"4","3","1","12","20","34","44","23","21","12","2","6","9","11","22","33","32","13","14","40",0};
     char ** numbers =0;
     printf("Would you want to introduce the numbers by yourself?\nif yes, give the size of the array, otherwise type zero\'0\': ");
     char size_ptr[10];
     fgets(size_ptr, 10,stdin);
     int size_temp = atoi(size_ptr);
     if(size_temp>0){
          arraySize =size_temp;
          bool end = false;
          do{
               printf("Intruduce the numbers, including spaces among them: \n");
               char line[1024];
               fgets(line, 1024,stdin); 
               numbers = malloc((arraySize+1)*sizeof(char*));
               int cant= parse(line, numbers);
               if(cant == (arraySize+1)){
                    //numbers = input_numbers;
                    end = true;
               }
               else{
                    printf("Error in input, expected %d numbers, received %d\n",arraySize, cant-1);
               }
          }while(!end);
     }else{
          numbers = temp;
     }
     printf("\n");
     int sliceSize = atoi(args[1]);
     int amount_processes= arraySize / sliceSize;
     if(amount_processes*sliceSize < arraySize){
          amount_processes++;
     }
     int i;
     int returnValues[amount_processes];
     int contador=0;
     for(i =0; i<amount_processes; i++){
          char *t[sliceSize+1]; 
          initializeZeros(t,sliceSize+1);
          sliceArray(numbers, sliceSize, t, i);
          t[sliceSize]=0;
          pid_t  pid;
          pid = fork();
          if(pid == 0){
               execvp ("./max_finder", t);
          }
     }

     for(i = 0;i<amount_processes; i++){
          int status; 
          pid_t  cpid;
          cpid=wait(&status);
          printf("Child with pid %d terminated with: %d\n",cpid,WEXITSTATUS(status));
          returnValues[contador] = WEXITSTATUS(status);
          contador++;
     }

     printf("Max number is: %d\n", max(returnValues,amount_processes));
     return 0;
}

char ** sliceArray(char **numbers, int size, char** nuevo, int amount_processes){
     int i = 0;
     numbers=((void*)(numbers)+(amount_processes*size*sizeof(char*)));
     while(i < size){
          if(numbers[0]!=0){
               nuevo[i]= numbers[0];
          }else{
               nuevo[i]=0;
               break;
          }
          i++;
          numbers++; 
     }
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