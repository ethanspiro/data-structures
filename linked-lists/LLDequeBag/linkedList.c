/* CS261- Assignment 3 - linkedList.c*/
/* Name: Ethan Spiro
 * Date: 4/24/14
 * Solution description: Implementation of linked list deque and bag
 */

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {

	//assert lst is not null
	assert (!EQ(lst, 0));

	//create a front sentinel node
	lst->firstLink = (struct DLink *)malloc(sizeof(struct DLink));
	assert(lst->firstLink != 0);

	//create a back sentinel node
	lst->lastLink = (struct DLink *)malloc(sizeof(struct DLink));
	assert(lst->lastLink != 0);

	//set front sentinel next to back sentinel
	lst->firstLink->next = lst->lastLink;

	//set back sentinal previous to front sentinel
	lst->lastLink->prev = lst->firstLink;

	//initialize size to 0
	lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{	
	struct linkedList *newList = (struct linkedList *)malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	//assert lst and l are not null
	assert (!EQ(lst, 0));
	assert (!EQ(l, 0));

	//allocate a new node
	struct DLink *newLink = (struct DLink *)malloc(sizeof(struct DLink));
	assert(!EQ(newLink, 0));

	//fill its value with parameter v
	newLink->value = v;

	//set the new links previous to the provided before link's previous
	newLink->prev = l->prev;

	//set the new links next to point to the provided before link
	newLink->next = l;

	//update the node before the inserted link to point to the new link
	l->prev->next = newLink;

	//set prev of provided before link to now point towards the new link (point back)
	l->prev = newLink;

	//update the size
	lst->size++;

}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//adds to front of the list by pointing to the link to the left of the front sentinel
	_addLinkBefore(lst, lst->firstLink->next, e);
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) 
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//adds to the back of list by adding a link right before the back sentinel
	_addLinkBefore(lst, lst->lastLink, e);
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) 
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//make sure the list is not empty
	assert(!isEmptyList(lst));

	return(lst->firstLink->next->value);
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//make sure the list is not empty
	assert(!isEmptyList(lst));

	//return value of link left to the last link
	return (lst->lastLink->prev->value);
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//assert l is not null
	assert (!EQ(l, 0));

	//make sure the link behind next points to the correct link
	l->prev->next = l->next;

	//make sure the link before prev points to the correct link
	l->next->prev = l->prev;

	//now that its "unchained"
	free(l);

	//update the size
	lst->size--;	
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) 
{
	//assert lst is not null
	assert (!EQ(lst, 0));

   	//make sure list isnt empty
   	assert(!isEmptyList(lst));

   	//remove the link to the right of front sentinel
	_removeLink(lst, lst->firstLink->next);
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{	

	//assert lst is not null
	assert (!EQ(lst, 0));

	//make sure list isnt empty
	assert(!isEmptyList(lst));

	//remove the last link by removing the link prev of back sentinel
	_removeLink(lst, lst->lastLink->prev);	
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) 
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//if 0 elements are in the list we know its empty (also fs == bs)
	return(lst->size = 0);
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	struct DLink *currentLink;

	currentLink = lst->firstLink->next;

	while(!EQ(currentLink, lst->lastLink)) {
		printf("%d ", currentLink->value);
		currentLink = currentLink->next;
	}

}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//since its a bag just use add before and use the front sentinel
	_addLinkBefore(lst, lst->firstLink->next, v);

}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) 
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	//create a pointer called currentLink for iterating
	struct DLink *currentLink;

	//make sure list isent empty
	assert(!isEmptyList(lst));

	//initialize to the first link in chain
	currentLink = lst->firstLink->next;

	//while the current link hasn't reached the end of the lniked list
	while(!EQ(currentLink, lst->lastLink)) {
		//check if the vaue of that link is the value we are searching for
		if(EQ(currentLink->value, e)) {
			//if it is return true
			return(1);
		}
		//update the currentLink for looping to point to next link
		currentLink = currentLink->next;
	}
	//else return false if you can't find a match
	return(0);
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) 
{
	//assert lst is not null
	assert (!EQ(lst, 0));

	struct DLink *currentLink;
	assert(!isEmptyList(lst));

	//initialize to first link in the chain
	currentLink = lst->firstLink->next;

	//while we have not reached the end of the linked list
	while(!EQ(currentLink, lst->lastLink)) {
		//if you have found the value you want to remove
		if(EQ(currentLink->value, e)) {
			//remove the link
			_removeLink(lst, currentLink);
			//break the loop so we only remove one instance of it
			break;	
		}
		//update currentLink for looping to next link
		currentLink = currentLink->next;
	}
}