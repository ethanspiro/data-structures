/* CS261- Assignment 3 - cirListDeque.c*/
/* Name: Ethan Spiro
 * Date: 4/24/14
 * Solution description: Implementation of circular linked list deque
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
  	//assert q is not null
  	assert(!EQ(q, 0));

  	//allocate space for the sentinel
  	q->Sentinel = (struct DLink *)malloc(sizeof(struct DLink));
  	//make sure its been allocated
  	assert(!EQ(q->Sentinel, 0));

  	//set next and pre to itself since there is only one Sentinel
  	q->Sentinel->next = q->Sentinel;
  	q->Sentinel->prev = q->Sentinel;

  	//intialize size to 0
  	q->size = 0;
}

/*
 create a new circular list deque
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	//allocate a new link
	struct DLink *temp = (struct DLink*)malloc(sizeof(struct DLink));
	//make sure its been allocated
	assert(!EQ(temp, 0));

	//fill it with value
	temp->value = val;

	//return the link
	return(temp);	 

}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	//assert q is not null
  	assert(!EQ(q, 0));

  	//assert lnk is not null
  	assert(!EQ(lnk, 0));

  	//assert lnk is in the deque
  	assert(!EQ(lnk->next, 0));
  	assert(!EQ(lnk->prev, 0));

  	//allocate a new link with value v
  	struct DLink *newLink = _createLink(v);

  	//update link in front of insertion link to point back to inserted link
  	lnk->next->prev = newLink;
  	//set newLinks next to link in front of it
  	newLink->next = lnk->next;
  	//set link before to point to inserted link
  	lnk->next = newLink;
  	//set the prev from new link to point back to the link you inserted after
  	newLink->prev = lnk;

  	//update the size
  	q->size++;

}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	//make sure q is not null
	assert(!EQ(q, 0));	 

	//add link after the link to the left of the Sentinal accessed by prev
	_addLinkAfter(q, q->Sentinel->prev, val);
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	//make sure q is not null
	assert(!EQ(q, 0));

	//add link to the front of the list by adding it after the sentinel
	_addLinkAfter(q, q->Sentinel, val);	 
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	//make sure q is not null
	assert(!EQ(q, 0));

	//make sure q is not empty
	assert(!isEmptyCirListDeque(q));

	//return the value of the first link
	return (q->Sentinel->next->value);
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null
	assert(!EQ(q, 0));

	//make sure q is not empty
	assert(!isEmptyCirListDeque(q));

	//return the value of the last link
	return (q->Sentinel->prev->value);
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	//make sure q is not null
	assert(!EQ(q, 0));

	//make sure q is not empty
	assert(!isEmptyCirListDeque(q));

	//make sure chain does not break
	lnk->prev->next = lnk->next;
	lnk->next->prev = lnk->prev;

	//free link
	free(lnk);

	//decrement size
	q->size--;
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q)
{
	//make sure q is not null
	assert(!EQ(q, 0));

	//make sure q is not empty
	assert(!isEmptyCirListDeque(q));

	//remove the first link
	_removeLink(q, q->Sentinel->next);

}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
  	//make sure q is not null
	assert(!EQ(q, 0));

	//make sure q is not empty
	assert(!isEmptyCirListDeque(q));	

	//remove the last link
	_removeLink(q, q->Sentinel->prev); 
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	//free every link by just continually removing the top until size = 0
	while(!EQ(q->size, 0)) {
		printf("Deleting link that holds %g...\n", frontCirListDeque(q));
		removeFrontCirListDeque(q);
	}

	//free the sentinel
	free(q->Sentinel);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) 
{
  	//make sure q is not null
  	assert(!EQ(q, 0));

  	//if size is 0 return true, else return false
	if (EQ(q->size, 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null
	assert(!EQ(q, 0));

	//make sure q is not empty
	assert(!isEmptyCirListDeque(q));	

	//new iterator
	struct DLink *i = q->Sentinel->next;

	//while iterator has not reached the end of the linked list
	while(!EQ(i, q->Sentinel)) {
		printf("%g ", i->value);	//print the value
		i = i->next;	//update
	}
	printf("\n"); 
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	//make sure q is not null
	assert(!EQ(q, 0));

	//make sure q is not empty
	assert(!isEmptyCirListDeque(q));

	//declare an iterator
	struct DLink *i = q->Sentinel->next;

	//declare a temp for reversing links in chain
	struct DLink *temp = NULL;

	//reverse the next and prev pointers
	while(!EQ(i, q->Sentinel)) {
		temp = i->prev;
		i->prev = i->next;
		i->next = temp;
		i = i->prev;
	}

	//update sentinal aka change its first and next
	temp = q->Sentinel->next;
	q->Sentinel->next = q->Sentinel->prev;
	q->Sentinel->prev = temp;

}
