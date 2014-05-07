
#include "stdlib.h"
#include "bmc_linked_list.h"

bmc_linked_list_node * add_at_head(bmc_linked_list *list, void *data); 

bmc_linked_list * bmc_linked_list_new() {
	bmc_linked_list *list = malloc(sizeof(bmc_linked_list));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

bmc_linked_list_node * bmc_linked_list_add(bmc_linked_list *list, void *data) {
	bmc_linked_list_node *node = malloc(sizeof(bmc_linked_list_node));
	node->data = data;
	node->next = NULL;
	
	if(list->head == NULL) {
		list->head = node;	
		list->tail = node;
	}
	else {
		list->tail->next = node;
		list->tail = node;
	}

	list->count++;

	return node;
}

bmc_linked_list_node * bmc_linked_list_insert(bmc_linked_list *list, void *data, int position) {

	/* Add at tail */
	if(position >= list->count) {
		return bmc_linked_list_add(list, data);
	}

	/* Add at head */
	if(position <= 0) {
		return add_at_head(list, data);
	}

	bmc_linked_list_node *node = list->head;
	for(int i = 0; i < position - 1; i++) {
		node = node->next;	
	}	

	bmc_linked_list_node *newNode = malloc(sizeof(bmc_linked_list_node));
	newNode->data = data;
	newNode->next = node->next;
	node->next = newNode;

	list->count++;

	return node;
}

void * bmc_linked_list_find(bmc_linked_list *list, void *data) {

	bmc_linked_list_node *node = list->head;
	while(node != NULL) {
		if(node->data == data) {
			return node->data;
		}
		node = node->next;
	}

	return NULL;
}

int bmc_linked_list_size(bmc_linked_list *list) {
	return 0;
}

void * bmc_linked_list_remove(bmc_linked_list *list, void *data) {
	return 0;
}

void bmc_linked_list_free(bmc_linked_list *list) {
	if(list->head == NULL) {
		free(list);
		return;
	}

	bmc_linked_list_node *node = list->head;
	while(node) {
		bmc_linked_list_node *next = node->next;
		free(node->data);
		free(node);
		node = next;
	}

	free(list);

	return;
}

/* Private functions */

bmc_linked_list_node * add_at_head(bmc_linked_list *list, void *data) {
	bmc_linked_list_node *node = malloc(sizeof(bmc_linked_list_node));
	node->data = data;
	node->next = NULL;

	if(list->head == NULL) {
		list->head = node;
	}
	else {
		node->next = list->head;
		list->head = node;
	}		

	return node;
}

