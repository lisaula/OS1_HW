#include  <stdio.h>
#include <stdlib.h>
#include  <sys/types.h>


int parse(char *line, char **argU)
{
	int cont = 0, cont2 = 0;
	int cant = 0;
    while (*line != '\0') 
    {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
          {
          		//printf("entro0\n");
               	*line++ = '\0';     /* replace white spaces with 0    */
          		cant++;
          }
          
          *argU = line;
          printf("aqui: %s argU: %s\n", line, *argU);
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

int main(int argc, char* argv[])
{
	int size;
	//printf("Size del array: ");
	//scanf("%d", &size);

	char line[1024];
	printf("Nums: ");
	fgets(line, 1024,stdin);
	printf("%s\n",line );
	char** args = malloc(6 * sizeof(char*)); //char**
	int cant = parse(line, args);
	printf("La cantidad: %d\n",cant);
	
	for(size = 0; size < cant - 1; size++)
	{
		printf("n %d: %s\n", size, args[size]);
	}
	
	int numbers[5];
	for(size = 0; size < cant - 1; size++)
	{
		numbers[size] = atoi(args[size]);
	}
	
	for(size = 0; size < cant - 1; size++)
	{
		printf("%d ", numbers[size]);
	}
	printf("\n");
	free(args);
} 