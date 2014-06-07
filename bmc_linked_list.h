
#ifndef _bmc_ll
#define _bmc_ll

typedef struct bmc_ll_node {
	struct bmc_ll_node *next;
	void *data;
	int size;
} bmc_ll_node;

typedef struct {
	int count;
	bmc_ll_node *head;
	bmc_ll_node *tail;
} bmc_ll;

bmc_ll * bmc_ll_new();
bmc_ll_node * bmc_ll_add(bmc_ll *list, void *data, int size);
bmc_ll_node * bmc_ll_insert(bmc_ll *list, void *data, int size,  int position);
int bmc_ll_find(bmc_ll *list, void *data);
bmc_ll_node * bmc_ll_at(bmc_ll *list, int index);
int bmc_ll_remove(bmc_ll *list, int index);
void bmc_ll_free(bmc_ll *list);

bmc_ll_node * bmc_ll_cycle(bmc_ll *list, int *index);
int bmc_ll_cycle2(bmc_ll *list);

#endif

