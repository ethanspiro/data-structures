/* CS261- Assignment 6 - hashMap.c*/
/* Name: Ethan Spiro
 * Date: 5/31/14
 * Solution description: Implementation of a hash map
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"


/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	/*write this*/	

	//declare pointers for placeholding
	struct hashLink *nextNode;
    struct hashLink *curNode;

	for(int i = 0; i < ht->tableSize; i++){ //for every table index
		curNode = ht->table[i];	//set curNode to the table index
		while(curNode !=0){ //while not null
			nextNode = curNode->next; //hold the place of the next node
			free(curNode); //free current node
			curNode = nextNode; //update place
		}
		ht->table[i] = 0; //set that index to null
	}
	free(ht->table); //free the whole table
	ht->tableSize = 0; //update size
	ht->count = 0; //update count
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*write this*/

	//preserve the old table temporarily
	struct hashLink **oldTable = ht->table;
	int oldTableSize = ht->tableSize;

	//allocate space for a new table with newTableSize
	ht->table = (hashLink**)malloc(newTableSize*sizeof(hashLink*));
	ht->tableSize = newTableSize;
	ht->count = 0;

	//fill with NULLS first
	int i;
	for (i = 0; i < ht->tableSize; i++) {
		ht->table[i] = NULL;
	}

	//buckets
	for (i = 0; i < oldTableSize; i++) {
		struct hashLink *curNode = oldTable[i];
		struct hashLink *nextNode;

		while (curNode) {
			nextNode = curNode->next;
			insertMap(ht, curNode->key, curNode->value);
			free(curNode);
			curNode = nextNode;
		}	
	} //end of for

	free(oldTable);
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  

	//for capturing the index of the Hash
	int hashingIndex;

	//if the haskLink exists, we want to delete it
	if(containsKey(ht, k)) {
		removeKey(ht, k);
	}
	//now can replace

	//choice of hashing function
	if(HASHING_FUNCTION == 1) {
		hashingIndex = stringHash1(k);
	}
	if(HASHING_FUNCTION == 2) {
		hashingIndex = stringHash2(k);
	}

	//adjust hashing index with mod
	hashingIndex = hashingIndex % ht->tableSize;
	if(hashingIndex < 0) {
		hashingIndex += ht->tableSize;
	}

	//create a new link in the chain
	struct hashLink *newLink = malloc(sizeof(struct hashLink));
	assert(newLink != NULL);
	newLink->key = k;
	newLink->value = v;
	newLink->next = 0;

	//if that index of the table is NUll place the new link there
	if(ht->table[hashingIndex] == NULL) {
		ht->table[hashingIndex] = newLink;
	}
	else {	//else go to the end of the chain and place there
		struct hashLink *cur = ht->table[hashingIndex];
		while(cur->next != NULL) {
			cur = cur->next;
		}
		//attach to the back
		cur->next = newLink;
	}
	//update the count of the table
	ht->count++;

	//monitor the load factor, resize if necessary
	if((tableLoad(ht)) >= LOAD_FACTOR_THRESHOLD) {
		//for debugging purposes
		printf("Table resized...\n");
		_setTableSize(ht, 2*ht->tableSize);
	}

}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	/*write this*/

	//for capturing the index of the Hash
	int hashingIndex;

	//hashing index 1 (for the first hash function)
	if(HASHING_FUNCTION == 1) {
		hashingIndex = stringHash1(k);
	}

	//hashing index 2 (for the second hash function)
	if(HASHING_FUNCTION == 2) {
		hashingIndex = stringHash2(k);
	}

	//adjust hashing index with mod
	hashingIndex = hashingIndex % ht->tableSize;
	if(hashingIndex < 0) {
		hashingIndex += ht->tableSize;
	}

	//create an iterator and set equal to begginning of correct chain
	struct hashLink *cur = ht->table[hashingIndex];

	while(cur != NULL) {
		//compares two keys, returns 0 if they are equal
		while((strcmp(cur->key, k)) != 0) {
			//if not equal, iterate to next link
			cur = cur->next;
		}
		//return the value of the hashlink that represents said key
		return (&(cur->value));
	}
	//else
	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	//for capturing the index of the Hash
	int hashingIndex;

	//hashing index 1 (for the first hash function)
	if(HASHING_FUNCTION == 1) {
		hashingIndex = stringHash1(k);
	}

	//hashing index 2 (for the second hash function)
	if(HASHING_FUNCTION == 2) {
		hashingIndex = stringHash2(k);
	}

	//adjust hashing index with mod
	hashingIndex = hashingIndex % ht->tableSize;
	if(hashingIndex < 0) {
		hashingIndex += ht->tableSize;
	}

	//create an iterator and set equal to begginning of correct chain
	struct hashLink *cur = ht->table[hashingIndex];

	while(cur != NULL) {
		//compares two keys, returns 0 if they are equal
		if((strcmp(cur->key, k)) == 0) {
			return 1;	//yes contains key
		}
		//move along the chain
		cur = cur->next;
	}
	//can't find it
	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	/*write this*/	
	//for capturing the index of the Hash
	int hashingIndex;

	//hashing index 1 (for the first hash function)
	if(HASHING_FUNCTION == 1) {
		hashingIndex = stringHash1(k);
	}
	//hashing index 2 (for the second hash function)
	if(HASHING_FUNCTION == 2) {
		hashingIndex = stringHash2(k);
	}

	//adjust hashing index with mod
	hashingIndex = hashingIndex % ht->tableSize;
	if(hashingIndex < 0) {
		hashingIndex += ht->tableSize;
	}

	//create iterators
	struct hashLink *cur = ht->table[hashingIndex];
	struct hashLink *previous = NULL;

	//if cur is NULL, there is no key for that value so return
	if(cur == NULL) {
		return;
	}

	//search until match or NULL(return)
	while ((strcmp(cur->key, k)) != 0) {
		previous = cur;
		cur = cur->next;
		if(cur == NULL) {
			return;
		}
	}

	//keep chain linked
	if(previous) {
		previous->next = cur->next;
	}
	else {	//no previous set whole thing to NULL
		ht->table[hashingIndex] = 0;
	}

	//remove key by freeing cur hashLink
	free(cur);
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	/*write this*/
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	/*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*write this*/
	//declare an int to store number of empty buckets
	int emptyBuckets = 0;
	
	int i;
	for(i = 0; i < ht->tableSize; i++) {
		if(ht->table[i] == NULL) {
			emptyBuckets++;
		}
	}

	return emptyBuckets;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	return ((double)ht->count / (double)ht->tableSize);
}

void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


