
#ifndef _bmc_linked_list
#define _bmc_linked_list

typedef struct bmc_linked_list_node {
	struct bmc_linked_list_node *next;
	void *data;
} bmc_linked_list_node;

typedef struct {
	int count;
	bmc_linked_list_node *head;
	bmc_linked_list_node *tail;
} bmc_linked_list;

bmc_linked_list * bmc_linked_list_new();
bmc_linked_list_node * bmc_linked_list_add(bmc_linked_list *list, void *data);
bmc_linked_list_node * bmc_linked_list_insert(bmc_linked_list *list, void *data, int position);
void * bmc_linked_list_find(bmc_linked_list *list, void *data);
int bmc_linked_list_size(bmc_linked_list *list);
void * bmc_linked_list_remove(bmc_linked_list *list, void *data);
void bmc_linked_list_free(bmc_linked_list *list);

#endif

