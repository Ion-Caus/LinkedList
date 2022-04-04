/**
\file
\brief Implementation of linked list data structure.
\author Ib Havn
\version 1.0.0
 \defgroup linked_list Linked List
 \{
 \brief A simple implementation of a Linked List.
 This is a simple implementation of a linked list that can hold void pointers to.
 \note The functions are NOT thread safe!!!
 \defgroup linked_list_init List Initialization
 \brief How to initialize the linked list.
 \defgroup linked_list_private Private Linked List Functions
 \brief Private functions.
 \defgroup linked_list_function Public Linked List Functions
 \brief Public Linked List functions.
 Here you you will find the functions you will need.
 
 \defgroup linked_list_return List Return codes
 \brief Codes returned from List functions.
 \}
 */
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdint.h>

/**
 \ingroup linked_list_return
 Return codes from linked list functions
 */
typedef enum {
    LINKED_LIST_OK,/**< Operation successful. */
    LINKED_LIST_EMPTY, /**< The list is empty. */
    LINKED_LIST_FULL, /**< The list is full. */
    LINKED_LIST_NOT_FOUND, /**< List item not found */
    LINKED_LIST_FOUND,/**< Item found */
    LINKED_LIST_CALLOC_ERROR,
    LINKED_LIST_NULL
} linkedList_return_codes_t;

// Abstract Data Type (ADT)
typedef struct linkedList_st* linkedList_t;

typedef struct node_st* node_t;

typedef struct linkedList_node* linkedList_iterator_t;

/********************************************//**
 \ingroup linked_list_init
 \brief Create and initialise Linked List.
 Initialize the List structure.
 \return pointer to the list.
 ***********************************************/
linkedList_t linkedList_create(void);


void linkedList_destroy(linkedList_t* self);

/********************************************//**
 \ingroup linked_list_function
 \brief Put an item into the head of the list.
 \return return code
 \retval LIST_OK: item stored in the list
 \retval LINKED_LIST_FULL: list is full (out of heap)
 \param[in] list pointer to list instance to work on.
 \param[in] item pointer to item to store in the list.
 ***********************************************/
linkedList_return_codes_t linkedList_push(linkedList_t list, void *item);

/********************************************//**
 \ingroup linked_list_function
 \brief Get an item from the head of the list.
 \return pointer to item
 \retval NULL: no items in list
 \retval void * to item returned
 \param[in] list pointer to list instance to work on.
 ***********************************************/
void * linkedList_pull(linkedList_t list);

/********************************************//**
 \ingroup linked_list_function
 \brief Peek an item from the list at the given index.
 \note \ref linkedList_peekItemByIndex does not removed the item from the list.
 \return pointer to item
 \retval NULL: no items in the list at given index
 \retval void * to item returned
 \param[in] list pointer to list instance to work on.
 \param[in] index to the peeked item.
 ***********************************************/
void* linkedList_peekItemByIndex(linkedList_t list, uint16_t index);

/********************************************//**
 \ingroup linked_list_function
 \brief Check if a specific item is in the list.
 The list will be checked to see if a given item exists in the list.
 \return Return code
 \retval LIST_FOUND: if item is found in list
 \retval LIST_NOT_FOUND: if item was not in the list
 \param[in] list pointer to list instance to work on.
 \param[in] item pointer to item to check if its in the list.
 ***********************************************/
linkedList_return_codes_t linkedList_containsItem(linkedList_t list, void *item);

/********************************************//**
 \ingroup linked_list_function
 \brief Get number of items in list.
 \return no items in list
 \param[in] list pointer to list instance to work on.
 ***********************************************/
int linkedList_length(linkedList_t list);

/********************************************//**
 \ingroup linked_list_function
 \brief Clear/Empty the list.
 All the list nodes are removed, and added to the free list.
 \param[in] list pointer to list instance to work on.
 ***********************************************/
void linkedList_clear(linkedList_t list);

/********************************************//**
 \ingroup linked_list_function
 \brief Remove an item from the list.
 The item will be removed from the list if it exists in the list.
 \return return code
 \retval LIST_OK: if item is removed from the list
 \retval LIST_NOT_FOUND: The item was not in the list
 \param[in] list pointer to list instance to work on.
 \param[in] item pointer to item to remove from the list.
 ***********************************************/
linkedList_return_codes_t linkedList_removeItem(linkedList_t list, void *item);

/********************************************//**
 \ingroup linked_list_function
 \brief Get an iterator for the list..
 \return iterator
 \retval pointer to iterator if the list is not empty
 \retval NULL: no elements in list
 \param[in] list pointer to list instance to work on.
 ***********************************************/
linkedList_iterator_t linkedList_getIterator(linkedList_t list);

/********************************************//**
 \ingroup linked_list_function
 \brief Return the item that the iterator points at, and increment the iterator.
 \note The item is not removed from the list
 \return pointer to the item the iterator points at
 \retval void * to item
 \retval NULL if the iterator has reach end of list
 \param[in] list pointer to list instance to work on.
 \param[in,out] iterator pointer to the iterator.
 ***********************************************/
void *linkedList_iteratorNext(linkedList_t list, linkedList_iterator_t *iterator);

#endif /* LINKED_LIST_H_ */
