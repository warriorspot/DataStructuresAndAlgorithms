#ifndef BMC_HM_H
#define BMC_HM_H

typedef struct {
	int size; /* The number of buckets in the map */
	void ** buckets;	
	int (*hash)(void *);
} bmc_hm;

bmc_hm * bmc_hm_create(int);
void bmc_hm_set_hash(bmc_hm *, int (*hash)(void *));
int bmc_hm_put(bmc_hm *, void *, void *);
void * bmc_hm_get(bmc_hm *, void *);
int bmc_hm_count(bmc_hm *);

#endif
