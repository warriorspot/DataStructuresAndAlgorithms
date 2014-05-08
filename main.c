
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "bmc_linked_list.h"

void print_list(bmc_linked_list *list);

void print_list(bmc_linked_list *list) {
	bmc_linked_list_node *node = list->head;
	while(node ) {
		printf("%s ", node->data); 
		node = node->next;
	}
	printf("\n");
}

int main(int argc, char **argv) {

	bmc_linked_list *list = bmc_linked_list_new(); 
	assert(list);

	for(int i = 1; i < argc; i++) {
		bmc_linked_list_add(list, argv[i], strlen(argv[i]) + 1);
	}

	print_list(list);

	for(int i = 1; i < argc; i++) {
		bmc_linked_list_insert(list, argv[i], strlen(argv[i]) + 1,  4);
	    	print_list(list);
	}

	print_list(list);
	
	bmc_linked_list_node *node = bmc_linked_list_at(list, 1);
	if(node) {
		printf("Found node!\n");
		bmc_linked_list_remove(list, 1);	
		print_list(list);
	}
	bmc_linked_list_free(list);

	return 0;

}
