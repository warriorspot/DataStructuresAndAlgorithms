#include <stdio.h>
#include <stdlib.h>
#include "bmc_hash_map.h"

int int_hash(void *);
int string_hash(void *);

int main(int argc, char **argv)
{
	bmc_hm *map = bmc_hm_create(1000);

	if(!map) 
	{
		fprintf(stderr, "Could not create map!\n");
		return -1;
	}

	bmc_hm_set_hash(map, &string_hash);

	bmc_hm_put(map, (void *)"key1", (void *)"Brennan");
	bmc_hm_put(map, (void *)"key2", (void *)"Emilia");
	bmc_hm_put(map, (void *)"key3", (void *)"Joe");
	bmc_hm_put(map, (void *)"key4", (void *)"Jen");
	
	char *value = (char *)bmc_hm_get(map, "key3");
	
	printf("Value: %s\n", value);

	return 0;
}

int int_hash(void *key) 
{
	return (int) key;
}

int string_hash(void *key) 
{
	int result = 0;

	char *string = (char *) key;
	while(*string != 0) 
	{
		result += (int)*string;
		string++;		
	}	


	return result;
}
