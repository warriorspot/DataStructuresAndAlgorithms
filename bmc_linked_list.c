
#include "string.h"
#include "stdlib.h"
#include "bmc_linked_list.h"

bmc_ll_node * add_at_head(bmc_ll *list, void *data, int size); 
bmc_ll_node * add_at_tail(bmc_ll *list, void *data, int size); 
bmc_ll_node * new_node(void *data, int size); 
void free_node(bmc_ll_node *node);

bmc_ll * bmc_ll_new() {
	bmc_ll *list = malloc(sizeof(bmc_ll));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

bmc_ll_node * bmc_ll_add(bmc_ll *list, void *data, int size) {	
	return bmc_ll_insert(list, data, size, list->count);
}

bmc_ll_node * bmc_ll_cycle(bmc_ll *list, int *index) {
	
	bmc_ll_node ** next_array = malloc(sizeof(bmc_ll_node *) * list->count);
	
	bmc_ll_node *ret = NULL;
	int ctr = 0;
	bmc_ll_node *node = list->head;
	while(node != NULL) {
		next_array[ctr] = node;
		
		for(int i = 0; i <= ctr; i++) {
			if(next_array[i] == node->next) {
				ret = node;
				if(index) *index = ctr;
				goto _cycle_exit;
			}		
		}
		node = node->next;
		ctr++;
	}
	
_cycle_exit:
	free(next_array);
	return ret;
}


bmc_ll_node * bmc_ll_insert(bmc_ll *list, void *data, int size, int position) {
	/* Add at tail */
	if(position >= list->count) {
		return add_at_tail(list, data, size);
	}

	/* Add at head */
	if(position <= 0) {
		return add_at_head(list, data, size);
	}

	bmc_ll_node *newNode = new_node(data, size);
	bmc_ll_node *node = list->head;
	for(int i = 0; i < position - 1; i++) {
		node = node->next;	
	}	

	newNode->next = node->next;
	node->next = newNode;

	list->count++;

	return node;
}

bmc_ll_node * bmc_ll_at(bmc_ll *list, int index) {
	bmc_ll_node *node = NULL;

	if(index >= list->count || index < 0) {
		return NULL;
	}

	node = list->head;
	for(int i = 0; i < index; i++) {
		node = node->next;	
	}

	return node;
}

int bmc_ll_find(bmc_ll *list, void *data) {
	int index = 0;
	bmc_ll_node *node = list->head;
	while(node != NULL) {
		if(memcmp(node->data, data, node->size) == 0) {
			return index;	
		}
		node = node->next;
		index++;
	}

	return -1;
}

int bmc_ll_remove(bmc_ll *list, int index) {
	if(index >= list->count || index < 0) {
		return -1;
	}

	bmc_ll_node *node = NULL;
	if(index == 0) {
		node = list->head;
		list->head = node->next;
		free_node(node);
		return 0;
	}

	node = bmc_ll_at(list, index - 1);
	bmc_ll_node *next_node = node->next;
	node->next = next_node->next;
	free_node(next_node);
	list->count--;

	return 0;
}

void bmc_ll_free(bmc_ll *list) {
	if(list->head == NULL) {
		free(list);
		return;
	}

	bmc_ll_node *node = list->head;
	while(node) {
		bmc_ll_node *next = node->next;
		free_node(node);
		node = next;
	}

	free(list);

	return;
}

/* Private functions */

void free_node(bmc_ll_node *node) {
	free(node->data);
	free(node);
}

bmc_ll_node * new_node(void *data, int size) {
	bmc_ll_node *node = malloc(sizeof(bmc_ll_node));
	node->next = NULL;
	node->size = size;
	node->data = malloc(size);
	memset(node->data, '\0', size);
	memcpy(node->data, data, size);

	return node;
}

bmc_ll_node * add_at_head(bmc_ll *list, void *data, int size) {
	bmc_ll_node *node = new_node(data, size);

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

bmc_ll_node * add_at_tail(bmc_ll *list, void *data, int size) {
	bmc_ll_node *newNode = new_node(data, size);
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
