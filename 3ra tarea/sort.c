#include  <stdio.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <math.h>

char ** sliceArray(char **numbers, int size, char** nuevo, int amount_processes);
int max(int *numbers,int size);
int main(int arg, char* args[])
{
     int arraySize = 20;
     char * numbers[]= {"4","3","1","12","20","34","44","23","21","12","2","6","9","11","22","33","32","13","14","40",0};
     char **temp = numbers;
     /*while(temp[0] != 0){
          printf("%s, ", temp[0]);
          temp++;
     }*/
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
          sliceArray(numbers, sliceSize, t, i);
          t[sliceSize]=0;
          int j;
          for(j=0; j< sliceSize+1;j++){
              // printf("%s, ", t[j]);
          }
          //printf("\n");
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
     /*
     pid_t  pid;
     pid = fork();
     if(pid == 0){
          printf("yo soy hijo\n");
          char * argv[] ={"1","2","33","4", 0};
          printf("numero2 %c\n", *(argv)[0]); 
          execvp ("./max_finder", argv);
     }else{
          int status; 
          wait(&status);
          printf("hola pid: %d termino %u\n",pid,status/255);
          printf("raro %d\n",WEXITSTATUS(status));
     }*/
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