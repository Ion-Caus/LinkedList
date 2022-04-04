//
//  linkedList.c
//  LinkedList
//
//  Created by Ion Caus on 04.04.2022.
//

#include "linkedList.h"

#include <stdlib.h>

typedef struct linkedList_st {
    node_t head;
    int size;
} linkedList_st;

typedef struct node_st {
    void* item;
    node_t next;
} node_st;

linkedList_t linkedList_create() {
    linkedList_t _linkedList = calloc(1, sizeof(linkedList_st));
    
    if (NULL == _linkedList) {
        return NULL;
    }
    
    _linkedList->size = 0;
    
    _linkedList->head = NULL;

    return _linkedList;
}

void linkedList_destroy(linkedList_t* self) {
    if (NULL == *self) return;
    
    node_t curr = (*self)->head;
    node_t next;
    
    while (curr) {
        
        next = curr->next;
        free(curr);
        curr = next;
        
    }
    free(*self);
    *self = NULL;
}

linkedList_return_codes_t linkedList_push(linkedList_t list, void *item) {
    if (NULL == list) {
        return LINKED_LIST_NULL;
    }
    
    node_t _node = calloc(1, sizeof(node_st));
    
    if (NULL == _node) {
        return LINKED_LIST_CALLOC_ERROR;
    }
    
    _node->item = item;
    _node->next = list->head;
    list->head = _node;

    list->size++;
    return LINKED_LIST_OK;
}

void* linkedList_pull(linkedList_t list) {
    if (list == NULL) return NULL;
    if (list->head == NULL) return NULL;
    
    node_t temp = list->head;
    list->head = temp->next;
    list->size--;
    
    void* item = temp->item;
    free(temp);
    
    return item;
}

void* linkedList_peekItemByIndex(linkedList_t list, uint16_t index) {
    if (NULL == list) {
        return NULL;
    }
    
    node_t temp = list->head;
    if (temp == NULL) return NULL;
    
    for (int i = 0; i < index; i++) {
        if (temp->next == NULL) return NULL;
        temp = temp->next;
    }
    return temp->item;
}


linkedList_return_codes_t linkedList_containsItem(linkedList_t list, void *item) {
    if (NULL == list) return LINKED_LIST_NULL;
    
    node_t curr = list->head;
    if (curr == NULL) return LINKED_LIST_EMPTY;
    
    while (curr) {
        if (curr->item == item) {
            return LINKED_LIST_FOUND;
        }
        curr = curr->next;
        
    }
    return LINKED_LIST_NOT_FOUND;
}

int linkedList_length(linkedList_t list) {
    if (NULL == list) {
        return -1;
    }
    return list->size;
}

void linkedList_clear(linkedList_t list) {
    if (list == NULL) return;
    
    node_t curr = list->head;
    node_t next;
    
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
    list->size = 0;
}

linkedList_return_codes_t linkedList_removeItem(linkedList_t list, void *item) {
    if (NULL == list) return LINKED_LIST_NULL;
    if (list->head == NULL) return LINKED_LIST_EMPTY;
    
    node_t curr = list->head;
    node_t prev = NULL;
    while (curr) {
        if (curr->item != item) {
            prev = curr;
            curr = curr->next;
            continue;
        }
            
        if (!prev) {
            list->head = curr->next;
        }
        else {
            prev->next = curr->next;
        }
        free(curr);
        list->size--;
        
        return LINKED_LIST_OK;
    }
    
    return LINKED_LIST_NOT_FOUND;
}
