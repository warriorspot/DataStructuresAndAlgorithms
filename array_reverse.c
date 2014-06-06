#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void print_array(char **, int);
void reverse(char**, int);

void print_array(char **array, int size)
{
	for(int i = 0; i < size; i++) 
	{
		printf("%s ", array[i]);
	}
	printf("\n");
}

void reverse(char **array, int size)
{
	char *temp, **head, **tail;

	head = array;
	tail = array + (size - 1);
	while(head < tail) {
		temp = *head;
		*head = *tail;
		*tail = temp;
		head++;
		tail--;
	}
}

int main(int argc, char **argv) 
{
	int size = argc - 1;
	if(size == 0) return 0;
	
	char **array = malloc(sizeof(char *) * size);
	assert(array);
		
	/* copy the strings into our array */
	for(int i = 0; i < size; i++) {
		array[i] = strdup(argv[i + 1]);
	}	

	print_array(array, size);
	reverse(array, size);
	print_array(array, size);

	/* clean up */
	for(int i = 0; i < size; i++) {
		free(array[i]);	
	}	
	free(array);

	return 0;
}

