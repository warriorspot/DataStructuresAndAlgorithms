
#include "string.h"
#include "stdlib.h"
#include "bmc_linked_list.h"

bmc_linked_list_node * add_at_head(bmc_linked_list *list, void *data, int size); 
bmc_linked_list_node * add_at_tail(bmc_linked_list *list, void *data, int size); 
bmc_linked_list_node * new_node(void *data, int size); 

bmc_linked_list * bmc_linked_list_new() {
	bmc_linked_list *list = malloc(sizeof(bmc_linked_list));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

bmc_linked_list_node * bmc_linked_list_add(bmc_linked_list *list, void *data, int size) {	
	return bmc_linked_list_insert(list, data, size, list->count);
}

bmc_linked_list_node * bmc_linked_list_insert(bmc_linked_list *list, void *data, int size, int position) {

	/* Add at tail */
	if(position >= list->count) {
		return add_at_tail(list, data, size);
	}

	/* Add at head */
	if(position <= 0) {
		return add_at_head(list, data, size);
	}

	bmc_linked_list_node *newNode = new_node(data, size);
	bmc_linked_list_node *node = list->head;
	for(int i = 0; i < position - 1; i++) {
		node = node->next;	
	}	

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

bmc_linked_list_node * new_node(void *data, int size) {
	bmc_linked_list_node *node = malloc(sizeof(bmc_linked_list_node));
	node->next = NULL;
	node->size = size;
	node->data = malloc(size);
	bzero(node->data, size);
	memcpy(node->data, data, size);

	return node;
}

bmc_linked_list_node * add_at_head(bmc_linked_list *list, void *data, int size) {
	bmc_linked_list_node *node = new_node(data, size);

	if(list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else {
		node->next = list->head;
		list->head = node;
	}		

	return node;
}

bmc_linked_list_node * add_at_tail(bmc_linked_list *list, void *data, int size) {
	bmc_linked_list_node *newNode = new_node(data, size);
	if(list->tail == NULL) {
		list->tail = newNode;
		list->head = newNode;
	}
	else {
		list->tail->next = newNode;
		list->tail = newNode;
	}

	return newNode;
}
