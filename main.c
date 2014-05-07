
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
		bmc_linked_list_add(list, strdup(argv[i]));
	}

	print_list(list);

	for(int i = 1; i < argc; i++) {
		bmc_linked_list_insert(list, strdup(argv[i]),  4);
	    print_list(list);
	}

	print_list(list);
	
	void *data = bmc_linked_list_find(list, argv[0]);
	if(data == NULL) {
		printf("Couldnt find %s\n", argv[0]);
	}
	data = bmc_linked_list_find(list, argv[1]);
	if(data != NULL) {
		printf("Found %s: %s\n", argv[1], data);
	}

	bmc_linked_list_free(list);

	return 0;

}
