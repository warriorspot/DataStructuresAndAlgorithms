
#include "string.h"
#include "stdlib.h"
#include "bmc_linked_list.h"

bmc_linked_list_node * add_at_head(bmc_linked_list *list, void *data, int size); 
bmc_linked_list_node * add_at_tail(bmc_linked_list *list, void *data, int size); 
bmc_linked_list_node * new_node(void *data, int size); 
void free_node(bmc_linked_list_node *node);

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

	newNode->next = node->next;
	node->next = newNode;

	list->count++;

	return node;
}

bmc_linked_list_node * bmc_linked_list_at(bmc_linked_list *list, int index) {
	bmc_linked_list_node *node = NULL;

	if(index >= list->count || index < 0) {
		return NULL;
	}

	node = list->head;
	for(int i = 0; i < index; i++) {
		node = node->next;	
	}

	return node;
}

int bmc_linked_list_find(bmc_linked_list *list, void *data) {
	int index = 0;
	bmc_linked_list_node *node = list->head;
	while(node != NULL) {
		if(memcmp(node->data, data, node->size) == 0) {
			return index;	
		}
		node = node->next;
		index++;
	}

	return -1;
}

int bmc_linked_list_remove(bmc_linked_list *list, int index) {
	if(index >= list->count || index < 0) {
		return -1;
	}

	bmc_linked_list_node *node = NULL;
	if(index == 0) {
		node = list->head;
		list->head = node->next;
		free_node(node);
		return 0;
	}

	node = bmc_linked_list_at(list, index - 1);
	bmc_linked_list_node *next_node = node->next;
	node->next = next_node->next;
	free_node(next_node);
	list->count--;

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
		free_node(node);
		node = next;
	}

	free(list);

	return;
}

/* Private functions */

void free_node(bmc_linked_list_node *node) {
	free(node->data);
	free(node);
}

bmc_linked_list_node * new_node(void *data, int size) {
	bmc_linked_list_node *node = malloc(sizeof(bmc_linked_list_node));
	node->next = NULL;
	node->size = size;
	node->data = malloc(size);
	memset(node->data, '\0', size);
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

	list->count++;
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

	list->count++;
	return newNode;
}
