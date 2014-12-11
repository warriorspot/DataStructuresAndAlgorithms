#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bmc_hash_map.h"


int hash(void *);
int get_bucket(bmc_hm *, void *);

bmc_hm * bmc_hm_create(int bucket_count) 
{
	bmc_hm *map = NULL;

	map = malloc(sizeof(bmc_hm));
	if(map == NULL) 
	{
		return NULL;
	}
	
	map->buckets = malloc(sizeof(void *) * bucket_count);	
	if(map->buckets == NULL) 
	{
		free(map);
		return NULL;
	}
	memset(map->buckets, (int)NULL, bucket_count);
	
	map->hash = &hash;
	map->size = bucket_count;
		
	return map;	
}

void bmc_hm_free(bmc_hm *map) 
{
	free(map->buckets);	
	free(map);
}

void bmc_hm_set_hash(bmc_hm *map, int (*hash)(void *)) 
{
	map->hash = hash;	
}

int bmc_hm_put(bmc_hm *map, void *key, void *value) 
{
	int result = 0;
	int bucket = get_bucket(map, key);
	map->buckets[bucket] = value;

	return result;
}

void * bmc_hm_get(bmc_hm *map, void *key) 
{
	int bucket = get_bucket(map, key);
	return map->buckets[bucket];
}

int bmc_hm_count(bmc_hm *map) 
{
	return 0;
}

/* Private functions */

int get_bucket(bmc_hm *map, void *key)
{
	int hash = map->hash(key);
	int bucket = hash % map->size;

	return bucket;
}

int hash(void *key) 
{
	return (int) key;
}

